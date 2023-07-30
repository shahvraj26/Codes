import java.util.Comparator;

import components.map.Map;
import components.map.Map.Pair;
import components.map.Map1L;
import components.set.Set;
import components.set.Set1L;
import components.simplereader.SimpleReader;
import components.simplereader.SimpleReader1L;
import components.simplewriter.SimpleWriter;
import components.simplewriter.SimpleWriter1L;
import components.sortingmachine.SortingMachine;
import components.sortingmachine.SortingMachine2;
import components.utilities.Reporter;

/**
 * Program to generate a tag cloud based on the frequency of each word
 *
 * @author Isaac Miller, Vraj Shah, & Rahul Nalam
 */
public final class TagCloudGenerator {

    /**
     * Compare keys of map in alphabetical order
     *
     */
    private static class Alphabetical
            implements Comparator<Map.Pair<String, Integer>> {
        @Override
        public int compare(Map.Pair<String, Integer> o1,
                Map.Pair<String, Integer> o2) {

            String str1 = o1.key();
            String str2 = o2.key();

            return str1.compareToIgnoreCase(str2);
        }
    }

    /**
     * Compare values of map in decreasing order
     */
    private static class Numerical
            implements Comparator<Map.Pair<String, Integer>> {
        @Override
        public int compare(Map.Pair<String, Integer> o1,
                Map.Pair<String, Integer> o2) {

            Integer int1 = o1.value();
            Integer int2 = o2.value();
            return int2.compareTo(int1);
        }
    }

    private static final String SEPARATORS = "'., ()-_?\"/!@#$%^&*\t1234567890:"
            + ";[]{}+=~`><";

    /**
     * Private constructor so this utility class cannot be instantiated.
     */
    private TagCloudGenerator() {
    }

    /**
     * Generates and creates an index HTML file using tags and
     * {@code out.content}
     *
     * @param out
     *            {@code out.content} allows the program to add into the index
     *            file
     * @param file
     *            name of the data file.
     * @param words
     *            Allows user to input a set amount of total words to be
     *            generated
     * @updates {@code out.content}
     *
     * @ensures <pre>
     * {@code out.content = #out.content * [the HTML tags]}
     * </pre>
     */
    private static void outputHeader(SimpleWriter out, String file, int words) {
        assert out != null : "Violation of: Output file is null";

        out.println("<html>");
        out.println("<head>");
        out.println("<title>Top " + words + " words in " + file + "</title>");
        out.println(
                "<link href=\"http://web.cse.ohio-state.edu/software/2231/web-sw2/assignments/projects/tag-cloud-generator/data/tagcloud.css\"  rel=\"stylesheet\" type=\"text/css\">");
        out.println(
                "<link href=\"doc/tagcloud.css\" rel=\"stylesheet\" type=\"text/css\">");
        out.println("</head>");
        out.println("<body>");
        out.println("<h2>Top " + words + " words in " + file + "</h2>");
        out.println("<hr>");
        out.println("<div class = \"cdiv\">");
        out.println("<p class = \"cbox\">");
    }

    /**
     * Returns the first "word" (maximal length string of characters not in
     * {@code separators}) or "separator string" (maximal length string of
     * characters in {@code separators}) in the given {@code text} starting at
     * the given {@code position}.
     *
     * @param text
     *            the {@code String} from which to get the word or separator
     *            string
     * @param position
     *            the starting index
     * @param separators
     *            the {@code Set} of separator characters
     * @return the first word or separator string found in {@code text} starting
     *         at index {@code position}
     * @requires <pre>
     * {@code 0 <= position < |text|}
     * </pre>
     * @ensures <pre>
     * {@code nextWordOrSeparator =
     *   text[ position .. position + |nextWordOrSeparator| )  and
     * if elements(text[ position .. position + 1 )) intersection separators = {}
     * then
     *   elements(nextWordOrSeparator) intersection separators = {}  and
     *   (position + |nextWordOrSeparator| = |text|  or
     *    elements(text[ position .. position + |nextWordOrSeparator| + 1 ))
     *      intersection separators /= {})
     * else
     *   elements(nextWordOrSeparator) is subset of separators  and
     *   (position + |nextWordOrSeparator| = |text|  or
     *    elements(text[ position .. position + |nextWordOrSeparator| + 1 ))
     *      is not subset of separators)}
     * </pre>
     */
    private static String nextWordOrSeparator(String text, int position,
            Set<Character> separators) {
        assert text != null : "Violation of: text is not null";
        assert separators != null : "Violation of: separators is not null";
        assert 0 <= position : "Violation of: 0 <= position";
        assert position < text.length() : "Violation of: position < |text|";

        boolean isSeparator = separators.contains(text.charAt(position));

        int nextPos = position + 1;
        while (nextPos < text.length()
                && (separators.contains(text.charAt(nextPos)) == isSeparator)) {

            nextPos++;

        }
        return text.substring(position, nextPos);
    }

    /**
     * Generates the set of characters in the given {@code String} into the
     * given {@code Set}.
     *
     * @param str
     *            the given {@code String}
     * @return the set of characters from generateElements
     *
     */
    private static Set<Character> generateElements(String str) {
        assert str != null : "Violation of: str is not null";

        Set<Character> strSet = new Set1L<Character>();

        int count = 0;
        while (count < str.length()) {
            if (!strSet.contains(str.charAt(count))) {
                strSet.add(str.charAt(count));
            }
            count++;
        }
        return strSet;
    }

    /**
     * Reads the words in the {@code map} while seperating each value with
     * {@code Set}
     *
     * @param mapCount
     *            {@code map} reads the value and the key based on if there is a
     *            seperator or not
     * @param seperators
     *            {@code set} reads the different seperators
     * @param in
     *            SimpleReader In reads the values in the {@code map}
     *
     */
    private static void readMapValues(Map<String, Integer> mapCount,
            Set<Character> seperators, SimpleReader in) {

        assert seperators
                .size() != 0 : "Violation of: seperator size is not zero";

        mapCount.clear();
        while (!in.atEOS()) {
            String l = in.nextLine().toLowerCase();
            int pos = 0;
            while (pos < l.length()) {
                String words = nextWordOrSeparator(l, pos, seperators);
                if (!seperators.contains(words.charAt(0))) {
                    if (!mapCount.hasKey(words)) {
                        mapCount.add(words, 1);
                    } else {
                        int newC = mapCount.value(words) + 1;
                        mapCount.remove(words);
                        mapCount.add(words, newC);
                    }
                }

                pos += words.length();
            }
        }

    }

    /**
     * Creates font sizes based on the css file
     *
     * @param max
     *            The given max value from outputTheWords method
     * @param min
     *            The given min value from outputTheWords method
     * @param num
     *            Allows user to input a set amount of total words to be
     *            generated
     *
     * @return the font number based on the arithmetics
     */
    private static String createFonts(int max, int min, int num) {
        assert max > min : "Violation of: max is larger than min";
        assert num > 0 : "Violation of : num is greater than zero";

        int maxFont = 48;
        int minFont = 11;

        int font = maxFont - minFont;
        font *= (num - min);
        font /= (max - min);
        font += minFont;

        return "f" + font;
    }

    /**
     * Outputs the top words into the following {@code map}, and extracts it
     * into {@code out.content}
     *
     * @param out
     *            {@code out.content} allows the program to add into the index
     *            file
     * @param words
     *            Allows user to input a set amount of total words to be
     *            generated
     * @param countWords
     *            Takes the {@code map} and allows it to add the top words
     */
    private static void outputTheWords(SimpleWriter out, int words,
            Map<String, Integer> countWords) {
        assert words > 0 : "Violation of: words is positive";

        Comparator<Pair<String, Integer>> orderCount = new Numerical();
        SortingMachine<Map.Pair<String, Integer>> sortCount;
        sortCount = new SortingMachine2<Map.Pair<String, Integer>>(orderCount);

        while (countWords.size() > 0) {
            sortCount.add(countWords.removeAny());
        }
        sortCount.changeToExtractionMode();

        Comparator<Pair<String, Integer>> orderLetter = new Alphabetical();
        SortingMachine<Map.Pair<String, Integer>> sortLetter;
        sortLetter = new SortingMachine2<Map.Pair<String, Integer>>(
                orderLetter);

        int max = 0;
        if (sortCount.size() > 0) {
            Map.Pair<String, Integer> maxPair = sortCount.removeFirst();
            max = maxPair.value();
            sortLetter.add(maxPair);
        }

        int highCount = 0;
        while (highCount < words && sortCount.size() > 1) {
            Map.Pair<String, Integer> countWord = sortCount.removeFirst();
            sortLetter.add(countWord);
            highCount++;
        }

        int min = 0;
        if (sortCount.size() > 0) {
            Map.Pair<String, Integer> minPair = sortCount.removeFirst();
            min = minPair.value();
            sortLetter.add(minPair);
        }
        sortLetter.changeToExtractionMode();

        while (sortLetter.size() > 0) {
            Map.Pair<String, Integer> countWord = sortLetter.removeFirst();
            String fontSize = createFonts(max, min, countWord.value());
            String tags = "<span style=\"cursor:default\" class=\"" + fontSize
                    + "\" title=\"count: " + countWord.value() + "\">"
                    + countWord.key() + "</span>";
            out.println(tags);
        }
    }

    /**
     * Outputs the cloud for the {@code Map} into the index html file
     *
     * @param out
     *            SimpleWriter Out adds to the index file
     * @param in
     *            SimpleReader In reads the values in the {@code map}
     * @param num
     *            The number inputted by the user
     */
    private static void outputCloud(SimpleWriter out, SimpleReader in,
            int num) {
        assert num > 0 : "Violation of : num is greater than zero";

        Map<String, Integer> mapCount = new Map1L<String, Integer>();

        readMapValues(mapCount, generateElements(SEPARATORS), in);
        outputTheWords(out, num, mapCount);

    }

    /**
     * Adds end values to created index files from {@code out.content}
     *
     * @param out
     *            The SimpleWriter to input to text file
     * @updates {@code out.content}
     *
     * @ensures <pre>
     * {@code out.content = #out.content * [the HTML tags]}
     * </pre>
     */
    private static void outputFooter(SimpleWriter out) {

        out.println("</p>");
        out.println("</div>");
        out.println("</body>");
        out.println("</html>");
    }

    /**
     * Main method.
     *
     * @param args
     *            the command line arguments; unused here
     */
    public static void main(String[] args) {
        SimpleWriter out = new SimpleWriter1L();
        SimpleReader in = new SimpleReader1L();

        out.print("Enter input file name: ");
        String inputName = in.nextLine();

        out.print("Enter an output file name: ");
        String outputName = in.nextLine();
        Reporter.assertElseFatalError(!inputName.equals(outputName),
                "Output file cannot be the same as input file");

        out.print("Number of words to generate: ");
        int numWords = in.nextInteger();

        Reporter.assertElseFatalError(numWords > 0,
                "Number of words must be positive");

        SimpleWriter fOut = new SimpleWriter1L(outputName);

        outputHeader(fOut, inputName, numWords);

        SimpleReader fIn = new SimpleReader1L(inputName);

        outputCloud(fOut, fIn, numWords);
        outputFooter(fOut);

        fIn.close();
        fOut.close();
        out.close();
        in.close();

    }

}
