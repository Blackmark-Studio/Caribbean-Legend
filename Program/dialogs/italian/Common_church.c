// boal 25/04/04 общий диалог церковь
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    
    string iDay, iMonth, lastspeak_date, eggStr;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }
	
    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {	
        npchar.quest.BadMeeting = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }
    
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}
	
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("Mio figlio","Mia figlia")+", purtroppo, non posso darti rifugio. Fuggi!","La guardia cittadina sta setacciando la città alla tua ricerca, "+GetSexPhrase("mio figlio","mia figlia")+". Le porte della mia chiesa sono sempre aperte per i sofferenti, ma non posso darti rifugio...",""+GetSexPhrase("Mio figlio","Mia figlia")+", devi scappare! Non indugiare, ti prego!"),LinkRandPhrase("Cosa stai facendo in chiesa, anima caduta? Esigo che te ne vada subito, prima che i soldati ti trovino qui e commettano un massacro!","Lascia il tempio immediatamente, beffatore! Non proteggerò mai un criminale come te!","Lascia il tempio del nostro Signore all'istante! Non abbiamo bisogno di assassini qui!"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Oh, su, padre...","Non ho bisogno del tuo aiuto comunque..."),LinkRandPhrase("Solo non ostacolare il mio cammino, Padre...","Me ne andrò, non preoccuparti...","Padre, smetti di fare storie - Non ho davvero tempo per questo"));
				link.l1.go = "fight";
				break;
			} 
            if (npchar.quest.BadMeeting != lastspeak_date)
			{
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && NPChar.location != "LosTeques_church" && rand(5) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // 280313
				{
					dialog.text = "...arderanno nell'inferno ardente per sempre! Mai vedranno...";
					link.l1 = RandPhraseSimple("Ehem! Sto disturbando, padre?","Questo è il discorso!");
					link.l1.go = "GenQuest_Church_2_Start_1";
					NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
				{
					Dialog.Text = ""+GetSexPhrase("Mio figlio","Mia figlia")+", sono lieto di rivederti!";
					link.l1 = "E sono lieto di vedervi in buona salute, padre "+NPChar.name+"...";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
				{
					Dialog.Text = ""+GetSexPhrase("Mio figlio","Mia figlia")+"! Sono lieto di rivederti in buona salute e di buon umore. Il Signore deve averci aiutato nella nostra impresa, giusto?";
					link.l1 = "Sì, "+RandPhraseSimple("padre","santo Padre")+", anche se non sempre il vento seguente soffiava nelle mie vele, anche se ho passato un po' più di tempo, forze e denaro - la tua missione è compiuta.";
					link.l1.go = "GenQuest_Church_1_Complete_1";
					break;
				}
				Dialog.Text = "Benvenuto nella nostra santa dimora, "+GetSexPhrase("mio figlio","mia figlia")+".";
				link.l1 = "Ciao, santo Padre.";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
				{
					dialog.text = "Saluti, Ellen, mia figlia.";
					link.l1 = "E a te, Padre.";
				}
				link.l1.go = "node_3";
				Link.l2 = "Non sei mio padre e non osare mai rivolgermi in quel modo di nuovo.";
				Link.l2.go = "node_2";
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}
			else
			{
				Dialog.Text = "Vattene dal tempio del Signore, bestemmiatore! Non abbiamo nulla di cui parlare!";
				Link.l1 = "Non volevo nemmeno.";
				Link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "node_2":
			dialog.text = "Oh, tu bestemmiatore! Vattene! Non osare a profanare il tempio del nostro Signore con la tua presenza!";
			link.l1 = "Non avevo nemmeno intenzione di restare qui.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
			{
				dialog.text = "Sono lieto che nonostante i tuoi... incontri con Jan, non dimentichi il nostro Signore e la Sua casa. Come posso aiutarti?";
			}
			else
			{
				dialog.text = "Che il Signore ti benedica e le tue faccende... Sei venuto da me per un motivo particolare?";
			}
    		link.l1 = RandPhraseSimple("Vorrei fare una donazione.","Voglio fare una donazione per una buona causa.");
    		link.l1.go = "donation";
    		link.l2 = RandPhraseSimple("Credo che sia ora di confessarmi.","Voglio confessarmi, "+RandPhraseSimple("padre.","santo Padre."));
    		link.l2.go = "ispoved";
    		link.l3 = RandPhraseSimple("Ho degli affari con te, "+RandPhraseSimple("padre.","santo Padre."),"Sono arrivato per affari, "+RandPhraseSimple("padre.","santo Padre."));
    		link.l3.go = "work";
			
			//--> Сага
			// Картахена, Чика Гонсалес
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && pchar.location == "Cartahena_church" && sti(pchar.money) >= 1000)
			{
				link.l4 = "Voglio ordinare un servizio di preghiera per la pace dell'anima di una signora.";
				link.l4.go = "saga";				
			}
			// поиски исцеления от заклятий
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location != "Bridgetown_church" && !CheckAttribute(npchar, "quest.seektreatment"))
			{ // все церкви, кроме Бриджтауна
				link.l4 = "Padre, ho bisogno di aiuto. Sono veramente malato. Una terribile maledizione pagana mi ha colpito. Per favore, aiutami, ti supplico!";
				link.l4.go = "seektreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location == "Bridgetown_church")
			{ // попал в Бриджтаун
				link.l4 = "Padre, ho bisogno di aiuto. Sono veramente malato. Una terribile maledizione pagana mi ha colpito. Per favore, aiutami, ti supplico!";
				link.l4.go = "findtreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessFindTreatment") && pchar.location == "Bridgetown_church")
			{ // пришёл в Бриджтаун по направлению
				link.l4 = "Padre, ho bisogno di aiuto. Sono veramente malato. Una maledizione pagana mi ha colpito. Mi hanno detto che sei tu che puoi aiutarmi. Ti prego...";
				link.l4.go = "findtreatment";
			}
			// исцеление от заклятий Джесс
			if(CheckAttribute(pchar, "questTemp.Saga.JessTreatment") && pchar.location == "Bridgetown_church")
			{
				link.l4 = "Padre, ho bisogno di aiuto. Sono veramente malato. Su di me è caduta una maledizione pagana terribile. Sono stato mandato da... Jessica Rose. Mi ha detto che tu potresti aiutarmi.";
				link.l4.go = "treatment";
			}
			if(CheckAttribute(npchar, "quest.candle"))
			{
				link.l4 = "Sulle candele...";
				link.l4.go = "candle";
			}
			if(CheckAttribute(npchar, "quest.prayer") && GetNpcQuestPastDayParam(npchar, "prayer_date") >= 1 && stf(environment.time) >= 22.0)
			{
				link.l4 = "Sono pronto a pregare, Padre.";
				link.l4.go = "prayer";
			}
			//<-- Сага
			
			// Warship, 30.05.11. Миниквест из дел чести "Divine justice".
			if(CheckAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest") && AffairOfHonor_GetCurQuest() == "GodJudgement" &&
				NPChar.city == PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId)
			{
				link.l5 = "Cose terribili stanno succedendo, santo Padre.";
				link.l5.go = "AffairOfHonor_GodJudgement_1";
			}
			
			link.l6 = "Mi scusi, ma devo andare.";
			link.l6.go = "exit";
		break;

		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "Non preoccuparti, mio figlio. Il Signore vedrà la tua sofferenza e ti tenderà una mano. Porta sempre con te una croce per rafforzare la tua fede.";
			Link.l1 = "Grazie, santo Padre.";
			Link.l1.go = "exit";
			AddItems(PChar, "amulet_3", 15);
			DeleteAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest");
		break;

// Jason-------------------------------------------------Сага----------------------------------------------
		//--> Чика Гонсалес
		case "saga" :
			dialog.text = "Umilmente eseguirò la tua volontà per 1000 pesos.";
			Link.l1 = "Ecco a te, Padre - per favore, prendi queste monete.";
			Link.l1.go = "saga_1";
		break;
		
		case "saga_1" :
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Grazie, mio figlio. Qual è il nome della signora, per la cui anima pregherò?";
			Link.l1 = "Si chiamava Chica Gonzales, ed ha lasciato questo mondo molti anni fa.";
			Link.l1.go = "saga_2";
		break;
		
		case "saga_2" :
			dialog.text = "È strano... È successo qualcosa ad Alvarez, ed è lui che ti ha chiesto di questo?";
			Link.l1 = "E chi è questo Alvarez e cosa c'è di così strano nella mia richiesta?";
			Link.l1.go = "saga_3";
		break;
		
		case "saga_3" :
			dialog.text = "Ebbene, come! Ogni mese, Alvarez, il guardiano del nostro faro da due decenni, ordina un servizio di preghiera per la pace dell'anima di questa signora. Nessuno tranne lui si è ancora preoccupato della signora Gonzales. E tu vieni qui. Così ho pensato. Tuttavia, non è affare mio. Certamente, sarò lieto di eseguire umilmente i tuoi desideri per aiutare l'anima sperduta a trovare tranquillità e la strada per il paradiso.";
			Link.l1 = "Grazie, santo Padre.";
			Link.l1.go = "saga_4";
		break;
		
		case "saga_4" :
			DialogExit();
			if(CheckAttribute(pchar,"questTemp.Saga7"))
			{
				AddQuestRecord("Saga", "151");
				DeleteAttribute(pchar,"questTemp.Saga7");
			}
			else AddQuestRecord("Saga", "15");
			Saga_SetOrtega();
			pchar.questTemp.Saga = "ortega";
			pchar.quest.Saga_Gonsales1.over = "yes"; //снять возможное прерывание
			if (GetCharacterIndex("SagaGonsalesB") != -1)
			{
				sld = characterFromId("SagaGonsalesB");
				sld.lifeday = 0;
			}
		break;
		
		// belamour участвовал в событиях Картахены
		case "saga_5" :
			dialog.text = "C'è un'altra anima per la quale vorresti ordinare un requiem?";
			Link.l1 = "Mmm... No, non credo. Devo ordinare per qualcun altro?";
			Link.l1.go = "saga_6";
		break;
		
		case "saga_6" :
			dialog.text = "Ebbene, forse per le centinaia di innocenti che sono caduti per mano tua o delle lame dei tuoi compagni senza Dio quando hai saccheggiato questa sfortunata città?.. Tuttavia, un umile prete difficilmente può sperare di raggiungere la coscienza di un uomo che ha ucciso semplici cittadini pacifici senza rimorsi...";
			Link.l1 = "Padre, non capisci... Tutto quello è nel passato. Qui e ora, non ho intenzione di far del male a nessuno.";
			Link.l1.go = "saga_7";
		break;
		
		case "saga_7" :
			pchar.questTemp.saga7 = true;
			dialog.text = "Posso fidarmi della tua parola...? Ma, in ogni caso, questo è terreno sacro che non dovrebbe essere macchiato di sangue. Quindi, non chiamerò le guardie. Vai in pace. Forse prima di affrontare il giudizio di Dio, avrai tempo per redimere almeno una parte dei tuoi peccati.";
			Link.l1 = "Forse. Sia fatta la volontà di Dio.";
			Link.l1.go = "saga_4";
		break;
		// <-- Чика Гонсалес
		
		// --> исцеление от заклятий
		case "treatment":
			dialog.text = "Jessica? Mi ricordo di lei. Povera peccatrice. Ma non è morta?";
			link.l1 = "È morta, santo Padre. Ora è morta, che il Signore riposi la sua anima. Ma mi ha assicurato che tu saresti stato in grado di aiutarmi.";
			link.l1.go = "treatment_1";
			DeleteAttribute(pchar, "questTemp.Saga.JessTreatment");
		break;
		
		case "treatment_1":
			dialog.text = "Chi ti ha messo questi incantesimi, mio figlio? Dimmi la verità.";
			link.l1 = "Lei... lei ha fatto. Jessica.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "Dio ci salvi! È quello che pensavo. Approfondire i riti pagani può gettare anche le anime più forti nell'abisso dell'oscurità... Ma... è davvero morta? O... non completamente?";
			link.l1 = "Sei estremamente perspicace, Padre. Ora è completamente morta.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			dialog.text = "Questo povero peccatore si è confessato molte volte con me. L'odio l'ha completamente distrutta dall'interno. Sapevo cosa stava combinando. Ho cercato di fermarla, di farle seguire la retta via, ma tutti i miei sforzi sono stati vani. L'ho avvertita del terribile pericolo e delle gravi conseguenze delle sue azioni sacrileghe...";
			link.l1 = "Sì, Santo Padre. Quello che ho visto era davvero terribile. Ma... come posso essere curato?";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "Per il potere della preghiera, mio figlio. Per il potere della santa preghiera purificatrice nel nostro tempio. Dovrai pregare per molto tempo, e non solo per te stesso. Dovrai pregare anche per lei.";
			link.l1 = "Per Jessica?";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "Sì. Per te stesso e per la sua anima. Vieni qui per le dieci di sera, in modo che nessuno possa distrarti. Dovrai pregare tutta la notte. Porta con te venti candele di cera spesse, accendile e prega finché non si consumano tutte.";
			link.l1 = "E poi sarò guarito?";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "Tutto è nelle mani del Signore. Ti insegnerò come pregare e lasciare la Sacra Scrittura per te. Il potere della santa preghiera distruggerà i sortilegi maligni che ti sono accaduti, e purificherà anche l'anima della povera Jessica.";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "Ho venti candele di cera con me. Sono pronto a rimanere nel tempio e iniziare a pregare.";
				link.l1.go = "treatment_9";
			}
			else
			{
				link.l1 = "Non ho ancora venti candele con me. Le prenderò!";
				link.l1.go = "treatment_7";
			}
		break;
		
		case "treatment_7":
			dialog.text = "Va bene, figlio mio. Ti aspetterò. Non perdere tempo!";
			link.l1 = "Sarò qui presto...";
			link.l1.go = "treatment_8";
		break;
		
		case "treatment_8":
			DialogExit();
			npchar.quest.candle = "true";
		break;
		
		case "candle":
			dialog.text = "Hai portato venti candele, mio figlio?";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "Sì, Padre. Ho con me venti candele di cera. Sono pronto a rimanere nel tempio e iniziare a pregare.";
				link.l1.go = "treatment_9";
				DeleteAttribute(npchar, "quest.candle");
			}
			else
			{
				link.l1 = "Non ancora - ma li otterrò con tutti i mezzi.";
				link.l1.go = "exit";
			}
		break;
		
		case "treatment_9":
			dialog.text = "Ebbene, mio figlio. Dammi questi e torna domani dopo le dieci di sera. Ti insegnerò le preghiere necessarie e ti lascerò nella chiesa per la notte.";
			link.l1 = "Grazie, santo Padre. Ci vediamo domani!";
			link.l1.go = "treatment_10";
		break;
		
		case "treatment_10":
			DialogExit();
			RemoveItems(pchar, "mineral3", 20);
			LAi_RemoveLoginTime(npchar);
			LAi_SetLoginTime(npchar, 6.0, 22.99);
			npchar.quest.prayer = "true";
			SaveCurrentNpcQuestDateParam(npchar, "prayer_date");
		break;
		
		case "prayer":
			dialog.text = "I have prepared the texts of the prayers for you , my son. I also left your twenty candles and the Holy Scripture. Light the candles and start praying. Pray without a stop; pray for your recovery and for the soul of this poor sinner Jessica. If you forget something or if you don't understand something - it doesn't really matter. Pray from your heart, your sincere desire is what matters to our Lord.";
			link.l1 = "Grazie, Padre. Ho capito.";
			link.l1.go = "prayer_1";
		break;
		
		case "prayer_1":
			dialog.text = "Tornerò al mattino. Prego anche per te...";
			link.l1 = "Grazie, santo Padre.";
			link.l1.go = "prayer_2";
		break;
		
		case "prayer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_BarbadosTreatment", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "seektreatment":
			dialog.text = "Quali incantesimi pagani ti hanno colpito, mio figlio?";
			link.l1 = "I don't know how they are called. I am weak and sluggish; I cannot run around, and it is very difficult for me to fight.";
			link.l1.go = "seektreatment_1";
		break;
		
		case "seektreatment_1":
			if (sti(pchar.questTemp.Saga.JessSeekTreatment) == 3)
			{
				dialog.text = "Ho sentito parlare di loro... Sono stati portati nel nostro mondo dalle streghe impie di questi pagani dalla pelle rossa. Ti consiglierei di vedere il padre superiore della chiesa di Bridgetown - ha trascorso diversi anni a studiare l'influenza perniciosa delle maledizioni indiane sui corpi e le anime dei cristiani.";
				link.l1 = "E sarebbe in grado di aiutarmi?!";
				link.l1.go = "seektreatment_4";
			}
			else
			{
				dialog.text = "Ho sentito parlare di quelli... Furono portati nel nostro mondo dalle streghe impie di questi pagani dalla pelle rossa. Sfortunatamente, l'unico consiglio che posso darti è passare più tempo in preghiera, mio figlio, e riporre le tue speranze nella misericordia del nostro Signore.";
				link.l1 = "Ma non c'è davvero nulla da fare a riguardo, Padre?! Resterò così... fino alla fine dei miei giorni?";
				link.l1.go = "seektreatment_2";
			}
		break;
		
		case "seektreatment_2":
			dialog.text = "Non disperare, mio figlio. Il Signore ti ascolterà e ti manderà aiuto. Ma ti consiglierei di informarti anche in altre sacre dimore - forse ci sono sacerdoti che sanno come rimuovere le maledizioni pagane.";
			link.l1 = "Grazie, Padre! Sarò guarito - anche se dovrò visitare ogni chiesa dell'arcipelago!";
			link.l1.go = "seektreatment_3";
		break;
		
		case "seektreatment_3":
			dialog.text = "Vai, mio figlio, e possa il Signore vegliare su di te.";
			link.l1 = "Arrivederci, padre.";
			link.l1.go = "exit";
			npchar.quest.seektreatment = "true";
			pchar.questTemp.Saga.JessSeekTreatment = sti(pchar.questTemp.Saga.JessSeekTreatment)+1;
		break;
		
		case "seektreatment_4":
			dialog.text = "Solo il Signore può aiutarti - e tu stesso, mio figlio. Un prete può solo insegnarti cosa fare e come. Vieni a vederlo.";
			link.l1 = "Grazie, padre! Mi avete salvato! Salperò immediatamente per la Barbados!";
			link.l1.go = "seektreatment_5";
		break;
		
		case "seektreatment_5":
			dialog.text = "Vai ora, e possa il Signore vegliare su di te.";
			link.l1 = "Arrivederci, Padre.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment");
			pchar.questTemp.Saga.JessFindTreatment = "true";
		break;
		
		case "findtreatment":
			dialog.text = "Quali maledizioni pagane ti hanno colpito, mio figlio? Lascia che indovini: non riesci a correre, una sciabola è troppo pesante per te e i tuoi movimenti sono lenti e goffi?";
			link.l1 = "Come lo sapeva, Padre?";
			link.l1.go = "findtreatment_1";
		break;
		
		case "findtreatment_1":
			dialog.text = "Non è stato difficile vederlo, osservando il tuo passo mentre ti avvicinavi a me, mio figlio. Che il Signore abbia misericordia delle nostre anime peccatrici... Dimmi, mio figlio, e sii sincero - chi ti ha posto questi incantesimi su di te?";
			link.l1 = "Hai bisogno di un nome, Padre?";
			link.l1.go = "findtreatment_2";
		break;
		
		case "findtreatment_2":
			dialog.text = "Se conosci il nome, allora pronuncialo.";
			link.l1 = "Il suo nome era... Jessica Rose.";
			link.l1.go = "findtreatment_3";
		break;
		
		case "findtreatment_3":
			dialog.text = "Dio ci salvi! Immergersi nei riti pagani può gettare anche le anime più forti nell'abisso delle tenebre... Cosa è successo a lei, a questa povera anima?";
			link.l1 = "È morta, Padre.";
			link.l1.go = "findtreatment_4";
		break;
		
		case "findtreatment_4":
			dialog.text = "Ma... è davvero morta? O... non completamente?";
			link.l1 = "Lei è estremamente perspicace, santo Padre. Ora lei è completamente morta.";
			link.l1.go = "treatment_3";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment"); // если было
			DeleteAttribute(pchar, "questTemp.Saga.JessFindTreatment"); // если было
		break;
		//<-- Сага
		
		// Church GenQuest_2 -->	
		case "GenQuest_Church_2_Start_1":
			dialog.text = "...e la misericordia del Signore! Possa l'oscurità universale consumare le loro anime per i loro peccati...";
			link.l1 = LinkRandPhrase("Santo Padre","Padre","Padre")+", non sei un po' troppo zelante? Sai, potresti avere un colpo...";
			link.l1.go = "GenQuest_Church_2_Start_2";
			link.l2 = "Beh... merda. Addio allora.";
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_2":
			dialog.text = "Oh, "+GetSexPhrase("mio figlio","mia figlia")+", terribile sacrilegio, il più vile dei crimini è appena accaduto! Rubare dalla chiesa!!! È come infilare la mano nella tasca del Signore stesso!";
			link.l1 = "Oh, capisco... Come è successo?";
			link.l1.go = "GenQuest_Church_2_Start_3";
			link.l2 = LinkRandPhrase("È molto triste e tutto il resto, ma devo davvero andare...","Le mie condoglianze, padre, ma devo andare...","Dev'essere che ti sei affidato troppo all'Onnipotente. Avresti dovuto usare serrature più sicure. Beh, devo andare...");
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_3":
			dialog.text = "Sotto la nuvola della notte, alcuni mascalzoni hanno rubato tutto quello raccolto dalla parrocchia! Questi blasfemi hanno preso persino il calice sacrificale!";
			link.l1 = "O tempora, o mores... Ma, spero, hai intrapreso qualcosa su una pista calda?";
			link.l1.go = "GenQuest_Church_2_Start_4";
		break;
			
		case "GenQuest_Church_2_Start_4":
			dialog.text = "Ma certo! Ho scomunicato questi ladri blasfemi, e ora sto pronunciando un'anatema contro di loro!";
			link.l1 = "Non ho dubbi che sia una misura molto efficace. Ma intendevo qualcosa di più pratico. Organizzare un inseguimento, per esempio.";
			link.l1.go = "GenQuest_Church_2_Start_5";
		break;
			
		case "GenQuest_Church_2_Start_5":
			dialog.text = "Ah, cosa può fare un semplice prete, legato dal voto di non resistenza al male? Questi furfanti sono certamente già lontano da qui, a bere nei pub accumulati con i furti o a cedere alla dissolutezza e dissipazione in compagnia di donne cadute! Spero davvero che incontreranno la loro fine lì!";
			link.l1 = RandPhraseSimple("Sono sicuro che tale fine è molto più attraente che essere impiccato. Tuttavia, non ti distrarrò più. Tutto il meglio.","Ebbene, prima o poi, tutti noi andremo dai nostri antenati, ma non direi di no a una fine più rapida per loro. Comunque, devo andare. Buona fortuna.");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Santo Padre","Padre","Padre")+", ma non sono gravato da alcun voto e con prontezza aiuterò il Signore a portare il tempo della retribuzione.";
			link.l2.go = "GenQuest_Church_2_Start_5_1";
		break;
		
		case "GenQuest_Church_2_Start_5_1": //выше - выход из диалога без подтверждения - странно, однако
			dialog.text = "Prego per te, mio figlio! Vai ora e dai a questi truffatori ciò che meritano!";
			link.l1 = "Non avere dubbi, Padre";
			link.l1.go = "GenQuest_Church_2_Start_6";
		break;
			
		case "GenQuest_Church_2_Start_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_2.StartQuest = true;
			PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City;	// Город, в котором спрашиваем
			PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // На каком острове опрашиваем бандюков
			PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_2.AskPeople = true;
			PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
			PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
			PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank)+8)*543+3210;
			PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount)/3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		break;
			
		case "GenQuest_Church_2_Thief_2":
			dialog.text = "Ebbene, forse, l'onnibene Creatore manda ai suoi figli sciocchi pestilenza e fame per punirli dei loro peccati...";
				link.l1 = "Per orgoglio, per esempio, o avarizia... Perché sei diventato pallido, padre?";
				link.l1.go = "GenQuest_Church_2_Thief_3";
			break;
			
		case "GenQuest_Church_2_Thief_3":
			if(rand(1) == 0) // Священник искренне раскаивается...
			{
				dialog.text = "Gesù, mio Signore, abbi pietà del tuo servo peccatore... Hai... Hai trovato i ladri? Li hai uccisi?";
					link.l1 = "Ricordiamo i dieci comandamenti, noti a ogni bravo cristiano dalla culla: non uccidere, non rubare, non portare falsa testimonianza. Può una persona timorata di Dio violarli - e, ancor più, un prete spirituale...?!";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
			}
			else
			{
				dialog.text = "C'è un'aria così pesante qui... Allora hai trovato i ladri? Li hai uccisi?";
					link.l1 = "Ricordiamo i dieci comandamenti, noti a ogni buon cristiano dalla culla: non uccidere, non rubare, non portare falsa testimonianza. Può una persona timorata di Dio violarli - e, ancor più, un sacerdote spirituale?!..";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_1_1":
			dialog.text = ""+GetSexPhrase("Mio figlio","Mia figlia")+"... Dio mi perdoni... tanto denaro, tanta tentazione... l'uomo è debole, veramente debole! Non ho potuto resistere... Ero fuori di me... pregavo giorno e notte, facevo penitenza, digiunavo rigorosamente, mortificavo la mia carne... Indegno, supplicavo solo il Cielo di risparmiare quei poveri uomini, che avevo tentato, spinto dalla mia stessa avidità...";
			link.l1 = LinkRandPhrase("Padre","Padre","Padre")+", calmati. Non hanno detto nulla al riguardo... e sicuramente non lo diranno. A proposito, mi hanno restituito volontariamente il calice della Comunione, che ho riportato a te.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_2":
			dialog.text = "Mio Signore, Ti ringrazio! Mio Dio, hai ascoltato le preghiere del tuo indegno servo, un peccatore inciampato intrappolato nella sporcizia e nei vizi...";
			link.l1 = "Chiunque avrebbe potuto inciampare... Ma poiché il tuo pentimento sembra sincero, direi così: sei un uomo perbene e un buon prete. Se ti presenti davanti al tribunale, non ne verrà fuori nulla di buono. Ed è a te decidere se restare al servizio del Signore o no - solo Lui può dirtelo e guidarti...";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_3":
			if(rand(1) == 0) // Священник хочет всучить ГГ бабло
			{
				dialog.text = ""+GetSexPhrase("Mio figlio","Mia figlia")+"... Con le lacrime di pentimento e gratitudine accetterò questo calice da te. La purezza e nobiltà della tua anima mi hanno veramente scosso. Ti benedico con tutto il mio cuore e umilmente ti prego di accettare questa piccola ricompensa di "+FindRussianMoneyString(iMoneyToCharacter)+"... Spero che sia abbastanza per coprire le vostre spese?";
				// ГГ не берёт деньги. Плюсанем репу
				link.l1 = "Questo è inutile, santo Padre "+NPChar.name+". Non sono esattamente la persona più povera, quindi sarebbe meglio che tu usassi questi soldi per il bene della tua parrocchia.";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				// ГГ берёт деньги
				link.l2 = "Grazie, "+LinkRandPhrase("Padre","padre","santo Padre")+", è più che sufficiente.";
				link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
			}
			else
			{
				dialog.text = ""+GetSexPhrase("Mio figlio","Mia figlia")+"... Con le lacrime di pentimento e gratitudine, accetterò questo calice da voi come segno della misericordia e del perdono del Signore. La purezza e la nobiltà della vostra anima mi hanno veramente scosso. Vi benedico con tutto il mio cuore!";
				link.l1 = "Grazie per la benedizione, "+LinkRandPhrase("padre.","Padre.")+".";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				link.l1 = "La benedizione è certamente necessaria, ma non farebbe male supportarla con qualcosa di più materiale, considerando le considerevoli spese che ho sostenuto...";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
			}
			ChurchGenQuest2_RemoveCup();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "Oh, figlio, mi dispiace davvero... Spero che questo piccolo contributo di "+FindRussianMoneyString(iMoneyToCharacter)+" sarà sufficiente per coprire le tue spese?";
			link.l1 = "Sì, "+LinkRandPhrase("padre.","Padre.")+", è abbastanza, grazie.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_1":
			dialog.text = "Non capisco del tutto le tue insinuazioni, "+GetSexPhrase("mio figlio","mia figlia")+", di cosa stai parlando?!";
			link.l1 = "Sto parlando delle terribili cose che l'avidità può fare a un uomo e che ho ottenuto da straccioni che presumibilmente hanno derubato la tua chiesa... Volevi dire qualcosa?";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_2":
			dialog.text = "Ti direi, figlio, che stai parlando con un chierico e dovresti mostrare un po' più di rispetto, o potresti finire per pentirtene. Riguardo a questo calice - non l'ho mai visto prima, ma se sei disposto a donarlo alla parrocchia, allora...";
			link.l1 = "Calma, padre. Non l'avrai finché non ti spieghi.";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_3":
			if(rand(1) == 0) // Просто несколько разные варианты диалога
			{
				dialog.text = "Cosa c'è da spiegare?! Ora, guarda - tu sei un "+GetSexPhrase("uomo intelligente","ragazza intelligente")+", e certamente dovrai capire che qualsiasi cosa questi furfanti possano aver detto - che io li avrei presumibilmente assunti - è una flagrante menzogna! Il Signore punirà questi blasfemi non solo per sacrilegio, ma anche per falsa testimonianza!";
				link.l1 = "Lascia in pace il Signore! Come puoi sapere cosa mi hanno detto quelle povere creature - quelle contro cui mi hai messo? Forse, li ho uccisi prima che avessero tempo di dirmi qualcosa di brutto su di te?";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
			}
			else
			{
				dialog.text = "There's nothing for me to talk about with you! You haven't fulfilled your obligation in the face of our Lord; you're swearing at the temple; you're attempting to blackmail a priest, displaying some church utensils - and it remains yet to be seen how you got it! Thank the God that I am not calling the acolytes to catch you red-handed!";
				link.l1 = "Ebbene... Vedo che sei talmente immerso nel peccato da non temere più il giudizio degli uomini. Ma esiste ancora la giustizia divina, e prima o poi tutti noi dovremo rispondere di fronte ad essa. Prendi i tuoi 'oggetti sacri' e rifletti se sei degno di toccarli, Padre "+NPChar.name+".";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
				link.l2 = "Perdonami i miei dubbi, Padre, perché un cuore mortale è debole, e l'anima è confusa. Per favore, prendi il calice e dammi la tua benedizione.";
				link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1":
			dialog.text = "Mmmm... "+GetSexPhrase("Mio figlio... Signore... Sir...","Mia figlia... Signorina... Signora...")+" "+PChar.name+"... Sono pronto a piegarmi davanti a te... e considerare i nostri disaccordi, per così dire... e compensare le tue spese con questa modesta somma di "+FindRussianMoneyString(iMoneyToCharacter)+"... ovviamente, se non stai per coinvolgere altri in questa faccenda...";
			// При этом варианте репу плюсуем
			link.l1 = "Non coinvolgerò nessuno. Prendi il calice! E non pensare nemmeno che accetterei l'oro che stavi segretamente pizzicando dalle tasche dei tuoi parrocchiani!";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
			// При этом - минусуем
			link.l2 = "Non coinvolgerò nessuno. Prendi il calice! Quest'oro lo prendo solo perché ho speso su di te un sacco di tempo e denaro.";
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1":
			// ничего не принесли священнику.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
			{
				link.l1 = "Cattive notizie, "+LinkRandPhrase("Padre","Padre","Padre")+": i ladri erano troppo infidi e ingegnosi, e quindi non sono riuscito a recuperare l'oro della chiesa...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
				break;
			}
			// Принесли священнику только чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
			{
				link.l1 = "Cattive notizie, "+LinkRandPhrase("Padre","Padre","Padre")+": Sono riuscito a raggiungere i ladri, ma il mio unico trofeo è stato questo calice.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Принесли священнику и деньги и чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "Sono certo che le piacerà la notizia - ho punito approssimativamente i ladri e ho preso da loro il denaro della parrocchia, e anche questo calice.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Padre","Padre","Padre")+", Ho portato brutte notizie... Ho dovuto passare molto tempo, forze e risorse per dare la caccia ai mascalzoni, ma quando li ho trovati, ho scoperto che avevano avuto il tempo di bere e spendere tutto, tranne questo calice...";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Священник - вор.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
			{
				dialog.text = "Oh, "+GetSexPhrase("mio figlio","mia figlia")+", cosa potrebbe essere successo a me? È la tua strada che è piena di pericoli e ansia, e la mia cella tranquilla, dominio di riflessione e preghiera, è un'isola tranquilla in un oceano infuriato di passioni umane...";
					link.l1 = "E nulla può turbare la serenità della tua beata solitudine?";
					link.l1.go = "GenQuest_Church_2_Thief_2";
				break;
			}
			// Короткий вариант прохождения квеста.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "Sono sicuro che questa notizia ti renderà felice - ho punito i ladri e ho riportato i soldi della parrocchia.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Padre","Padre","Padre")+"... Devo deluderti. Ho perseguito i ladri in tutto l'arcipelago, superato un gran numero di pericoli e ostacoli, quasi rovinato me stesso, e alla fine li ho raggiunti, ma ahimè... avevano già avuto tempo di sperperare i soldi della chiesa.";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1": // ГГ решил заныкать деньги...
			if(rand(1) == 0)	// Священник верит ГГ но не даёт денег...
			{
				if(rand(4) == 3) // Более "мягкий" исход событий.
				{
					dialog.text = "Oh, "+GetSexPhrase("mio figlio","mia figlia")+". Le tue parole mi hanno immerso in profondo dolore - ma non disperazione, perché la disperazione è un peccato mortale! Il Signore ci ha presentato un'altra prova per rafforzare la nostra fede.";
						link.l1 = "Amen, Padre...";
						link.l1.go = "exit";
						sQuestTitle = NPChar.City + "ChurchGenQuest2";
						AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
						AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
						CloseQuestHeader(sQuestTitle);
						ChangeCharacterComplexReputation(PChar,"nobility", -2);
						DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
						NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
				}
				else
				{
					dialog.text = ""+GetSexPhrase("Mio figlio","Mia figlia")+", non mentire al tuo pastore spirituale.";
						link.l1 = "Mi dispiace davvero, Padre, ma giuro che sto dicendo la verità.";
						link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
				}
			}
			else
			{
				// Священник даёт деньги ГГ...
				iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
				dialog.text = "Oh, "+GetSexPhrase("mio figlio","mia figlia")+". Le tue parole mi hanno gettato in profonda tristezza - ma non disperazione, perché la disperazione è un peccato mortale! Il Signore ci ha messo di fronte a un'altra prova per rafforzare la nostra fede. Ma i tuoi sforzi e le tue spese dovrebbero essere compensate, nonostante siano state vane. Per favore, accetta questa modesta somma - "+FindRussianMoneyString(iMoneyToCharacter)+" - e continua il tuo cammino virtuoso!";
					link.l1 = "Mmm!... Grazie, padre, userò questi soldi per una causa virtuosa.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
					link.l2 = LinkRandPhrase("Padre","Padre","Padre")+"... Non posso accettare una ricompensa per un lavoro che non ho fatto. Sarebbe meglio usare questi soldi per rinnovare l'altare.";
					link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
			if(rand(6) == 3)
			{
				dialog.text = "Bene, ti credo, "+GetSexPhrase("mio figlio","mia figlia")+". Il Signore ci ha visitato con un'altra prova per rafforzare la nostra fede.";
				link.l1 = "Amen...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1"
				break;
			}
				dialog.text = "Disprezzabile, pensavi davvero di ingannare il nostro Signore?! Maledizione su di te"+GetSexPhrase(", mascalzone",", sgualdrina")+"! Vattene e ricorda che questi soldi non ti porteranno alcun beneficio!";
				link.l1 = "Come è possibile?! Padre!..";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			ChangeCharacterComplexReputation(PChar,"nobility", -3);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			ChangeCharacterComplexReputation(PChar, "nobility", -6);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddCharacterExpToSkill(PChar, "Fortune", -70);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			npchar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1":
			if(rand(1) == 0) // Поверил.
			{
				dialog.text = "Oh, "+GetSexPhrase("mio figlio","mia figlia")+". Le tue parole mi hanno gettato in profonda tristezza - ma non nella disperazione, perché la disperazione è un peccato mortale! Il Signore ci ha posto di fronte ad un'altra prova per rafforzare la nostra fede.";
				link.l1 = "Amen, Padre...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // Переход сюда, т.к. одно и тоже.
			}
			else
			{
				dialog.text = "Sì, è proprio quel calice che è stato rubato con i soldi... Ma... Se l'hai preso, come mai non hai riportato indietro i denaro? Era una somma considerevole, e sicuramente quei mascalzoni non avrebbero potuto spenderla così in fretta..."+GetSexPhrase("Mio figlio","Mia figlia")+", ricorda che non c'è peccato più grande che mentire al tuo pastore spirituale e portare false testimonianze nel tempio di fronte a Dio!";
				link.l1 = "Santo Padre "+NPChar.name+", Ho quasi perso la mia vita, ottenendo questo vaso, pensavo di farti felice. Non dirò nulla su quanto denaro ho speso per tutto questo!";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
			}
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
			dialog.text = "Vattene e ringrazia l'Onnipotente, che mi ha dato un cuore mite. È l'unico motivo per cui non sei ancora marcato come ladro e furfante!";
			link.l1 = "Come può essere?! "+LinkRandPhrase("Santo Padre","Padre","Padre")+"!..";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -5);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, iMoneyToCharacter);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -1);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_1":
			dialog.text = "Oh, "+GetSexPhrase("mio figlio","mia figlia")+". Le tue parole mi hanno gettato in una profonda tristezza - ma non nella disperazione, perché la disperazione è un peccato mortale! Il Signore ci ha messo di fronte a un'altra prova per rafforzare la nostra fede.";
			link.l1 = "Amen, Padre...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_1":
			dialog.text = "Signore, Ti ringrazio! Davvero, tu eri il Suo strumento, mio figlio! Sapevo che il nostro Padre Celestiale ti avrebbe mostrato la strada e fornito tutto l'aiuto di cui avevi bisogno. Ho pregato senza sosta, e...";
			link.l1 = "Sai, padre, in questioni come questa, le armi sono sicuramente più utili delle preghiere. Ma, a quanto pare, le tue preghiere sono state davvero ascoltate.";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_2":
			dialog.text = ""+GetSexPhrase("Mio figlio","Mia figlia")+", voglio ricompensarti adeguatamente, tu"+GetSexPhrase(", come un vero cavaliere della Madre Chiesa,","")+"ha fatto tutto il possibile...";
			link.l1 = "Padre, stai davvero esagerando i miei umili successi. Ora ti lascio per lodare il nostro Signore...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
		// <-- квесты церкви

		case "donation":
			dialog.Text = "Certo, "+GetSexPhrase("mio figlio","mia figlia")+". Quanto vorresti donare alla Santa Chiesa?";
			Link.l1 = "Mi dispiace, Santo Padre, ma ho cambiato idea.";
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = "La mia donazione sarà modesta - solo 100 pesos.";
				Link.l2.go = "donation paid_100";
			}
			if(makeint(PChar.money)>=1000)
			{
				Link.l3 = "1000 pesos. Penso che dovrebbe essere sufficiente.";
				Link.l3.go = "donation paid_1000";
			}
			if(makeint(PChar.money)>=5000)
			{
				Link.l4 = "Sono fortunato con i soldi, quindi donerò 5000 pesos.";
				Link.l4.go = "donation paid_5000";
			}
			//-->> квест пожертвования хозяйки борделя
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = "Padre, voglio fare una donazione non a mio nome. Lo sto facendo su richiesta.";
				Link.l5.go = "HostessChurch";
			}
			//<<-- квест пожертвования хозяйки борделя
		break;

		case "No donation":
			dialog.Text = "Hmm... Beh, questa è la tua decisione, e sei libero di cambiare idea. E non dimenticare che ciò sarà preso in considerazione nel Giorno del Giudizio.";
			Link.l1 = "Come molte altre cose. Cambiamo argomento.";
			Link.l1.go = "node_3";
			Link.l2 = "Mi dispiace, Padre, ma è ora per me di andare.";
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = "A nome della Santa Chiesa ti ringrazio, "+GetSexPhrase("mio figlio","mia figlia")+", per il tuo dono.";
			Link.l1 = "Ho bisogno di parlare con te, Padre.";
			Link.l1.go = "node_3";
			Link.l2 = "Mi dispiace, Padre, ma è ora per me di andare.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = "A nome della Santa Chiesa ti ringrazio.";
            Link.l1 = "Ho bisogno di parlare con te, Padre.";
			Link.l1.go = "node_3";
			Link.l2 = "Mi dispiace, Padre, ma è ora per me di andare.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = "A nome della Santa Chiesa ti ringrazio, per il tuo dono.";
            Link.l1 = "Devo parlare con te, Padre.";
			Link.l1.go = "node_3";
			Link.l2 = "Mi dispiace, Padre, ma è ora per me di andare.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = "Certo, "+GetSexPhrase("mio figlio","mia figlia")+", Sto ascoltando voi.";
			link.l1 = "Ho cambiato idea. Forse la prossima volta.";
			link.l1.go = "exit";
			link.l2 = "Sono così pieno di peccati, Padre. Un giorno non sarà sufficiente per elencare tutte le mie malefatte...";
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = "Ciascuno di noi è un peccatore, mio figlio...";
			link.l1 = "Sì, ma sulla mia coscienza pesa il fardello di migliaia di morti. Ho derubato e affondato navi...";
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = "Spero che non ci fossero tra quelli che navigavano sotto la bandiera di "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "No, certo che no, Padre.";
			link.l1.go = "ispoved_3";
			link.l2 = "Di tutti i tipi, Padre...";
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = "Allora il nostro Signore ti assolverà di quei peccati. Perché questa è un'epoca crudele, e distruggendo i nemici del tuo sovrano stai salvando le vite dei suoi fedeli sudditi.";
			link.l1 = "Grazie, Padre, è stato un grande conforto... Ora me ne vado.";
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = "Il Signore non ti assolverà da un tale peccato! Prega e pentiti, pentiti e prega! C'è solo una strada per te ora - verso il chiostro!";
			link.l1 = "Il chiostro dovrà aspettare. Non in questa vita, almeno. Addio...";
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
        	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
        	{
        		dialog.text = "Mi dispiace, "+GetSexPhrase("mio figlio","mia figlia")+", ma tutte le confessionali sono occupate al momento. Sarò in grado di ascoltare la tua confessione tra almeno mezz'ora.";
				link.l1 = "Scusatemi, "+RandPhraseSimple("padre","Padre")+", questa è una questione diversa. Padre "+PChar.GenQuest.ChurchQuest_1.PriestName+", da "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+", una volta ti ha dato dei tesori inestimabili della biblioteca teologica. Mi ha chiesto di restituirli.";
				link.l1.go = "GenQuest_Church_1_Dialog_1";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
				break;
        	}
			dialog.text = "Che tipo di affari ti ha portato qui, "+GetSexPhrase("mio figlio","mia figlia")+"?";
			link.l1 = "Voglio farle una domanda, Padre...";
			link.l1.go = "quests"; // ссылка к НПС
            link.l2 = RandPhraseSimple("Volevo parlare di lavorare per il bene della chiesa di "+NationNameGenitive(sti(NPChar.nation))+".","Come vanno le cose nella parrocchia? Avete bisogno di aiuto?");
			link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
	            link.l3 = RandPhraseSimple("Padre","Padre")+", Voglio parlare con te di affari finanziari."; //(пересылка в кредиты)
	            link.l3.go = "LoanForAll";
            }
			// -->
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = "Ho bisogno di guarigione.";
                link.l4.go = "healthAdd_1";
            }
            
			//квест мэра - на связь с нашим шпионом
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
	            link.l7 = RandPhraseSimple("Padre","Santo Padre")+", sono qui su richiesta di un uomo. Il suo nome è governatore "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".";
	            link.l7.go = "IntelligenceForAll";
            }
			//--> Jason Церковная депеша
			if (CheckAttribute(pchar, "GenQuest.Monkletter") && npchar.city == pchar.GenQuest.Monkletter.City)
			{
	            link.l10 = "Padre, vi ho portato dei documenti da un monaco nella città di "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity)+".";
	            link.l10.go = "Monkletter";
            }
			//<-- Церковная депеша
			//--> Jason Доставка молитвенников
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "go" && sti(npchar.nation) == sti(pchar.GenQuest.Churchbooks.Nation) && npchar.city != pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "Padre, vengo dalla colonia di "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity)+". La chiesa locale ha bisogno di più libri di preghiere, e un monaco locale ha suggerito di vederti riguardo a questa questione.";
	            link.l11.go = "Churchbooks";
            }
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "return" && npchar.city == pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "Padre, ho portato i libri di preghiera per la vostra parrocchia.";
	            link.l11.go = "Churchbooks_2";
            }
			//<-- Доставка молитвенников
			link.l99 = "Ho cambiato idea, ho molto da fare.";
			link.l99.go = "exit";
		break;

		case "prihod":
			if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
		    {
		        dialog.text = "È fantastico. Eppure, in questi tempi cupi, "+GetSexPhrase("mio figlio","mia figlia")+", non ogni visitatore del tempio può essere utile alla nostra Madre Chiesa.";
				link.l1 = LinkRandPhrase("Padre","Padre","Padre")+", Sono un vero cristiano, e le mie intenzioni di servire la nostra Madre Chiesa sono le più sincere."+GetSexPhrase("Chi la sosterrà, se non il suo leale cavaliere, come me?","")+"";
				link.l1.go = "GenQuest_Church_1_Start_1";
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
		    }
			else
			{
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}	
            dialog.text = "Tutto è tranquillo nella parrocchia finora, "+GetSexPhrase("mio figlio","mia figlia")+". Grazie per l'offerta.";
    		link.l2 = "Bene, se le cose vanno bene, credo che proseguirò con i miei affari.";
    		link.l2.go = "exit";
			DeleteAttribute(npchar, "quest.add");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
		break;
		
		// Church GenQuest_1 -->
		case "GenQuest_Church_1_Start_1":
			dialog.text = "Ebbene, ho una missione delicata, che richiederebbe non solo purezza di intenzioni, ma anche grande coraggio e notevole discrezione...";
			link.l1 = LinkRandPhrase("Padre","Padre","Padre")+", Sarò felice di offrirti qualsiasi servizio, anche se per questo dovrò andare dritto all'inferno! Dio mi perdoni per le mie parole impie.";
			link.l1.go = "GenQuest_Church_1_Start_2";
		break;
			
		case "GenQuest_Church_1_Start_2":
			PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
			Church_GenQuest1_InitStartParam(NPChar);
			dialog.text = "Oh! Bene... Ma, ancora, questo è un affare molto delicato... Un po' di tempo fa padre superiore "+PChar.GenQuest.ChurchQuest_1.ToName+" da "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Gen")+" su "+XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland+"Voc")+"ha preso in prestito alcuni lavori teologici e antichi manoscritti dalla biblioteca di una chiesa per me per un po'. Poiché la richiesta era sostenuta dall'insistenza dell'arcivescovo di non impedire la diffusione della bella luce della conoscenza, non ho potuto rifiutare, anche se presumo che le difficoltà dei viaggi marittimi non gli permetteranno di restituire i manoscritti in tempo... Potresti aiutarmi a risolvere questo problema?";
			link.l1 = "Ho paura, "+LinkRandPhrase("Padre","padre","santo Padre")+", Non potrò farlo per te. Questo è un affare molto delicato e solo un vero diplomatico riuscirebbe a risolverlo.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Padre","Padre","Padre")+", la tua missione non mi sembra troppo complicata. Me ne andrò subito.";
			link.l2.go = "GenQuest_Church_1_Start_3";
		break;
			
		case "GenQuest_Church_1_Start_3":	// Квест взят
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.StartQuest = true;
			PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_1.AskOwner = true;
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
		break;
			
		case "GenQuest_Church_1_Dialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene"))	// Сцена 2а
			{
				dialog.text = "Oh! Sì... Infatti, ora ricordo... Ma, "+GetSexPhrase("mio figlio","mia figlia")+", questi tesori sono più di natura spirituale piuttosto che materiale! Hanno già aiutato immensamente i miei parrocchiani e potrebbero farlo anche in futuro!";
				link.l1 = "Ma, "+LinkRandPhrase("Padre","Padre","Padre")+", i parrocchiani di Padre "+PChar.GenQuest.ChurchQuest_1.PriestName+" hanno anche bisogno di salvezza, e senza queste opere, gli mancherà il sostegno dei pilastri della teologia, e i suoi sermoni mancheranno di ispirazione.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_1";
			}
			else	// Сцена 2б-а и 2б-б
			{
				dialog.text = "Oh, sì!.. Certamente... "+GetSexPhrase("Mio figlio","Mia figlia")+", questi tesori sono più di natura spirituale che materiale! Hanno già aiutato enormemente i miei parrocchiani, quindi, con mia vergogna, ho 'dimenticato' di restituirli al loro legittimo proprietario...";
				link.l1 = "Certo, "+RandPhraseSimple("Padre","Padre","Padre")+", infatti. Ecco perché Padre "+PChar.GenQuest.ChurchQuest_1.PriestName+" mi ha chiesto di consegnargli personalmente questi libri.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_1": // Сцена 2а
			dialog.text = "Capisco, mio figlio, ma non preghiamo ogni giorno il nostro Signore: 'e perdona i nostri peccati, come noi perdoniamo chi ci ha offeso'? E la chiesa di "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" più ricco della mia modesta parrocchia.";
			link.l1 = "Ha certamente ragione, Padre, ma mi è venuto in mente un altro passo della Sacra Scrittura: 'non cercare la via facile, perché è lì che il Diavolo ci tende l'agguato, e la sua voce è tanto più sottile e la tentazione tanto più forte, quanto più facile è la via!' E padre "+PChar.GenQuest.ChurchQuest_1.PriestName+"stava già per mandare un messaggio riguardo alla tua dimenticanza all'arcivescovo - sono riuscito a dissuaderlo solo all'ultimo momento.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_1":
			dialog.text = "A-A-All'arcivescovo?! Per una questione così piccola!.. Perché? Davvero? Stavo per inviare questi lavori al mio amato fratello in Cristo comunque - è solo che non c'era un'occasione favorevole per consegnarglieli. Ma in te, "+GetSexPhrase("mio figlio","mia figlia")+", vedo un vero e degno servitore del nostro Signore. Ecco - prendi questi libri e manoscritti e per favore consegnali a Padre "+PChar.GenQuest.ChurchQuest_1.PriestName+" sano e salvo. E aggiungi a ciò la mia più sincera gratitudine.";
			link.l1 = "Certo, "+LinkRandPhrase("Padre","Padre","Padre")+". Certo...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			// Предмет "рукопись" -->
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			// <-- Предмет "рукопись"
		break;
			
		case "GenQuest_Church_1_Dialog_1_2":	// Сцена 2б-а и 2б-б
			// Генерим кэпа -->
			sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "mercen_" + (rand(14)+14), "man", "man", 15, NPChar.nation, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 40, 35, "blade_13", "pistol3", "grapeshot", 30);
			FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS16, 75, 70, 65);
			sld.Abordage.Enable = false;
			sld.ShipEnemyDisable  = true; // флаг не обижаться на выстрелы
			LAi_SetImmortal(sld, true);
			sld.Dialog.FileName = "GenQuests_Dialog.c";
			sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
			Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetType("ChurchGenQuest1_CapGroup", "trade");
			Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetTaskNone("ChurchGenQuest1_CapGroup");
			Group_LockTask("ChurchGenQuest1_CapGroup");
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
			PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
			PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
			PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			// <-- Генерим кэпа
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // Сцена 2б-а
			{
				dialog.text = "Ma, "+GetSexPhrase("mio figlio","mia figlia")+"... Vedi, la cosa è che la settimana scorsa ho incontrato un capitano della nave '"+sld.Ship.Name+"', dove sono stato chiamato per amministrare la comunione a un marinaio morente. Con mia grande gioia, capitano "+GetFullName(sld)+"mi ha detto che stava per "+XI_ConvertString("Colony"+GetColonyExpect2Colonies(NPChar.city,PChar.GenQuest.ChurchQuest_1.QuestTown))+". E anche se non garantiva alcuna condizione, ha comunque accettato di aiutare e mi ha assicurato che il porto di "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" sicuramente verrà a farci visita. Quindi ho colto questa opportunità, ho mandato via libri con quell'uomo gentile e ho affidato il loro ulteriore destino al Signore.";
				link.l1 = "Mmm, sei sicuro che a questo capitano si possa fare affidamento? Ha capito il valore delle opere a lui affidate e l'importanza di questa missione?";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
			}
			else // Сцена 2б-б
			{
				dialog.text = "Oh, "+GetSexPhrase("mio figlio","mia figlia")+"! Sei solo alcune ore in ritardo! Ho già inviato i libri del Padre "+PChar.GenQuest.ChurchQuest_1.PriestName+" con il capitano "+PChar.GenQuest.ChurchQuest_1.CapFullName+". Questa mattina, quell'uomo timorato di Dio è venuto a fare una confessione e ha menzionato che oggi la sua nave avrebbe salpato per "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.CapColony)+". E anche se il signor capitano non garantiva alcuna condizione, ha comunque accettato di aiutare e mi ha assicurato che il porto di "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+"lui sicuramente verrà a visitare.";
				link.l1 = LinkRandPhrase("Padre","Padre","Padre")+"... sei sicuro che si possa fidare di questo capitano? E voglio anche sapere come si chiama la sua nave.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1":	// 2б-а
			dialog.text = "Faccio fiducia alle persone, "+GetSexPhrase("mio figlio","mia figlia")+", ogni singolo di noi è creato a immagine e somiglianza del nostro Signore, e il Suo fuoco sacro brucia in ogni anima!";
			link.l1 = "Ugh. Questo è un argomento pesante, di sicuro. Beh... Allora beneditemi, Padre, e auguratemi buona fortuna nella mia ricerca di quel capitano.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // Полная инфа о кэпе
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_1":
			dialog.text = "Dovresti fidarti delle persone, "+GetSexPhrase("mio figlio","mia figlia")+". Per quanto riguarda la sua nave - non ho nulla da dire.";
			link.l1 = "E hai dato preziosi manoscritti a qualche capitano senza nemmeno preoccuparti di conoscere il nome della sua nave?!!";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_2":
			dialog.text = "Vedi, "+GetSexPhrase("mio figlio","mia figlia")+", capitano "+PChar.GenQuest.ChurchQuest_1.CapFullName+" è molto timorato di Dio...";
			link.l1 = "Bene, l'ho già sentito.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_3":
			dialog.text = "Pazienza, "+GetSexPhrase("giovane uomo","giovane signora")+"! Capitano "+PChar.GenQuest.ChurchQuest_1.CapFullName+" è una persona molto timorata di Dio, e fino a questo giorno la sua nave portava un nome che un chierico non dovrebbe mai dire nemmeno in pensiero, figuriamoci ad alta voce! E oggi durante la sua confessione gli ho fatto notare questo. Perché, come dice la Bibbia, la purezza dell'anima deve essere preservata da noi peccatori, più della purezza del corpo, perché il nostro Signore nega il Suo Regno agli osceni...";
			link.l1 = "Capisco, "+LinkRandPhrase("Padre","Padre","Padre")+", Capisco! "+PChar.GenQuest.ChurchQuest_1.CapFullName+", un noto giocatore d'azzardo e ubriacone, famoso in tutto i Caraibi, ha deciso di rinominare la sua vecchia tinozza su tuo suggerimento?";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_4":
			dialog.text = "Sei molto perspicace, "+GetSexPhrase("mio figlio","mia figlia")+". Non conosco il nuovo nome di questa nave, ma certamente è qualcosa di esaltante.";
			link.l1 = "Oh, "+RandPhraseSimple("Padre","Padre","Padre")+"... Grazie per tutto. E prega per la mia anima peccatrice...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
		break;
			
		case "GenQuest_Church_1_Complete_1":
			dialog.text = "Oh, mio figlio! Ho pregato con fervore, e sembra che tutto si sia risolto nel miglior modo possibile! Per il tuo aiuto e la tua fede, "+GetSexPhrase("mio figlio","mia figlia")+", il paradiso e il canto angelico certamente ti aspetteranno...";
			link.l1 = RandPhraseSimple("Padre.","Padre.")+", Non ho intenzione di incontrare San Pietro tanto presto, Dio non voglia. Per quanto riguarda i viventi - hanno bisogno di molte cose materiali oltre alle promesse di beatitudine celeste...";
			link.l1.go = "GenQuest_Church_1_Complete_2";
		break;
			
		case "GenQuest_Church_1_Complete_2":
			dialog.text = "Sì, sì, "+GetSexPhrase("mio figlio","mia figlia")+", naturalmente. Ti ricompenserò come meriti. Prendi questo e ricorda che il nostro Signore punisce quelle anime stolte, che desiderano troppo le benedizioni terrene e adorano il diavolo giallo!";
			link.l1 = "Grazie, "+LinkRandPhrase("Padre","Padre","santo Padre")+". Prendi i tuoi attesi libri e manoscritti e prega per la mia anima peccatrice... Addio!";
			link.l1.go = "GenQuest_Church_1_Complete_3";
		break;
			
		case "GenQuest_Church_1_Complete_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			RemoveItems(PChar, "Bible", 1);
			items[FindItem("Bible")].Name = "itmname_bible";
			BackItemDescribe("Bible");
			DeleteAttribute(items[FindItem("Bible")], "City");
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddCharacterExpToSkill(PChar, "Leadership", 50); // Бонус в авторитет
			AddCharacterExpToSkill(PChar, "Fortune", 50); // Бонус в удачу
			TakeNItems(pchar, "chest", 3+hrand(1));
			PlaySound("interface\important_item.wav");
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
			Group_DeleteGroup("ChurchGenQuest1_CapGroup"); // Трем кэпа
			PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; // Завершаем, если вдруг осталось
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
			break;
		// <-- Church GenQuest_1

        case "healthAdd_1":
            if (stf(pchar.Health.maxHP) == 60.0) // отлично
            {
                dialog.text = "La tua salute è "+GetHealthNameMaxSmall(pchar)+", e le ferite si chiuderanno da sole. Devi solo evitare il spargimento di sangue e prenderti cura della tua salute.";
    			link.l1 = "Grazie, è sicuramente un sollievo. Cercherò di astenermi dalle lotte per un po'.";
    			link.l1.go = "exit";
            }
            else
            {
    			dialog.text = "La tua salute è "+GetHealthNameMaxSmall(pchar)+", e anche se le ferite si rimargineranno da sole, dovresti prenderne cura.";
    			link.l1 = "Cosa serve per questo?";
    			link.l1.go = "healthAdd_2";
			}
			link.l2 = "E perché la mia salute peggiora?";
    		link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = "È molto semplice, "+GetSexPhrase("mio figlio","mia figlia")+". Ogni volta che vieni ferito, subisci danni. Questo non passa senza lasciare traccia. La tua salute peggiora con ogni ferita e, di conseguenza, diventi più debole. Il tuo equipaggio, vedendo un capitano debole, perde rispetto per te. Tuttavia, diventi più attento, e la tua capacità di difenderti aumenta temporaneamente. Riposo e minimizzazione delle ferite ti aiuteranno a mantenerti pieno di forza.";
			link.l1 = "Grazie per l'illuminazione.";
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = "Preghiere e astensione dalla violenza, "+GetSexPhrase("mio figlio","mia figlia")+". Allora il Signore ti restituirà ciò che hai perso.";
			link.l1 = "Ma potresti pregare per me?";
			link.l1.go = "healthAdd_3";
			link.l2 = "Quindi non c'è modo? Hmm... Mi hai davvero rassicurato, grazie.";
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
            if (npchar.quest.HealthMonth != iMonth)
            {
    			dialog.text = "Io? È probabile che sia possibile. Ma dovrai fare una donazione alla nostra parrocchia.";
    			link.l1 = pcharrepphrase("Quanto costa?","Volentieri! Quanto?");
    			link.l1.go = "healthAdd_4";
    			link.l2 = "Credo che me la caverò da solo...";
    			link.l2.go = "exit";
			}
			else
			{
                dialog.text = ""+GetSexPhrase("Mio figlio","Mia figlia")+", Sto già pregando per il tuo benessere. Queste preghiere mi occuperanno tutto il tempo fino alla fine del mese.";
    			link.l1 = "Grazie, "+RandPhraseSimple("padre.","Santo Padre.");
    			link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = "Cento mila pesos saranno un pagamento sufficiente per il miracolo della guarigione.";
			link.l1 = pcharrepphrase("Cosa?!! Sei completamente pazzo? Pagherei una tale somma solo dopo aver derubato un paio di chiese!","È troppo per me. Dicono la verità - la salute non può essere comprata con i soldi.");
			link.l1.go = "exit";
            if (sti(pchar.Money) >= 100000)
            {
    			link.l2 = "Sono d'accordo!";
    			link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
            AddMoneyToCharacter(pchar, -100000);
            AddCharacterMaxHealth(pchar, 4); // можно не проверять, тк явно меньше 51
            npchar.quest.HealthMonth = iMonth;
			dialog.text = "Bene. La tua salute migliorerà un po'. Ma devi ancora evitare le schermaglie e prenderti cura di te stesso, o questo effetto svanirà. Dovrò passare un intero mese in preghiere per il tuo corpo peribile.";
			link.l1 = "Grazie. Se succede qualcosa, tornerò a vederti tra un mese.";
			link.l1.go = "exit";
		break;
		
		//квест пожертвования хозяйки борделя
		case "HostessChurch":
			dialog.text = "E chi è quell'anima gentile che dona i soldi?";
			link.l1 = "Hmm... Quella è la madama del bordello locale.";
			link.l1.go = "HostessChurch_call";
			link.l2 = "Preferirei tenere i nomi segreti. Può esserci una donazione anonima, giusto?";
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return"; //флаг на возвращение
		break;
		
		case "HostessChurch_call":
			if (isBadReputation(pchar, 5)) 
			{
				if (rand(100) < GetCharacterSkill(pchar, "Fortune")) //рендом вешаем на удачу
				{
					dialog.text = "Sei un peccatore, eppure per un peccatore chiedi? Faresti meglio a pensare prima alla tua anima, infatti tutti noi appariremo davanti al Signore!";
					link.l1 = "È vero. Spero che il nostro Signore mi sarà misericordioso... Allora, riguardo alla donazione?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Vattene dietro di me, Satana!!! Prendi i tuoi soldi impuri e vattene!";
					link.l1 = "Come mai, Padre?! Siamo venuti da te con il cuore aperto, e tu...";
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) //рендом вешаем на харизму
				{
					dialog.text = "Sono contento che tu stia aiutando i peccatori a trovare la via verso il nostro Signore. Per questo sarai debitamente ricompensato in Paradiso!";
					link.l1 = "Sarebbe fantastico! Allora, che ne dici della donazione?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Non posso accettare denaro procurato nel peccato. Restituiscilo a quella donna caduta, "+GetSexPhrase("mio figlio","mia figlia")+". Nessuno può trovare una via verso Dio attraverso il denaro.";
					link.l1 = "È un peccato che tu la stia respingendo. Un vero peccato.";
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		
		case "HostessChurch_notCall":
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				dialog.text = "Prendere questi soldi, senza nemmeno sapere, da dove provengono...";
				link.l1 = "Sì, padre, esattamente. Per favore, accetta questo contributo, fatto dal cuore!";
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = "Prendere questi soldi, senza nemmeno sapere da dove vengono? Sei pazzo?! E se questi soldi fossero macchiati di sangue!";
				link.l1 = "Padre, tutti i soldi sono macchiati di sangue...";
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = "Lo accetto, "+GetSexPhrase("mio figlio","mia figlia")+". Vai e racconta che la tua donna è caduta.";
			link.l1 = "Bene, padre. Grazie.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_ok_1":
			dialog.text = "Lo accetto, "+GetSexPhrase("mio figlio","mia figlia")+". Parla di questo tuo benefattore.";
			link.l1 = "Bene, padre. Grazie.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_bad":
			dialog.text = "Vattene, prole dell'Inferno, e non osare mostrare di nuovo il tuo volto qui!";
			link.l1 = "Eh, come desideri.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_1":
			dialog.text = "Questa è la mia decisione. Vai in pace, "+GetSexPhrase("mio figlio","mia figlia")+".";
			link.l1 = "Addio, padre.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_2":
			dialog.text = "È questo che pensi, blasfemo?! Lascia il tempio immediatamente e non osare mostrare più il tuo volto qui!";
			link.l1 = "Oh, davvero? Non importa, me ne vado...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;

		//--> Jason Церковная депеша
		case "Monkletter":
			if (CheckAttribute(pchar, "GenQuest.Monkletter.Late"))
			{
				dialog.text = "Avevo quasi perso la speranza di rivedere questi documenti. Perché ci hai messo così tanto tempo, mio figlio?";
				link.l1 = "Sono stati... sviluppi imprevisti, Padre.";
				link.l1.go = "Monkletter_1";
			}
			else
			{
				dialog.text = "Stavo aspettando questi documenti, figlio mio. Grazie per la consegna rapida. Per favore, accetta queste monete e vai con la mia benedizione.";
				link.l1 = "Grazie, Padre. È stato un piacere per me aiutare la Santa Chiesa!";
				link.l1.go = "Monkletter_3";
			}
		break;
		
		case "Monkletter_1":
			dialog.text = "Siamo tutti nelle mani di Dio, mio figlio... L'uomo propone, ma Dio dispone. Dammi questi documenti e vai in pace.";
			link.l1 = "Ecco a te, padre. Tutto il meglio a te!";
			link.l1.go = "Monkletter_2";
		break;
		
		case "Monkletter_2":
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "2");
			CloseQuestHeader("Monkletter");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter_3":
			dialog.text = "La benedizione di Dio, mio figlio. Possa l'Onnipotente vegliare su di te nei tuoi viaggi!";
			link.l1 = "Arrivederci, Padre.";
			link.l1.go = "Monkletter_4";
		break;
		
		case "Monkletter_4":
			pchar.quest.Monkletter_Over.over = "yes"; //снять таймер
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "3");
			CloseQuestHeader("Monkletter");
			TakeNItems(pchar, "gold_dublon", 10+rand(5));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
			addLiberMisBonus();
		break;
		//<-- Церковная депеша
		
		//--> Jason Доставить молитвенники
		case "Churchbooks":
			dialog.text = "Sei stato inviato a prenderci i libri di preghiera - per la chiesa di "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity+"Gen")+"? Bene. Ho un pacco con trenta libri di preghiera. Prendilo, mio figlio.";
			link.l1 = "Grazie, padre. Addio!";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			dialog.text = "Che il Signore vegli su di te nei tuoi viaggi! Vai in pace...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Churchbooks", "2");
			pchar.GenQuest.Churchbooks = "return";
			GiveItem2Character(pchar, "prayer_book");//поставить соотв.предмет
		break;
		
		case "Churchbooks_2":
			if (CheckAttribute(pchar, "GenQuest.Churchbooks.Late"))
			{
				dialog.text = "Grazie per il tuo aiuto, mio figlio, anche se è arrivato con un certo ritardo.";
				link.l1 = "Sono stato ritardato da sviluppi imprevisti, Padre.";
				link.l1.go = "Churchbooks_3";
			}
			else
			{
				dialog.text = "Grazie per il tuo aiuto, mio figlio. Hai portato questi libri appena in tempo. Per favore, accetta questo amuleto santificato come ricompensa - ti salverà dal pericolo nell'ora più buia.";
				link.l1 = "Grazie, Padre. È stato un piacere aiutare la Santa Chiesa!";
				link.l1.go = "Churchbooks_4";
			}
		break;
		
		case "Churchbooks_3":
			dialog.text = "È tutto nelle mani di Dio, mio figlio. Vai in pace!";
			link.l1 = "Arrivederci, padre.";
			link.l1.go = "exit";
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			AddQuestRecord("Churchbooks", "3");
			CloseQuestHeader("Churchbooks");
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;
		
		case "Churchbooks_4":
			dialog.text = "La benedizione di Dio, mio figlio. Possa l'Onnipotente proteggerti dai pericoli sul tuo cammino!";
			link.l1 = "Addio, Padre.";
			link.l1.go = "Churchbooks_5";
		break;
		
		case "Churchbooks_5":
			pchar.quest.Churchbooks_Over.over = "yes"; //снять таймер patch-5
			DialogExit();
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			GiveItem2Character(pchar, pchar.GenQuest.Churchbooks.Item);
			Log_Info("You have received '"+XI_ConvertString(pchar.GenQuest.Churchbooks.Item)+"'");
			AddQuestRecord("Churchbooks", "4");
			CloseQuestHeader("Churchbooks");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
			addLiberMisBonus();
		break;
	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	DeleteAttribute(rItem, "City");
	rItem.Weight = 2;
	rItem.Name = "itmname_Bible";
	rItem.picIndex = 6;
	rItem.picTexture = "ITEMS_9";
	BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr); 
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
	PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;
	
	// Чтоб жизнь медом не казалась... Какие сцены будут в квесте, определяем в самом начале.
	int iRand = Rand(2);
	switch(iRand)
	{
		case "0":
			PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2A (just pick up the manuscript from the priest)."); 
		break;
		
		case "1":
			PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-A (search for a cap. There is full information about him).");
		break;
		
		case "2": // Этот флаг уже не проверяем, т.к. если нет тех, что выше, по-любому есть этот
			PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-B (search for a cap. The name of the ship is unknown)."); 
		break;
	}
}
