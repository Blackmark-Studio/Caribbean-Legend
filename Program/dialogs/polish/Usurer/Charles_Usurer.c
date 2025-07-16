// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi to pytanie niedawno...","Tak, pozwól mi zgadnąć... Znowu krążysz w kółko?","Słuchaj, ja tu zajmuję się finansami, nie odpowiadam na pytania...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam w tej chwili nic do omówienia."),"Umph, gdzież to moja pamięć uleciała...","Zgadłeś, przykro mi...","Rozumiem...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "usurer" && !CheckAttribute(npchar, "quest.TrialTalk1"))
            {
                link.l1 = " ";
                link.l1.go = "trial";
            }
		break;
		
		case "trial":
			dialog.text = " ";
			link.l1 = " ";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = " ";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = " ";
			link.l1 = "Hello, Captain. How may I assist you today?";
			link.l1.go = "";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
