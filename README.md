## Bol.com TruClient Script - Assignment Submission

This LoadRunner TruClient-Web (Chromium, 2025.1) script automates searching for "warehouse" on `bol.com`, retrieving article counts, and clicking the top and a random result. It includes a C function to generate a random index, demonstrating TruClient-C interaction.

### Steps and Assignment Mapping

1. **Step 16: Navigate to Bol.com Homepage**  
   - **Assignment Step**: 1 (Navigate to `bol.com`).  
   - Navigates to `https://www.bol.com/`.

2. **Step 18: Wait for Search Textbox**  
   - **Assignment Step**: 2 (Wait for search interface).  
   - Waits for the search textbox to load.

3. **Step 19: Accept All Cookies**  
   - **Assignment Step**: 2 (Handle initial page setup).  
   - Clicks "Alles accepteren" to bypass cookies popup.

4. **Step 21: Search for Warehouse**  
   - **Assignment Step**: 2 (Search for a term).  
   - Searches for "warehouse" via a JavaScript function.

5. **Step 22: Wait until Wait for Top Result exists**  
   - **Assignment Step**: 2 (Wait for results).  
   - Waits for the top result to appear. This step is marked as optional to prevent script failure when no results are found (e.g., with search term `@!?`), allowing the script to proceed to handle the no-articles scenario.

6. **Step 25: Retrieve Total Number of Articles**  
   - **Assignment Step**: 3 (Store number of articles).  
   - Uses JavaScript to query the DOM for the article count (e.g., "4,224 resultaten") with `document.evaluate`. Sets `window.numberOfArticles` to 0 if the element isn’t found or if "Geen zoekresultaat" is present, handling no-articles cases.

7. **Step 26: Set Global Number of Articles**  
   - **Assignment Step**: 4 (Turn into JavaScript variable).  
   - Sets `window.numberOfArticlesGlobal` to the value of `window.numberOfArticles` and saves to `numArticles` parameter.

8. **Step 27: Check for No Articles**  
   - **Assignment Step**: 5 (Check for articles).  
   - Sets `window.noArticlesFound` based on `window.numberOfArticles`.

9. **Step 28: If Articles Found**  
   - **Assignment Step**: 6, 8 (Process results and use C function).  
   - Executes if `window.noArticlesFound === false`.

   - **Step 28.1: Click on Click on Top Result link**  
     - **Assignment Step**: 5 (Click top result).  
     - Clicks the top search result.

   - **Step 28.2: Wait until Wait for Product Page to Load (Random Result) exists**  
     - **Assignment Step**: 5 (Wait for page load).  
     - Waits for the top result’s product page.

   - **Step 28.3: Evaluate JavaScript code window.history.back()**  
     - **Assignment Step**: 6 (Return to results).  
     - Executes `window.history.back()`.

   - **Step 28.4: Wait until Wait for Results Page link exists**  
     - **Assignment Step**: 6 (Wait for results page).  
     - Waits for the results page to reload.

   - **Step 28.5: Evaluate JavaScript code**  
     - **Assignment Step**: 6 (Prepare random selection).  
     - Sets `articleCount` to the number of articles on the current page (e.g., 24).

   - **Step 28.6: Evaluate C function getRandomArticleIndex**  
     - **Assignment Step**: 8 (Call C function).  
     - Calls `getRandomArticleIndex` to generate a random index.

   - **Step 28.7: Evaluate JavaScript code**  
     - **Assignment Step**: 6 (Click random result).  
     - Clicks the article at the random index.

   - **Step 28.8: Wait until Wait for Product Page to Load (Random Result) exists**  
     - **Assignment Step**: 6 (Wait for page load).  
     - Waits for the random result’s product page.

   - **Else**:  
     - **Assignment Step**: 7 (Handle no articles).  
     - Logs "No articles found for the search term" if no articles are found.

### C Function: `getRandomArticleIndex`

- **Purpose**: Generates a random index (0 to `articleCount-1`) for Step 6, fulfilling Step 8.
- **Location**:  
  - **Declared in**: `globals.h` (`int getRandomArticleIndex(void);`).  
  - **Defined in**: `C-functions.c`.
- **Implementation**:  
  ```c
  int getRandomArticleIndex(void) {
    const char* countStr;
    int count;
    int randomIndex;
    char result[10];

    // Get article count from parameter
    countStr = lr_eval_string("{articleCount}");
    count = atoi(countStr);

    if (count <= 0) {
        lr_error_message("Invalid article count: %s", countStr);
        return -1;
    }

    // Seed random and generate index
    srand((unsigned int)time(NULL));
    randomIndex = rand() % count;

    // Convert to string and save to LR param
    sprintf(result, "%d", randomIndex);
    lr_save_string(result, "randomIndex");

    lr_output_message("Random article index (from C): %s", result);
    return randomIndex;}
  ```
- **Called From**: Step 28.6 ("Evaluate C" step), using `articleCount` and saving to `randomIndex`.

### Testing

- **"warehouse"**: Retrieves articles, clicks top and random results.
- **"@!?"**: Step 22 fails but continues (as it’s optional), sets `window.numberOfArticles` to 0, and logs "No articles found for the search term" in the Else block.

### Potential Improvements (If More Time Were Available)

If I had more time, I would make the following improvements to enhance the script’s robustness and usability:

- **Replace Step 22 with a Dynamic Check**: Instead of making Step 22 optional, I’d replace it with an "Evaluate JavaScript" step to check for the top result or "Geen zoekresultaat" message, setting a flag like `window.resultsFound`. This would avoid any failure while providing better control over the script flow.
- **Parameterize the Search Term**: Use a LoadRunner parameter for the search term (e.g., `SearchTerm`) to easily test different inputs like "warehouse" or "@!?" without modifying the script.
- **Enhance Error Handling**: Add more checks for DOM elements in JavaScript steps (e.g., Step 28.5, Step 28.7) to handle cases where elements might be missing or the page structure changes.
- **Add Wait Steps**: Insert additional wait steps (e.g., after Step 21 and Step 28.3) to improve stability, ensuring pages are fully loaded before proceeding.


### Files

- `Action.c`, `vuser_init.c`, `vuser_end.c`: Script files.
- `globals.h`: C function declaration.
- `C-functions.c`: C function definition.
- `SearchFunctions.js`: Search function.

