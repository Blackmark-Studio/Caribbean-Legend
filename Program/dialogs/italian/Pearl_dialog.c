void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Non abbiamo niente di cui parlare!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> пиплы в поселении
		case "PearlMan":
			NextDiag.TempNode = "PearlMan";
			dialog.text = NPCStringReactionRepeat("Ciao! Il mio nome è  "+GetFullName(npchar)+". Cosa posso fare per te?","Ciao ancora una volta!","Gli ospiti sono molto rari in questo dietro di oltre...","È un vero piacere parlare con una nuova faccia! Sono già stanco di tutte quelle vecchie grugniture...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Oh, niente...","Anch'io...","Vedo...","Eh...",npchar,Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
		break;
		case "PearlMan_1":
			dialog.text = "Stiamo raccogliendo perle qui, servendo  "+NationNameGenitive(sti(npchar.nation))+", sai...";
			link.l1 = "Sì, lo so...";
			link.l1.go = "exit";
			link.l2 = "Ehi, ascolta, è possibile comprare direttamente dal 'produttore' alcuni di questi piccoli gingilli, cosa diresti?";
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = "Oh no, certo che no! Il furto di anche solo una piccola perla è punito con la morte!";
				link.l1 = "Ordini crudeli avete qui, questo è certo...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Sì, abbiamo ordini severi qui, e uno può facilmente perdere la testa per qualsiasi malefatta. Non mi occupo di questo, ma posso consigliarti di parlare con gli indigeni locali a proposito. Hanno da qualche parte dove scappare se qualcosa va storto, quindi dovrebbero essere più audaci di noi...";
				link.l1 = "Capisco... Va bene, grazie.";
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = LinkRandPhrase("Sei completamente  "+GetSexPhrase("pazzo? Sparisci, idiota","pazzo? Sparisci, stupido sciocco")+"!",""+GetSexPhrase("Cosa?! Sei fuori di testa, idiota","Cosa?! Sei fuori di testa, stupida ragazza")+"?! Sparisci con tutte le tue domande...",""+GetSexPhrase("Hai perso la testa, cara? Quali pirati? Qui?! Semplicemente sparisci, stupido","Hai perso la testa, cara? Quali pirati? Qui?! Smettila di rompere, stupida ragazza")+"...");
			link.l1 = RandPhraseSimple("Non c'è bisogno di essere maleducato...","Guarda la tua lingua!");
			link.l1.go = "exit";
		break;

		// ==> индейцы в поселении
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Viso pallido","Bianca squaw")+" vuole parlare?","Di nuovo tu, "+GetSexPhrase("viso pallido","squaw bianca")+".",""+GetSexPhrase("Viso pallido ama parlare. Sembra una squaw.","La pellerossa bianca ama parlare.")+"","Gli spiriti hanno portato il mio viso pallido "+GetSexPhrase("fratello","sorella")+" a me.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sì.","Sì, sono io di nuovo.","Molto poetico.","Sono felice di vederti anche io",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = "Dimmi, perché sei venuto.";
			link.l1 = "Oh, niente in particolare, volevo solo ascoltare quello che hai da dire.";
			link.l1.go = "exit";
		break;
		
				
		case "CitizenNotBlade":
			dialog.text = "Capitano, cosa stai facendo? Nascondi la tua arma, prima che causi un sacco di problemi!";
			link.l1 = LinkRandPhrase("Bene.","Bene.","Non preoccuparti, sto già mettendo via...");
			link.l1.go = "exit";
		break;  

	}
}
