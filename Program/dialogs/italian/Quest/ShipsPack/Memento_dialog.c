void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "Che cosa volete?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;

		// Диалог с Алонсо после успешного абордажа
		case "Memento_MortimerGrimDead_Alonso_1":
			dialog.text = "Capo, la giornata è nostra. L'avanguardia sta finendo di ripulire il ponte inferiore. Nessun prigioniero... Ah! Vedo che anche voi non avete avuto pietà.";
			link.l1 = "Per qualche motivo mi aspettav"+GetSexPhrase("o","a")+" un discorso pomposo da lui. E invece si è lanciato subito nella battaglia.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_2";
			Achievment_Set("ach_CL_154");
		break;

		case "Memento_MortimerGrimDead_Alonso_2":
			dialog.text = "Posso esprimere un'opinione?";
			link.l1 = "Permesso accordato.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_3";
			link.l2 = "No, abbiamo finito qui.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_end";
		break;

		case "Memento_MortimerGrimDead_Alonso_3":
			dialog.text = "Perché li abbiamo attaccati? Quel brigantino non rappresentava alcuna minaccia per noi, non trasportava merci. Su Grimm si dicevano molte cose, ma solo i trafficanti di schiavi lo temevano. Oggi avete fatto una strage – e per cosa, esattamente?";
			if (sti(pchar.questTemp.ISawDiegoDeLanda) >= 2)
			{
				link.l1 = "...";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_4";
			}
			else
			{
				link.l1 = "Parli a nome dell'equipaggio?";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
			}
		break;

		case "Memento_MortimerGrimDead_Alonso_4":
			dialog.text = "E non è la prima volta...";
			link.l1 = "Parli a nome dell'equipaggio?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
		break;

		case "Memento_MortimerGrimDead_Alonso_5":
			dialog.text = "No. Credetemi, se l'equipaggio avesse avuto simili domande, vorrebbe dire che non faccio bene il mio lavoro e voi sareste già un morto che cammina\n"+
			"Fortunatamente per voi, la gente ha fatto un bel bottino con questa sanguinosa avventura. Le tasche di ogni marinaio su questa nave erano piene zeppe di dobloni!\n"+
			"Non c'erano veri carichi di valore, solo cianfrusaglie indigene e amuleti inquietanti. Ma la ciurma si è comunque arricchita. Grimm, a quanto pare, pagava bene\n"+
			"Spero che non reclamerete la vostra parte di quell'oro, capo?";
			link.l1 = "Non lo farò, Alonso. Grazie per tenermi aggiornato.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_6";
			link.l2 = "Lo farò. Assicurati che la mia parte venga portata in cabina.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_7";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_6":
			dialog.text = "Sono sempre dalla vostra parte, capo. A proposito, cosa farete con la 'Memento'?";
			link.l1 = "La prenderò come bottino – cos'altro potrei fare?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Non ho ancora deciso"+GetSexPhrase("","a")+".";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
		break;

		case "Memento_MortimerGrimDead_Alonso_7":
			dialog.text = "Sono sempre dalla vostra parte, capo. A proposito, cosa farete con la 'Memento'?";
			link.l1 = "La prenderò come bottino – cos'altro potrei fare?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Non ho ancora deciso"+GetSexPhrase("","a")+".";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
			AddCrewMorale(Pchar, -10);
			AddItems(Pchar, "gold_dublon", 500);
		break;

		case "Memento_MortimerGrimDead_Alonso_8":
			dialog.text = "Meglio di no. È tutta ricoperta di simboli tribali strani. E ci sono voci brutte su di lei – dicono che abbia sopravvissuto a un'epidemia mostruosa, e che sui ponti danzassero i morti\n"+
			"E dello scheletro a poppa non parliamone nemmeno: finché qualche idiota non proverà a rubare quel teschio per vanteria, nessuno tranne me oserà fare la guardia laggiù.";
			link.l1 = "Ricevuto, Alonso. Torna al lavoro.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_9";
		break;

		case "Memento_MortimerGrimDead_Alonso_9":
			dialog.text = "Sì, capo.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_end";
		break;

		case "Memento_MortimerGrimDead_Alonso_end":
			DialogExit();
			AddDialogExitQuestFunction("Memento_MortimerGrimDead_Alonso_2");
		break;

		// Диалог с Алонсо в первую ночь
		case "Memento_Dich_EtapOne_Alonso_1":
			dialog.text = "Capitano, scusate se vi disturbo a quest'ora.";
			link.l1 = "Rapporto, Alonso.";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_2";
			if (CheckAttribute(pchar, "questTemp.Memento_Dich_EtapTwo"))
			{
				dialog.text = "Capitano? Che ci fate qui? Avete dormito qui?";
				link.l1 = "Non importa.";
				link.l1.go = "Memento_Dich_EtapTwo_Alonso_2";
				link.l2 = "Nella mia cabina è... inquietante.";
				link.l2.go = "Memento_Dich_EtapTwo_Alonso_2";
			}
		break;

		case "Memento_Dich_EtapOne_Alonso_2":
			dialog.text = "Le cose vanno male. L'umore dell'equipaggio è a terra! La gente dice apertamente che la nave è maledetta. Si lamentano di vedere cose strane di notte.";
			link.l1 = "Cosa vedono esattamente?";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_3";
		break;
		
		case "Memento_Dich_EtapOne_Alonso_3":
			dialog.text = "Incubi, a quanto pare. Ma il peggio è che uno dei nostri è morto di febbre. Un ragazzo giovane, forte — bruciato in poche ore.";
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				link.l1 = "Questo lo deciderà il medico. "+sld.name+" sa il fatto suo.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
			else
			{
				link.l1 = "Non è possibile. Tieni la ciurma sotto controllo, Alonso. È il tuo compito.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
		break;

		case "Memento_Dich_EtapOne_Alonso_4":
			dialog.text = "Agli ordini!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapOne_End");
		break;

		// Диалог с Алонсо во вторую ночь
		case "Memento_Dich_EtapTwo_Alonso_2":
			dialog.text = "Capisco. Molti dell’equipaggio ora dormono tutti insieme — hanno paura di restare soli. Come se fosse possibile rimanere davvero soli su una nave…";
			link.l1 = "Come vedi, non ci sono riuscito. Cos’è successo?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_3";
		break;

		case "Memento_Dich_EtapTwo_Alonso_3":
			dialog.text = "Una rissa — José ha accoltellato Marcel. Gridava che 'portava la peste'.";
			link.l1 = "La situazione è peggiorata?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_4";
		break;

		case "Memento_Dich_EtapTwo_Alonso_4":
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				dialog.text = ""sld.name+" vi ha già fatto rapporto stamattina. Abbiamo perso undici anime. Cosa facciamo?";
			}
			else
			{
				dialog.text = "Altre undici anime perse. Cosa facciamo?";
			}
			link.l1 = "Prenderò una decisione.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_5";
		break;

		case "Memento_Dich_EtapTwo_Alonso_5":
			dialog.text = "Spero bene, capitano. Che facciamo con José? L’omicidio non è uno scherzo.";
			link.l1 = "Impiccatelo dopo il grog. Faremo capire che la situazione è sotto controllo.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_6";
			link.l2 = "Trenta frustate. Se sopravvive — vuol dire che Dio l’ha voluto.";
			link.l2.go = "Memento_Dich_EtapTwo_Alonso_7";
		break;

		case "Memento_Dich_EtapTwo_Alonso_6":
			dialog.text = "Agli ordini!";
			link.l1 = "...";
			link.l1.go = "exit";
			SetCrewQuantity(pchar, GetCrewQuantity(pchar) - 1);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;

		case "Memento_Dich_EtapTwo_Alonso_7":
			dialog.text = "Agli ordini!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddCrewMorale(Pchar, -10);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;
		
		// Диалог с Алонсо в третью ночь
		case "Memento_Dich_EtapThree_AlonsoPrizrak_1":
			dialog.text = "Capo! Allarme!! Deve andare subito al ponte inferiore!";
			link.l1 = "Cosa è successo?";
			link.l1.go = "Memento_Dich_EtapThree_AlonsoPrizrak_2";
		break;
		
		case "Memento_Dich_EtapThree_AlonsoPrizrak_2":
			dialog.text = "È meglio che lo vediate con i vostri occhi. Andiamo, presto!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_4_1");
		break;
		
		// Уже утром
		case "Memento_Dich_EtapThree_Alonso_1":
			dialog.text = "Buongiorno, capo!";
			link.l1 = "Eh?!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_2";
		break;
		
		case "Memento_Dich_EtapThree_Alonso_2":
			dialog.text = "Ehm, non ha un bell'aspetto. Ha dormito male? Beh, adesso le darò una bella notizia. L'epidemia è finita. Anzi, si è scoperto che non c'è mai stata.";
			link.l1 = "Com'è possibile?";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_3";
		break;
		
		case "Memento_Dich_EtapThree_Alonso_3":
			dialog.text = "La gente si è fatta prendere dal panico, ha ascoltato troppe sciocchezze su una nave maledetta. Il potere dell'autosuggestione è tremendo, glielo assicuro. Ha già condannato più di una nave.";
			link.l1 = "Ma la gente è morta!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_4";
		break;
		
		case "Memento_Dich_EtapThree_Alonso_4":
			dialog.text = "Combattimenti, ferite sporche, carne salata andata a male — normale aritmetica marinaresca. Se non ci fossimo lasciati influenzare tanto dai racconti su navi maledette, chissà, forse avremmo perso un paio di uomini in meno\n"+
			"Lo scheletro a poppa non aiutava certo il morale. Per fortuna qualche… burlone gli ha rubato il cappello durante la notte\n"+
			"Visto che il sacrilegio non ha attirato un fulmine sulla nave, l'equipaggio si è un po' rincuorato e l'astuzia marinaresca ha cominciato a pianificare nuovi scherzi allo scheletro. Tipo questo...";
			link.l1 = "Non toccate lo scheletro!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_5";
		break;
		
		case "Memento_Dich_EtapThree_Alonso_5":
			dialog.text = "Ehm... Beh, se ha sviluppato dei sentimenti affettuosi per lui, allora certo, non lo toccheremo. Buona giornata, capo.\n"+
			"A proposito, ottimo cappello! Le sta davvero bene. Al precedente proprietario era chiaramente troppo piccolo.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_End");
		break;
		
		// Диалоги с командой Мементо
				case "Memento_Sailor_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Salve, capitano. Dovrebbe parlare con il capitano Grim.";
				link.l1 = "Scusa, marinaio, ma qui spicchi.";
				link.l1.go = "Memento_Sailor_1_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Altro, capitano?";
				link.l1 = "Niente.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_1";
		break;
		
		case "Memento_Sailor_1_1":
			dialog.text = "Capisco cosa intende, capitano. Ho servito sotto un capitano libero — proprio come lei. Cercava tesori, commerciava, trasportava merci. E decise di derubare dei mercanti — non andò bene. I sopravvissuti furono impiccati per pirateria.";
			link.l1 = "E il capitano Grim vi ha comprati?";
			link.l1.go = "Memento_Sailor_1_2";
		break;
		
		case "Memento_Sailor_1_2":
			dialog.text = "Ci ha comprati tutti insieme, come merce. Ogni nave ha bisogno di marinai esperti, e Grim non recluta nelle taverne ... Ma ci nutre e paga bene. E noi serviamo — e tiriamo a sorte.";
			link.l1 = "Il sorteggio?";
			link.l1.go = "Memento_Sailor_1_3";
		break;
		
		case "Memento_Sailor_1_3":
			dialog.text = "Mi scusi, non dovremmo parlarne.";
			link.l1 = "Perché non andate via?";
			link.l1.go = "Memento_Sailor_1_4";
		break;
		
		case "Memento_Sailor_1_4":
			dialog.text = "Dove? Qui almeno c'è una possibilità. Forse avrò fortuna. Ogni nave ha il suo sorteggio. Grim il suo, voi il vostro. Non siamo uomini, solo numeri nel registro di bordo.";
			link.l1 = "Sulla mia nave le regole sono diverse.";
			link.l1.go = "Memento_Sailor_1_5";
		break;
		
		case "Memento_Sailor_1_5":
			dialog.text = "Come vuole, capitano. Buona giornata.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_1";
		break;
		
		case "Memento_Sailor_2":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Era da tanto che non avevamo ospiti sulla nostra gloriosa nave!";
				link.l1 = "Sei un marinaio? Non ne hai l'aspetto.";
				link.l1.go = "Memento_Sailor_2_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Altro, capitano?";
				link.l1 = "Niente.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_2";
		break;
		
		case "Memento_Sailor_2_1":
			dialog.text = "Ah! Il capitano mi ha comprato direttamente dalla cella. Dovevano impiccarmi a Port Royal – ho accoltellato un ragazzino che recitava sempre poesie. Se l'è meritato, quel bastardo.";
			link.l1 = "Quindi ti è andata bene?";
			link.l1.go = "Memento_Sailor_2_2";
		break;
		
		case "Memento_Sailor_2_2":
			dialog.text = "Eccome! Il capitano non è tirchio, ma a volte bisogna partecipare ai suoi ... giochi.";
			link.l1 = "Che tipo di giochi?";
			link.l1.go = "Memento_Sailor_2_3";
		break;
		
		case "Memento_Sailor_2_3":
			dialog.text = "Ogni settimana peschiamo bastoncini: quello corto vuol dire lavoro pericoloso o, a volte, saltare fuori bordo. Divertente, insomma. Non per tutti, ma il capitano dice che così elimina gli indegni.";
			link.l1 = "Indegni di cosa?";
			link.l1.go = "Memento_Sailor_2_4";
		break;
		
		case "Memento_Sailor_2_4":
			dialog.text = "Che ne so io? Il capitano sa parlare, predica come un prete: «Solo affrontando la morte si può vivere davvero!»\n"+
			"(sputa)";
			link.l1 = "Per uno sputo sul ponte si prende la frusta. Ti comporti da bandito, non da marinaio. Addio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_2";
		break;
		
		case "Memento_Sailor_3":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Salve, capitano.";
				link.l1 = "Come sei arrivato qui?";
				link.l1.go = "Memento_Sailor_3_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Altro, capitano?";
				link.l1 = "Niente.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_3";
		break;
		
		case "Memento_Sailor_3_1":
			dialog.text = "Il capitano Grim ha catturato la nave negriera su cui mi trovavo. Ero malato, moribondo nella stiva ... non ricordo molto. Mi sono risvegliato qui, sulla Memento.";
			link.l1 = "E cosa è successo agli altri schiavi?";
			link.l1.go = "Memento_Sailor_3_2";
		break;
		
		case "Memento_Sailor_3_2":
			dialog.text = "Non lo so. Il capitano dice di aver liberato tutti, ma io ero l'unico portato a bordo. Gli altri, forse, si sono dispersi sulle isole o sono morti per le ferite. Ricordo poco di quel giorno.";
			link.l1 = "Almeno ora sei libero.";
			link.l1.go = "Memento_Sailor_3_3";
		break;
		
		case "Memento_Sailor_3_3":
			dialog.text = "Libero? Qui nessuno è libero. Il capitano dà oro, cibo, vestiti, ma in cambio pretende totale fedeltà — e ci fa pescare quella maledetta pagliuzza.";
			link.l1 = "Il sorteggio?";
			link.l1.go = "Memento_Sailor_3_4";
		break;
		
		case "Memento_Sailor_3_4":
			dialog.text = "Ogni settimana qualcuno pesca la pagliuzza corta e riceve un compito pericoloso – non tutti tornano. Il capitano dice che così si separano i vivi dai morti.";
			link.l1 = "E voi lo sopportate?";
			link.l1.go = "Memento_Sailor_3_5";
		break;
		
		case "Memento_Sailor_3_5":
			dialog.text = "Ognuno spera che la fortuna lo assista. Il capitano sa cosa muove ciascuno: paura della forca, avidità d'oro, desiderio di saldare un debito per la vita salvata. A me non interessa nulla di tutto ciò. Non mi servono soldi, e che debito puoi avere per qualcosa che non ricordi?";
			link.l1 = "Non hai paura a parlarne apertamente?";
			link.l1.go = "Memento_Sailor_3_6";
		break;
		
		case "Memento_Sailor_3_6":
			dialog.text = "Cosa possono farmi? Questa è una nave di morti, capitano, e qui è il mio posto. Ma lei — no.";
			link.l1 = "Se lo dici tu. Addio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_3";
		break;
		
		case "Memento_Sailor_4":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Benvenuto a bordo della Memento, capitano.";
				link.l1 = "Un soldato spagnolo su una nave pirata? Non si vede tutti i giorni.";
				link.l1.go = "Memento_Sailor_4_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Altro, capitano?";
				link.l1 = "Niente.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_4";
		break;
		
		case "Memento_Sailor_4_1":
			dialog.text = "Sono un disertore. Il capitano Grim mi ha comprato direttamente dalla forca nella piazza di San José. Ha pagato caro – un intero sacco di dobloni per la mia pelle.";
			link.l1 = "Per cosa l'hanno condannata?";
			link.l1.go = "Memento_Sailor_4_2";
		break;
		
		case "Memento_Sailor_4_2":
			dialog.text = "L'ufficiale Saldo ci ha mandati a sorvegliare i lavoratori nella giungla, dove metà muore di febbre in una settimana. Ho pensato che la mia vita valesse di più. Ora servo chi l'ha valutata in monete sonanti.";
			link.l1 = "Nessun rimpianto?";
			link.l1.go = "Memento_Sailor_4_3";
		break;
		
		case "Memento_Sailor_4_3":
			dialog.text = "Per quanto si attorcigli la corda... Il capitano è generoso con chi gli è fedele. Ma a volte ci mette alla prova – il sorteggio. Non tutti sono fortunati.";
			link.l1 = "Il sorteggio?";
			link.l1.go = "Memento_Sailor_4_4";
		break;
		
		case "Memento_Sailor_4_4":
			dialog.text = "Sa, a qualcuno tocca salire sull'albero in tempesta, a qualcun altro stare in prima linea. Il capitano dice che così si vede se sei pronto. Pronto a cosa, non so, ma spero che la fortuna mi assista.";
			link.l1 = "Buona fortuna... suppongo.";
			link.l1.go = "Memento_Sailor_4_5";
		break;
		
		case "Memento_Sailor_4_5":
			dialog.text = "Grazie, capitano. La morte arriva per tutti, prima o poi.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_4";
		break;
		
		/*case "Memento_Sailor_5":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Диалог 5";
				link.l1 = "Диалог 5";
				link.l1.go = "exit";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Что-нибудь ещё, капитан?";
				link.l1 = "Ничего.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_5";
		break;*/
		
		case "Memento_MortimerGrim_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Benvenuto a bordo della Memento, collega. Mi chiamo Mortimer Grim.";
				link.l1 = "Capitano "+GetFullName(pchar)+". Grazie per avermi accolto...";
				link.l1.go = "Memento_MortimerGrim_2";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Di cos'altro vogliamo parlare?";
				if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
				{
					link.l1 = "Ha una lama straordinaria, capitano.";
					link.l1.go = "Memento_MortimerGrim_question_1_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
				{
					link.l2 = "Il suo cannocchiale si abbina perfettamente allo scheletro.";
					link.l2.go = "Memento_MortimerGrim_question_2_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
				{
					link.l3 = "Devo dire che ha un equipaggio davvero variegato.";
					link.l3.go = "Memento_MortimerGrim_question_3_1";
				}
				link.l4 = "Nulla... collega. Vento in poppa.";
				link.l4.go = "exit";
				NextDiag.TempNode = "Memento_MortimerGrim_1";
			}
		break;

		case "Memento_MortimerGrim_2":
			dialog.text = "I Caraibi sono generosi con chi corre verso il patibolo, lo so bene.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_3";
		break;

		case "Memento_MortimerGrim_3":
			dialog.text = "Sì? Vuole chiedere qualcosa?";
			link.l1 = "Ha uno scheletro dietro di sé.";
			link.l1.go = "Memento_MortimerGrim_4";
			link.l2 = "Bel vento oggi, vero? E anche il tempo è ottimo.";
			link.l2.go = "Memento_MortimerGrim_5";
		break;

		case "Memento_MortimerGrim_4":
			dialog.text = "Quale scheletro? Dietro di me c'è solo il blu dei Caraibi.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;
		
				case "Memento_MortimerGrim_5":
			dialog.text = "Sono d'accordo, collega. Magari fosse sempre così!";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;
		
		case "Memento_MortimerGrim_6":
			dialog.text = "Ah ah ah! Questa battuta non invecchia mai! Non si spaventi: il vecchio Yorick, come questa nave, è un souvenir della mia vita passata. Letteralmente, ovviamente.";
			link.l1 = "'Ovviamente'?";
			link.l1.go = "Memento_MortimerGrim_7";
		break;
		
		case "Memento_MortimerGrim_7":
			dialog.text = "Collega, ha paura della morte? Non è una minaccia, sono davvero curioso.";
			link.l1 = "Certo. Chi dice il contrario, mente.";
			link.l1.go = "Memento_MortimerGrim_8_leadership";
			link.l2 = "No. Ci finiremo tutti.";
			link.l2.go = "Memento_MortimerGrim_8_weapon";
			link.l3 = "E lei?";
			link.l3.go = "Memento_MortimerGrim_8_sneak";
		break;
		
		case "Memento_MortimerGrim_8_leadership":
			dialog.text = "Oh! La morte è madre di tutte le paure. Solitudine, oscurità o punizione — sono solo sue maschere.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Memento_MortimerGrim_8_weapon":
			dialog.text = "Oh! La morte è madre di tutte le paure. Solitudine, oscurità o punizione — sono solo sue maschere.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "Memento_MortimerGrim_8_sneak":
			dialog.text = "Oh! La morte è madre di tutte le paure. Solitudine, oscurità o punizione — sono solo sue maschere.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Memento_MortimerGrim_9":
			dialog.text = "Non serve cercare lontano. Prenda il vecchio Yorick: un mucchio d'ossa con una lanterna nel petto — eppure ha fatto tremare anche un capitano temuto come lei!";
			if (startHeroType == 4)
			{
				dialog.text = "Non serve cercare lontano. Prenda il vecchio Yorick: un mucchio d'ossa con una lanterna nel petto — eppure ha fatto tremare perfino la coraggiosa Helen, figlia del grande Sean MacArthur!";
			}
			link.l1 = "Parla bene, ma non ha detto cosa farne di tutto questo.";
			link.l1.go = "Memento_MortimerGrim_10";
		break;
		
		case "Memento_MortimerGrim_10":
			dialog.text = "Io lo so, ma il mio rimedio non è per tutti. Potrà provarlo in seguito, ma prima mi dica cosa ne pensa lei.";
			link.l1 = "La Bibbia dice che la morte non esiste.";
			link.l1.go = "Memento_MortimerGrim_11_1";
			link.l2 = "Se mi faccio prendere dalla paura, la nave è perduta.";
			link.l2.go = "Memento_MortimerGrim_11_2";
			link.l3 = "La risposta è affondata sul fondo di una bottiglia di rum.";
			link.l3.go = "Memento_MortimerGrim_11_3";
		break;
		
		case "Memento_MortimerGrim_11_1":
			dialog.text = "È vero. L'unica cosa su cui concordo con quel libro.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;
		
		case "Memento_MortimerGrim_11_2":
			dialog.text = "Lodevole. Ma non si preoccupi: la morte non esiste.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;
		
		case "Memento_MortimerGrim_11_3":
			dialog.text = "Yo-ho-ho! Cinico. Ma anche senza rum le dico: la morte non esiste.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;
		
				case "Memento_MortimerGrim_12":
			dialog.text = "È semplice: la vera vita inizia solo quando si sconfigge la morte. Io ci sono stato, oltre il velo, e credetemi, ho iniziato a vivere davvero solo ora.";
			link.l1 = "Come, scusi?";
			link.l1.go = "Memento_MortimerGrim_13";
		break;
		
		case "Memento_MortimerGrim_13":
			dialog.text = "Non importa, collega.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
		break;
		
		case "Memento_MortimerGrim_question_1_1":
			dialog.text = "Mi fa piacere che l'abbia notato, collega! Non sono un fan della vanità, ma che razza di pirata sarei senza un terribile cutlass?";
			link.l1 = "È davvero così importante?";
			link.l1.go = "Memento_MortimerGrim_question_1_2";
		break;
		
		case "Memento_MortimerGrim_question_1_2":
			dialog.text = "Eccome! L’unica volta che ho alleggerito visibilmente la cassa della nave per uno scopo personale è stato proprio per questa lama. Duemila dobloni d'oro, collega! Diavolo, se potessi risorgere una seconda volta, lo farei solo per il suo prezzo!\n"+
			"È un'arma eccellente. Ma sembra che le manchi ancora qualcosa...";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_1 = true;
		break;
		
		case "Memento_MortimerGrim_question_2_1":
			dialog.text = "Un regalo di una persona. Un ottimo conversatore, che comprendeva la morte come nessun altro — e con un'immaginazione notevole, come può vedere.";
			link.l1 = "Ha un aspetto inquietante.";
			link.l1.go = "Memento_MortimerGrim_question_2_2";
		break;
		
		case "Memento_MortimerGrim_question_2_2":
			dialog.text = "Memento mori, collega.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_2 = true;
		break;
		
		case "Memento_MortimerGrim_question_3_1":
			dialog.text = "Il mio equipaggio ha molto più in comune tra loro di quanto pensi... Tutti sono stati da me liberati da forche e catene, ognuno ha sentito il respiro della morte. Questo sentimento unisce più del sangue o della bandiera.";
			link.l1 = "Immagino che non assuma uomini nelle taverne?";
			link.l1.go = "Memento_MortimerGrim_question_3_2";
		break;
		
		case "Memento_MortimerGrim_question_3_2":
			dialog.text = "Si stupirebbe di quanto volentieri si uniscano all’equipaggio ex schiavi e condannati a morte: scambiare la stiva di uno schiavista o il patibolo con la coperta della Memento? A bordo ora ho 178 uomini — e ognuno di loro mi deve la vita.";
			link.l1 = "Ma deve pur pagare l’equipaggio e mantenere la nave. La gratitudine non basta.";
			link.l1.go = "Memento_MortimerGrim_question_3_3";
		break;
		
		case "Memento_MortimerGrim_question_3_3":
			dialog.text = "Sono un pirata di successo, collega. Un vero hostis humanitatis. Così mi chiamerebbero i veri nemici dell'umanità — schiavisti e reali incoronati. La differenza tra loro è solo nel nome\n"+
			"Per fortuna, hanno molto oro. Le monete prese dai mercanti di carne le spendo per salvare chi è stato condannato dalla corona. Il resto va all’equipaggio — io non ho bisogno di nulla. A che serve l’oro a un morto? Presto lo capiranno...";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_3 = true;
		break;
		
		// Диалог с Алонсо
		case "Memento_Alonso_phantom_11":
			dialog.text = "Ecco la nostra miserabile situazione, capo.";
			link.l1 = "Che cos'è tutto questo?!";
			link.l1.go = "Memento_Alonso_phantom_12";
		break;
		
		case "Memento_Alonso_phantom_12":
			dialog.text = "È rimasto solo lei. La malattia ha portato via tutti. Ci ha delusi.";
			link.l1 = "Non è possibile!";
			link.l1.go = "Memento_Alonso_phantom_13";
		break;
		
		case "Memento_Alonso_phantom_13":
			dialog.text = "Ci ha portati su una nave maledetta.";
			link.l1 = "...";
			link.l1.go = "Memento_Alonso_phantom_14";
		break;
		
		case "Memento_Alonso_phantom_14":
			dialog.text = "Ha condannato tutti a morte!";
			link.l1 = "Alonso, che ti succede?!";
			link.l1.go = "Memento_Alonso_phantom_15";
			npchar.model = "skel1";
			npchar.model.animation = "skeleton";
			npchar.sex = "skeleton";
			Characters_RefreshModel(npchar);
			SetMusic("classic_music_retribution_1");
		break;
		
		case "Memento_Alonso_phantom_15":
			dialog.text = "Mortui vivos docent.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_6");
		break;
		
		// Диалог с Гримом
		
				case "Memento_MortimerGrim_phantom_11":
			dialog.text = "Perché vi siete fermato, collega? Avete cambiato idea? Allora perché avete attaccato?";
			link.l1 = "Grim? Ma sei morto!";
			link.l1.go = "Memento_MortimerGrim_phantom_12";
		break;

		case "Memento_MortimerGrim_phantom_12":
			dialog.text = "Ah! Ciò che è morto non può morire. E poi, state correndo troppo: magari avete vinto l'abbordaggio, ma sopravvivrete? Lo scopriremo ora!";
			link.l1 = "Quella battaglia è finita settimane fa! Sei morto!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_11");
		break;

		case "Memento_MortimerGrim_phantom_21":
			dialog.text = "Ora è finita. Congratulazioni per la vittoria.";
			link.l1 = "Grim?";
			link.l1.go = "Memento_MortimerGrim_phantom_22";
			LAi_UseAtidoteBottle(pchar);
		break;

		case "Memento_MortimerGrim_phantom_22":
			dialog.text = "Sai, sono felice. Sinceramente felice che tu mi abbia ucciso. Davvero.";
			link.l1 = "Di cosa stai parlando?";
			link.l1.go = "Memento_MortimerGrim_phantom_23";
		break;

		case "Memento_MortimerGrim_phantom_23":
			dialog.text = "Sono un codardo, collega. Un semplice, miserabile codardo che ha avuto paura della morte – come migliaia prima di lui. Quando l'equipaggio morì di peste... e per colpa mia, sono impazzito dalla paura. Ho vagato un mese da solo su una nave dei morti.";
			link.l1 = "Cosa è successo davvero?";
			link.l1.go = "Memento_MortimerGrim_phantom_24";
		break;

		case "Memento_MortimerGrim_phantom_24":
			dialog.text = "Non ho superato la prova della morte. Invece di accettarla, sopravvivere e imparare qualcosa, ho iniziato ad averne ancora più paura. E per soffocare questa paura... ho costretto altri a passare ciò che ho passato io.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_25";
		break;

		case "Memento_MortimerGrim_phantom_25":
			dialog.text = "Grazie, collega. Per avermi liberato da questa... esistenza. Ora so con certezza che la morte non esiste. E non ho più paura. Non c'è più nessuno da incolpare o da schiavizzare.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_26";
		break;

		case "Memento_MortimerGrim_phantom_26":
			dialog.text = "Non separate la 'Memento' dal suo capitano. Mortimer... il Capitano Mortimer era un brav'uomo. Cercatelo a Dominica. E la nave... la nave vi accoglierà.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_27";
		break;

		case "Memento_MortimerGrim_phantom_27":
			dialog.text = "Mortui vivos docent, collega. I morti insegnano ai vivi. Addio.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_13");
		break;
		
	}
} 