// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi jakieś pytanie niedawno, gdy byłeś w sklepie...","To już trzecie pytanie dzisiaj. Muszę zajmować się interesami, a nie prowadzić bezcelowe rozmowy...","Więcej pytań? A może zamiast tego zawrzemy umowę?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam teraz nic do powiedzenia."),"Tak, to prawda. Próbowałem... Kiedy byłem w sklepie...","Tak, to już trzecie pytanie...","Hm, może uda nam się ubić interes...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;				
	}
	UnloadSegment(NPChar.FileDialog2);
}
