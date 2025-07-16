// диалог каторжников в шахте
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
			dialog.text = NPCStringReactionRepeat("Mi dispiace, ma sarebbe meglio per entrambi se non parlassimo più. Mi puniranno, e ti chiederanno di andare via.","Ti ho già detto tutto, amico. O vuoi che mi frustino per colpa tua?","Non sto ascoltando...","La spa-ada colpisce e clan-ang il piccone...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Regole severe avete qui...","No, certo, non lo voglio.","Mmm...","Papà, riesci a sentirmi...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Capitano, cosa stai facendo? Nascondi la tua arma, prima che ti metti nei guai!";
			link.l1 = LinkRandPhrase("Bene.","Bene.","Non preoccuparti, lo sto nascondendo...");
			link.l1.go = "exit";
		break;  
	}
}
