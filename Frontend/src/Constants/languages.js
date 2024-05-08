export const LANGUAGE_VERSIONS = {
  cpp: "1.0.0",
  javascript: "18.15.0",
  typescript: "5.0.3",
  python: "3.10.0",
  java: "15.0.2",
  csharp: "6.12.0",
};

export const CODE_SNIPPETS = {
  cpp: `\nprocedure main (void)\n{\n\tint n;\n\tint sum;\n\n\tn = 2;\n\tsum = 0;\n\tif (n >= 1)\n\t{\n\t\tsum = n * (n + 1) * (2 * n + 1) / 6;\n\t}\n\tprintf("Sum is: %d", sum);\n\treturn sum;\n}\n`,
  javascript: `\nfunction greet(name) {\n\tconsole.log("Hello, " + name + "!");\n}\n\ngreet("Seawolf in JS!");\n`,
  typescript: `\ntype Params = {\n\tname: string;\n}\n\nfunction greet(data: Params) {\n\tconsole.log("Hello, " + data.name + "!");\n}\n\ngreet({ name: "Hello Seawolf in Typescript!" });\n`,
  python: `\ndef greet(name):\n\tprint("Hello, " + name + "!")\n\ngreet("Hello Seawolf in Python!")\n`,
  java: `\npublic class HelloWorld {\n\tpublic static void main(String[] args) {\n\t\tSystem.out.println("Hello Seawolf in Java!");\n\t}\n}\n`,
  csharp:
    'using System;\n\nnamespace HelloWorld\n{\n\tclass Hello { \n\t\tstatic void Main(string[] args) {\n\t\t\tConsole.WriteLine("Hello Seawolf in C#!");\n\t\t}\n\t}\n}\n',
};
