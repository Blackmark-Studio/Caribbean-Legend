// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;   
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande, "+GetSexPhrase("giovane uomo","signorina")+"?","Di che cosa hai bisogno, "+GetSexPhrase("affascinante","bella")+"? Chiedi pure."),"Domande di nuovo","Hi-hi, se non ti dispiace - domande...",""+GetSexPhrase("Mm, perché non scegli una bellezza per te? Sto cominciando ad avere sospetti su di te...","Ehm, perché non scegli una bellezza per te stesso? Ho paura che qui non abbiamo ragazzi, hi-hi...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto, mi scusi.","Effettivamente, non importa."),"Mi... scusi, non ho domande, per ora.","Hai ragione, è già la terza volta. Mi scuso.","Forse la prossima volta, Signora.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Ascolta, Aurora, ho bisogno di una ragazza per la notte. E voglio portarla a casa con me. Puoi organizzare questo?";
                link.l1.go = "Gigolo";
			}	
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Gigolo":
			dialog.text = "Certo, caro. Hai già trovato una Damigella adatta o dovrei farlo io?";
			link.l1 = "Certo che l'ho fatto. Ho messo gli occhi su una ragazza di nome Lucille.";
			link.l1.go = "Gigolo_1";
		break;
		
		case "Gigolo_1":
			dialog.text = "Ti stai riferendo a Lucille Montaigne?";
			link.l1 = "La verità sia detta, non le ho chiesto il cognome. Tutto ciò che so è che si chiama Lucille, una ragazza giovane, bella e bionda.";
			link.l1.go = "Gigolo_2";
		break;
		
		case "Gigolo_2":
			dialog.text = "Sì, la descrive molto bene. Va bene. Ma dimmi, perché lei? Le altre ragazze non sono di tuo gradimento?";
			link.l1 = "Ebbene, vedi... ha appena iniziato a lavorare qui, quindi credo che non sia ancora abbastanza esperta nel 'Mestiere' da essere troppo pesante per la mia borsa.";
			link.l1.go = "Gigolo_2_1";
			link.l2 = "Vedi, adoro le bionde con la pelle chiara. Lucille sarà perfetta a riguardo.";
			link.l2.go = "Gigolo_2_2";
		break;
		
		case "Gigolo_2_1":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand1) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 5000;
				dialog.text = "Ora, signore, questo non è vero! È giovane, bella e esperta, i miei clienti non fanno altro che ammirarla. Ti costerà molto. Cinquemila pesos per una notte con lei, e nemmeno un peso in meno.";
				if (sti(pchar.money) >= 5000)
				{
					link.l1 = "Costoso, ma molto bene. Prendi la tua moneta.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "È costoso! Non ho così tanto. Ti parlerò più tardi.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 2500;
				dialog.text = "Sospiri, hai ragione, Monsieur, è carina e giovane ma manca di esperienza. I miei clienti di solito non la notano, ecco perché ho chiesto. Ma se tu veramente ami le ragazze riservate, direi che è una buona scelta. Ti costerà duemila e cinquecento pesos.";
				if (sti(pchar.money) >= 2500)
				{
					link.l1 = "Purtroppo, lei andrà bene. Prendi la tua moneta.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "È costoso! Non ho così tanto. Ti parlerò più tardi.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_2_2":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand2) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 4500;
				dialog.text = "Non saresti il primo, bello. A volte i miei clienti fanno la coda per la sua attenzione, poiché è molto diversa dalle figlie dalla pelle scura delle nostre isole. Ti costerà quattromila e cinquecento pesos.";
				if (sti(pchar.money) >= 4500)
				{
					link.l1 = "Costoso, ma molto bene. Prendi le tue monete.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "È costoso! Non ho così tanto. Ti parlerò più tardi.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 3000;
				dialog.text = "Davvero, Monsieur? Già nostalgico di casa? Le mie creole e soprattutto le mie mulatte sono più appassionate di questa rilassata gattina parigina. Ma ahimè, è la tua scelta. Ti costerà tremila pesos.";
				if (sti(pchar.money) >= 3000)
				{
					link.l1 = "Costoso, ma va bene. Prendi le tue monete.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "È costoso! Non ho così tanto. Ti parlerò più tardi.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharlie.Gigolo.Money));
			dialog.text = "Come desideri, caro. Lucille ti aspetterà con impazienza alle undici di sera. Inoltre, non deve tornare più tardi delle sette di mattina. Se non arrivi prima di mezzanotte, si occuperà di un altro cliente e poi dovrai aspettare la sera successiva per prenderla.\nE non pensare di... farle del male in qualsiasi modo, altrimenti te ne pentirai. Un avvertimento, caro.";
			link.l1 = "Non ti preoccupare, la tratterò come un'amante, non come un brutale. La prenderò alle undici. Ora cosa dovrei fare fino ad allora?";
			link.l1.go = "Gigolo_4a";
		break;
		
		case "Gigolo_4a":
			dialog.text = "Beh, non lo so nemmeno io, cara. Passa dalla taverna, fai due chiacchiere con il barista...";
			link.l1 = "Non una cattiva idea. Farò proprio così. Buona giornata!";
			link.l1.go = "Gigolo_4";
		break;
		
		case "Gigolo_4":
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			DialogExit();
			AddQuestRecord("SharlieC", "2");
			pchar.questTemp.Sharlie.Gigolo = "girl";
			Sharlie_CreateGigoloGirl();
			QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerDelLoc("fortfrance_brothel", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
			//NewGameTip("Доступна функция перемотки времени! Она доступна через опцию 'мысли вслух' в меню действий (ENTER).");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
