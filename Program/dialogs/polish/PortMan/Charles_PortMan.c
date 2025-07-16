// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakiego rodzaju pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Już próbowałeś zadać mi pytanie "+GetAddress_Form(NPChar)+"... ","Już trzeci raz dzisiaj mówisz o jakimś pytaniu...","Spójrz, jeśli nie masz nic do powiedzenia o sprawach portowych, to nie zawracaj mi głowy swoimi pytaniami.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie.","Nie mam o czym rozmawiać."),"Nieważne.","Rzeczywiście, już trzeci raz...","Przepraszam, ale na razie nie interesują mnie sprawy portowe.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// НСО пошив мундира Xenon-->
		case "Tailor":
			dialog.text = "Tak, rozumiem cię doskonale, nie krzycz tak. Ale już wyjaśniłem - tym razem było znacznie więcej korespondencji i poczty niż zwykle. Nie martw się, twoje materiały nie znikną i zostaną dostarczone na następnym statku kurierskim.";
			link.l1 = "...";
			link.l1.go = "Tailor_01";
		break;
		
		case "Tailor_01":
			DialogExit();
			sld = characterFromId("Patria_Tailor");
			sld.dialog.currentnode = "Tailor_02";
			Lai_SetPlayerType(pchar);
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Tailor_02":
			dialog.text = "Cóż, najwyraźniej były ważniejsze przesyłki. A statek nie może być przeciążony. Jednak nie jestem poinformowany, jak poczta jest rozdzielana. Proszę, uspokój się i nie denerwuj. Powtarzam: wszystkie twoje materiały dotrą nienaruszone, tylko nieco później.";
			link.l1 = "...";
			link.l1.go = "Tailor_03";
		break;
		
		case "Tailor_03":
			npchar.dialog.currentnode = "First time";
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Patria_Tailor");
			sld.dialog.currentnode = "Tailor_04";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		// <-- пошив мундира
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
