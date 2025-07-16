// диалоги обитателей плантаций
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, i, n;
	string sTemp;
	bool bOk;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Hai bisogno di qualcosa?";
			link.l1 = "No, non lo faccio.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// рабы
		case "plantation_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Sono così stanco, sto già cadendo...","Non posso continuare a vivere così!"),RandPhraseSimple("Questo lavoro mi sta uccidendo.","Le guardie vogliono tutti noi morti!"));				
			link.l1 = RandPhraseSimple("Che peccato.","Mi dispiace.");
			link.l1.go = "exit";				
		break;
		
		// рабы-пираты по пиратской линейке
		case "pirate_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Ascolta, vattene!","Vattene!"),RandPhraseSimple("Cosa vuoi?!","Vattene all'inferno da qui!"));				
			link.l1 = RandPhraseSimple("Mh...","Beh...");
			link.l1.go = "exit";				
		break;
		
		// охрана - солдаты
		case "plantation_soldier":
            dialog.text = RandPhraseSimple(RandPhraseSimple("Vai a infastidire il capo della piantagione","Non distrarre gli schiavi, amico."),RandPhraseSimple("Il mio lavoro è motivare questi bastardi pigri.","Maledizione, troppo caldo oggi, come sempre..."));
			link.l1 = RandPhraseSimple("Vedo...","Certo...");
			link.l1.go = "exit";
		break;
		
		// охрана - протектор
		case "plantation_protector":
            if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					PlaySound("Voice\English\soldier_arest_1.wav");
    				dialog.text = RandPhraseSimple("Pirata?! Prendetelo!","È un pirata! Attacco!");
					link.l1 = RandPhraseSimple("Pirata. E allora?","Eh, prova pure.");
					link.l1.go = "fight"; 
					break;
				}
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = RandPhraseSimple("Oho, stai navigando sotto la bandiera di "+NationNameGenitive(sti(pchar.nation))+"! Penso che il nostro comandante sarà lieto di parlare con te!","Bene-bene, sa di "+NationNameAblative(sti(pchar.nation))+" qui! Una spia?! È ora che tu parli con il nostro comandante.");
				link.l1 = RandPhraseSimple("Per prima cosa, ti manderò all'inferno!","È il momento per te di parlare con la mia lama!");
				link.l1.go = "fight"; 
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						PlaySound("Voice\English\soldier_arest_1.wav");
						dialog.text = RandPhraseSimple("Pirata?! Prendetelo!","È un pirata! Attacco!");
						link.l1 = RandPhraseSimple("Pirata!? Dove?","Eh, prova pure.");
						link.l1.go = "fight"; 
						break;
					}
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Chi sei tu e cosa vuoi da queste parti?","Fermati! Qual è il tuo affare qui?");
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Voglio vedere il capo di questo posto per discutere affari. Ho una licenza di commercio.";
						link.l1.go = "Licence";
					}
					else
					{
						link.l1 = "Voglio vedere il capo di questo posto per discutere affari.";
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) link.l1.go = "PegYou";
						else link.l1.go = "NotPegYou";
					}
					if (IsCharacterPerkOn(pchar, "Trustworthy"))
					{
						link.l2 = "(Affidabile) Onorevoli signori, sono qui per un commercio equo e reciprocamente vantaggioso. Per favore, lasciatemi vedere il proprietario della piantagione.";
						link.l2.go = "mtraxx_soldier_1";
						notification("Trustworthy", "Trustworthy");
					}
				}
				else
				{
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Chi sei e cosa vuoi qui?","Fermati! Qual è il tuo affare qui?");
					link.l1 = "Voglio vedere il capo di questo posto per discutere affari.";
					link.l1.go = "NotPegYou";
				}
			}
		break;
		
		case "Licence":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = "Una licenza? Aspetta un secondo... Ah-ah, questo è divertente! So chi sei. Sei ricercato, amico! E la ricompensa per la tua testa è molto grande! Prendetelo!";
				link.l1 = RandPhraseSimple("Ebbene, in questo caso dovrai solo incontrare la mia lama!","Vaffanculo.");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				PlaySound("Voice\English\soldier_arest_1.wav");
				dialog.text = "Vediamo... ah! La tua licenza è scaduta. Quindi seguimi, ti porterò dal comandante...";
				link.l1 = RandPhraseSimple("Merda! Credo sia il momento per te di incontrare la mia lama, compagno.","Non credo proprio...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			dialog.text = "Bene. Puoi entrare. Comportati bene e non disturbare gli schiavi.";
			link.l1 = "Non preoccuparti, amico.";
			link.l1.go = "plantation_exit";
		break;
		
		case "PegYou":
			PlaySound("Voice\English\soldier_arest_2.wav");
            dialog.text = "Affari? Ah-ah! Beh, questo è divertente! Tu profumi di "+NationNameAblative(sti(GetBaseHeroNation()))+"da mille miglia! È ora che tu incontri il nostro comandante.";
			link.l1 = "No, penso sia ora che tu conosca la mia lama.";
			link.l1.go = "fight";
		break;
		
		case "NotPegYou":
            dialog.text = "Bene. Puoi entrare. Comportati bene e non disturbare gli schiavi.";
			link.l1 = "Non preoccuparti, amico.";
			link.l1.go = "plantation_exit";
		break;
		
		case "plantation_exit":
           DialogExit();
		   NextDiag.CurrentNode = "plantation_repeat";
		break;
		
		case "plantation_repeat":
            dialog.text = "Andiamo, muoviti!";
			link.l1 = "...";
			link.l1.go = "plantation_exit";
		break;
		
		// управляющий в Маракайбо // Addon 2016-1 Jason
		case "Plantator":
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2") // belamour legendary edition 
			{
				dialog.text = "Qual è il tuo affare qui, signore?";
				link.l1 = TimeGreeting()+", signore. Ho una proposta commerciale per te. Ho degli schiavi da vendere. "+FindRussianQtyString(sti(GetSquadronGoods(pchar,GOOD_SLAVES)))+". Interessato?";
				link.l1.go = "mtraxx";
				break;
			}
            dialog.text = "Qual è il tuo affare qui, signore?";
			link.l1 = "Solo in giro, volevo dire ciao.";
			link.l1.go = "plantator_x";
		break;
		
		case "plantator_x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator";
		break;
		
		case "plantator_1":
			bOk = GetSquadronGoods(pchar, GOOD_COFFEE) >= 500 || GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500 || GetSquadronGoods(pchar, GOOD_COPRA) >= 500;
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup") && bOk) //пробуем выкупить Красавчика
			{
				dialog.text = "Di nuovo tu, signore. Come stai?";
				link.l1 = "Ho una proposta commerciale per te. Produci zucchero e cacao. Mi piacerebbe acquistare i tuoi prodotti ma non per denaro, posso offrirti i miei prodotti in cambio. Forse, potremmo fare un affare?";
				link.l1.go = "mtraxx_5";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_6" && bOk)
			{
				dialog.text = "Di nuovo tu, signore. Come stai?";
				link.l1 = "Ho una proposta commerciale per te. Tu produci zucchero e cacao. Mi piacerebbe acquistare i tuoi prodotti, ma non per denaro, posso offrire i miei prodotti in cambio. Forse, potremmo fare un affare?";
				link.l1.go = "mtraxx_5";
				break;
			}
            dialog.text = "Di nuovo tu, signore. Come stai?";
			link.l1 = "Grazie, sto bene.";
			link.l1.go = "plantator_1x";
		break;
		
		case "plantator_1x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator_1";
		break;
		
		case "mtraxx":
			// belamour legendary edition возможность обмануть плантатора -->
			if(GetSquadronGoods(pchar, GOOD_SLAVES) >= 50 || CheckCharacterPerk(pchar, "Trustworthy") || ChangeCharacterHunterScore(Pchar, "spahunter", 0) <= -50)
			{
            dialog.text = "Devo deluderti, signore, ma al momento non abbiamo bisogno di schiavi. Il capitano Eduardo de Losada ci ha già fornito i pirati che ha catturato nella sua ultima incursione.";
			link.l1 = "Pirati qui? Come riuscite a dormire qui?";
			link.l1.go = "mtraxx_1";
			}
			else
			{
				dialog.text = "Ah, vediamo allora... Comprerò i tuoi schiavi. Mi sembra solo che tu non sia chi dici di essere. Vieni con me all'ufficio del comandante, cara mia, e se mi sbaglio, coprirò completamente i tuoi costi morali. E ora ti prego di scusarmi. Guardia!";
				link.l1 = RandPhraseSimple("Sogni d'oro, non mi arrenderò vivo!");
				link.l1.go = "mtraxx_fail";
			}
		break;
		
		case "mtraxx_fail":
            DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddQuestRecord("Roger_3", "27");
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			Mtraxx_PlantPellyClear();
			Mtraxx_TerraxReset(3);
		break;
		// <-- legendary edition
		case "mtraxx_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "Abbiamo una buona guardia, quindi le possibilità di rivolta sono basse. Ma hai ragione in un certo senso: questi bastardi sono lavoratori terribili. Non li avrei comprati se il governatore non mi avesse chiesto di mostrare rispetto a don de Losada. Inoltre, non ha nemmeno chiesto molto per loro.";
			link.l1 = "Capisco. Dovrò navigare verso Los-Teques allora... Signore, posso fare un giro per la tua piantagione ed esplorarla? Forse, vorrei comprare parte della tua produzione...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Sei un mercante?";
			link.l1 = "In qualche modo, sì. Non sono un mercante professionista, ma non mi tirerei mai indietro di fronte a un affare promettente.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Interessante. Molto bene, hai il mio permesso. Torna se avrai qualche idea.";
			link.l1 = "Grazie, signore. Credo che lo farò.";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   NextDiag.CurrentNode = "plantator_1";
		   pchar.questTemp.Mtraxx = "plant_3";
		   AddQuestRecord("Roger_3", "5");
		   Mtraxx_PlantSetMaxRocur();
		break;
		
		case "mtraxx_5":
            dialog.text = "Perché no? Quali merci offri?";
			if (GetSquadronGoods(pchar, GOOD_COFFEE) >= 500)
			{
				link.l1 = "500 scatole di caffè.";
				link.l1.go = "mtraxx_coffee";
			}
			if (GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500)
			{
				link.l2 = "500 scatole di vaniglia.";
				link.l2.go = "mtraxx_cinnamon";
			}
			if (GetSquadronGoods(pchar, GOOD_COPRA) >= 500)
			{
				link.l3 = "500 casse di copra.";
				link.l3.go = "mtraxx_copra";
			}
		break;
		
		case "mtraxx_coffee":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 11;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Cinquecento casse di caffè? Bene-bene... Vediamo... (contando) Sono pronto a scambiare il tuo caffè per "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" sacchi di zucchero e "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  scatole di cacao. Affare?";
			link.l1 = "Mmm... Speravo in condizioni migliori. Beh, chi se ne frega. Affare fatto!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Affidabile) Stimato signore, permettetemi di obiettare! Vi ho portato merci della più alta qualità. Conosco il valore di ogni unità, sia di ciò che offro sia di ciò che offrite in cambio. Merito un carico leggermente più grande dalla vostra parte, e questo affare sarà comunque vantaggioso per voi - lo sapete molto bene.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Trustworthy", "Trustworthy");
			}
		break;
		
		case "mtraxx_cinnamon":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 19;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 106;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 106;
            dialog.text = "Cinquecento casse di vaniglia? Bene-bene... Vediamo... (contando) Sono pronto a scambiare la tua vaniglia per "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" sacchi di zucchero e "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  casse di cacao. Affare?";
			link.l1 = "Hmm... Speravo in condizioni migliori. Beh, chi se ne importa. Affare fatto!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Affidabile) Stimato signore, permettetemi di obiettare! Vi ho portato merci della più alta qualità. Conosco il valore di ogni unità, sia di ciò che offro sia di ciò che offrite in cambio. Merito un carico leggermente più grande da parte vostra, e questo affare sarà ancora proficuo per voi - lo sapete molto bene.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Trustworthy", "Trustworthy");
			}
		break;
		
		case "mtraxx_copra":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 20;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Cinquecento casse di copra? Bene-bene... Vediamo...(contando) Sono pronto a scambiare la tua copra per "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" sacchi di zucchero e "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  casse di cacao. Affare?";
			link.l1 = "Mmm... Speravo in condizioni migliori... Beh, chi se ne importa. Accordato!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Affidabile) Stimato signore, permettami di obiettare! Ti ho portato merci della più alta qualità. Conosco il valore di ogni unità, sia di ciò che offro che di ciò che offri in cambio. Merito un carico leggermente più grande da parte tua, e questo affare sarà comunque profittevole per te - lo sai molto bene.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Trustworthy", "Trustworthy");
			}
		break;
		
		case "mtraxx_6":
            dialog.text = "Splendido! È un affare proficuo per entrambi! Quando effettueremo lo scambio?";
			link.l1 = "Dovrei preparare la merce prima. Credo anche tu. Iniziamo lo scambio domani alle quattro del pomeriggio. I miei uomini consegneranno le casse prima del tramonto.";
			link.l1.go = "mtraxx_7";
		break;
		
		
		case "mtraxx_7":
            dialog.text = "Affare fatto. Allora, ci vediamo domani, signore!";
			link.l1 = "Ci vediamo...";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			AddQuestRecord("Roger_3", "10");
			pchar.questTemp.Mtraxx = "plant_7";
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.mtraxx_plant_goods.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtraxx_plant_goods.win_condition.l1.location = pchar.location;
			pchar.quest.mtraxx_plant_goods.function = "Mtraxx_PlantFindRocurDay";
		break;
		
		case "mtraxx_9":
            dialog.text = "Ecco qui, signore. Se avrai mai bisogno di zucchero o cacao, vieni a trovarmi. In qualsiasi momento!";
			link.l1 = "Se questo affare si rivelerà proficuo - ci rivedremo. Dovrei andare ora, signore.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_10":
            dialog.text = "Addio, signore!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantAfterTrading");
		break;
		
		case "mtraxx_soldier_1":
            dialog.text = "Non sembri un mercante, straniero. Mostra la tua licenza.";
			link.l1 = "Risparmiatemi! Un pezzo di carta decide se una persona può commerciare o no? Sono troppo costosi! Ho iniziato a commerciare solo recentemente, ma è già diventata la mia passione! Lasciatemi passare, e mi assicurerò di parlare bene di voi due al proprietario.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_soldier_2":
            dialog.text = "Hai una lingua d'argento, tirchio. Va bene, continua. Ma non dimenticare di dire al capo che siamo noi che ti abbiamo raccomandato a lui.";
			link.l1 = "Certo. Grazie.";
			link.l1.go = "plantation_exit";
		break;
		
		case "mtraxx_PlantVykup_2":
            dialog.text = "Sei ben versato nei prezzi correnti, Capitano! Hai un chiaro talento per la negoziazione, anche se sembri un novizio. Va bene, se la tua merce è davvero di prima classe, suppongo che dovrei aggiungere un piccolo extra per te.";
			link.l1 = "Certo, di prima classe, lo giuro! Un'altra cosa, signore. Vorrei comprare qualcosa da te.";
			link.l1.go = "mtraxx_PlantVykup_3";
		break;
		
		case "mtraxx_PlantVykup_3":
            dialog.text = "Oh? E cosa potrebbe essere?";
			link.l1 = "Qualcuno, non qualcosa. Vorrei comprare uno dei tuoi schiavi come servitore personale. È possibile?";
			link.l1.go = "mtraxx_PlantVykup_4";
		break;
		
		case "mtraxx_PlantVykup_4":
            dialog.text = "Nessun problema. Troveremo qualcuno adatto a te.";
			link.l1 = "Sono interessato a uno schiavo specifico. Quello con il viso affascinante, qualcuno di cui non ti vergogneresti a portare a eventi formali o a far servire vino ai tuoi ospiti. Si è presentato come Jean Picard. Ci siamo già trovati bene.";
			link.l1.go = "mtraxx_PlantVykup_5";
		break;
		
		case "mtraxx_PlantVykup_5":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 70)
			{
				dialog.text = "Sì, c'è richiesta per Jean Picard - non solo per servire vino. Un influente inglese mi ha già contattato. Un uomo di nome, come si chiamava... Pattornson? Mi ha consegnato una lettera.";
				link.l1 = "Ma né Pattornson né il suo cliente si sono ancora presentati. Sono pronto a comprare Jean da te qui e ora. Dichiara il tuo prezzo - le signore stanno aspettando!";
				link.l1.go = "mtraxx_PlantVykup_10";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Ah, capisco. Ma temo di dover rifiutare - Jean Picard non è in vendita. Mi dispiace, signore.";
				link.l1 = "Oh? Perché mai? Sono disposto a pagare profumatamente. Dì solo il tuo prezzo.";
				link.l1.go = "mtraxx_PlantVykup_6";
				notification("Skill Check Failed (70)", SKILL_COMMERCE);
			}
		break;
		
		case "mtraxx_PlantVykup_6":
            dialog.text = "Prezioso. Ha già un acquirente. L'ho promesso a qualcun altro. Non c'è altro da dire. Torniamo al nostro accordo iniziale e completiamo lo scambio.";
			link.l1 = "Mmm, come desideri, signore.";
			link.l1.go = "mtraxx_PlantVykup_7";
		break;
		
		case "mtraxx_PlantVykup_7":
            dialog.text = "Splendido! È un affare redditizio per entrambi! Quando effettueremo lo scambio?";
			link.l1 = "Dovrei preparare prima la merce. Credo tu debba fare lo stesso. Iniziamo lo scambio domani alle quattro del pomeriggio. I miei uomini consegneranno le casse prima del tramonto.";
			link.l1.go = "mtraxx_PlantVykup_8";
		break;
		
		
		case "mtraxx_PlantVykup_8":
            dialog.text = "Affare fatto. Allora, ci vediamo domani signore!";
			link.l1 = "Ci vediamo...";
			link.l1.go = "mtraxx_PlantVykup_9";
		break;
		
		case "mtraxx_PlantVykup_9":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup2 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_1");
		break;
		
		case "mtraxx_PlantVykup_10":
            dialog.text = "Come desidera, signore. Ma capisca, il prezzo è salato: cinquecento dobloni.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Non è un problema - ecco a te. Un buon servo personale vale molto di più di un semplice schiavo, come ben sai.";
				link.l1.go = "mtraxx_PlantVykup_11";
			}
			else
			{
				link.l2 = "E' un prezzo molto alto, signore. Ma sono molto interessato a questo schiavo. Aspetta qui. Se Pattornson si presenta, digli che Picard è già stato venduto - ah-ah-ah!";
				link.l2.go = "mtraxx_PlantVykup_13";
			}
		break;
		
		case "mtraxx_PlantVykup_11":
            dialog.text = "Hai ragione. Farò le disposizioni. Picard ti aspetterà fuori.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "mtraxx_PlantVykup_12":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup3 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Maracaibo_ExitTown", "rld", "loc17", "Mtraxx_PlantPlantVykup_2");
		break;
		
		case "mtraxx_PlantVykup_13":
            dialog.text = "Se viene con l'intero importo, dubito che lo respingerò. Quindi sbrigati, Capitano.";
			link.l1 = "Torno presto.";
			link.l1.go = "mtraxx_PlantVykup_14";
		break;
		
		case "mtraxx_PlantVykup_14":
            DialogExit();
			NextDiag.CurrentNode = "mtraxx_PlantVykup_15";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
		break;
		
		case "mtraxx_PlantVykup_15":
            dialog.text = "Hai portato l'oro per Jean Picard, Capitano? Il tempo stringe.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Sono ben consapevole di ciò. Quindi ecco, prendi il tuo oro, e dammi il mio nuovo servitore di casa.";
				link.l1.go = "mtraxx_PlantVykup_16";
			}
			else
			{
				link.l2 = "Lo sto ancora raccogliendo - sei tu quello che ha fissato un prezzo così alto, signore.";
				link.l2.go = "mtraxx_PlantVykup_14";
			}
		break;
		
		case "mtraxx_PlantVykup_16":
            dialog.text = "Non ho mai visto qualcuno spendere così tanto per acquisire un servo. Ma a giudicare da quanto sei ben vestito, devi essere abituato a tali grandi acquisti. Informerò i miei uomini e Picard ti aspetterà all'uscita.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
	}
} 
