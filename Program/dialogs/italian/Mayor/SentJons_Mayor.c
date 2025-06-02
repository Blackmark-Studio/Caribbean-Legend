// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi? Chiedi pure.","Ti sto ascoltando, qual è la domanda?"),"Questa è la seconda volta che stai cercando di chiedere...","Questa è la terza volta che cerchi di chiedere...","Quando finirà tutto questo?! Sono un uomo impegnato, occupato con le questioni della colonia e tu continui a disturbarmi!","blocca",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ora. Luogo e momento sbagliati"),"Vero... Ma più tardi, non ora...","Chiederò... Ma un po' più tardi...","Mi dispiace, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "antigua")
			{
				link.l1 = "Sua Eccellenza, vorrei informarla che possiedo un certo pezzo di informazione sulla scomparsa del Mercurio.";
                link.l1.go = "G_Girl";
			}
		break;
		
		// Jason Дороже золота
		case "G_Girl":
			dialog.text = "Informazioni? Su cosa, ancora?";
			link.l1 = "La brigantina, vostra Eccellenza. Trasporto della posta. Documenti di grande importanza e simili. Ho sentito parlare dell'indagine e, ovviamente, come amico leale della Corona Britannica, mi piacerebbe aiutare.";
			link.l1.go = "G_Girl_1";
		break;
		
		case "G_Girl_1":
			dialog.text = "Splendido! Il baronetto Cortney sarà entusiasta di riceverti! Organizzerò un incontro immediatamente.";
			link.l1 = "Grazie, Signore. Sono di fretta qui e apprezzerei se fosse veloce.";
			link.l1.go = "G_Girl_2";
		break;
		
		case "G_Girl_2":
			dialog.text = "Non preoccuparti, avrai tutto il tempo del mondo. Guardie! Arrestatelo!";
			link.l1 = "Grazie... aspetta, cosa? È uno scherzo?!";
			link.l1.go = "G_Girl_3";
		break;
		
		case "G_Girl_3":
			DialogExit();
			GoldenGirl_AntiguaArest();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
