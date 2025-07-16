// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi?","Cosa vorresti sapere?"),"Di cosa hai bisogno, "+GetAddress_Form(NPChar)+"?","Questa è la terza volta che provi a chiedermi...","Ne ho abbastanza di te, sparisci!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Scusa, ho cambiato idea.","Non è niente, scuse."),"Ho dimenticato, le mie scuse...","La terza volta è la volta buona, eh? Scusami...","Scusa, scusa! Allora me ne andrò da solo...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak")
			{
				link.l1 = "Saluti. L'inquisitore di Santiago, Dadre Vincento, ti ha menzionato nella sua lettera. Ha detto che potresti aiutarmi.";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak_next")
			{
				link.l1 = "Qualche notizia da Padre Vincento, "+npchar.name+"?";
                link.l1.go = "guardoftruth_5";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && CheckCharacterItem(pchar, "jewelry33") && CheckCharacterItem(pchar, "jewelry34") && CheckCharacterItem(pchar, "jewelry35"))
			{
				link.l1 = "Ho bisogno di vedere Padre Vincento. Ho trovato gli oggetti che lo interessano.";
                link.l1.go = "guardoftruth_7";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "inquisition")
			{
				link.l1 = "Allora, "+npchar.name+", cosa ti ha detto Padre Vincento?";
                link.l1.go = "guardoftruth_11";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Certo, Signor. Devi essere un uomo di alta reputazione se Padre Vincento stesso fa affari con te.";
			link.l1 = "Splendido. Allora sei il nostro corriere. Ora ascolta, quest'uomo è di grande interesse per Padre Vincento. È sotto la tua responsabilità ora, devi trasferirlo a Santiago o trovare qualcuno che lo farà.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "...";
			link.l1 = "Sei responsabile del prigioniero per conto dell'Inquisitore. Non ti consiglierei di togliere le sue manette, Gaius Marchais è un uomo forte. Consegnate questa lettera a padre Vincento e ditegli che aspetto una risposta da lui tra due giorni. Questo dovrebbe essere sufficiente, spero.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			Log_Info("You part with the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Capito, Signore. Farò il meglio che posso. Non è la prima volta che aiuto il santo padre.";
			link.l1 = "Non è tutto. Il capitano della carraca, San Gregorio, Carlos Guevarra deve essere stato qui. Mi ha portato la vaniglia. Ti ha dato la mia lettera?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Sì, il tuo carico è in buono stato e ti sta aspettando, Signore.";
			link.l1 = "Bene, lo farò trasportare sulla mia nave allora. Sarò qui per due giorni ad aspettare la risposta di Padre Vincento. Questo non è un addio per ora, "+npchar.name+"!";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			LocatorReloadEnterDisable("mayak9", "boat", false);
			ref sld = characterFromId("GOT_Marshe");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakNextStage", 0, 0, 2, false);
			SetCharacterGoods(pchar, GOOD_CINNAMON, GetCargoGoods(pchar, GOOD_CINNAMON) + sti(pchar.questTemp.Guardoftruth.VanilleQty));
			AddQuestRecord("Guardoftruth", "21");
		break;
		
		case "guardoftruth_5":
			dialog.text = "Sì, Signore. Ecco una lettera da Padre Vincento. È molto soddisfatto di te, il resto lo saprai dalla lettera.";
			link.l1 = "Splendido. Fino ad allora, "+npchar.name+". E per ora - addio.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_exit";
			GiveItem2Character(pchar, "specialletter");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_next";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Molto bene. Dammi e li porterò al santo padre.";
			link.l1 = "Non c'è modo, amico! Non è stato facile ottenerli e non li consegnerò così. Li darò solo personalmente a Padre Vincento.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Ma signore! Come posso sapere che non mi stai truffando?";
			link.l1 = "Dai un'occhiata: il turibolo, il calice e la croce con il lapislazzuli... "+npchar.name+", chi pensi che io sia? Pensi davvero che io sia abbastanza stupido da andare all'Inquisizione senza di loro?";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Perdonami, signore... Vieni domani e dirò al Padre Vincento del tuo arrivo.";
			link.l1 = "Bene. Ci vediamo domani.";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakLastStage", 0, 0, 1, false);
		break;
		
		case "guardoftruth_11":
			dialog.text = "Sua Grazia vi riceverà, Signore. Non ritardare la tua visita. Ecco il documento, mostralo alle guardie e ti faranno entrare. Ma prima issa una bandiera spagnola o i soldati probabilmente ti arresteranno.";
			link.l1 = "Capito. Spagnolo allora. Grazie, amico! Sono sulla mia strada!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper");
			pchar.questTemp.Guardoftruth = "santiago";
			AddQuestRecord("Guardoftruth", "34");
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 400);//скрытность
			GuardOT_SetPadreVincento();
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
