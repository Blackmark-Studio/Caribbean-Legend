// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz? Pytaj śmiało.","Słucham cię, o co chodzi?"),"To już drugi raz, gdy próbujesz zapytać...","To już trzeci raz, kiedy znów próbujesz zapytać...","Kiedy to się skończy?! Jestem zajętym człowiekiem, pracującym nad sprawami kolonii, a ty wciąż próbujesz o coś pytać!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie teraz. Złe miejsce i czas."),"Prawda... Ale później, nie teraz...","Zapytałbym... Ale trochę później...","Przykro mi, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "saga" && !CheckAttribute(npchar, "quest.saga"))
			{
				link.l1 = "Chcę zobaczyć Chevaliera de Poincy. Chodzi o dług moich braci.";
                link.l1.go = "puancie";
			}
			//<-- Бремя гасконца
		break;
		
		case "puancie":
			dialog.text = "Aha, cóż, jestem poinformowany o tym długu... Czy masz przy sobie wymaganą sumę?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Oczywiście, że tak. Jak mogłoby być inaczej?";
				link.l1.go = "puancie_1";
			}
			else
			{
				link.l1 = "Nie, nie mam jeszcze tyle pieniędzy.";
				link.l1.go = "puancie_exit";
			}
		break;
		
		case "puancie_exit":
			dialog.text = "Wróć więc, gdy będziesz mieć, i nie zawracaj głowy Kawalerowi.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "puancie_1":
			dialog.text = "Przejdź przez drzwi po prawej stronie. Chevalier cię przyjmie.";
			link.l1 = "Dzięki!";
			link.l1.go = "puancie_2";
		break;
		
		case "puancie_2":
			DialogExit();
			npchar.quest.saga = "true";
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", true);//чтобы не вышел
			LocatorReloadEnterDisable("Charles_townhall", "reload3", false);//откроем вход к Пуанси
			ref sld = characterFromId("Puancie");
			ChangeCharacterAddressGroup(sld, "Charles_Roomtownhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			sld.dialog.currentnode = "saga";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
