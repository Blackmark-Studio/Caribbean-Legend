void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
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
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		case "Alonso":
			NextDiag.TempNode = "Alonso";
			
			if (GetDLCenabled(DLC_APPID_1))
			{
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FirstStage", "ready"))
				{
					dialog.text = "Posso parlare, capitano?";
					link.l1 = "Più tardi, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Avanti.";
					link.l2.go = "Alonso_1";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.SecondStage", "ready"))
				{
					dialog.text = "Posso parlare, capitano?";
					link.l1 = "Più tardi, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Avanti.";
					link.l2.go = "Alonso_Lvl_8_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.ThirdStage", "ready"))
				{
					dialog.text = "Posso parlare, capitano?";
					link.l1 = "Più tardi, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Avanti.";
					link.l2.go = "Alonso_Lvl_12_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FourthStage", "ready"))
				{
					dialog.text = "Posso parlare, capitano?";
					link.l1 = "Più tardi, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Avanti.";
					link.l2.go = "Alonso_Lvl_16_Start";
					break;
				}
			}
			
			dialog.text = "Niente da segnalare, capitano.";
			link.l1 = "Continua così, Alonso.";
			link.l1.go = "exit";
		break;
		
		case "Alonso_1":
			DelLandQuestMark(npchar);
			dialog.text = "Come ve la cavate?";
			link.l1 = "Che intendi?";
			link.l1.go = "Alonso_2";
		break;
		
		// Основная развилка стадии 1
        case "Alonso_2":
            dialog.text = "Sono mesi che solcate questi mari caraibici, mentre alcuni non sopravvivono neanche una settimana. L'equipaggio vi rispetta, questo è certo, ma io? Io mi preoccupo per il vostro futuro.\n"+
                          "Condividete i vostri pensieri, fatelo per l'equipaggio. Dove è diretta la "+pchar.ship.name+"?";
                          
            link.l1 = "Non ho un piano. Prima voglio conoscere queste acque. L'avventura ci troverà da sola.";
            link.l1.go = "Alonso_Choice_1";
            
            link.l2 = "Queste acque sono piene di predatori, Alonso. E la "+pchar.ship.name+" è il più piccolo di loro. Per ora.";
            link.l2.go = "Alonso_Choice_2";
            
            link.l3 = "Mi piace fare soldi. Preferibilmente in modo legale. Ma vedremo come andrà.";
            link.l3.go = "Alonso_Choice_3";
			
            if (!SandBoxMode)
            {
                link.l4 = "Lo sai bene. Dopo quella memorabile conversazione sull'Ulisse, tutto si è solo complicato…";
                link.l4.go = "Alonso_Choice_4";
            }
        break;
        
        case "Alonso_Choice_1":
            dialog.text = "Ecco la libertà! L'importante è avere abbastanza per mantenere la nave e tenere qualcosa nei forzieri per i tempi duri.\n"+
                          "Dovunque vi porti l'umore, la missione o la mappa del tesoro - prendete passeggeri, carichi, qualsiasi lavoretto capiti sulla vostra strada.\n"+
                          "Un po' di piccolo commercio non guasta - comprate a poco dove conviene, vendete dove potete.\n"+
                          "E se per strada vedete un mercante solitario… Eh. Avete ragione, capitano. L'avventura ci troverà davvero.";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50);
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            
            link.l1 = "Grazie per il buon consiglio, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_2":
            dialog.text = "Affare redditizio, se la nave lo permette. Trovate i mercanti solitari e mostrate loro cosa significa davvero 'chi più spende meno spende'.\n"+
                          "Sfortunatamente per voi, entra in gioco un altro detto: 'La verità viene sempre a galla'. C'è sempre una lingua lunga nell'equipaggio che spiffererà le vostre imprese al primo porto.\n"+
                          "Quindi o derubate tutte le bandiere un po', o scegliete il vostro nemico per la vita.\n"+
                          "Anche se forse mi sto portando avanti. Se le cose si mettono davvero male, a Port Royal c'è un avvocato che per dei bei pesos risolve qualsiasi problema con le autorità. Chiamiamola tassa sulla pirateria, eh eh!";
            
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", -1);
            
            link.l1 = "Grazie per il buon consiglio, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_3":
            dialog.text = "Eh, qui non posso aiutarvi molto, capitano. Vi serve una vera nave mercantile: un brigantino goletta, o meglio ancora, un bark. Probabilmente me ne pentirò, ma meglio montare cannoni leggeri o buttarli del tutto.\n"+
                          "Prendete contratti di carico dai negozianti, commerciate per conto vostro lungo la strada e trasportate passeggeri.\n"+
                          "Quando avrete risparmiato abbastanza, investite in negozi e banche. Vedrete, capitano - arriverà il giorno in cui i vostri soldi faranno soldi, e potrete permettervi una grande nave con duecento uomini a bordo.\n"+
                          "Per la quale, tra l'altro, non pagherete voi, ma i vostri affari.";
            
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            AddCharacterExpToSkill(pchar, SKILL_SAILING, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "Grazie per il buon consiglio, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_4":
            dialog.text = "Io la vedo diversamente, capitano. Sull'Ulisse eravate solo un passeggero - quelle povere anime non hanno controllo sul loro destino. Ora siete un capitano che si è guadagnato il suo cappello, il che significa che potete risolvere qualsiasi problema. Ve l'ho già detto - non c'è posizione più alta nel nostro mondo.\n"+
                          "Il mio istinto mi dice che questa epopea con vostro fratello durerà ancora anni, quindi pensate prima a voi stesso. Monsieur Michel non andrà da nessuna parte, eh eh…\n"+
                          "Non siete l'unico con problemi nei Caraibi. È il momento perfetto per aiutare gli altri mentre guadagnate denaro, equipaggiamento e contatti. Imparerete tutto ciò che vi servirà per questa faccenda di famiglia lungo la strada…";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 100);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "Grazie per il buon consiglio, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
		
        case "Alonso_Common_End":
            dialog.text = "Non limitatevi a un solo ruolo, capitano. Fate solo quello che volete. Prendete tutto e non restituite niente. Andrà tutto bene.";
            link.l1 = "E grazie anche per le parole di saggezza.";
            link.l1.go = "Alonso_Common_End_2";
        break;
        
        case "Alonso_Common_End_2":
            dialog.text = "Eh, per questo mi pagate, capitano. Pensate che all'equipaggio basti la misera paga per eseguire i vostri ordini?\n"+
                          "Dozzine di uomini ammassati in spazi angusti, senza sapere quando vedranno terra, o se la vedranno. E affondare una nave? Un gioco da ragazzi.";
            link.l1 = "Sì, sì, conosco questo discorso, Alonso. Cosa dicevi delle navi?";
            link.l1.go = "Alonso_Common_End_3";
        break;
        
        case "Alonso_Common_End_3":
            dialog.text = "Eh! Una nave è una prigione, un accampamento militare e un monastero tutto insieme. Un raduno di uomini, insomma. Quindi i problemi si risolvono o con le parole o con la frusta. Nel vostro caso, la seconda, eh eh, non è un'opzione, così ho pensato di fare due chiacchiere. Per rendervi le cose più facili, diciamo.";
            link.l1 = "Sei mai stato in prigione? Nell'esercito? In un monastero, Dio ce ne scampi? E comunque, Alonso, parlami di te. Non so quasi niente di te.";
            link.l1.go = "Alonso_Story_1";
        break;
        
        // История Алонсо
        case "Alonso_Story_1":
            dialog.text = "Beh, i monasteri li ho evitati, non mentirò. Anche se ho servito nella Santa Inquisizione una volta…";
            link.l1 = "Come diavolo è successo?";
            link.l1.go = "Alonso_Story_2";
        break;
        
        case "Alonso_Story_2":
            dialog.text = "Oh! È andata così. Tiravo avanti come mercenario nella guerra europea. Il diavolo sa come è iniziata o chi combatteva contro chi. Sapevamo solo che la guerra durava da trent'anni e quale comandante pagava più o meno regolarmente. Quella sì che era un'avventura!\n"+
                          "Era nel '42… o era il '41? Non importa. Due compagnie, entrambe al servizio dell'Imperatore, si incontrarono in una foresta. Nella nebbia. E iniziarono a farsi a pezzi! Tre giorni di massacro!";
            link.l1 = "Com'è possibile?";
            link.l1.go = "Alonso_Story_3";
        break;
        
        case "Alonso_Story_3":
            dialog.text = "Prova a distinguere amico da nemico in quella nebbia. E poi non ci pagavano da tre mesi, quindi tutti pensavano al bottino.\n"+
                          "Ci siamo ammazzati a metà a vicenda. Quando ce ne siamo accorti, era troppo tardi. È lì che ho conosciuto questo moscovita. Grande come un orso, ma con un cuore d'oro!";
            link.l1 = "E poi cosa è successo?";
            link.l1.go = "Alonso_Story_4";
        break;
        
        case "Alonso_Story_4":
            dialog.text = "Sapete com'è in guerra? Il primo a riferire è l'eroe. Così abbiamo pensato - tanto vale trarre vantaggio da questo disastro!\n"+
                          "Ci siamo messi d'accordo con i ragazzi, siamo andati dal pagatore, abbiamo riferito di una 'gloriosa battaglia'. Ai morti tagliarono la paga, ai sopravvissuti pagarono, io e il mio amico ricevemmo dei bonus, e il comandante la sua parte.";
            link.l1 = "Allora sei ricco, Alonso.";
            link.l1.go = "Alonso_Story_5";
        break;
        
        case "Alonso_Story_5":
            dialog.text = "Ah! Poi abbiamo passato una settimana a bere vino e giocare a carte. Per fortuna, il mio nuovo amico dal lontano regno di Mosca aveva un debole per le cose rare, altrimenti sarei finito in prigione per debiti. Mi comprò un trofeo: una magnifica pistola a tre canne, e a buon prezzo. Non approfittò della mia sfortuna.";
            link.l1 = "Una storia fantastica, Alonso. Mi sembra che te la sia appena inventata.";
            link.l1.go = "Alonso_Gift";
        break;
        
        // Вручение подарка
        case "Alonso_Gift":
            dialog.text = "Mi offendete, capitano. Ecco, prendete questo piccolo regalo.";
            link.l1 = "Cos'è?";
            link.l1.go = "Alonso_Gift_2";
        break;
        
        case "Alonso_Gift_2":
            // Выдаем Берендейку
            GiveItem2Character(pchar, "talisman20");
			SetAlchemyRecipeKnown("talisman20");
            
            dialog.text = "Una bandoliera per il combattimento con moschetto. Nella patria del mio amico moscovita tutti ne portano una. O almeno così diceva.\n"+
                          "Che vi serva bene, capitano. Consideratelo un regalo dell'equipaggio.";
            link.l1 = "Inaspettato! Grazie, Alonso. Allora, che mi dici del tuo servizio nell'Inquisizione?";
            link.l1.go = "Alonso_Escape";
        break;
        
        case "Alonso_Escape":
            PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Eh…\n"+
                          "Suonano le campane, capitano! È ora di tornare al lavoro. Continueremo un'altra volta.";
            link.l1 = "Continueremo sicuramente questa conversazione. Grazie per il regalo!";
            link.l1.go = "exit";
            
			AddDialogExitQuestFunction("LoyaltyPack_FirstStage_DlgExit");
        break;
		
		// (Уровень 8) - Продолжаем историю
        case "Alonso_Lvl_8_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Avete realizzato molto dalla nostra ultima conversazione, e nessuno - né l'equipaggio, né io - dubita più dei vostri talenti.";
			link.l1 = "C'erano dubbi?";
			link.l1.go = "Alonso_Lvl_8_1";
        break;

        case "Alonso_Lvl_8_1":
            dialog.text = "Certo che c'erano. Siamo gente semplice - abituati a prepararci al peggio. Godetevi la libertà, capitano. Continuate così e vedrete un lato completamente diverso dei Caraibi.";
            link.l1 = "Piacere di sentirlo. Ora raccontami del tuo servizio nell'Inquisizione. L'ultima volta hai iniziato con una storia dell'esercito e hai finito con quella.";
            link.l1.go = "Alonso_Lvl_8_2";
        break;

        case "Alonso_Lvl_8_2":
            dialog.text = "Cosa c'è da raccontare? Dopo quel massacro insensato ma molto redditizio nella foresta, io e il moscovita diventammo amici per la pelle e combinammo parecchi altri affari.\n"+
                          "Ricordo che una volta decidemmo di assaltare un convoglio imperiale. Gli esploratori dissero che trasportavano trofei, oro, armi...";
            link.l1 = "E allora, ci siete riusciti?";
            link.l1.go = "Alonso_Lvl_8_3";
        break;

        case "Alonso_Lvl_8_3":
            dialog.text = "Gioco da ragazzi. Attaccammo da due lati, dispersero le guardie, aprimmo i carri - e trovammo cavoli! Cavoli marci e puzzolenti per qualche guarnigione! Ma sapete cosa? Non mangiavamo da una settimana, quindi fummo felici anche di quello!";
            link.l1 = "Come se sul mio vascello si mangiasse meglio.";
            link.l1.go = "Alonso_Lvl_8_4";
        break;

        case "Alonso_Lvl_8_4":
            dialog.text = "Beh, ora ci sono abituato. Ma allora… Dopo una settimana di foraggiamento, avresti rosicchiato la corteccia dagli alberi!\n"+
                          "Ma il mio amico non si perse d'animo. Tirò fuori una fiaschetta con il suo intruglio speciale - ricetta moscovita, disse. A noi non importava, purché non fosse aceto! Dopo qualche sorso, anche quel cavolo sembrava una prelibatezza!";
            link.l1 = "Disgustoso.";
            link.l1.go = "Alonso_Lvl_8_5";
        break;

        case "Alonso_Lvl_8_5":
            dialog.text = "Disgustoso è lo stato dei nostri barili d'acqua, ma quella sbobba moscovita mi salvò la vita quel giorno.";
            link.l1 = "Come sarebbe?";
            link.l1.go = "Alonso_Lvl_8_6";
        break;

        case "Alonso_Lvl_8_6":
            dialog.text = "Ci ubriacammo da morire proprio lì nel fango della strada con i cavoli che galleggiavano. Beh, una parola tira l'altra, e litigai con un nobiluzzo. Un tedesco, tutto azzimato e impettito. Troppo fine per bere con noi, puliva solo il suo moschetto e lanciava frecciatine.\n"+
                          "Quindi siamo lì seduti, riposiamo, affoghiamo i dispiaceri sopra i cavoli. E lui inizia a farci la predica sulla saggezza militare. Dice che le nostre fidate spade e picche saranno presto dimenticate, ma la baionetta - quello è il futuro e la chiave di tutto.\n"+
                          "Così litigai con lui, e in qualche modo ci accordammo per combattere fino alla morte - con le baionette, nientemeno. Non chiedetemi come è successo, non me lo ricordo nemmeno io.\n"+
                          "Ma di baionette in tutta la compagnia ce n'erano solo due. Una di quell'ufficialetto, l'altra di Fox, un inglese. Presi in prestito il suo fucile e massacrai il tedesco fino ad ammazzarlo, poi me la svignai.";
            link.l1 = "Ma eri affamato e ubriaco.";
            link.l1.go = "Alonso_Lvl_8_7";
        break;

        case "Alonso_Lvl_8_7":
            dialog.text = "Capii dopo che l'intruglio del mio amico davvero stabilizza la mano quando maneggi un pesante moschetto. Quindi ora sono più propenso a concordare con le idee del tedesco morto.";
            link.l1 = "E cosa c'entra questo con il tuo servizio nell'Inquisizione?";
            link.l1.go = "Alonso_Lvl_8_Gift";
        break;

        case "Alonso_Lvl_8_Gift":
            dialog.text = "Non mi credete di nuovo, capitano! Ecco, prendete questo.";
            link.l1 = "Una bottiglia e un foglio di carta?";
            link.l1.go = "Alonso_Lvl_8_Gift_2";
        break;

        case "Alonso_Lvl_8_Gift_2":
            // Даём игроку настойку и рецепт
            GiveItem2Character(pchar, "vodka");
            SetAlchemyRecipeKnown("vodka");

            dialog.text = "È l'intruglio di cui vi parlavo. E la ricetta. Nel caso vi piaccia, eh eh.";
            link.l1 = "Scusa, amico mio, ma scarabocchi e qualche intruglio torbido non…";
            link.l1.go = "Alonso_Lvl_8_Gift_3";
        break;

        case "Alonso_Lvl_8_Gift_3":
            // Даём игроку мушкет с багинетом
            GiveItem2Character(pchar, "mushket10");

            dialog.text = "Va bene, va bene, capitano. Volevo regalarvelo comunque. Questo tipo di arma non fa per me, ma voi la troverete utile. Le baionette sono bestie rare. Ma una volta che imparerete a usarla, dimenticherete le sciabole.";
            link.l1 = "Aspetta, è il moschetto di quell'ufficiale imperiale? Quello che hai ucciso?";
            link.l1.go = "Alonso_Lvl_8_Gift_4";
        break;

        case "Alonso_Lvl_8_Gift_4":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Proprio quello. Come vedete, vi ho detto la verità, capitano.";
            link.l1 = "Ma non è questo che chiedevo.";
            link.l1.go = "Alonso_Lvl_8_Escape";
        break;

        case "Alonso_Lvl_8_Escape":
            dialog.text = "Suonano le campane, capitano! È ora di tornare al lavoro. Continueremo un'altra volta.";
            link.l1 = "Continueremo sicuramente questa conversazione. Grazie per il moschetto!";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_SecondStage_DlgExit");
        break;

        // (Уровень 12)
        case "Alonso_Lvl_12_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Capitano, riguardo alle nuove reclute...";
			link.l1 = "È successo qualcosa?";
			link.l1.go = "Alonso_Lvl_12_1";
        break;

        case "Alonso_Lvl_12_1":
            dialog.text = "Volevo riferirvi che a cena una delle reclute ha menzionato che voleva arruolarsi specificamente sulla vostra nave.";
            link.l1 = "E cosa significa esattamente?";
            link.l1.go = "Alonso_Lvl_12_2";
        break;

        case "Alonso_Lvl_12_2":
            dialog.text = "Che presto potrebbero essercene altri come lui. Ora avete un nome, capitano.";
            link.l1 = "Strano che ancora non sappia cosa si nasconde dietro il tuo nome. E quella storia sull'Inquisizione non l'hai mai finita.";
            link.l1.go = "Alonso_Lvl_12_3";
        break;

        case "Alonso_Lvl_12_3":
            dialog.text = "Oh, dove ero rimasto... Giusto! Decidemmo di diventare fornitori militari. La guerra stava finendo, bisognava pensare al futuro. E il mio amico aveva sempre la testa piena di piani per il futuro.";
            link.l1 = "È un bel salto di carriera. Poco prima vi ubriacavate vicino a un carro saccheggiato pieno di cavoli.";
            link.l1.go = "Alonso_Lvl_12_4";
        break;

        case "Alonso_Lvl_12_4":
            dialog.text = "E allora? Ricevemmo un ordine per cento elmi per qualche reggimento. Ci diedero un buon anticipo. Ci rallegrammo, andammo a festeggiare... Giocammo a carte.\n"+
                          "La mattina ci svegliamo --- l'anticipo è sparito, l'esercito parte tra due giorni, e noi non abbiamo neanche un elmo!";
            link.l1 = "E cosa avete fatto?";
            link.l1.go = "Alonso_Lvl_12_5";
        break;

        case "Alonso_Lvl_12_5":
            dialog.text = "Andammo sul campo di battaglia fresco, raccogliemmo cappelli dai morti. Poi inchiodammo pezzi di metallo vari, attaccammo piastre... Sembrava ridicolo, ma funzionava! Poteva salvare da un colpo di sciabola. Beh, almeno una volta di sicuro. Buono come qualsiasi elmo, no?!";
            link.l1 = "Il quartiermastro ha apprezzato la vostra ingegnosità?";
            link.l1.go = "Alonso_Lvl_12_6";
        break;

        case "Alonso_Lvl_12_6":
            dialog.text = "Ci mandò al tribunale per appropriazione indebita e frode. Ma sapete cosa? I soldati dissero poi che quei cappelli salvarono loro la vita più di una volta. E anche la nostra, come si scoprì.";
            link.l1 = "Come sarebbe?";
            link.l1.go = "Alonso_Lvl_12_7";
        break;

        case "Alonso_Lvl_12_7":
            dialog.text = "Beh, finimmo entrambi in prigione. E la nostra compagnia fu mandata in missione. Non so dove o contro chi, e probabilmente non lo sapevano neanche loro. Non tornarono mai.\n"+
                          "...\n"+
                          "Scusate, capitano. Continueremo un'altra volta. Prendete questo cappello e le istruzioni. L'ho fatto ieri per rallegrarvi... Ma mi sono solo rattristato per niente.";
            link.l1 = "Certamente, Alonso. Grazie per il regalo.";
            link.l1.go = "Alonso_Lvl_12_Gift";
        break;

        case "Alonso_Lvl_12_Gift":
            // Даём игроку шляпу
            GiveItem2Character(pchar, "hat10");
            SetAlchemyRecipeKnown("Hat10");

            DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_ThirdStage_DlgExit");
        break;

        // (Уровень 16) - Финальный
        case "Alonso_Lvl_16_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Capitano, volevo solo riferire che il vostro equipaggio riceve il trattamento reale nelle taverne e nei bordelli ora. Servire sotto la vostra bandiera significa qualcosa di questi tempi!";
			link.l1 = "Grazie, Alonso... Peccato che io non stia ancora vedendo molto di questo trattamento reale per me stesso.";
			link.l1.go = "Alonso_Lvl_16_1";
        break;

        case "Alonso_Lvl_16_1":
            dialog.text = "Lo vedrete presto. I Caraibi sono una torta divisa tra poche dozzine di capitani. Presto avrete un posto a quel tavolo e prenderete la vostra fetta.\n"+
                          "E chi lo sa? Forse sarete voi la leggenda dei Caraibi che prenderà tutta la torta.";
            link.l1 = "Allora finirai la tua storia? Ci siamo fermati dove sei finito in prigione.";
            link.l1.go = "Alonso_Lvl_16_2";
        break;

        case "Alonso_Lvl_16_2":
            dialog.text = "Ah! Il caso dei grandi ladri di cappelli. Un moscovita e un portoghese in una cella minuscola da qualche parte nelle Fiandre. In attesa di sentenza. Di morte, naturalmente.\n"+
                          "Ci salvò un signore importante - risultò essere l'ambasciatore moscovita! Vecchio amico di Fadey. Era di passaggio, seppe della nostra disgrazia, comprò la nostra libertà!";
            link.l1 = "Fadey? IL Fadey? E tu non hai detto niente?!";
            link.l1.go = "Alonso_Lvl_16_3";
        break;

        case "Alonso_Lvl_16_3":
            dialog.text = "Già. Lì ci separammo: lui tornò alla sua Mosca, o per combattere i polacchi o per grandi affari. Io girovagai ancora un po' per la vecchia patria, ed eccomi qui.";
            link.l1 = "Impressionante, Alonso. Tutto questo tempo e sei riuscito a raccontarmi di tutto tranne che di te stesso. Strano come un tipo furbo come te si sia lasciato sfuggire quella cosa dell'Inquisizione.";
            link.l1.go = "Alonso_Lvl_16_4";
        break;

        case "Alonso_Lvl_16_4":
            dialog.text = "E vi ho detto la pura verità, capitano! Non mi credete - chiedete a Fadey stesso. Non è difficile trovarlo a Basse-Terre.";
            link.l1 = "Forse lo farò. E il mio regalo?";
            link.l1.go = "Alonso_Lvl_16_5";
        break;

        case "Alonso_Lvl_16_5":
            dialog.text = "Eh?";
            link.l1 = "Mi hai fatto un regalo alla fine di ogni storia.";
            link.l1.go = "Alonso_Lvl_16_Escape";
        break;

        case "Alonso_Lvl_16_Escape":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Sentite? Suonano le campane. È ora di lavorare.";
            link.l1 = "Continua così, Alonso.";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_FourthStage_DlgExit");
        break;
	}
} 