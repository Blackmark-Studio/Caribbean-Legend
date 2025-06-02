// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakiego rodzaju pytania, "+GetSexPhrase("mój synu","moja córko")+"?","Pytaj śmiało, słucham..."),"Słucham, mów teraz, "+GetSexPhrase("mój synu","moja córko")+"...","Po raz trzeci, "+GetSexPhrase("mój synu","moja córko")+"Proszę, mów czego potrzebujesz.","Duchowny ma od groma pracy, "+GetSexPhrase("mój synu","moja córko")+" a ty mnie ewidentnie rozpraszasz...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie w tej chwili, ojcze..."),"Nie mam nic do powiedzenia, przepraszam.","Zapytam, ale później. Wybacz mi, ojcze.","Proszę wybaczyć, święty ojcze...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
