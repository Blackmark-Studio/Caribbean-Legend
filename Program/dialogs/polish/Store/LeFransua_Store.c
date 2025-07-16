// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi jakieś pytanie niedawno, kiedy byłeś w moim sklepie...","To już trzecie pytanie dzisiaj. Muszę zajmować się interesami, a nie wdawać się w bezsensowne rozmowy...","Więcej pytań? Może zamiast tego zawrzemy umowę?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie mam w tej chwili nic do omówienia."),"Tak, to prawda. Próbowałem... Będąc w sklepie...","Tak, to już trzecie pytanie...","Hm, może możemy ubić jakiś interes...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
