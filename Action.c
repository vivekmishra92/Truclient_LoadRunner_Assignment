//   *****************************************************************************************************************************************
//   ****   PLEASE NOTE: This is a READ-ONLY representation of the actual script. For editing please press the "Develop Script" button.   ****
//   *****************************************************************************************************************************************

Action()
{
	truclient_step("16", "Navigate to 'https://www.bol.com/'", "snapshot=Action_16.inf");
	truclient_step("18", "Wait until Waar ben je naar op zoek? textbox exists", "snapshot=Action_18.inf");
	truclient_step("19", "Click on Alles accepteren button", "snapshot=Action_19.inf");
	truclient_step("21", "Call Function SearchFunctions.searchForWarehouse", "snapshot=Action_21.inf");
	truclient_step("22", "Wait until Wait for Top Result exists", "snapshot=Action_22.inf");
	truclient_step("25", "Evaluate JavaScript code (function() {  // Loo...CA.done(); })();", "snapshot=Action_25.inf");
	truclient_step("26", "Evaluate JavaScript code (function() {  // Set...);  }); })();", "snapshot=Action_26.inf");
	truclient_step("27", "Evaluate JavaScript code (function() {  TCA.lo...ound  } })();", "snapshot=Action_27.inf");
	truclient_step("28", "If ( window.noArticlesFound === false )", "snapshot=Action_28.inf");
	{
		truclient_step("28.1", "Click on Click on Top Result link", "snapshot=Action_28.1.inf");
		truclient_step("28.2", "Wait until Wait for Product Page to... (Random Result) exists", "snapshot=Action_28.2.inf");
		truclient_step("28.3", "Evaluate JavaScript code window.history.back()", "snapshot=Action_28.3.inf");
		truclient_step("28.4", "Wait until Wait for Results Page link exists", "snapshot=Action_28.4.inf");
		truclient_step("28.5", "Evaluate JavaScript code (function() {  // Sel...se);  } })();", "snapshot=Action_28.5.inf");
		truclient_step("28.6", "Evaluate C function getRandomArticleIndex", "snapshot=Action_28.6.inf");
		truclient_step("28.7", "Evaluate JavaScript code (async function() {  ...e');  } })();", "snapshot=Action_28.7.inf");
		truclient_step("28.8", "Wait until Wait for Product Page to... (Random Result) exists", "snapshot=Action_28.8.inf");
	}

	return 0;
}
