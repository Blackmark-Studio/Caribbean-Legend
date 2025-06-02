// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Hai già provato a farmi una domanda "+GetAddress_Form(NPChar)+"...","Stai parlando di una certa questione per la terza volta oggi...","Guarda, se non hai nulla da dirmi riguardo agli affari del porto, allora non infastidirmi con le tue domande.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea.","Non ho niente di cui parlare."),"Mai mente.","Infatti, già la terza volta...","Mi dispiace, ma per ora non sono interessato alle questioni del porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// НСО пошив мундира Xenon-->
		case "Tailor":
			dialog.text = "Sì, ti capisco perfettamente, non gridare così. Ma ho già spiegato - questa volta c'era molta più corrispondenza e posta del solito. Non preoccuparti, i tuoi materiali non spariranno e saranno consegnati sulla prossima nave corriere.";
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
			dialog.text = "Ebbene, ovviamente, c'erano pacchi più importanti. E la nave non può essere sovraccarica. Tuttavia, non sono informato su come viene distribuita la posta. Ti prego di calmarti e non nervosarti. Ripeto: tutti i tuoi materiali arriveranno intatti, solo un po' più tardi.";
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
