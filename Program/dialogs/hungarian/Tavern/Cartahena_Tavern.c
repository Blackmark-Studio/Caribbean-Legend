// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("A "+ GetCityName(npchar.city) +" összes pletykája az Ön rendelkezésére áll. Mit szeretnél megtudni?",
                          "Éppen errôl beszéltünk. Biztos elfelejtette...", "Most már harmadszor zaklatsz...",
                          "Ismétled ugyanazt, mint egy papagáj...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudod, " + NPChar.name + ", talán legközelebb.", "Rendben, valamiért elfelejtettem...",
                      "Igen, ez tényleg a harmadik alkalom...", "Igen...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && !CheckAttribute(npchar, "quest.gonsales"))
			{
				link.l1 = "Enrique Gonzales-t keresem. Meg tudnád mondani, hogyan találom meg?";
				link.l1.go = "saga";				
			}
		break;
			
		case "saga":
			dialog.text = "Mindenki ismeri Senor Gonzales-t! A háza a kikötôi hatóság mellett van.";
			link.l1 = "Hány éves?";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "Nos, nem tudom biztosan, de legalább ötven évesnek tûnik. Már jó ideje abban a házban lakik. Szeret mindenféle kalózokról szóló meséket mesélni, amelyekkel valószínûleg csak álmában találkozott.";
			link.l1 = "Úgy tûnik, ô az ember, akire szükségem van. Köszönöm, "+npchar.name+", nagy segítség voltál!";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			DialogExit();
			npchar.quest.gonsales = "true";
			pchar.questTemp.Saga.Gonsales = "true";
			pchar.quest.Saga_Gonsales1.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales1.win_condition.l1.location = "Cartahena_houseF2";
			pchar.quest.Saga_Gonsales1.function = "Saga_CreateGonsalesA";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
