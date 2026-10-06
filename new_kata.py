import argparse
import os
import sys
import urllib.request
import json

API_URL = "https://www.codewars.com/api/v1/code-challenges/"

LANG_MAP = {
    "c++": {"api_name": "cpp", "folder": "cxx", "ext": ".cpp"},
    "c":   {"api_name": "c",   "folder": "c", "ext": ".c"},
}

# Parse command line arguments
parser = argparse.ArgumentParser(description="Create a new kata folder from Codewars API")
parser.add_argument("kata_id", help="Codewars kata ID")
parser.add_argument("-l", "--language", choices=["c++", "c"], default="c++", help="Language (default: c++)")
args = parser.parse_args()

# Get the language for this kata
lang = LANG_MAP[args.language]

# Check if the kata contains a version to the requested language
kata_url = API_URL + args.kata_id
try:
    with urllib.request.urlopen(kata_url) as response:
        data = json.loads(response.read())
except urllib.error.HTTPError as e:
    print(f"Error: API returned {e.code} for kata '{args.kata_id}'")
    sys.exit(1)

if lang["api_name"] not in data.get("languages", []):
    print(f"Error: kata '{data.get('slug', args.kata_id)}' does not support {args.language}")
    sys.exit(1)

# Create the kata folder
slug = data["slug"].replace("-", "_")
base_dir = os.path.dirname(os.path.abspath(__file__))
kata_dir = os.path.join(base_dir, "katas", lang["folder"], slug)

os.makedirs(kata_dir, exist_ok=True)

# Write the instructions
instructions_path = os.path.join(kata_dir, "instructions.md")
with open(instructions_path, "w", encoding="utf-8") as f:
    f.write(data.get("description", ""))

# Write the CMake configuration
cmake_path = os.path.join(kata_dir, "CMakeLists.txt")
with open(cmake_path, "w", encoding="utf-8") as f:
    f.write(
        "cmake_minimum_required(VERSION 3.20)\n"
        f"project({slug})\n"
        f"add_executable({slug} main{lang['ext']})\n"
    )

# Write the main source file
source_path = os.path.join(kata_dir, "main" + lang["ext"])
with open(source_path, "w", encoding="utf-8") as f:
    f.write("// Kata: " + data["name"] + "\n\n")
    if args.language == "c++":
        f.write(
            "#include <gtest/gtest.h>\n\n"
            f"TEST(Codewars, {slug})\n"
            "{\n"
            "    EXPECT_TRUE(true);\n"
            "}\n"
        )
    else:
        f.write(
            "#include <unity.h>\n\n"
            "void setUp(void) {}\n"
            "void tearDown(void) {}\n\n"
            f"void test_{slug}(void)\n"
            "{\n"
            "    TEST_ASSERT_TRUE(1);\n"
            "}\n\n"
            "int main(void)\n"
            "{\n"
            "    UNITY_BEGIN();\n"
            f"    RUN_TEST(test_{slug});\n"
            "    return UNITY_END();\n"
            "}\n"
        )

print(f"Created: {kata_dir}")
