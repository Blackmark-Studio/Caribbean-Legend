// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			if(startHeroType == 4)
			{
				dialog.text = NPCStringReactionRepeat("Certo, Helen. Cos'è?","Ah, finalmente ricordato cosa volevi?","Sei sicuro di stare bene? Cominci a preoccuparmi. Forse dovresti vedere un medico?","Bene, Helen. Prenditi un po' di sonno, respira aria fresca - insomma, prenditi una pausa. Poi torna. Mhm?","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("No, niente di che.","No, no, scusa per il disturbo.","Hai probabilmente ragione...","Sì, probabilmente hai ragione. È la cosa migliore da fare.",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),"Hai cercato di farmi una domanda poco tempo fa, "+GetAddress_Form(NPChar)+"...","Durante tutto il giorno, questa è la terza volta che parli di qualche domanda...","Altre domande, presumo?","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Umpf, dove se n'è andata la mia memoria...","Sì, è davvero la terza volta...","No, quali domande?...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				link.l1 = "Ascolta, "+npchar.name+", chi è Jan Svenson e come posso trovarlo?";
                link.l1.go = "Svenson";
			}	
			//<-- Бремя гасконца
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Ascolta, è arrivato qui in città un alchimista, un medico? È italiano, ha circa trent'anni, si chiama Gino Gvineili. Hai sentito parlare di lui?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "Svenson":
			dialog.text = "È la prima volta che incontro un uomo che non sa chi sia il Diavolo della Foresta. Quel soprannome gli è stato dato dagli spagnoli e hanno offerto un sacco pieno d'oro per la testa di quel corsaro di Providence Island quindici anni fa! Sì, gli anni volano... La gente ha già iniziato a dimenticare il nostro Jan. Forse è davvero tempo che si riposi.";
			link.l1 = "Sono arrivato di recente qui e non so molto...";
			link.l1.go = "Svenson_1";			
		break;
		
		case "Svenson_1":
			dialog.text = "Se sei interessato al passato, posso venderti un libro di storia. Molti darebbero una fortuna per questo, ma io...";
			link.l2 = "Non darmi buca! Ti ho fatto una domanda. Ripeto. Dove vive Jan Svenson? Ho una conversazione seria per lui.";
			link.l2.go = "Svenson_2";
		break;
		
		case "Svenson_2":
			dialog.text = "Vive in una villa di fronte alla residenza del nostro sindaco, accanto alla fontana. Ma al momento sta passando dei momenti difficili e non ti consiglierei di disturbarlo a meno che non sia di massima importanza.";
			link.l1 = "Perché?";
			link.l1.go = "Svenson_3";			
		break;
		
		case "Svenson_3":
			dialog.text = "La sua ragazza preferita, Helen, conosciuta anche come Rumba, la figlia del suo defunto vecchio amico Shawn McArthur, è scomparsa. Riposa in pace, vecchio... Jan tratta la giovane diavoletta come sua figlia, dato che lui non ha figli suoi. Ma la ragazza è svanita insieme al suo schooner 'Arcobaleno' e tutto l'equipaggio\nMi dispiace per la ragazza. Una rara bellezza, anche intelligente. Calda e ardente come il fuoco, ecco perché la chiamavano Rumba! Suo padre le ha insegnato tutto quello che sapeva, lei ha ereditato la nave e ogni singolo membro dell'equipaggio è rimasto al suo fianco. Anche i più vecchi lupi di mare la riconoscevano come capitano...";
			link.l1 = "Una piratessa? Che cosa le potrebbe essere successo?";
			link.l1.go = "Svenson_4";			
		break;
		
		case "Svenson_4":
			dialog.text = "Chissà... Una settimana non è così tanto, ma la vedova di MacArthur è convinta che sia successo qualcosa di sbagliato a sua figlia e ha convinto Svenson. Ha chiamato i suoi uomini e ha iniziato a cercare lui stesso senza risultati. 'Arcobaleno' e il suo equipaggio sono semplicemente svaniti\nPosso dirti dove trovare Gladys per mille pezzi di otto.";
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = "La tua conoscenza è piuttosto costosa, ma hai stuzzicato il mio interesse. Ecco i tuoi soldi. Dove la trovo?";
				link.l1.go = "Svenson_5";
			}
			else
			{
				link.l1 = "Non. Me la caverò da solo se ne avrò bisogno. Ciao, grazie per il racconto!";
				link.l1.go = "Svenson_6";
			}		
		break;
		
		case "Svenson_5":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "La sua casa è vicino al molo, a sinistra dell'ormeggio. Ma probabilmente non è lì. Passa tutto il giorno appollaiata sulle mura del forte a guardare sua figlia amata. Deve aver già pianto a dirotto.";
			link.l1 = "Grazie per la storia! Addio, compagno!";
			link.l1.go = "Svenson_6";			
		break;
		
		case "Svenson_6"://устанавливаем Глэдис на форт
			DialogExit();
			ref sld = characterFromId("Gladis");
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl_8";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("JS_girl"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("No, non l'ho. Abbiamo erboristi e medici, ma nessuno con un nome del genere.","È la prima volta che sento un nome così strano. No, l'uomo di cui parli non è mai venuto a trovarci.","Non abbiamo nemmeno un alchimista qua. Abbiamo medici, ma nessuno con un nome strano come quello.");
			link.l1 = "Capisco. Che peccato. Continuerò a cercare!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
