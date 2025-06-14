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
			dialog.text = "Cosa volete?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;
		
		// Квест "Путеводная звезда"
		// Этап 0, ПРОЛОГ
		case "PZ_Alonso_1":
			dialog.text = "Mi scuso di disturbare i vostri alloggi, Mio Signore Capitano, ma questa cosa è davvero importante.";
			link.l1 = "Spero proprio di sì, Alonso. Se tutti voi iniziate a entrare qui come se fosse casa vostra, avremo qualche problema. Allora, che succede?";
			link.l1.go = "PZ_Alonso_2";
		break;
		
		case "PZ_Alonso_2":
			dialog.text = "Abbiamo visto che qualcuno ha frugato nella tua cassa.";
			link.l1 = "Cosa?! Aspetta un attimo... Come hai fatto a capirlo? E che ci facevate tutti nella mia cabina?";
			link.l1.go = "PZ_Alonso_3";
		break;
		
		case "PZ_Alonso_3":
			dialog.text = "Puliamo le tue stanze di tanto in tanto quando sei fuori – in città o a riposare sulle brande. Non te ne sei mai accorto? O forse te ne sei solo dimenticato?";
			link.l1 = "Ah, giusto. Beh, ora puoi andare.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Tichingitu_1":
			dialog.text = "Capitano Charles, guardate! Qualcuno stava frugando nel vostro cassetto grande.";
			link.l1 = "Cosa? Quando te ne sei accorto? Sai chi è stato?";
			link.l1.go = "PZ_Tichingitu_2";
		break;
		
		case "PZ_Tichingitu_2":
			dialog.text = "Non molto tempo fa, quando venivo da voi. Gli spiriti non dicono chi possa essere.";
			link.l1 = "Bel tocco, Tichingitu. Ora, se permetti, devo controllare se manca qualcosa.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Duran_1":
			dialog.text = "Ehi, Capitano, che stai guardando? Qualcuno ha rovistato tra le tue cose. Persino io me ne sono accorta.";
			link.l1 = "Non eri tu, vero? In fondo, non ti pago mica con la stessa generosità di François.";
			link.l1.go = "PZ_Duran_2";
		break;
		
		case "PZ_Duran_2":
			dialog.text = "Heh, se fossi stato io il ladro, non te lo direi di certo, giusto? Avrei preso il bottino e lasciato tutto in ordine. Questo casino non è roba mia.";
			link.l1 = "Odio ammetterlo, ma hai ragione. Va bene, Claude, riserva le tue frecciatine per dopo. Devo vedere cosa ha portato via quel ladro.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Folke_1":
			dialog.text = "Capitano, oggi ho visto che qualcuno ha frugato nel vostro baule. Non ve ne siete accorto?";
			link.l1 = "Cosa? Non sto sempre a controllare la cassapanca, Folke, e non sono nemmeno sempre in cabina. Dimmi la verità — sei stato tu? Hai combinato qualche casino di nuovo e hai chiesto altri prestiti in banca l’ultima volta che siamo sbarcati?";
			link.l1.go = "PZ_Folke_2";
		break;
		
		case "PZ_Folke_2":
			dialog.text = "Assolutamente no, Capitano. Non ho nulla di vostro né nelle mie tasche né nel mio baule. E mai ci sarà.";
			link.l1 = "Me lo auguro proprio. Puoi andare – darò un’occhiata a cosa manca.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_OsmatrivaemKautu":
			DialogExit();
			
			if (npchar.id == "Tichingitu")
			{
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				npchar.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (npchar.id == "Duran" || npchar.id == "Folke")
			{
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Enc_Officer_dialog.c";
				npchar.Dialog.CurrentNode = "hired";
			}
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "loc2", "PZ_OsmatrivaemSunduk", -1);
		break;
		
		case "PZ_LigaInJungle_1":
			dialog.text = "Charles de Maure, giusto?";
			link.l1 = "Dalla tua faccia capisco che già sai la risposta. Allora, che cosa vuoi?";
			link.l1.go = "PZ_LigaInJungle_2";
		break;
		
		case "PZ_LigaInJungle_2":
			dialog.text = "La tua testa.";
			link.l1 = "Affascinante! Devo ammettere che mi piace l’inizio di questa conversazione. Ma, prima di proseguire, potresti almeno dirmi chi avrei offeso? Forse possiamo trattare.";
			link.l1.go = "PZ_LigaInJungle_3";
		break;
		
		case "PZ_LigaInJungle_3":
			dialog.text = "Non siamo degli sprovveduti, Monsieur de Maure. Anche se glielo dicessimo, non le servirebbe a nulla – il nostro padrone ha già lasciato l’Arcipelago. Non potrà fargli del male, né offrirgli le sue scuse. Abbiamo già ricevuto il compenso, e ora tocca a noi mantenere la parola data.";
			link.l1 = "Se hai già ricevuto il tuo compenso, perché spargere ancora altro sangue?";
			link.l1.go = "PZ_LigaInJungle_4";
		break;
		
		case "PZ_LigaInJungle_4":
			dialog.text = "Non siamo degli sprovveduti. La nostra reputazione vale più dell’oro.";
			link.l1 = "Temo che stavolta non sarai all’altezza, mio Signore Capitano.";
			link.l1.go = "PZ_LigaInJungle_5";
		break;
		
		case "PZ_LigaInJungle_5":
			dialog.text = "Vedremo, mio Signore Capitano. Fruga nel suo cadavere quando avremo finito! Brucia ogni cosa che trovi!";
			link.l1 = "Bruciare cosa?.. ";
			link.l1.go = "PZ_LigaInJungle_6";
		break;
		
		case "PZ_LigaInJungle_6":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("LigaInJungle_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_LigaInJunglePosleBitvy");
			
			if (CharacterIsHere("Longway"))
			{
				sld = characterFromId("Longway");
				LAi_SetCheckMinHP(sld, 1, true, "");
			}
		break;
		
		case "PZ_Longway_1":
			dialog.text = "Quello che ha detto l’uomo mascherato... Potrebbe essere...?";
			link.l1 = "Che c'è, Longway? Non è la prima volta che dei segugi vengono a cercarmi, ma tu sembri stranamente turbato.";
			link.l1.go = "PZ_Longway_2";
		break;
		
		case "PZ_Longway_2":
			dialog.text = "Longway crede di sapere chi ha mandato questi uomini contro di te, Mio Signore Capitano.";
			link.l1 = "Qualcosa di cui dovrei essere al corrente?";
			link.l1.go = "PZ_Longway_3";
		break;
		
		case "PZ_Longway_3":
			dialog.text = "Questo è il modo del Lord Rodenburg: far sparire chi gli ha dato una mano ma sa troppo.";
			link.l1 = "Davvero... Quel tizio mascherato ha detto che il suo padrone ha lasciato l'Arcipelago di recente. È proprio quello che Lucas stava pianificando! Pensi che dovremmo aspettarci altri attacchi?";
			link.l1.go = "PZ_Longway_4";
		break;
		
		case "PZ_Longway_4":
			dialog.text = "È saggio essere pronti a tutto, Mio Signore Capitano.";
			link.l1 = "Sagge parole. Così faremo. Ma cosa cercava Lucas? Cosa pensava che avessi io? Hai qualche idea, Longway?";
			link.l1.go = "PZ_Longway_5";
		break;
		
		case "PZ_Longway_5":
			dialog.text = "Mm-mm, no, Longway non ha la minima idea di cosa possa essere, mio Signore Capitano.";
			link.l1 = "È un peccato. Ma va bene, andiamo via da qui, giusto?";
			link.l1.go = "PZ_Longway_6";
		break;
		
		case "PZ_Longway_6":
			DialogExit();
			
			Return_LongwayOfficer();
			
			chrDisableReloadToLocation = false;
			pchar.questTemp.PZ_RazgovorGerrits = true;
			pchar.questTemp.PZ_PodozrenieLucas = true;
		break;
		
		// Этап 1, ВЕРНЫЙ КЛЯТВЕ
		case "PZ_Longway_11":
			dialog.text = "Mio Signore Capitano, Longway desidera parlare con voi. È cosa di grande peso.";
			if (CheckAttribute(pchar, "questTemp.PZ_PodozrenieLucas"))
			{
				link.l1 = "Che c’è, Longway? Ti turba il modo in cui Lucas ci ha salutati, o hai fiutato qualche novità?";
				link.l1.go = "PZ_Longway_12";
				AddCharacterExpToSkill(pchar, "Sneak", 100);
			}
			else
			{
				link.l1 = "Certo! Che hai in mente?";
				link.l1.go = "PZ_Longway_13";
			}
		break;
		
		case "PZ_Longway_12":
			dialog.text = "Purtroppo, no.";
			link.l1 = "Allora che succede, Longway?";
			link.l1.go = "PZ_Longway_13";
		break;
		
		case "PZ_Longway_13":
			dialog.text = "Longway non può dirlo. Ma... desidera chiedere il permesso di andarsene.";
			link.l1 = "Andartene? Intendi, per sempre? Perché, Longway? Come tuo capitano, ho diritto di sapere il motivo.";
			link.l1.go = "PZ_Longway_14";
		break;
		
		case "PZ_Longway_14":
			dialog.text = "È vero, Mio Signore Capitano. Ma Longway non è né schiavo né servo. È venuto ad offrire aiuto di sua propria volontà, e può andarsene allo stesso modo. Non sarà per sempre – c’è una faccenda importante che attende. Longway spera di tornare quando sarà compiuto.";
			link.l1 = "Di che si tratta? Parla - se non come tuo capitano, almeno come chi ha già condiviso il peggio con te.";
			link.l1.go = "PZ_Longway_15";
		break;
		
		case "PZ_Longway_15":
			dialog.text = "Tutto ciò che Longway può dire è che ha fatto un giuramento — molto tempo fa. Ora è giunto il momento di mantenerlo. Altrimenti... la vita di Longway non ha alcun senso.";
			link.l1 = "Hai ragione, Longway – non sei un prigioniero, e io non sono un carceriere. Sei libero di andartene. Che gli dèi ti guidino.";
			link.l1.go = "PZ_Longway_Otpustit_1";
			link.l2 = "Puoi andare, ma almeno dimmi dove stai andando. Potrei aiutarti senza fare troppe domande.";
			link.l2.go = "PZ_Longway_Pomoch_1";
			link.l3 = "Anch'io ho un compito importante – salvare mio fratello. Per questo, ho bisogno di ogni uomo, compreso te, Longway. Senza di te non ce la facciamo.";
			link.l3.go = "PZ_Longway_NeOtpuskaem_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_1":
			dialog.text = "Non tentare di fare leva sulla mia pietà o sul mio senso del dovere. Capisco benissimo. Hai mai fatto un giuramento, Mio Signore Capitano?";
			link.l1 = "Ma certo che sì. Raccontami tutto com’è andata, e io con la mia ciurma ti daremo senz’altro una mano.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_2";
		break;
		
		case "PZ_Longway_NeOtpuskaem_2":
			dialog.text = "Longway non può. Semplicemente... non può. È un grande mistero, e neppure mio da raccontare.";
			link.l1 = "Che peccato. Pensavo ci fosse fiducia tra noi. Tu non lasci la nave – ora ho tutti gli ufficiali dalla mia parte.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_3";
			link.l2 = "Hai ragione, Longway – non sei un prigioniero, e io non sono un carceriere. Sei libero di andartene. Che il vento ti sia favorevole.";
			link.l2.go = "PZ_Longway_Otpustit_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_3":
			dialog.text = "Non puoi farlo!";
			link.l1 = "Purtroppo posso, Longway. Ora torna ai tuoi doveri.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_4";
		break;
		
		case "PZ_Longway_NeOtpuskaem_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition = "PZ_LongwayUhoditOtNasNavsegda";
		break;
		
		case "PZ_Longway_Otpustit_1":
			dialog.text = "Non pensavo che mi avresti lasciato andare così facilmente. Grazie, Mio Signore Capitano.";
			link.l1 = "Ah, non è nulla. Ma dimmi – dove posso trovarti quando avrai finito con i tuoi affari?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
		break;
		
		case "PZ_Longway_Pomoch_1":
			dialog.text = "Longway davvero non può dirlo, per quanto lo desideri con tutto il cuore. Ma apprezza la disponibilità del Mio Signore Capitano ad aiutare.";
			link.l1 = "Così sia. Dove dovrei cercarvi quando avrete mantenuto il vostro giuramento?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
			pchar.questTemp.PZ_LongwayGood = true;
		break;
		
		case "PZ_Longway_GdeIskat_1":
			dialog.text = "Conto di sbrigare i miei affari entro un mese. Dopo ciò, Longway vi aspetterà ancora una settimana alla taverna di Basse-Terre.";
			link.l1 = "Ebbene, come vuoi tu, amico mio. Non è un addio. Ci vediamo a Basse-Terre.";
			link.l1.go = "PZ_Longway_GdeIskat_2";
		break;
		
		case "PZ_Longway_GdeIskat_2":
			DialogExit();
			
			RemovePassenger(pchar, npchar);
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.location = "None";
			
			SetQuestHeader("PZ");
			AddQuestRecord("PZ", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			SetTimerCondition("PZ_IshemLongway", 0, 0, 30, false);
		break;
		
		case "PZ_SharliePlennik_BadFinal_1":
			dialog.text = "Ebbene, salve, Capitano.";
			link.l1 = "Quel tuo sorrisetto mi dà il voltastomaco, signore.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_2";
		break;
		
		case "PZ_SharliePlennik_BadFinal_2":
			dialog.text = "Sono sconvolto. Sono venuto a dirti che finalmente sei libero. Ma se desideri restare ancora un po' in questa lussuosa cabina, sei il benvenuto.";
			link.l1 = "Affatto. Dunque, hanno trovato Longway? Dov’è? Sta marcendo in una delle celle?";
			link.l1.go = "PZ_SharliePlennik_BadFinal_3";
		break;
		
		case "PZ_SharliePlennik_BadFinal_3":
			dialog.text = "In un altro mondo, più adatto a lui, non ci avrebbe nemmeno degnati di uno sguardo e sarebbe corso subito a combattere.";
			link.l1 = "Maledizione! Potevi semplicemente catturarlo.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_4";
		break;
		
		case "PZ_SharliePlennik_BadFinal_4":
			dialog.text = "Vi sono certi uomini che è assai più semplice spedire al Creatore che prendere vivi, lo sapete? Dovreste ringraziarci che non ve ne facciamo una colpa – il vostro cinese ha scatenato un altro massacro, e ci son voluti altri reparti di tiratori scelti per sistemarlo.";
			link.l1 = "Sì, proprio così. Ti ringrazio di cuore.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_5";
		break;
		
		case "PZ_SharliePlennik_BadFinal_5":
			dialog.text = "A proposito, visto che era tuo amico, abbiamo trovato dei fogli addosso a lui. Non abbiamo capito che fossero — forse tu lo saprai meglio. Su alcune parti, non coperte di sangue, c'era scritto del ciarpame incomprensibile.";
			link.l1 = "Questo è... Merda. Grazie di avermeli riportati. Addio, ufficiale.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_6";
		break;
		
		case "PZ_SharliePlennik_BadFinal_6":
			DialogExit();
			
			LAi_ActorGoToLocator(npchar, "goto", "goto22", "", -1);
			DoQuestCheckDelay("PZ_SharliePlennik_BadFinal_2", 3.0);
		break;
		
		case "PZ_BasTerStop":
			dialog.text = "Vieni con noi, il Comandante desidera parlarti.";
			link.l1 = "Immagino che questo riguardi la mia ricerca per il Cinese, vero?";
			link.l1.go = "PZ_BasTerStop_2";
		break;
		
		case "PZ_BasTerStop_2":
			dialog.text = "Vedrete con i vostri propri occhi, monsieur.";
			link.l1 = "Sono forse accusato di qualcosa?";
			link.l1.go = "PZ_BasTerStop_3";
		break;
		
		case "PZ_BasTerStop_3":
			dialog.text = "Affatto. Nessuno cerca di arrestarvi o trattenervi. Per ora. Quando ho detto che il Comandante desidera parlarvi, intendevo proprio questo.";
			link.l1 = "Oh, beh...";
			link.l1.go = "PZ_BasTerStop_4";
		break;
		
		case "PZ_BasTerStop_4":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_town")], false);
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto17", "PZ_BasTer_TurmaPriveli");
		break;
		
		case "PZ_BasTer_OtryadPeshera_1":
			dialog.text = "Hai qualche idea? Questo tizio dalla pelle gialla è una dannata minaccia. Non siamo la prima banda mandata qui. Gli ordini sono ordini, ma non ho intenzione di schiattare da idiota entrando senza un piano solido.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				link.l1 = "È lì dentro, solo come un cane, e io sto con voi. Lascialo a me – voi pensate solo a coprirmi. Ce la caveremo.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "Ne ho uno io. Morirete tutti, proprio qui.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				link.l1 = "Non preoccuparti, dobbiamo solo scambiare due parole con lui.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "Mi dispiace, ma oggi morirete tutti quanti. E non sarà per mano di un cinese.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_1":
			pchar.questTemp.PZ_Podelnik = true;
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Quindi non sei un cacciatore di taglie... Ma anche se lo fossi, sei amico di quel dannato cinese!";
				link.l1 = "Proprio così. Tanto dovrei comunque sbarazzarmi di te – inutile rimandare l'inevitabile.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Cosa vuoi dire?! Avevi promesso di aiutarmi!";
				link.l1 = "Penso che tu non ci avresti comunque lasciato una via d'uscita pacifica. Non è nulla di personale.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_OtryadPeshera_Kill_3");
		break;
		
		case "PZ_BasTer_OtryadPeshera_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Mi piacerebbe crederci.";
				link.l1 = "Ho già visto di peggio. Un cinese non ci rovinerà la giornata. Forza, ragazzi!";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "E se la conversazione non dovesse andare come previsto?";
				link.l1 = "Lo detesterei, ma allora dovrò difendermi. Andiamo.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_3":
			DialogExit();
			
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload2", "PZ_IshemLongway_OtryadUPeshery");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway":
			dialog.text = "Mio Signore Capitano?! Longway non può credere che siete con loro!";
			link.l1 = "No, Longway, sono qui solo per parlare! Non è come pensi!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_2":
			dialog.text = "Allora saresti venuto da solo. Vuoi solo farmi abbassare la guardia per poi assalirmi con questi soldati, non è vero?";
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayGood"))
			{
				link.l1 = "Se potessi, lo farei. Sono io l'unica ragione per cui non ti hanno ancora assalito. Calmati, e parliamone, giusto?";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_3";
			}
			else
			{
				link.l1 = "Basta con le chiacchiere! Se avessi voluto, ti avrei già mandato all’inferno. Butta giù le armi, e parliamo. Questo è un ordine del tuo capitano.";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_3":
			dialog.text = "Sì. Longway si fida di te, Mio Signore Capitano.";
			link.l1 = "Ecco, così va meglio. Ora, dimmi...";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_4";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_4":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadom_DialogLongway_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_5":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Monsieur, che succede? Cos’è questa... commovente riunione? Dovevi aiutarci a far fuori quel selvaggio cinese, non è vero?";
				link.l1 = "Sì, lo sono. Lo porto via con me, e tutto questo spargimento di sangue finirà. Dirai al comandante che l'abbiamo ucciso insieme. Affare fatto?";
				link.l1.go = "PZ_BasTer_SOtryadomOhotnik_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Ben fatto, Capitano! Ha deposto le armi. È un bene averti dalla nostra parte. Ora portiamolo dal comandante.";
				link.l1 = "Perché mai dovrei farlo? Ho già pagato una multa in oro per le azioni di Longway – e pure generosa. I tuoi colleghi ufficiali erano presenti – possono confermare. Il comandante mi ha dato il permesso di portare il mio uomo sulla nave.";
				link.l1.go = "PZ_BasTer_SOtryadomDrug_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadomDrug_1":
			dialog.text = "Il Comandante forse ha avuto abbastanza di quest’oro insanguinato, ma non io. Alcuni di quei poveracci massacrati in quella maledetta grotta erano miei amici. E poi, dubito che gli importerà se facciamo fuori il Cinese, comunque.";
			link.l1 = "Sicuro che vuoi saperlo? E riguardo ai tuoi amici che sono stati fatti fuori... hai mai sentito parlare di quella sfrontata banda di briganti? Dev’essere stato opera loro.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_2";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_2":
			StartInstantDialog("Longway", "PZ_BasTer_SOtryadomDrug_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_3":
			dialog.text = "";
			link.l1 = "Longway, non hai ammazzato tutti quei soldati come dicono, vero?";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_4";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_4":
			dialog.text = "Esatto, Mio Signore Capitano. Longway ha visto quella banda. Si sono nascosti più in fondo alla grotta per non farsi notare da lui. E Longway ha udito suoni di chiacchiere, bestemmie e risse tra banditi e soldati.";
			link.l1 = "";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_5";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_5":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadomDrug_6", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_6":
			dialog.text = "";
			link.l1 = "Vedete? Tutto torna. Longway avrà pure un diavolo dentro, ma è un uomo onesto. Ce ne andiamo. Se ci toccate, infangherete la vostra uniforme. Addio, signori.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_7";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_7":
			DialogExit();
			
			AddQuestRecord("PZ", "13");
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_CharacterDisableDialog(sld);
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_1":
			dialog.text = "Neanche per sogno, monsieur! Ha massacrato un mucchio dei nostri uomini, e ora vuoi lasciarlo scappare così?! O ci aiuti a far fuori quel bastardo, oppure stai dannatamente alla larga dai nostri piedi!";
			link.l1 = "Temo di dover intervenire. Mi dispiace, davvero.";
			link.l1.go = "PZ_BasTer_SOtryadomOhotnik_2";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_CharacterDisableDialog(sld);
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_1":
			dialog.text = "Se volevi solo parlare, non mi avresti chiesto di deporre le armi. Ma una tigre resta sempre una tigre, anche senza artigli. Devi aver già deciso di tradire Longway molto tempo fa—non c’è bisogno che menti. Difenditi, Capitano!";
			link.l1 = "Porca puttana!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_MyUbilLongway_BadFinal");
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Non riesco a credere che ce l’abbiamo fatta passare con quel tipo! Ma dimmi, perché ti ha chiamato Capitano?";
				link.l1 = "È più ingarbugliato di quanto sembra, amico. Dovevo calmare il tuo comandante. Quello che conta è il risultato, giusto? E il risultato è che Longway è morto, e io ti ho dato una mano con questo.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Neanche la tua presenza è servita – ci ha assaliti lo stesso, maledetto selvaggio...";
				link.l1 = "Non dovresti parlarne così. Ci ha assaliti perché era turbato e pensava che io stessi con te.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Forse. In tal caso, addio, monsieur. Riferiremo noi al comandante che il cinese è finalmente morto.";
				link.l1 = "Molto bene, grazie. Addio, ragazzi.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Beh, arrabbiato o bestia che sia, non cambia nulla – prima ha ucciso molti dei nostri, ha versato il primo sangue.";
				link.l1 = "Qualcosa deve averlo spinto a ridursi così. Ma non soffermiamoci oltre. Io me ne vado, e tu puoi tornare dal comandante quando ti pare. Addio.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_3":
			DialogExit();
			
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterNationReputation(pchar, FRANCE, 12);
			AddQuestRecord("PZ", "11");
			CloseQuestHeader("PZ");
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog":
			dialog.text = "Mio Signore Capitano?";
			link.l1 = "Ahò! Ti ho cercato dappertutto, Longway. Hai sollevato un bel polverone in città. Dobbiamo parlare a lungo, perciò torniamo subito a bordo.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_2";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_2":
			dialog.text = "Laggiù!";
			link.l1 = "Vedo che abbiamo compagnia. Pare che faremo un po' tardi.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_3";
			locCameraFromToPos(-12.27, 1.29, -8.89, true, -3.23, -1.20, -4.77);
			DoQuestCheckDelay("PZ_IshemLongway_SorraKomendant_Dialog_Povernutsya", 1.3);
			
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				LAi_SetHP(sld, 60.0, 60.0);
			}
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_SorraKomendant_Pobeda1");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_4":
			dialog.text = "Ne arrivano altri!";
			link.l1 = "Ostinate canaglie — questo glielo riconosco. Qui siamo troppo allo scoperto. Andiamo nella grotta — sarà più facile difenderci.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_5";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_5":
			DialogExit();
			pchar.questTemp.PZ_IshemLongway_SorraKomendant = true;
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_6":
			dialog.text = "Non possiamo restare qui per sempre.";
			link.l1 = "E questa è la prima cosa che vuoi dire dopo tutto quello che è successo, Longway? Non pensi sia ora di spiegare cosa sta succedendo?";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_7";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_7":
			dialog.text = "Mio Signore Capitano, Longway...";
			link.l1 = "Ma hai ragione – non possiamo restare. Andiamo via prima che arrivi un’altra pattuglia. Parleremo sulla nave, una volta salpati.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_8";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_8":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_1":
			dialog.text = "L’astuzia e la crudeltà dell’uomo bianco non hanno confini.";
			link.l1 = "Ehi, sono bianco anch’io! E poi, hai ammazzato i loro compagni e camerati — è naturale che abbiano il sangue agli occhi.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_2";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_2":
			dialog.text = "Li assolvete, Mio Signore Capitano?";
			link.l1 = "Ti assolvo, Longway. E ti prego di non giudicare la gente per il colore della pelle. Proprio tu dovresti capirlo meglio di chiunque altro. Siamo stati interrotti... dove eravamo rimasti...?";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_3";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_3":
			dialog.text = "Capitano! Dietro di voi!";
			link.l1 = "Oh, oggi non ci lasceranno certo scambiare due parole in pace...";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_4";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_4":
			DialogExit();
			LAi_SetCurHPMax(pchar);
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			
			sld = CharacterFromID("Longway");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=6; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 60.0, 60.0);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya_5");
			
			AddDialogExitQuest("MainHeroFightModeOn"); // Rebbebion, fix
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_6":
			dialog.text = "Chiaro, Mio Signore Capitano.";
			link.l1 = "Va bene, ma non perdiamo tempo qui. Tu ed io dobbiamo parlare a lungo. Seguimi – torniamo alla nave.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_7";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_7":
			DialogExit();
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			AddQuestRecord("PZ", "14");
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			DeleteQuestCondition("PZ_KorablBuhta_BadFinal");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_1":
			dialog.text = "Mio Signore Capitano, siete davvero voi...?";
			link.l1 = "Aye, Longway. Tutto a posto?";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_2";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_2":
			dialog.text = "Longway sta bene. Grazie. Ma, Capitano! Guardate!";
			link.l1 = "Corri alla grotta, svelto! È una buona posizione difensiva!";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_3";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_3":
			DialogExit();
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SrazuNashli_4":
			dialog.text = "Longway controllerà se i soldati stanno ancora arrivando.";
			link.l1 = "Andremo insieme – non possiamo resistere contro tutta la guarnigione.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_5";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_5":
			dialog.text = "Sì, Mio Signore Capitano?";
			link.l1 = "Abbiamo molte cose di cui discutere. Ora seguimi – dobbiamo salpare l’ancora subito.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_6";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_6":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		// Этап 2, СТРАНИЦЫ ИСТОРИИ
		case "PZ_LongwayRazgovorOProshlom":
			dialog.text = "Grazie ancora per avermi dato una mano, Mio Signore Capitano. Sono certo che avrete molte domande.";
			link.l1 = "Questo è dir poco. Perché hai ammazzato quei soldati? Non sei uno che uccide per piacere—lo so.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_LongwayRazgovorOProshlom_2":
			dialog.text = "No, Longway no. I soldati hanno cercato di fermare Longway, e la prigione non era un'opzione. Non ascoltano un cinese—solo agli uomini bianchi danno quel privilegio.";
			link.l1 = "Nemmeno tra loro si ascoltano sempre, questi bianchi, ma capisco cosa intendi. Però, sgozzarli come animali in mezzo alla città? Che ci facevi a Basse-Terre?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_3":
			dialog.text = "Not only do white people often not listen to me; sometimes they won't even talk. And when they do, it's to call the guards. Longway didn't choose his skin or his eyes, but he's proud of who he is. When soldiers mock and threaten, Longway grows tired... and angry.";
			link.l1 = "D’ora in avanti, lavoriamo insieme. La gente parla con me invece di chiamare le guardie... di solito. Ma sul serio, parlami della tua missione. Lascia che ti dia una mano.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_4";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_4":
			dialog.text = "Per favore, Mio Signore Capitano, capisca Longway. Ha giurato di fare questo da solo. Non lo forzi. Longway merita almeno questo da lei.";
			link.l1 = "Ti sono davvero grata, ma avrei potuto occuparmi di van Merden da sola, allora. Però, eravamo già pari dall’inizio — hai detto che ti ho salvato la faccia, e tu la vita a me. Ora ti ho salvato ancora io.";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) link.l1.go = "PZ_LongwayRazgovorOProshlom_5";
			else link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_5":
			dialog.text = "Hmm... avete ragione, Mio Signore Capitano. Longway pensa che voi siate il suo vero amico tra gli uomini bianchi. Una volta credeva di averne uno, ma si era crudelmente sbagliato. Ricordate John Murdock? Johan van Merden?";
			link.l1 = "Che strano che tu abbia menzionato van Merden. Proprio di recente, qualcuno ha strappato alcune pagine dal suo archivio sotto il mio stesso naso. Era forse collegato al tuo caso? Hai trovato il ladro?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_6";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_6":
			dialog.text = "L’ho fatto. Il ladro era... Longway. Egli vi chiede umilmente perdono, Mio Signore Capitano. All’epoca, non sapeva se poteva affidarsi a voi senza timore.";
			if (sti(pchar.reputation.nobility) <= 60)
			{
				link.l1 = "Parli di amicizia, ma mi derubi alle spalle? Questa è la prima e ultima volta, Longway. Hai capito?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(61))+")", "None");
			}
			else
			{
				link.l1 = "E come hai fatto a portare a termine il colpo, Longway?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_1";
				notification("Reputation Check Passed", "None");
			}
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_1":
			dialog.text = "Longway comprende. Lo dice sul serio.";
			link.l1 = "Spero di sì. Ora raccontami come sei arrivato a questa vita – quale giuramento hai fatto, quando, e a chi.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_2";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) AddComplexSelfExpToScill(100, 100, 100, 100);
			notification("Longway disapproves", "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_2":
			dialog.text = "Sì, Mio Signore Capitano\nLongway cerca colei che ancora vive ed è per lui la più importante: Chang Xing.";
			link.l1 = "Chang Xing - è il tuo migliore amico?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_1":
			dialog.text = "Grazie alla vostra gentilezza, il resto dell’equipaggio si è presto abituato a me e ha iniziato a fidarsi.";
			link.l1 = "Va bene, ho capito. Non sei tipo da complimenti, ma buon lavoro, Longway... se hai ripulito il casino che hai lasciato entrando.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_2";
			AddComplexLandExpToScill(200, 200, 0);
			pchar.questTemp.PZ_FlagArhiv = true;
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_2":
			dialog.text = "Giusto. Ma non c’è tempo per queste cose.";
			link.l1 = "Immagino di no. Ma cerca di non farlo più, giusto? Se hai bisogno di qualcosa, chiedi pure. Puoi fidarti di me. Ora, parlami del tuo giuramento.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_3":
			dialog.text = "Naturalmente, Longway è lieto di spartire il suo fardello con voi, Mio Signore Capitano.\nLongway cerca la persona viva a lui più cara che gli resta—Chang Xing.";
			link.l1 = "Chang Xing - è il tuo migliore amico, giusto?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_7":
			dialog.text = "Chang Xing è la mia famiglia, mia sorella. È scomparsa anni fa. Per trovarla, Longway cerca chiunque possa sapere dove si trovi.";
			link.l1 = "Che cosa c’entra tutto questo con l’archivio di van Merden? Ha forse a che vedere con la scomparsa di tua sorella?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_8";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_8":
			dialog.text = "Esatto. Tutto è legato insieme. Longway e Johan si conobbero molti anni fa, nella terra che voi chiamate Formosa, molto prima che io arrivassi nell’Arcipelago.";
			link.l1 = "Vi conoscete da così tanti anni? E van Merden c’entra qualcosa? Che storia incredibile! Qual era il suo legame con la sparizione di tua sorella?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_9";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_9":
			dialog.text = "Mi ha aiutato nella mia caccia a uomini davvero spregevoli—persino secondo gli standard dei bianchi. Oliveiro Fermentelos, Antoon van Diemen e Joep van der Vink.";
			link.l1 = "A giudicare dai loro nomi, uno è portoghese, gli altri due sono olandesi.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_10";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_10":
			dialog.text = "Sì, è esatto. Ma la ricerca non ha portato a nulla. Longway ha aspettato con pazienza il segno del Cielo. Così, quando hai preso l’archivio di van Merden, ho deciso di studiarlo io. Quando ho trovato le prime pagine dove si parlava di Oliveiro, le ho strappate e sono fuggito dalla cabina.";
			link.l1 = "Tutto, alla fine, trova il suo posto nella storia.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_11";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_11":
			dialog.text = "Ma la vera storia comincia solo ora. Mio Signore Capitano, volete sentire della ricerca di Longway fin dall’inizio? Siete pronto a sedervi ed ascoltare?";
			link.l1 = "È proprio per questo che vi ho convocato in cabina. Procedete pure.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_12";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_12":
			DialogExit();
			
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			DoQuestReloadToLocation("Formosa", "patrol", "patrol1", "PZ_Formosa_Start");
		break;
		
		case "PZ_Formosa_Tavern_1":
			dialog.text = "Gli uomini cinesi qui non ci mettono piede. Questo è un locale rispettabile, per gente rispettabile – non per tipi come te.";
			link.l1 = "Ho solo una domanda. Lasciami chiedere, poi me ne andrò.";
			link.l1.go = "PZ_Formosa_Tavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_Tavern_2":
			dialog.text = "Prima impara a parlare come si deve! Te l’ho già detto: gente come te qui non la vogliamo.";
			link.l1 = "Dove posso trovare Oliveiro Fermentelos? Dimmi, e me ne andrò subito.";
			link.l1.go = "PZ_Formosa_Tavern_3";
		break;
		
		case "PZ_Formosa_Tavern_3":
			dialog.text = "Anche tu fai finta di non sentire? Non mettermi alla prova, o questo posto puzzerà presto di budella e paura.";
			link.l1 = "La mia gente vive qui da millenni. Questa è la nostra isola, e non possiamo nemmeno entrare in una misera taverna?";
			link.l1.go = "PZ_Formosa_Tavern_4";
		break;
		
		case "PZ_Formosa_Tavern_4":
			dialog.text = "Oh, fai il gradasso, eh? Per questo potresti finire impiccato. Fuori dai piedi!";
			link.l1 = "...";
			link.l1.go = "PZ_Formosa_Tavern_5";
		break;
		
		case "PZ_Formosa_Tavern_5":
			DialogExit();
			locCameraSleep(true);
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("PZ_Formosa_smuggler");
			LAi_CharacterEnableDialog(sld);
			//AddLandQuestMark(sld, "questmarkmain");
			LAi_Fade("PZ_Formosa1_9", "");
		break;
		
		case "PZ_Formosa_smuggler_1":
			dialog.text = "Ho sentito del tuo grosso guaio, piccolo amico. Non dovevi far tanto rumore—nome sbagliato, posto sbagliato.";
			link.l1 = "Ne sai qualcosa di quest’uomo?! Parla!";
			link.l1.go = "PZ_Formosa_smuggler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_2":
			dialog.text = "Calmati, compare.";
			link.l1 = "Chiedo venia.";
			link.l1.go = "PZ_Formosa_smuggler_3";
		break;
		
		case "PZ_Formosa_smuggler_3":
			dialog.text = "Non voglio le tue scuse, ma i tuoi soldi sì. Forse allora ti darò una mano. Mi chiamo Marcelo Schulte. E tu? Hai moneta, giusto?";
			link.l1 = "Il mio nome è Chang Tu. Ho denaro. Questo basta?";
			link.l1.go = "PZ_Formosa_smuggler_4";
		break;
		
		case "PZ_Formosa_smuggler_4":
			dialog.text = "(fischia) Escudos, pesos, fiorini, dobloni... e perfino qualcuna di quelle monete strane che usate voi altri. Questo va bene. Giusto, Chung Chung, vedrò cosa riesco a scoprire su quell’uomo. Non preoccuparti, sono qui quasi ogni giorno, quindi i tuoi soldi sono al sicuro. Passa ogni giorno, ci incontreremo di sicuro, giusto?";
			link.l1 = "Spero di sì. Non mi resta più un soldo...";
			link.l1.go = "PZ_Formosa_smuggler_5";
		break;
		
		case "PZ_Formosa_smuggler_5":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A few days have passed,"+ NewStr() +"April 4, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_tavern", "goto", "goto1", "PZ_Formosa_Spustya4Dnya");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_11":
			dialog.text = "Ah, Chang-Chang! Sei già arrivato.";
			link.l1 = "È Chang Tu.";
			link.l1.go = "PZ_Formosa_smuggler_12";
		break;
		
		case "PZ_Formosa_smuggler_12":
			dialog.text = "Non importa, amico.";
			link.l1 = "Hai scoperto dove si trova Oliveiro?";
			link.l1.go = "PZ_Formosa_smuggler_13";
		break;
		
		case "PZ_Formosa_smuggler_13":
			dialog.text = "No, nemmeno la più pallida idea.";
			link.l1 = "I miei soldi!";
			link.l1.go = "PZ_Formosa_smuggler_14";
		break;
		
		case "PZ_Formosa_smuggler_14":
			dialog.text = "Non essere così nervoso! Pensi che mi sarei avvicinato di nuovo se non avessi scoperto nulla? Ti presenterò qualcuno che sa. E fortunato te, adora voi asiatici. Ha pure dei servitori che ti somigliano—persino delle serve. Sta imparando anche la tua lurida lingua. Si chiama Johan van Merden. Ti aspetterà in una casa a due piani vicino alla residenza.";
			link.l1 = "La mia gratitudine.";
			link.l1.go = "PZ_Formosa_smuggler_15";
		break;
		
		case "PZ_Formosa_smuggler_15":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1_back", "PZ_Formosa1_11", -1);
			LAi_ActorGoToLocation(npchar, "goto", "goto3", "", "", "", "", -1);
			npchar.location = "None";
			LocatorReloadEnterDisable("Formosa", "houseSp1", false);
		break;
		
		case "PZ_Formosa_JohanVanMerden_1":
			dialog.text = "Tu sei Chang Chang, a quanto pare? Avanti, non fare il timido.";
			link.l1 = "È Chang Tu.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2";
			DelLandQuestMark(npchar);
			locCameraFromToPos(-1.91, 2.06, -1.75, true, 2.23, -0.85, 0.85);
		break;
		
		case "PZ_Formosa_JohanVanMerden_2":
			dialog.text = "Ah, davvero? Mi scuso. Quel Marcelo e la sua sfilata di buffonate... Peccato che così pochi mostrino curiosità per la tua gente. E tutto questo solo per una lingua diversa, per la forma dei tuoi occhi. Ma tu sei sveglio. Non come la gente nera, eh eh eh.";
			link.l1 = "(in mandarino) Quindi il contrabbandiere non mentiva—sei davvero un uomo di cultura. E parli davvero la nostra lingua?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2a";
			link.l2 = "Vi porgo il mio ringraziamento per le parole gentili sulla mia cultura. Siete forse Johan van Merden?";
			link.l2.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_2a":
			dialog.text = "Oh... Ho capito solo poche parole. Sto ancora imparando, vede. Potrebbe continuare in olandese?";
			link.l1 = "Come desiderate. Siete Johan van Merden?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_3":
			dialog.text = "Sì, Chung Tu, sono io. Ho sentito che cerchi Oliveiro Fermentelos. So dove trovarlo, ma prima dimmi—perché lo cerchi? La tua risposta deciderà la mia.";
			link.l1 = "Lui... ha rapito l’ultima e più cara della mia famiglia – mia sorella, Chang Xing.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_4";
		break;
		
		case "PZ_Formosa_JohanVanMerden_4":
			dialog.text = "Allora devo deluderti, Chang Tu. Ormai, probabilmente non c’è più speranza per lei. Sarà stata venduta come schiava a qualche ricco piantatore, o gettata in un bordello. In ogni caso, non riuscirai a salvarla.";
			link.l1 = "Credo che Chang Xing sia ancora viva. Oliveiro ha posato gli occhi su di lei. Lei lo ha rifiutato con fierezza. Lui l'ha rapita quando non ero a casa. E... ha massacrato i nostri genitori.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_5";
		break;
		
		case "PZ_Formosa_JohanVanMerden_5":
			dialog.text = "Mi... dispiace davvero. Se è così, Chang Xing—giusto?—potrebbe essere ancora vivo. Ecco che facciamo: dammi un po’ di tempo per scoprire esattamente dove si trova Oliveiro in questo momento. Diciamo una settimana. Ci vediamo di nuovo allora. Incontrami fuori dalle porte della città—non si sa mai chi ti tiene d’occhio qui. Non voglio immischiarmi più di quanto sia abituato, spero tu capisca.";
			link.l1 = "Son... son profondamente grato a Voi, Mio Signore Capitano van Merden. Attendo con ansia il nostro prossimo incontro.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_6";
		break;
		
		case "PZ_Formosa_JohanVanMerden_6":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A week has passed,"+ NewStr() +"April 11, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_ExitTown", "goto", "goto3", "PZ_Formosa_Spustya7Dney");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_JohanVanMerden_11":
			dialog.text = "Ciao, Chung Tu. Vedo la fiamma nei tuoi occhi. Ho delle notizie, ma non sono buone.";
			link.l1 = "Ogni notizia ha per me un valore immenso. Vi prego, raccontate, Mynheer van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_12";
		break;
		
		case "PZ_Formosa_JohanVanMerden_12":
			dialog.text = "Aye... Fermentelos è salpato per Batavia circa un mese fa. È l’unico indizio che ho su di lui. La buona notizia è che si fermerà laggiù per un po’, quindi se parti ora lo raggiungi. La cattiva? È uno degli amici più stretti del Governatore Generale Anthony van Diemen. Non ti lasceranno nemmeno avvicinare.";
			link.l1 = "Questa notizia mi basta. Le mie umili grazie a voi, Mynheer van Merden. Partirò senza indugio.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_13";
		break;
		
		case "PZ_Formosa_JohanVanMerden_13":
			dialog.text = "Qualcosa mi diceva che l’avresti detto, così ho deciso di dare una mano per pareggiare i conti tra te e Chang Xing. Ho scritto una lettera a un vecchio amico mio, Oliver Trust. Possiede una bottega a Batavia. Mi deve un favore, quindi ti aiuterà.";
			link.l1 = "Io... non so proprio cosa dire...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_14";
			//Log_Info("Вы получили письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Formosa_JohanVanMerden_14":
			dialog.text = "Un semplice «grazie» basta. Se non riesci a trovare Oliveiro in città, cerca la Stella del Mattino. Puoi sempre rintracciarlo seguendo la sua nave. Buona fortuna, amico—ne avrai bisogno tu e tua sorella.";
			link.l1 = "Vi ringrazio dal profondo del mio cuore, Mio Signore Capitano van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_15";
		break;
		
		case "PZ_Formosa_JohanVanMerden_15":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Batavia,"+ NewStr() +"May 29, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Batavia", "merchant", "mrcActive5", "PZ_Batavia_Puteshestvie");
			LaunchFrameForm();
		break;
		
		case "PZ_OliverTrust_1": //
			dialog.text = "Chi sei tu, e che diavolo fai qui? Non faccio affari con gente come te.";
			link.l1 = "Ho una lettera per voi.";
			link.l1.go = "PZ_OliverTrust_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_OliverTrust_2":
			dialog.text = "Ah, il messaggero! Anche se oggi non aspettavo alcuna lettera. Resta qui! Vado a dare un’occhiata.";
			link.l1 = "Sei tu Oliver Trust? Van Merden mi ha mandato da te.";
			link.l1.go = "PZ_OliverTrust_3";
			//Log_Info("Вы отдали письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_OliverTrust_3":
			dialog.text = "So leggere, sai. Di solito ti manderei via, ma tipi come van Merden non accettano un no come risposta. Finalmente è giunta l’ora di regolare i conti con van Diemen.";
			link.l1 = "Il mio bersaglio è Fermentelos. E van Diemen, invece?";
			link.l1.go = "PZ_OliverTrust_4";
		break;
		
		case "PZ_OliverTrust_4":
			dialog.text = "Non sono affari tuoi. Dovresti ringraziare il cielo che ti sto anche solo aiutando. Ora ascolta bene, prima che decida che tutto questo è una pessima idea. Conosco Fermentelos. È stato qui per un po', ma ora non c’è più. La Stella del Mattino è salpata qualche settimana fa. Dio solo sa quando tornerà. Quindi la tua preda è cambiata, ed è un amico di Fermentelos...";
			link.l1 = "... van Diemen.";
			link.l1.go = "PZ_OliverTrust_5";
		break;
		
		case "PZ_OliverTrust_5":
			dialog.text = "Aye.   Sai anche questo? Immagino che Johan ti abbia raccontato tutto? Oh, van Merden... sei proprio uno sfrontato, maledetto. Ma se già conosci van Diemen, saprai pure del suo rango, vero? E allora, Mio Signore Capitano, quale sarebbe il tuo gran piano per arrivare al Governatore Generale? Non vorrai certo assaltare la sua residenza a testa bassa, eh!";
			link.l1 = "Chang Tu è un guerriero di gran valore.";
			link.l1.go = "PZ_OliverTrust_6";
		break;
		
		case "PZ_OliverTrust_6":
			dialog.text = "Un guerriero abile, eh? Ti rendi conto che ormai siamo tutti invischiati? E che ne sarà di me se ti catturano? Dovrò aiutarti, per la tua pelle e la mia, ormai. Oltre a vivere nella sua residenza, Van Diemen fa spesso visita alla piantagione fuori città e alla sua amante Vette.";
			link.l1 = "Hai accennato a darmi una mano.";
			link.l1.go = "PZ_OliverTrust_12";
		break;
		
		case "PZ_OliverTrust_12":
			dialog.text = "Credo che ognuno debba avere una passione, un passatempo. Quanto a me, colleziono armi rare e costose. A volte hanno una storia, a volte no, ma sono sempre letali. La mia collezione può tornare utile alla tua crociata. Allora, dimmi, dove prevedi di tendere un agguato a van Diemen?";
			link.l1 = "(Residenza) Dal momento che possiedi così tante buone armi, prenderò la lama migliore. Con questa, Chang Tu sarà invincibile tra gli uomini bianchi.";
			link.l1.go = "PZ_OliverTrust_resedinsia_1";
			link.l2 = "(Piantagione) Li coglierò di sorpresa sulla strada della piantagione – non avranno dove scappare.";
			link.l2.go = "PZ_OliverTrust_Plantation1";
			link.l3 = "(Padrona) La padrona – lì non ci saranno molte persone, quindi le guardie non avranno il tempo di reagire.";
			link.l3.go = "PZ_OliverTrust_lubovnitsa_1";
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			InterfaceStates.Buttons.Save.enable = false;
		break;
		
		// Rebbebion, ну, с Богом...
		case "PZ_OliverTrust_Plantation1":
			pchar.questTemp.PZ_Batavia_plantation_Go = true;
			
			dialog.text = "Buona scelta! Mi hai sorpreso. Per sfruttarla al meglio, ti servirà un'arma da fuoco decente. Dimmi, quanto lontano sai mirare, Chang Tu?";
			link.l1 = "A dirla schietta... non troppo lontano, devo assicurarmi di non mancare il bersaglio."link.l1.go ="Piantagione in vista, Mio Signore Capitano. Siamo abbastanza vicini per sentire l'odore del sangue nascosto sotto il profumo della canna da zucchero.";
			link.l2 = "Colpirò da lontano – il mio nemico non capirà nemmeno da dove gli sia piovuta addosso la morte.";
			link.l2.go = "PZ_OliverTrust_Plantation_FarDistance1";
			notification("Jager Unlocked", "Longway");
			SetCharacterPerk(pchar, "Jager");
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket6"); 
			EquipCharacterByItem(pchar, "mushket6");
			//Log_Info("Вы получили башенный мушкетон");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "grapeshot", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "grapeshot");
			
			dialog.text = "Capisco. In tal caso, prenda questo! Un'antica schioppetta portoghese da torre, spara cartucce di grosso calibro. Non ne forgiano più, nemmeno nel Vecchio Mondo.";
			link.l1 = "Ne ho visto uno quand'ero bambino...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance2";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance2":
			dialog.text = "Allora, sai come si usa?";
			link.l1 = "No...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance3";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance3":
			dialog.text = "Tieni a mente, il meccanismo intercambiabile s’è arrugginito col tempo. Nessun olio potrà sistemarlo – è rotto per sempre. Caricarlo è dura, quindi facciamolo adesso. Osserva bene – serve un po’ di forza, così. Ma non troppa, o lo spaccherai.";
			link.l1 = "Così?";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance4";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance4":
			dialog.text = "Giusto.";
			link.l1 = "Capito. Mille grazie!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_Plantation_FarDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket2x2"); 
			EquipCharacterByItem(pchar, "mushket2x2");
			//Log_Info("Вы получили двуствольный штуцер");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "cartridge", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "cartridge");
			
			dialog.text = "Un vero cacciatore! Attento, questo era un dono. È uno di quei rari casi in cui un'arma è tanto decorata quanto letale. Un fucile da caccia a due canne! Pesante in mano, ma semplice da usare. Hai già capito come sparare con questo coso?";
			link.l1 = "Capito. Grazie infinite!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_lubovnitsa_1":
			dialog.text = "Hai ragione sulle guardie, ma non sottovalutare il pericolo. Van Diemen non mette mai piede in città senza il suo braccio destro, Joep van der Vink.";
			link.l1 = "Quindi, stanno insieme a Vette...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_2";
			pchar.questTemp.PZ_Batavia_lubovnitsa_Go = true;
			AddCharacterSkillDontClearExp(pchar, "Sailing", 10);
			AddCharacterSkillDontClearExp(pchar, "Commerce", 10);
			AddCharacterSkillDontClearExp(pchar, "Repair", 10);
			notification("Naval Skills +", "Longway");
			notification("Rat Wolf Unlocked", "Longway");
			SetCharacterPerk(pchar, "RatsWolf");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_2":
			dialog.text = "Cosa? Ah! Hai proprio una bella fantasia, cinese! Antoon è un codardo, e van der Vink sta lì solo per proteggerlo, nel caso qualcuno rovini il loro 'momento privato'\nJoep indossa sempre una corazza pesante – quasi nessuna lama riesce a trapassarla. Ecco perché anche a te serve qualcosa di speciale. Prendi questo stocco. È lungo, più robusto della maggior parte delle altre spade, e pesa come una vera lama.";
			link.l1 = "Una rapier per combattere chi porta corazza...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_3";
			//Log_Info("Вы получили асоледу");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_26");
			EquipCharacterByItem(Pchar, "blade_26");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_3":
			dialog.text = "Non puntare direttamente sull'armatura – non hai in mano uno stocco. Mira alle fessure, ai punti deboli: l’inguine, le ascelle, la gola. Sfiancalo, imposta tu il ritmo. Joep brandisce pure un’ascia pesante, quindi non cercare di parare – schiva, piuttosto\nSe non trovi spiragli, prendi questa archibugio. Di solito è caricato a pallettoni, ma per te ho preparato una serie di dardi d’acciaio.";
			link.l1 = "Frecce per un moschetto...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_4";
			//Log_Info("Вы получили бландербуз");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "pistol8");
			EquipCharacterByItem(Pchar, "pistol8");
			AddItems(Pchar, "harpoon", 30);
			AddItems(Pchar, "gunpowder", 30);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "harpoon");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_4":
			dialog.text = "Insolito, giusto? Un miscuglio di vecchio e nuovo. È pensato per sparare con una mano sola, ma se è troppo pesante, usane pure due. Molti fanno così./Ecco, prova anche questa corazza di vimini. È più leggera della corazza di Joep, ma ti protegge comunque abbastanza bene. Non lasciare che la sua ascia ti colpisca in pieno — nemmeno un’armatura di Milano resisterebbe a quell’arma. Hai capito?";
			link.l1 = "Sì, capisco. Grazie, Signor Fiducia!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили кожаный корсет");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "cirass5");
			EquipCharacterByItem(Pchar, "cirass5");
		break;
		
		case "PZ_OliverTrust_resedinsia_1":
			dialog.text = "Sicuro di te, eh? Forse ti ho parlato troppo presto della mia collezione. Ma... ormai sei dentro fino al collo. Assaltare una residenza in pieno giorno è da veri pazzi, nessuno se lo aspetta. Questa lama dovrebbe andare a genio ai tuoi scopi. Non è la migliore al mondo, ma per trafiggere, tagliare e spaccare è proprio l’ideale.";
			link.l1 = "Clewang! Questa lama la conosco. Gente delle isole vicine la usa spesso.";
			link.l1.go = "PZ_OliverTrust_resedinsia_2";
			pchar.questTemp.PZ_Batavia_resedinsia_Go = true;
			notification("Duelist Unlocked", "Longway");
			SetCharacterPerk(pchar, "FencingMaster");
			SetCharacterPerk(pchar, "HT1");
		break;
		
		case "PZ_OliverTrust_resedinsia_2":
			dialog.text = "Have you used one before? Good. You'll have little time and many enemies to face. Here, take this as well - a handgun with three barrels, beautifully inlaid. Load it now in front of me; you won't have time for that later. And wear this dueling waistcoat. It's light, it will give you the speed you'll need, and some protection.";
			link.l1 = "Grazie, signor Fiducia!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили клеванг");
			//Log_Info("Вы получили трёхствольный дробовик");
			//Log_Info("Вы получили жилет бретера");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_30");
			EquipCharacterByItem(Pchar, "blade_30");
			GiveItem2Character(PChar, "pistol2");
			EquipCharacterByItem(Pchar, "pistol2");
			GiveItem2Character(PChar, "cirass6");
			EquipCharacterByItem(Pchar, "cirass6");
			AddItems(Pchar, "grapeshot", 50);
			AddItems(Pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "grapeshot");
		break;
		
		case "PZ_OliverTrust_13":
			dialog.text = "Aspetta, non abbiamo ancora finito. È nel nostro interesse comune che tu resti vivo. Prendi questa medicina per curare le tue ferite dopo la battaglia. \nE anche quest’elisir. Fa schifo al gusto e all’odore, ma stronca ogni veleno che ti scorre nelle vene. Joep van der Vink, la guardia del corpo di Van Diemen, unge le sue lame con quella porcheria. Spavaldo bastardo, così tu avrai il vantaggio.";
			link.l1 = "Non so se potrò mai ringraziarvi abbastanza, Mio Signore Capitano...";
			link.l1.go = "PZ_OliverTrust_14";
			//Log_Info("Вы получили 10 лечебных зелий");
			//Log_Info("Вы получили противоядие");
			PlaySound("interface\important_item.wav");
			AddItems(Pchar, "potion1", 10);
			AddItems(Pchar, "potion3", 1);
		break;
		
		case "PZ_OliverTrust_14":
			dialog.text = "Il miglior ringraziamento sarebbe non consegnarmi se ti beccano. Anche se, molto probabilmente, ti taglieranno la gola subito. Ma se riesci a restare vivo, dì a Van Diemen che deve la sua morte a me. Puoi farlo?";
			link.l1 = "Nessun problema. Ti ringrazio ancora, Signor Fidato. Addio!";
			link.l1.go = "PZ_Batavia_NaOhotu";
		break;
		
		case "PZ_Batavia_NaOhotu":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				DoQuestReloadToLocation("Batavia", "reload", "reload1", "PZ_Batavia_BitvaSoStrazhnikami");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				DoQuestReloadToLocation("Batavia_HouseF3", "reload", "reload1", "PZ_Batavia_BitvaLubovnitsa");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				/*EndQuestMovie();
				sld = &Locations[FindLocation("Batavia_plantation")];
				sld.locators_radius.quest.detector4 = 3.0;
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1 = "locator";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.location = "Batavia_plantation";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator_group = "quest";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator = "detector4";
				PChar.quest.PZ_Batavia_plantation1.win_condition = "PZ_Batavia_plantation_selfdialog";*/
				DoQuestReloadToLocation("Batavia_plantation", "quest", "detector2", "PZ_Batavia_plantation_setguards");
			}
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_1":
			dialog.text = "Fermo! Dove credi d’andare, cinese?";
			link.l1 = "Alla residenza.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_2";
			locCameraFromToPos(-0.44, 7.45, 24.65, true, -1.90, 5.10, 18.50);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_2":
			dialog.text = "Era una domanda retorica, genio. Cosa ti fa credere che qualcuno lascerebbe entrare uno come te là dentro?";
			link.l1 = "Ho affari con il signor Van Diemen. Fammi passare, per favore.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_3";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_3":
			dialog.text = "Sapete il nome del governatore generale? Bene... ditemi qual è il vostro affare. Lo riferirò e vi farò sapere la risposta.";
			link.l1 = "La mia conversazione è solo con Mynheer Van Diemen. Mi sta aspettando. Spostati, oppure te ne pentirai.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_4";
			locCameraSleep(true);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_4":
			dialog.text = "Eh, eh, non cantare vittoria, occhi stretti. O si fa come dico io, oppure niente.";
			link.l1 = "Allora si va come dico io.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_5";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_5":
			DialogExit();
			LAi_SetActorType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_SoldResid_1"));
			LAi_group_MoveCharacter(pchar, LAI_GROUP_PLAYER);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			
			sld = CharacterFromID("PZ_SoldResid_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
				
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			DoQuestCheckDelay("PZ_Batavia_resedinsia_1", 0.9);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_1":
			dialog.text = "Maledetto villano! Chi ti ha messo alle calcagna? Ti pago più di quella feccia, se vuoi!";
			link.l1 = "Voi bianchi pensate solo all’oro. Che i draghi maledicano la vostra razza. Son venuto per avere notizie, ma la vostra gente non mi lascia entrare.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2":
			dialog.text = "Cosa vuoi?!";
			link.l1 = "Fermentelos. Dove si nasconde adesso?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3":
			dialog.text = "Oliveiro? Ma perché diavolo lo cerchi? Non ti dirò proprio niente!";
			link.l1 = "Ha massacrato la mia famiglia e rapito mia sorella. Il mio consiglio, Mio Signore Capitano: cominciate a parlare. Per il vostro stesso bene.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4":
			dialog.text = "Cosa pensi di farmi? Tra poco tutta la guarnigione sarà qui.";
			link.l1 = "Hai mai sentito parlare di Lynchy? È una punizione della mia gente. Vuol dire ‘Morte per Mille Tagli’.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5":
			dialog.text = "Non avrai il tempo di farmi a pezzi, idiota!";
			link.l1 = "È un modo di dire. Il boia incide tagli, uno dopo l’altro. O taglia via pezzi di carne. Facciamo quello che riusciamo finché c’è tempo – a meno che tu non cominci a parlare.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Sepp", "mercen_26", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
			sld.name = "Joep";
			sld.lastname = "van der Vink";
			GiveItem2Character(sld, "topor_04");
			EquipCharacterByItem(sld, "topor_04");
			GiveItem2Character(sld, "pistol3");
			EquipCharacterByItem(sld, "pistol3");
			sld.CantLoot = true;
			LAi_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Batavia_townhallRoom", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			
			LAi_SetStayType(pchar);
			locCameraFromToPos(-3.06, 1.64, -0.43, true, 1.87, -1.20, 2.39);
			DoQuestCheckDelay("PZ_Batavia_BitvaResidensia_7", 2.5);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_7":
			dialog.text = "A-A-A!!! Basta! Basta, bastardo lurido. Te lo dico, te lo dico tutto. Solo fermati. Joep! Finalmente! Dove diavolo sei stato tutto questo tempo?!";
			link.l1 = "Che tempismo maledetto...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9":
			dialog.text = "Antoon? Devi vedere un medico subito. Ti ci porto appena finisco qui. E tu! Che diavolo fai, macellaio codardo?!";
			link.l1 = "Macellaio Giallo? Mi piace, in un certo senso. Ma c’è solo una domanda che mi tormenta, e nessuno sembra avere il coraggio di rispondermi...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10":
			dialog.text = "Che domanda?!";
			link.l1 = "Dove si trova Oliveiro Fermentelos? Non puoi dirmelo e basta?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11":
			dialog.text = "Non me ne frega un accidente di Fermentelos! Chi ti ha dato i soldi e le informazioni?!";
			link.l1 = "Oliver Trust. Ah, e mi ha detto di riferirti che gli devi la tua morte.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12";
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_ActorSetGroundSitMode(sld);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12":
			dialog.text = "Fiducia?! Ah-ah-ah-ah-ah-ah-ah! Quel pidocchioso credeva di potersi vendicare solo perché gli abbiamo portato via la piantagione? Presto gli prenderemo la bottega e la vita, appena avrò finito con te.";
			link.l1 = "Stai sprecando il mio tempo.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1.character = "PZ_Sepp";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition = "PZ_Batavia_BitvaResidensia_8";
		break;
		
		case "PZ_Batavia_PlantationSelfDialog":
			dialog.text = "(in mandarino) Allora, cerchiamo un buon posto per un agguato.";
			if (CheckCharacterItem(pchar, "mushket6"))
			{
				link.l1 = "(in mandarino) Con questo ferro arrugginito, dovrò avvicinarmi. Scarica rapida - tagliente e spietata. Il terrore e il panico faranno il resto.";
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = "(in mandarino) Proprio qui. All’inizio non mi noteranno nemmeno. Le battaglie migliori sono quelle che non cominciano... o che finiscono in fretta, senza troppo spargimento di sangue.";
				link.l1.go = "Exit";
			}
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_Batavia_PlantationFight");
		break;
		
		case "PZ_Batavia_PlantationDimen1":
			if (!CharacterIsAlive("PZ_SoldPlantation_1") && !CharacterIsAlive("PZ_SoldPlantation_2") &&  !CharacterIsAlive("PZ_SoldPlantation_3") && !CharacterIsAlive("PZ_SoldPlantation_4") && !CharacterIsAlive("PZ_SoldPlantation_5") && !CharacterIsAlive("PZ_SoldPlantation_6"))
			{
				dialog.text = "Brutto bastardo... Sei uno schiavo fuggiasco, vero? Dove diavolo hai preso un’arma del genere? Ti ha mandato qualcuno...?";
				link.l1 = "Niente tempo! Dimmi subito dov’è Oliveiro Fermentelos – ora!";
				link.l1.go = "PZ_Batavia_PlantationDimen2";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_PlantationDimenSit");
			}
		break;
		
		case "PZ_Batavia_PlantationDimen2":
			dialog.text = "Hehehe, divertente... Non c’è tempo – il sangue mi scorre fuori dalla pancia. Brucia all’inferno, pagano...";
			link.l1 = "(in mandarino) No!!!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_Batavia_PlantationDimenDead1");
		break;
		
		case "PZ_Batavia_Plantation_DimenDeadSelfDialog":
			dialog.text = "(in mandarino) Perché, perché, perché?! E adesso come diavolo dovrei trovare Fermentelos?!";
			link.l1 = "Ma prima, devo nascondermi – qualcuno avrà già fatto rapporto su questa carneficina...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_1":
			dialog.text = "Hic! Un cinese! Non mi aspettavo che uno come te fosse invitato qui. Ti piace guardare, eh? Hehe.";
			link.l1 = "Perché ci sono così tante persone qui...? E tu chi diavolo sei?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_2":
			dialog.text = "Non mi riconosci dai miei abiti? E bada come parli al Governatore Generale! Hic!";
			link.l1 = "Dunque, voi dovete essere il Signor Van Diemen. Mi scuso per la mia ignoranza. Che sia forse una fiera quella che vedo qui?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_3";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_3":
			dialog.text = "Proprio così, brav’uomo, e non si discute! Un carnevale di travestiti! Ah-ah-ah! Non male, villano! Son certa che Luthers impazzirebbe dalla voglia di indossare il vestito di Vette, ah ah ah!";
			link.l1 = "Luthers?..";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4";
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4":
			dialog.text = "Quell’ometto miserabile che chiama marito, gli piace spiare dall’armadio mentre la sua cara mogliettina si fa montare da un altro. E lei? Neanche ci bada!";
			link.l1 = "";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4_1";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, sld);
			CharacterTurnByChr(pchar, sld);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), sld);
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_4", 2.5);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4_1":
			Event("QuestDelayExit","sl", "", 0);
			dialog.text = "Giusto, Vette, tesoro mio? Eh-eh.";
			link.l1 = "(in mandarino) Che diavolo sta succedendo qui...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_5";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, CharacterFromID("PZ_Brigitta"));
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), npchar);
			locCameraFromToPos(-2.21, 1.90, 2.26, true, -0.81, -0.40, 4.36);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_5":
			dialog.text = "Hic! Non so cosa tu abbia appena detto, ma dallo sguardo e dal tono mi pare che tu sia d'accordo con me! Van Haan è proprio un porco maledetto. E tu chi saresti? Un operaio? Ti ha portato Vette, giusto?";
			link.l1 = "Io...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_6";
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), pchar);
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_7":
			dialog.text = "Portare qui un manovale è davvero troppo, persino per Vette. Questo qui è chiaramente smarrito e nel posto sbagliato. Ehi, tu. Sparisci e dimentica tutto quello che hai visto. Chi è il tuo padrone? Lo contatteremo noi, e sarete entrambi pagati per tenere la bocca chiusa. Magari ti lasceranno pure tornare dalla tua famiglia nel continente. Rispondi e levati dai piedi.";
			link.l1 = "In verità, sono qui per affari.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_8";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_8":
			dialog.text = "Heh, affari. Solo il signor van Diemen fa davvero “Affari” qui. Il mio compito è tenerlo al sicuro da gente come voi. E Luthers... fa il Luthers. Oppure... è stata davvero Vette a invitarti qui?";
			link.l1 = " No, sono qui per...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_9";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_9":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Rubbe");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_10":
			dialog.text = "La mia cara Vette porterebbe davvero qui uno stramaledetto muso giallo?! Fuori dai piedi!!!";
			link.l1 = "Quel miserabile cornuto...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_11";
			link.l2 = "Nessuno ti sta parlando. Chiudi quella fogna. Non fare finta di avere coglioni o dignità.";
			link.l2.go = "PZ_Batavia_BitvaLubovnitsa_12";
			GiveItem2Character(npchar, "blade_06");
			EquipCharacterByItem(npchar, "blade_06");
			LAi_SetActorType(npchar);
			npchar.model.animation = "man";
			Characters_RefreshModel(npchar);
			SetCameraDialogMode(npchar);
			locCameraToPos(-1.88, 1.72, 0.27, false);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_11":
			dialog.text = "Co-co-cornuto?! No, io la amo più di me stesso. Ah, uno stupido cinese come te non capirebbe mai, giusto?";
			link.l1 = "(in mandarino) Maledetto bastardo.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_12":
			dialog.text = "Co-co-cazzo?! Va tutto bene! Sì! So solo che altri uomini danno più piacere alla mia cara Vette, tutto qui!";
			link.l1 = "Come diciamo nella mia terra, un uomo resta uomo finché gli rimane anche solo un dito. Se tu fossi uomo, lo capiresti.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_13":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Brigitta");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_14":
			dialog.text = "Non l’ho certo invitato io, però, sai, è piuttosto simpatico. Magari si fermerà anche dopo che ve ne sarete andati tutti. L’ho già provato con il nostro cane, ma non l’ho mai fatto con...";
			link.l1 = "Taci, quando parlano gli uomini, sgualdrina! L’unica bestia qui sei tu. Io sono qui per affari. Cerco Oliveiro Fermentelos. Dovete essere suoi amici. Potreste dirmi dove posso trovarlo, signor Van Diemen?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_15";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_15":
			dialog.text = "Antoon, mi ha insultata! Mi ha insultata! Non vorrai mica lasciar correre, giusto?!";
			link.l1 = "...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_16";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_16":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_AntoniOneDimen");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_17":
			dialog.text = "Hehe, scusa, amico, ma la signorina è furiosa. Temo che dovrò insegnarti un po' di buone maniere. Lezione uno.";
			link.l1 = "Ma potete aiutarmi nella mia ricerca di Oliveiro?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_18";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_18":
			dialog.text = "Non servirà a nulla per uno schiavo morto.";
			link.l1 = "(in mandarino) Maledetti tutti voi...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_19";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_19":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			PlaySound("Voice\Russian\hambit\Longway-02.wav");
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Sepp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Rubbe");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Batavia_BitvaLubovnitsa_3");
			
			sld = CharacterFromID("PZ_Brigitta");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			PlaySound("People Fight\Peace_woman_death_05.wav");
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_5", 3.0);	//Нужно ещё раз, а то не бежит
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_21":
			dialog.text = "(in mandarino) Maledizione! Non ho imparato un accidente!";
			link.l1 = "(in mandarino) Non dimenticherò mai questo giorno... Devo andarmene prima che arrivino le guardie. Non che si preoccupino dei lamenti che escono da questo manicomio...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_14":
			dialog.text = "(in mandarino) Gli dei hanno maledetto questo giorno! Van Diemen è morto dissanguato mentre io mi occupavo del suo scagnozzo...!";
			link.l1 = "(in mandarino) Le guardie stanno arrivando. Dovrò farmi strada a colpi di spada per uscire di qui.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final":
			DialogExit();
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_30");
				TakeItemFromCharacter(pchar, "pistol2");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_26");
				TakeItemFromCharacter(pchar, "pistol8");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				TakeItemFromCharacter(pchar, "mushket6");
				TakeItemFromCharacter(pchar, "mushket2x2");
			}
			EquipCharacterByItem(Pchar, "blade_11");
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			
			
			SetCurrentTime(2, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Formosa,"+ NewStr() +"26 July 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa", "goto", "goto7", "PZ_Formosa2_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_21":
			dialog.text = "Oh, è Chang Chang! Di cosa hai bisogno stavolta, mio piccolo amico?";
			link.l1 = "È Chang Tu... che vuoi dire?";
			link.l1.go = "PZ_Formosa_smuggler_22";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_22":
			dialog.text = "Stai grondando disprezzo per me, vero? Non saresti venuto qui se non ti servisse qualcosa.";
			link.l1 = "Sapete dove si trova van Merden? È in città? Non è a casa sua. Devo parlargli.";
			link.l1.go = "PZ_Formosa_smuggler_23";
		break;
		
		case "PZ_Formosa_smuggler_23":
			dialog.text = "Un uomo non può certo starsene chiuso in casa tutto il giorno, ad aspettare che arrivi uno solo dalla pelle gialla. Ha faccende da sbrigare sull’isola. Tornerà in città stanotte, quindi non preoccuparti, Chang Chang!";
			link.l1 = "Grazie. Addio.";
			link.l1.go = "PZ_Formosa_smuggler_24";
		break;
		
		case "PZ_Formosa_smuggler_24":
			SetCurrentTime(1, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestReloadToLocation("Formosa", "goto", "goto7", "PZ_Formosa2_IshemMerden_3");
		break;
		
		case "PZ_Formosa_bandit_1":
			dialog.text = "Ehi, occhi stretti! Dove corri a quest’ora? Tutta la brava gente ormai dorme.";
			link.l1 = "E allora tu?";
			link.l1.go = "PZ_Formosa_bandit_2";
		break;
		
		case "PZ_Formosa_bandit_2":
			dialog.text = "Ben detto! Siamo in pattuglia! Si dice che un piccolo bastardo giallo si aggiri per la città, importunando brava gente timorata di Dio.";
			link.l1 = "Chi potrebbe essere, ditemi?";
			link.l1.go = "PZ_Formosa_bandit_3";
		break;
		
		case "PZ_Formosa_bandit_3":
			dialog.text = "Basta chiacchiere – si sta facendo tardi e inizio ad avere sonno.";
			link.l1 = "Presto il tuo sonno sarà eterno.";
			link.l1.go = "PZ_Formosa_bandit_4";
		break;
		
		case "PZ_Formosa_bandit_4":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_JohanVanMerden");
			ChangeCharacterAddressGroup(sld, PChar.location, "patrol", "patrol7");
			GiveItem2Character(sld, "blade_31");
			EquipCharacterByItem(sld, "blade_31");
			LAi_SetActorType(sld);
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_FormosaBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Formosa2_IshemMerden_7");
			
			DoQuestCheckDelay("PZ_Formosa2_IshemMerden_6", 10.0);
		break;
		
		case "PZ_Formosa_JohanVanMerden_21":
			dialog.text = "Chang Tu, tutto bene, giusto?";
			link.l1 = "Mynheer van Merden! Io sto bene, grazie al vostro intervento. E voi, tutto a posto? Questa è la domanda che conta di più.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_22";
		break;
		
		case "PZ_Formosa_JohanVanMerden_22":
			dialog.text = "Sempre a pensare agli altri, vero? Abbiamo questa cosa in comune. Non potevo starmene lì a guardare mentre ti assalivano, anche se sapevo che te la saresti cavata. Per rispondere alla tua domanda, sto bene, solo un po' stanca. Le gambe mi tremano un po'. Entriamo, se non ti dispiace. Lì possiamo parlare.";
			link.l1 = "Ma certo, Mynheer van Merden, dopotutto questa è casa vostra.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_23";
		break;
		
		case "PZ_Formosa_JohanVanMerden_23":
			DoQuestReloadToLocation("Formosa_houseSp1", "goto", "goto1", "PZ_Formosa2_IshemMerden_8");
		break;
		
		case "PZ_Formosa_JohanVanMerden_24":
			dialog.text = "Ora possiamo parlare senza fretta, in pace e tranquillità. Dimmi, cosa ti porta da me, Chang Tu?";
			link.l1 = "Hai ragione, Mynheer van Merden. Sono appena tornato da Batavia, e...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_25";
		break;
		
		case "PZ_Formosa_JohanVanMerden_25":
			dialog.text = "Aspetta. È forse il povero Chang Xing...?";
			link.l1 = "No, affatto! Spero proprio di no. Il cielo ancora tiene il suo destino nascosto a me. E quanto a Fermentelos... non si trova a Batavia. Van Diemen non mi ha aiutato per nulla.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_26";
		break;
		
		case "PZ_Formosa_JohanVanMerden_26":
			dialog.text = "Non lo farebbe mai, lui e Oliveiro sono vecchi compari. Come dicono gli inglesi, amici e complici. Mi stupirei se ti desse qualcosa di utile.";
			link.l1 = "Sì, grazie a te e a Trust, ho messo le mani su armi potenti. Ho assalito Van Diemen per interrogarlo e scoprire dove fosse Fermentelos. Ma è crepato prima che potessi cavargli qualcosa...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_28";
		break;
		
		case "PZ_Formosa_JohanVanMerden_28":
			dialog.text = "Impressionante.  Hai capito che la gente non parla mai per il solo gusto di parlare.  Così hai imparato che esistono... altri sistemi per sciogliere le lingue, diciamo così.  Pensavo avessi scoperto della morte di tua sorella e che per questo fossi impazzito.  Ma allora, cosa ti spinge da me adesso?  Ti ho già detto che non so dove vada Fermentelos, a parte quelle rare volte in cui si fa vedere a Batavia.  Con Van Diemen fuori gioco, anche quell’ultima traccia è svanita.";
			link.l1 = "Ma voi conoscete molte cose e molta gente. Pensavo che forse potreste aiutarmi ancora, magari chiedendo in giro di Fermentelos, come avete fatto prima. Siete stato il primo uomo bianco a trattarmi bene. Il primo... amico bianco.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_29";
		break;
		
		case "PZ_Formosa_JohanVanMerden_29":
			dialog.text = "È... commovente.";
			link.l1 = "Mynheer van Merden, perché sorridete...?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_30";
		break;
		
		case "PZ_Formosa_JohanVanMerden_30":
			dialog.text = "Eh? Oh, perdonami, Chang Tu. Sto invecchiando, diventando sentimentale e malinconico col tempo. Questo sorriso è sincero – non potrei nasconderlo. Mi fa piacere che tu mi consideri amico. E dato che siamo amici, mi aspetto che ogni tanto tu mi dia una mano. In cambio, ti aiuterò senz’altro con Fermentelos. Non temere – non stai camminando in una trappola.";
			link.l1 = "Hmm, aiutarti in che modo?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_31";
		break;
		
		case "PZ_Formosa_JohanVanMerden_31":
			dialog.text = "Da quando ci siamo visti l’ultima volta, ho approfondito lo studio della vostra lingua e cultura, in particolare la medicina. Vorrei che ogni tanto mi procurassi certe tavolette antiche. Ti ricompenserò generosamente, come per qualunque altro incarico. E spero che potremo esercitarci a parlare cinese ogni tanto. Mi vergogno a chiederlo ai miei servi, ma a un amico...";
			link.l1 = "Chang Tu farà tutto il possibile, Signore van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_32";
		break;
		
		case "PZ_Formosa_JohanVanMerden_32":
			dialog.text = "Bene. Io e te abbiamo una lunga strada davanti, amico mio. Una lunga strada. Ah! Penso sarebbe un ottimo nome di copertura per te. È utile per il mio mestiere. In olandese dicono “Lange Afstand.” Gli inglesi dicono “Long Way.” Quale preferisci?";
			link.l1 = "Preferisco la versione inglese. Lungo. Tragitto. Longway. Suona bene nella mia lingua. Grazie per aver ascoltato, Mio Signore van Merden. Longway attenderà il vostro comando e sarà pronto ad assistervi e soddisfare le vostre richieste.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_33";
		break;
		
		case "PZ_Formosa_JohanVanMerden_33":
			DialogExit();
			
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			bQuestDisableMapEnter = true;
			pchar.GenQuest.CabinLock = true;
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_SegodnyaVremya_2", 5.0);
		break;
		
		// Этап 3, СЛЕД ЗВЕЗДЫ
		case "PZ_Longway_PosleRasskaza":
			dialog.text = "Parlando dell’archivio, Mio Signore Capitano, l’avete con voi? È tutto ciò che mi occorre – il cifrario lo porto già inciso nella memoria.";
			if (CheckCharacterItem(pchar, "MerdokArchive"))
			{
				notification("All Skills +", "Longway");
				AddCharacterExpToSkill(npchar, "Leadership", 50);
				AddCharacterExpToSkill(npchar, "FencingL", 50);
				AddCharacterExpToSkill(npchar, "FencingS", 50);
				AddCharacterExpToSkill(npchar, "FencingH", 50);
				AddCharacterExpToSkill(npchar, "Pistol", 50);
				AddCharacterExpToSkill(npchar, "Fortune", 50);
				AddCharacterExpToSkill(npchar, "Sneak", 50);
				AddCharacterExpToSkill(npchar, "Sailing", 50);
				AddCharacterExpToSkill(npchar, "Accuracy", 50);
				AddCharacterExpToSkill(npchar, "Cannons", 50);
				AddCharacterExpToSkill(npchar, "Grappling", 50);
				AddCharacterExpToSkill(npchar, "Defence", 50);
				AddCharacterExpToSkill(npchar, "Repair", 50);
				AddCharacterExpToSkill(npchar, "Commerce", 50);	
				
				link.l1 = "Sì, l'ho tenuto, pensando che un giorno potesse tornare utile.";
				link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_1";
			}
			else
			{
				link.l1 = "Purtroppo no. Era davvero l’ultima speranza di ritrovare tua sorella?";
				link.l1.go = "PZ_Longway_PosleRasskaza_2";
			}
		break;
		
		case "PZ_Longway_PosleRasskaza_2":
			dialog.text = "Longway è assai lieto che Mio Signore Capitano si preoccupi. Per ora, ancora c'è speranza. Ho trovato una nuova traccia su Guadeloupe.";
			link.l1 = "D'accordo, allora. Raccontami cosa ti è successo laggiù.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_1":
			dialog.text = "È stata una scelta saggia. Forse là dentro troveremo qualcosa che ci aiuterà a cercare Chang Xing.";
			link.l1 = "Sarebbe perfetto. Studiamolo subito.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_2";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_2":
			dialog.text = "Sì, studiamolo insieme. L’anno è... 1637. Antoon van Diemen ha venduto... ha venduto...";
			link.l1 = "Schiavi, giusto?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_3";
			AddQuestRecordInfo("PZ_ArchiveOneMerden", "1");
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_3":
			dialog.text = "Donne della mia gente, vendute a ricchi uomini bianchi.";
			link.l1 = "È orribile.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_4":
			dialog.text = "Mio Signore Capitano, non vi vedo sorpreso. Non vi turba affatto il destino di quelle donne?";
			link.l1 = "Longway, of course it sincerely troubles me. I've seen this filth from the inside. But I've always been an advocate for women... and a bit of a ladies' man, to be honest. It's good you killed van Diemen; he deserved it. Is there anything else?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_5":
			dialog.text = "Van Diemen lavorava solo con chi si fidava ciecamente – Joep van der Vink, la sua mano destra, e quel dannato Oliveiro Fermentelos. E... e...";
			link.l1 = "Che c’è? Sei diventato pallido, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_6":
			dialog.text = "Johan van Merden...";
			link.l1 = "Mi dispiace tanto. È terribile, ma perché sei così sconvolto? Prima hai detto di aver strappato tutte le pagine che parlavano di Fermentelos. Non hai trovato il nome di van Merden allora?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_7";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_7":
			dialog.text = "Longway aveva fretta e dev'essersi lasciato sfuggire questo dettaglio importante.";
			link.l1 = "Capisco. Quando siete pronti, continuiamo la ricerca e vediamo se troviamo qualcosa che possiamo usare subito.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_8";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_8":
			dialog.text = "È scritto che Fermentelos mandava i suoi uomini a caccia di donne, le sostituiva e cancellava ogni traccia. Poi Merden le spediva a Batavia, dove van der Vink e van Diemen vendevano le nostre donne ai bianchi. Se solo l’avessi saputo prima...";
			link.l1 = "Dunque, alla fine hanno fatto tutti comunella. Non incolparti, Longway. Non potevi saperlo. L’archivio è arrivato tra le tue mani solo di recente. C’è qualcos’altro?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_9";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_9":
			dialog.text = "Sì. Sono quasi dieci anni che vanno avanti così. Tante donne hanno perso le loro famiglie, il loro onore, ogni speranza... Ma poi Fermentelos ha smesso di fare affari con van Merden. È solo per questo che mi ha aiutato – tutto ciò che desiderava era sbarazzarsi del suo vecchio compare.";
			link.l1 = "Quali altri dettagli delle loro luride malefatte sono annotati qui?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_10";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_10":
			dialog.text = "Altre delle nere elucubrazioni di van Merden. Ha scoperto che van Diemen lo stava fregando con il denaro. Così mi ha mandato a Batavia, sperando che ci lasciassi la pelle, ma anche che portassi con me van Diemen all’inferno.";
			link.l1 = "Freddo. Ma anche incredibilmente astuto.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_11";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_11":
			dialog.text = "Poteva andare ancora peggio. È stato van Merden a mandare quei tagliagole a casa sua per farmi fuori. È intervenuto solo quando ha capito che avrei potuto farcela da solo, Mio Signore Capitano.";
			link.l1 = "Aveva tutto calcolato, senza ombra di dubbio.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_12";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_12":
			dialog.text = "Dopo che sono tornato vivo, deve aver pensato che avessi scoperto le sue vere intenzioni e fossi venuto per vendetta. Durante la nostra conversazione, teneva la pistola puntata sotto il tavolo. Ma poi l’ho chiamato mio primo amico bianco... e quello quasi scoppiava a ridere...";
			link.l1 = "È terribile, Longway. Fa male scoprire che quelli che credevamo amici ridevano di noi alle nostre spalle tutto il tempo.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_13";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_13":
			dialog.text = "Longway ha imparato qualcosa molto tempo fa, poco prima di mettere piede in questo arcipelago. Sono stato preso dai portoghesi e volevano impiccarmi. Lord Rodenburg mi ha salvato la vita.";
			link.l1 = "È così che sei finito al suo servizio? Anche Lucas era a Formosa?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_14";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_14":
			dialog.text = "Sì, esatto. E non solo lui – anche Van Berg. Van Merden mi disse che fu lui a consigliare Rodenburg di risparmiarmi. Ma tempo dopo Longway seppe da una fonte poco raccomandabile che in realtà fu proprio Johan a mandare i portoghesi sulle mie tracce. Allora non ci credevo... ma ora capisco che potrebbe essere vero...";
			link.l1 = "Rivoltante.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_15";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_15":
			dialog.text = "Eppure, quel giorno i dubbi si sono annidati nel mio cuore. Così, quando ho saputo che Mio Signore Capitano e van Merden si erano affrontati, Longway ha ricordato la vostra gentilezza e si è schierato dalla vostra parte.";
			link.l1 = "Quella era la scelta giusta, Longway. Eh, guarda un po’, alla fine il tuo primo vero amico bianco ero proprio io.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_16";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_16":
			dialog.text = "Così va a finire, Mio Signore Capitano. Ora capisco. Van Merden mi disse che ero suo amico. Ma in verità, Longway non era altro che un altro bracciante per lui – soltanto un po’ più utile degli altri. Tutto qui. Le altre pagine riguardano contabilità e affari tra Van Berg e Rodenburg.";
			link.l1 = "Capisco. E ora è proprio il momento che tu mi racconti cosa hai combinato a Guadeloupe.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_3":
			dialog.text = "Cercavo la Stella del Mattino. Una delle pagine strappate dagli archivi diceva che era stata vista l’ultima volta vicino a San Cristoforo.";
			link.l1 = "Perché lì? Avevamo concordato di incontrarci a Guadalupa, ed è lì che ti ho trovato.";
			link.l1.go = "PZ_Longway_PosleRasskaza_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_4":
			dialog.text = "Perché Saint Christopher è la tana di Georges Gravel, uno degli informatori di van Merden. Georges pensa che io sia ancora al servizio di Johan. Inoltre, Gravel ha commesso una volta un torto grave contro van Merden. E Longway ha aiutato a nasconderlo.";
			link.l1 = "E quale sarebbe stata l’offesa?";
			link.l1.go = "PZ_Longway_PosleRasskaza_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_5":
			dialog.text = "Non è importante. Ciò che conta è che Georges aveva un debito con Longway. Così, sono andato alla chiesa dove Gravel fa l'assistente prete. Mio Signore Capitano vuole ascoltare il resto? Sembra un po' distratto.";
			link.l1 = "Scusa, mi sono distratta. Sì, certo, vai pure, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_6":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Capsterville,"+ NewStr() +"St. Christopher Island.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "patrol", "patrol12", "PZ_Kapstervil_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Zhorzh_1":
			dialog.text = "Bene, non sei arrivato troppo tardi. Non vorrei restare qui un attimo di più del necessario, sai! Di cosa hai bisogno stavolta, Longway?";
			link.l1 = "Cambia tono, Gravel. L’organizzazione ha bisogno dei tuoi servigi.";
			link.l1.go = "PZ_Zhorzh_2";
		break;
		
		case "PZ_Zhorzh_2":
			dialog.text = "Devo ammettere, non ho loro notizie da molto tempo. Si sono forse dimenticati di me?";
			link.l1 = "Posso rinfrescare loro la memoria. Magari raccontando a Lord van Merden quel che hai combinato.";
			link.l1.go = "PZ_Zhorzh_3";
		break;
		
		case "PZ_Zhorzh_3":
			dialog.text = "Va bene, va bene, non c’è bisogno di infuriarsi così! Che posso fare per te, giusto?";
			link.l1 = "Mi serve sapere tutto sulla Stella del Mattino. Qualsiasi cosa trovi, va bene. Più ne hai, meglio è.";
			link.l1.go = "PZ_Zhorzh_4";
		break;
		
		case "PZ_Zhorzh_4":
			dialog.text = "Certo, ma ci vorrà tempo! Due giorni! Almeno.";
			link.l1 = "Perché ci metti così tanto?";
			link.l1.go = "PZ_Zhorzh_5";
		break;
		
		case "PZ_Zhorzh_5":
			dialog.text = "Di solito prendo qualche moneta dalla cassetta delle offerte per sciogliere la lingua ai miei informatori. Ma ci hanno derubato di recente! Il Padre annuncerà una nuova raccolta di donazioni, certo, ma dobbiamo ancora riparare il tetto – che perde acqua! Ci vorranno un sacco di offerte per sistemarlo.";
			link.l1 = "Due giorni. Non posso restare qui in eterno. Non dispongo di tutto questo tempo. Longway non è famoso per la sua pazienza. E Lord van Merden ne ha ancora meno. O devo forse ricordartelo io, Gravel?";
			link.l1.go = "PZ_Zhorzh_6";
		break;
		
		case "PZ_Zhorzh_6":
			dialog.text = "Non posso controllare ciò che sta oltre la mia portata! Farò quel che posso. Però, ci metterei molto meno se tu trovassi quei briganti e riportassi le nostre donazioni!";
			link.l1 = "Ci penserò su. Tu comincia a cercare. Due giorni. Non di più. Ci vediamo allo stesso posto, alla stessa ora.";
			link.l1.go = "PZ_Zhorzh_7";
		break;
		
		case "PZ_Zhorzh_7":
			DialogExit(); 
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A Day Later..."+ NewStr() +"In Search of the Church Robbers.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil_Jungle", "goto", "goto1", "PZ_Kapstervil_Jungle");
			LaunchFrameForm();
		break;
		
		case "PZ_VorugaChurch_1":
			dialog.text = "Ehi, guarda un po’! Un uomo dagli occhi stretti sulla nostra isola! Fuggi dai tuoi padroni, eh? Da chi ti stai nascondendo, se posso chiedere?";
			link.l1 = "Sono un uomo libero.";
			link.l1.go = "PZ_VorugaChurch_2";
		break;
		
		case "PZ_VorugaChurch_2":
			dialog.text = "Ah! Ma certo che lo sei. Però sembri tosto e sveglio, anche se hai gli occhi un po’ a mandorla. Vuoi unirti alla nostra ciurma? Tanto non credo tu abbia un altro posto dove andare, giusto?";
			link.l1 = "Longway pensa che tu sia più interessato a derubarlo che ad arruolarlo.";
			link.l1.go = "PZ_VorugaChurch_3";
		break;
		
		case "PZ_VorugaChurch_3":
			dialog.text = "Heh, ritieniti fortunato. Abbiamo appena svaligiato una chiesa in città, ci credi? Perché? Perché rubare ai ladri non è davvero rubare.";
			link.l1 = "Non avevo intenzione di venirti a cercare, ma sono contento d’averti trovato.";
			link.l1.go = "PZ_VorugaChurch_4";
		break;
		
		case "PZ_VorugaChurch_4":
			dialog.text = "Ci dai la caccia, eh? Ah, quindi sei un mercenario, non uno schiavo in fuga. Peggio per te, allora.";
			link.l1 = "Giusto.";
			link.l1.go = "PZ_VorugaChurch_5";
		break;
		
		case "PZ_VorugaChurch_5":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetCheckMinHP(npchar, 1, true, "PZ_VorugaChurch_win");
			for (i=11; i<=14; i++)
			{
				sld = CharacterFromID("PZ_KapstervilBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_VorugaChurch_6":
			if (!CharacterIsAlive("PZ_KapstervilBandit_11") && !CharacterIsAlive("PZ_KapstervilBandit_12") && !CharacterIsAlive("PZ_KapstervilBandit_13"))
			{
				dialog.text = "Maledizione...   Perché non mi hai fatto fuori subito?   Che diavolo vuoi da me? Vuoi trascinarmi in galera?";
				link.l1 = "Non m’importa nulla di questo. Dimmi solo dove hai nascosto l’oro.";
				link.l1.go = "PZ_VorugaChurch_7";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_VorugaChurch_win");	
			}
		break;
		
		case "PZ_VorugaChurch_7":
			dialog.text = "Heh... Maledetto bastardo dalla pelle gialla...";
			link.l1 = "La pazienza di Longway si sta consumando. Scoprirò comunque la verità. La sola domanda è quanto a lungo soffrirai.";
			link.l1.go = "PZ_VorugaChurch_8";
			LAi_group_Delete("EnemyFight");
		break;
		
		case "PZ_VorugaChurch_8":
			dialog.text = "Va bene, d'accordo... È in una grotta. Lì c'è tutto. I soldi sono tuoi. Solo... solo non ammazzarmi, giusto?";
			link.l1 = "Non ho mai detto che non ci sarebbe stato alcun tormento...";
			link.l1.go = "PZ_VorugaChurch_9";
		break;
		
		case "PZ_VorugaChurch_9":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_VorugaChurch_win_2", 0.9);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0":
			StartQuestMovie(true, false, true);
			locCameraFromToPos(2.48, 0.87, 9.26, true, 6.72, -0.85, 6.05);
			dialog.text = "(in mandarino) Ecco il covo dei banditi.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_0_1";
			CharacterTurnToLoc(pchar, "box", "box1");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "PZ_Kapstervil_Grot_1", -1);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1":
			dialog.text = "(in Mandarino) È davvero tanto!";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_1_1";
			CharacterTurnToLoc(pchar, "box", "box1");
			locCameraFromToPos(6.83, 2.65, 6.62, true, 2.83, -1.00, 7.67);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1_1":
			dialog.text = "(in mandarino) Sento passi...";
			link.l1 = "(in mandarino) C'è qualcun altro qui...";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_2";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_2":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_1", "sold_fra_7", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.17, 0.65, -1.42, 0.00);
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_2", "sold_fra_5", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.10, 0.65, 0.30, 3.00);
			
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_Kapstervil_Grot_2", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_3":
			dialog.text = "Che diavolo stiamo facendo qui? Non è rimasto più nessuno – ci siamo assicurati che tutti quei furfanti fossero spariti.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_4");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_5":
			dialog.text = "Ecco il punto, idiota! Torneranno, e noi li accoglieremo a dovere.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_1"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_5");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_7":
			dialog.text = "Darò un'occhiata in giro, per accertarmi che nessun bastardo si nasconda. Tanto mi annoio comunque...";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_8";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_8":
			DialogExit();
			LAi_Fade("PZ_Kapstervil_Grot_5_1", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_9":
			dialog.text = "(in mandarino) Soldati! Che sventura... E ora che dovrei fare io?";
			link.l1 = "(in mandarino) Ho bisogno di questi soldi più dei soldati bianchi! Non me ne andrò senza, capito?";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_10";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_10":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("PZ_Kapstervil_GrotSoldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyWithRadius");
				LAi_group_SetRelation("EnemyWithRadius", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_SetLookRadius("EnemyWithRadius", 6.0);
				LAi_group_SetHearRadius("EnemyWithRadius", 2.0);
				LAi_group_SetSayRadius("EnemyWithRadius", 12.0);
				LAi_group_SetCheck("EnemyWithRadius", "PZ_Kapstervil_Grot_6");
			}
		break;
		
		case "PZ_Zhorzh_11":
			dialog.text = "Ah, monsieur Longway, siete tornato!";
			link.l1 = "Ma certo. Avevi forse dei dubbi? Hai scoperto qualcosa sulla Stella del Mattino, Georges?";
			link.l1.go = "PZ_Zhorzh_12";
		break;
		
		case "PZ_Zhorzh_12":
			dialog.text = "Sì, monsieur. È un galeone pesante, comandato da uno spagnolo, o almeno così dicono...";
			link.l1 = "È portoghese. Voi bianchi non riuscite nemmeno a riconoscervi tra di voi.";
			link.l1.go = "PZ_Zhorzh_13";
		break;
		
		case "PZ_Zhorzh_13":
			dialog.text = "Ah, giusto. Errore mio. Comunque, ho scoperto che ha modificato pesantemente il galeone per farlo sembrare una nave mercantile, con cannoni di piccolo calibro e un equipaggio ridotto. Però ha ingrandito la stiva, riempiendola fino all’orlo – è così pesante che fatica pure a stare a galla.";
			link.l1 = "Così ha deciso di cambiare vita. Bene. Ora, dove posso trovarlo?";
			link.l1.go = "PZ_Zhorzh_14";
		break;
		
		case "PZ_Zhorzh_14":
			dialog.text = "Questa è più difficile. Si sposta di continuo tra le nostre colonie e quelle inglesi, ma resta sempre tra le Isole Sopravento. Tuttavia, ho saputo che in questo momento sta andando a Basse-Terre con una gran partita di vino.";
			link.l1 = "Devo capire come arrivarci in fretta.";
			link.l1.go = "PZ_Zhorzh_15";
		break;
		
		case "PZ_Zhorzh_15":
			dialog.text = "Questa è faccenda vostra, monsieur Longway. Ho già abbastanza grane per conto mio... come sistemare quel dannato tetto.";
			link.l1 = "A proposito di preoccupazioni, ho trovato quei ladri di chiesa. Ecco indietro i soldi della tua donazione. Ripara il tetto – non sta bene che il tuo Dio resti senza uno.";
			link.l1.go = "PZ_Zhorzh_16";
		break;
		
		case "PZ_Zhorzh_16":
			dialog.text = "Grazie mille, monsieur Longway! Non avrei mai immaginato che saresti stato tu a farlo.";
			link.l1 = "Neanch’io l’avrei mai pensato. Ma dovevo pur impiegare quei due giorni in qualche modo.";
			link.l1.go = "PZ_Zhorzh_17";
		break;
		
		case "PZ_Zhorzh_17":
			dialog.text = "Dunque, devi andare a Guadalupa? Ti troverò una nave che punta da quelle parti. Aspetta mie notizie, giusto?";
			link.l1 = "Sarebbe d'aiuto. Ti ringrazio, Georges.";
			link.l1.go = "PZ_Zhorzh_18";
		break;
		
		case "PZ_Zhorzh_18":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("The Next Morning..."+ NewStr() +"Capsterville", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "goto", "goto19", "PZ_Kapstervil_PoiskZvezda");
			LaunchFrameForm();
		break;
		
		case "PZ_Kapstervil_Kurier_1":
			dialog.text = "Devi essere un conoscente di Georges? Mi ha chiesto di darti questo.";
			link.l1 = "Un biglietto? Vi sono grato. Come avete intuito che fosse rivolto a me?";
			link.l1.go = "PZ_Kapstervil_Kurier_2";
		break;
		
		case "PZ_Kapstervil_Kurier_2":
			dialog.text = "Davvero?";
			link.l1 = "Ah, giusto.";
			link.l1.go = "PZ_Kapstervil_Kurier_3";
		break;
		
		case "PZ_Kapstervil_Kurier_3":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("PZ_Kapstervil_ChitaemPismo", 1.5);
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog":
			dialog.text = "(Legge la lettera) Monsieur Longway, la pinaccia ‘Provence’ salpa per Basse-Terre domani all’alba. Il capitano, Mathieu Terugny, lo trovi in taverna. Porgi i miei saluti a monsieur van Merden. - Georges Gravel.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_ChitaemPismo_Dialog_2";
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog_2":
			DialogExit();
			LAi_RemoveCheckMinHP(pchar);
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			sld = characterFromId("PZ_Kapstervil_tavernkeeper");
			sld.dialog.currentnode = "PZ_TerunyiTavern1";
			LAi_SetBarmanType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_TerunyiTavern1":
			dialog.text = "Qui non serviamo da bere alla tua razza. E a meno che non voglia sentire lamentele sulle pulci, non ti affitterò nemmeno una stanza.";
			link.l1 = "Non ho bisogno né di un bicchiere né di una stanza. E... Longway non ha le pulci.";
			link.l1.go = "PZ_TerunyiTavern2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_TerunyiTavern2":
			dialog.text = "Come diavolo dovrei saperlo? Va bene, sputa il rospo. Cosa vuoi? Allora fuori dai piedi.";
			link.l1 = "Lo farò. Sto cercando il Capitano Mathieu Terugny. Non riesco proprio a trovarlo. Sai dove si trova?";
			link.l1.go = "PZ_TerunyiTavern3";
		break;
		
		case "PZ_TerunyiTavern3":
			dialog.text = "Sta tutto indaffarato a preparare la sua nave nella bottega del porto. Quello sì che è importante, molto più che perdere tempo a chiacchierare con un cinese come te, ma pare proprio che tu questo non lo capisca.";
			link.l1 = "In realtà, un tempo ero... Lascia stare. Non conta adesso.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateTerunyi");
		break;
		
		case "PZ_Terunyi1":
			dialog.text = "Cosa vuoi, cinese? Non vedi che ho da fare? Devo preparare la mia nave.";
			link.l1 = "Capitano Mathieu Terugny?";
			link.l1.go = "PZ_Terunyi2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Terunyi2":
			dialog.text = "Bene, adesso non fa più ridere. Come accidenti fai a sapere chi sono io? Ti manda qualcuno?";
			link.l1 = "Nessun bisogno di preoccuparsi. Ho sentito che navighi verso Basse-Terre. Puoi portarmi a bordo come passeggero? Ti pagherò.";
			link.l1.go = "PZ_Terunyi3";
		break;
		
		case "PZ_Terunyi3":
			dialog.text = "Le cose vanno sempre meglio. Sto andando a Saint-Pierre, non a Basse-Terre, ma deviare di poco non mi costa nulla. Meglio così: non dovrò sopportare la tua presenza a bordo più dello stretto necessario. Cinquemila pesos. Si parte tra tre ore. Paghi al molo. Anche se faccio il mercante, qui non si mercanteggia. Capito?";
			link.l1 = "Sì. Grazie. Ci vediamo al molo, Capitano Terugny.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToPier");
		break;
		
		case "PZ_Terunyi4":
			dialog.text = "Alla fine sei venuto, cinese. Pensavo non ce l’avresti fatta – nessuno dà mai soldi veri alla tua razza di sua spontanea volontà.";
			link.l1 = "Cinquemila pesos, proprio come hai chiesto. Sei pronto a salpare?";
			link.l1.go = "PZ_Terunyi5";
		break;
		
		case "PZ_Terunyi5":
			AddMoneyToCharacter(pchar, -5000);
			
			dialog.text = "No, no! Dovrei essere io a chiedertelo. Ma suppongo che tu sia pronto. Forza. Sarai tu a remare sulla scialuppa. E non aspettarti una cabina decente! Se facciamo questa deviazione, è solo per colpa tua.";
			link.l1 = "Non cerco conforto. Portami solo lì.";
			link.l1.go = "PZ_Terunyi6";
		break;
		
		case "PZ_Terunyi6":
			DialogExit();
			
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			InterfaceStates.Buttons.Save.enable = true;
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_Flashback_Final_1", 3.5);
		break;
		
		case "PZ_Longway_PosleRasskaza21":
			dialog.text = "...così Longway non è riuscito a capire esattamente dove sta andando la Stella del Mattino.";
			link.l1 = "Sì, capisco proprio come sei finito in quel casino.";
			link.l1.go = "PZ_Longway_PosleRasskaza22";
		break;
		
		case "PZ_Longway_PosleRasskaza22":
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena")) sStr = "Helena";
			else sStr = "Alonso";
			dialog.text = "Ho avvistato una brigantina nelle acque di Guadalupa. Forse era la Banten. Cercherò di scoprirne di più. Bene, ora puoi andare, Longway. Portami "+sStr+".";
			link.l1.go = "PZ_Longway_PosleRasskaza23";
		break;
		
		case "PZ_Longway_PosleRasskaza23":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeLong("PZ_LongwayUhoditIzKauty", "PZ_HelenaOrAlonso");
		break;
		
		case "PZ_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Mio Capitano, va tutto bene? Sono arrivata appena Longway ha detto che avevi bisogno di me.";
				link.l1 = "Sto solo cercando di mettere insieme i pezzi. Ricordi il nome di quella brigantina che abbiamo visto al largo dell’isola?";
				link.l1.go = "PZ_Helena_3";
			}
			else
			{
				dialog.text = "Volevate vedermi, Mio Signore Capitano?";
				link.l1 = "Aye. Ricordi la brigantina che abbiamo avvistato di recente? Scopri dove si trova e come si chiama.";
				link.l1.go = "PZ_Helena_2";
			}
		break;
		
		case "PZ_Helena_2":
			dialog.text = "Ricordo, ma perché questo improvviso interesse per una brigantina? Scoprire la verità potrebbe richiedere un bel po' di tempo.";
			link.l1 = "Helen, fallo e basta, ti prego. E sì, so che potrebbe metterci un po'. Aspetterò.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Helena_3":
			dialog.text = "No, non ho controllato. Perché? È una cosa che conta, giusto?";
			link.l1 = "Mm-hmm. Puoi scoprire di più? Devo sapere dove sono ancorati adesso, se non hanno già lasciato le acque di Guadalupa.";
			link.l1.go = "PZ_Helena_4";
		break;
		
		case "PZ_Helena_4":
			dialog.text = "Certamente. Solo per avvertirti, potrebbe volerci un po'. Prendo una scialuppa e due uomini con me, giusto, Charles?";
			link.l1 = "Ma certo, Helen, grazie. Resterò ad aspettare.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Alonso_11":
			dialog.text = "Mio Signore Capitano, avete invocato la mia presenza?";
			link.l1 = "Sì, Alonso. Abbiamo incrociato una brigantina al largo dell’isola, tornando a prendere Longway. Hai per caso sentito come si chiamava?";
			link.l1.go = "PZ_Alonso_12";
		break;
		
		case "PZ_Alonso_12":
			dialog.text = "No, il mio compito è sorvegliare le nuove leve e guidare l’assalto d’abbordaggio. Inoltre, non possiedo un cannocchiale, e non eravamo poi così vicini.";
			link.l1 = "Giusto. Ma devo comunque scoprirlo. Fallo e basta.";
			link.l1.go = "PZ_Alonso_13";
		break;
		
		case "PZ_Alonso_13":
			dialog.text = "Aye, Capitano. Credo di poterlo fare in mezza giornata.";
			link.l1 = "Sbrigati. Ti aspetto.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_PoiskBanten":
			DialogExit();
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			LAi_SetStayType(pchar);
			SetLaunchFrameFormParam("Five hours later...", "PZ_PoiskBanten_2", 0, 4.0);
			LaunchFrameForm();
			locCameraSleep(true);
		break;
		
		case "PZ_Helena_5":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Ho imparato tutto. È andato tutto bene mentre non c’ero, mio capitano?";
				link.l1 = "Sì, sto bene, grazie, Helen. Dimmi pure.";
				link.l1.go = "PZ_Helena_7";
			}
			else
			{
				dialog.text = "Uff, sono tornata. Ho trovato la tua brigantina.";
				link.l1 = "Bentornato. Dove si trova e come si chiama quella donna?";
				link.l1.go = "PZ_Helena_6";
			}
		break;
		
		case "PZ_Helena_6":
			dialog.text = "La Banten. Quel nome vi dice qualcosa, vero? Ora è al faro, e alcuni dei suoi uomini sono sbarcati. Attaccheremo quella nave, Mio Signore Capitano?";
			link.l1 = "No, dobbiamo scoprire chi è sbarcato di preciso. Andremo al faro via terra. Visto che abbiamo già perso tempo, è ora di lasciare il porto. Meglio gettare l’ancora in un posto appartato. Capster Beach andrà bene. Sbrighiamoci, Helen.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Helena_7":
			dialog.text = "Beh, la bricca si chiama Banten, ed è ancorata vicino al faro. Parte dell’equipaggio è già sbarcata lì. Che cosa intendi fare?";
			link.l1 = "Per scoprirlo, dovremo arrivare al faro senza farci vedere, e possiamo farlo solo a piedi. La nostra nave deve gettare l’ancora in un posto sicuro. Che ne dici di Capster Beach?";
			link.l1.go = "PZ_Helena_8";
		break;
		
		case "PZ_Helena_8":
			dialog.text = "Buona idea. Charles, vuoi che venga al faro con te?";
			link.l1 = "Ci rifletterò mentre spostiamo la nave – sei già abbastanza sfinito così.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Alonso_15":
			dialog.text = "Sono tornato appena ho finito, Mio Signore Capitano.";
			link.l1 = "Molto bene. Fai rapporto, Alonso.";
			link.l1.go = "PZ_Alonso_16";
		break;
		
		case "PZ_Alonso_16":
			dialog.text = "La corvetta è ancora al largo dell’isola – proprio al faro, per essere precisi. Sullo specchio di poppa c’è scritto Banten. Alcuni dei loro uomini sono già sbarcati.";
			link.l1 = "Bel lavoro, Alonso. Prepara subito l'equipaggio per salpare l'ancora.";
			link.l1.go = "PZ_Alonso_17";
		break;
		
		case "PZ_Alonso_17":
			dialog.text = "Anche tu pronto per l’abbordaggio?";
			link.l1 = "Non ancora. Se il loro capitano punta al faro, potrebbe nascondersi in città se attacchiamo dal mare. Navigheremo fino alla Spiaggia di Capster per mettere al sicuro la nostra nave, poi ci avvicineremo al faro via terra.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_BasTerMayak":
			DialogExit();
			locCameraSleep(false);
			LAi_SetPlayerType(pchar);
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Guadeloupe", true);
			
			AddQuestRecord("PZ", "15");
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1 = "location";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1.location = "Shore29";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition = "PZ_Banten_PlyazhKapster";
			
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1 = "Timer";
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.hour = sti(GetTime() + 7);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition = "PZ_Banten_PlyazhKapster_Proval";
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, pchar, "", -1);
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Saga\Helena.c";
				npchar.Dialog.CurrentNode = "Helena_officer";
			}
		break;
		
		case "PZ_Longway_21":
			dialog.text = "Mio Signore Capitano, guardate! C’è qualcuno dentro il faro.";
			link.l1 = "Bene, siamo arrivati in tempo! Sbrighiamoci e prendiamoli. Alonso avrà un bel da fare oggi.";
			link.l1.go = "PZ_Longway_22";
		break;
		
		case "PZ_Longway_22":
			dialog.text = "Ma che succede se ci lasciano la pelle nel frattempo?";
			link.l1 = "Cosa proponi?";
			link.l1.go = "PZ_Longway_23";
		break;
		
		case "PZ_Longway_23":
			dialog.text = "Entriamo di soppiatto e ascoltiamo di nascosto cosa si dicono, prima di agire.";
			link.l1 = "Dubito che riusciremo a farlo senza farci vedere dalla finestra. Ma proviamoci comunque.";
			link.l1.go = "PZ_Longway_24";
		break;
		
		case "PZ_Longway_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			LAi_SetCheckMinHP(npchar, 1, true, "SkritoeBessmertie");
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1 = "locator";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.location = "Mayak4";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator_group = "goto";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator = "goto31";
			PChar.quest.PZ_MayakPodslushivanie.win_condition = "PZ_MayakPodslushivanie";
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1":
			dialog.text = "Pensa bene a ciò che ti ho detto. Rifletti a fondo. Il denaro non è un problema – entro certi limiti, si capisce. Ma anche quel limite ti sembrerà una montagna d’oro – il cinese deve morire! Ho già mandato uomini sulle sue tracce, senza risultato. Stavolta però, se si alleano con la tua ciurma...";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_1_1";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_BasTerJailOff_Clone"));
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1_1":
			StartInstantDialog("PZ_BasTerJailOff_Clone", "PZ_MayakPodslushivanie_Dialog_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_2":
			dialog.text = "Guarda, ci stanno spiando! È lui! Lui e quel dannato capitano suo!";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_3";
			CharacterTurnToLoc(npchar, "item", "flower5");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_3":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			locCameraToPos(1.52, 18.87, -9.55, true);
			DoQuestCheckDelay("CameraReset", 1.0);
			DeleteAttribute(pchar, "questTemp.NoFast");
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_Neznakomets");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = CharacterFromID("PZ_BasTerJailOff_Clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_MayakPodslushivanie_win");
			
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_Neznakomets_Bandit_"+i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_Mayak_KomendantSidit_1":
			if (!CharacterIsAlive("PZ_Neznakomets_Bandit_1") && !CharacterIsAlive("PZ_Neznakomets_Bandit_2") && !CharacterIsAlive("PZ_Neznakomets_Bandit_3")&& !CharacterIsAlive("PZ_Neznakomets_Bandit_4"))
			{
				dialog.text = "Maledetto bastardo d’asiatico... Ho dovuto sopportare l’inferno per colpa tua. E adesso, per tutto questo, sto per crepare...";
				link.l1 = "Vi porteremo dal nostro medico, Signore Comandante. Basta che ci dici con chi stavi parlando – è di massima importanza.";
				link.l1.go = "PZ_Mayak_KomendantSidit_2";
				LAi_group_Delete("EnemyFight");
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_MayakPodslushivanie_win");	
			}
		break;
		
		case "PZ_Mayak_KomendantSidit_2":
			dialog.text = "Il suo nome... è Joep van der Vink, lui... kha...";
			link.l1 = "...";
			link.l1.go = "PZ_Mayak_KomendantSidit_3";
		break;
		
		case "PZ_Mayak_KomendantSidit_3":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			DoQuestCheckDelay("PZ_Mayak_Longway", 1.5);
		break;
		
		case "PZ_Longway_25":
			dialog.text = "";
			link.l1 = "È morto... Beh, almeno ora sappiamo il nome. Longway...?";
			link.l1.go = "PZ_Longway_26";
		break;
		
		case "PZ_Longway_26":
			dialog.text = "Questo proprio non può essere...";
			link.l1 = "Sembri un po' pallido, Longway.";
			link.l1.go = "PZ_Longway_27";
		break;
		
		case "PZ_Longway_27":
			dialog.text = "Longway era più che certo d’aver fatto fuori van der Vink dieci anni fa\nStanno filando via! La loro nave va come il vento!";
			link.l1 = "Sì, un brigantino magnifico... purtroppo per noi. Anche se arrivassimo alla nostra nave in tempo, loro sarebbero già spariti quando avremo issato le vele e preso il vento.";
			link.l1.go = "PZ_Longway_28";
		break;
		
		case "PZ_Longway_28":
			dialog.text = "Potrebbe essere la fine...";
			link.l1 = "No, Longway. Ascoltami. Se hanno deciso di restare nell'Arcipelago, prima o poi li incontreremo di nuovo – questo mondo è piccolo, e i Caraibi lo sono ancora di più. Non appena ritroveremo la loro pista, lascerò tutto e li inseguirò. Te lo giuro. Mi senti?";
			link.l1.go = "PZ_Longway_29";
		break;
		
		case "PZ_Longway_29":
			dialog.text = "Sì, Mio Signore Capitano. Grazie.";
			link.l1 = "Coraggio, Longway. Dobbiamo sbrigarci a tornare alla nave – la morte del Comandante farà presto scalpore.";
			link.l1.go = "PZ_Longway_30";
		break;
		
		case "PZ_Longway_30":
			DialogExit();
			
			Return_LongwayOfficer();
			LAi_RemoveCheckMinHP(npchar);
			AddQuestRecord("PZ", "17");
			sld = &Locations[FindLocation("Mayak4")];
			sld.locators_radius.goto.goto31 = 0.5;
			
			chrDisableReloadToLocation = false;
			QuestOpenSeaExit();
			
			pchar.questTemp.PZ_Etap4_Start = true;
		break;
		
		// Этап 4, Обманчивая Звезда
		case "PZ_PoterpKrushenie_1":
			dialog.text = "Monsieur! Un momento! Siete voi un capitano?";
			link.l1 = "Forse. Come l’hai capito? E che cosa vuoi?";
			link.l1.go = "PZ_PoterpKrushenie_2";
		break;
		
		case "PZ_PoterpKrushenie_2":
			dialog.text = "Ebbene, qui non c'è altro che montagne e una giungla fitta - nessuna strada verso la città. Eppure, eccoti qui. Non starai mica facendo solo il turista, vero?";
			link.l1 = "Acuta osservazione. Ma non mi hai ancora detto cosa desideri.";
			link.l1.go = "PZ_PoterpKrushenie_3";
		break;
		
		case "PZ_PoterpKrushenie_3":
			dialog.text = "Ah, giusto! Capitano, la nostra nave s'è schiantata sugli scogli proprio fuori da questa cala. Siamo gli unici sopravvissuti...";
			link.l1 = "Mi dispiace. Vuoi che ti porti da qualche parte, vero?";
			link.l1.go = "PZ_PoterpKrushenie_4";
		break;
		
		case "PZ_PoterpKrushenie_4":
			dialog.text = "Aye... Non vi darò alcun fastidio, lo giuro. Lasciateci solo a Belize, e da lì ce la caveremo.";
			link.l1 = "Non è lontano, vero? In tal caso, benvenuto a bordo.";
			link.l1.go = "PZ_PoterpKrushenie_5";
			link.l2 = "Mi dispiace, ma sto andando dall’altra parte.";
			link.l2.go = "PZ_PoterpKrushenie_7";
		break;
		
		case "PZ_PoterpKrushenie_5":
			dialog.text = "Grazie, Capitano! Chissà per quanto saremmo rimasti bloccati senza di te.";
			link.l1 = "Già. Non perdiamo tempo, avanti!";
			link.l1.go = "PZ_PoterpKrushenie_6";
		break;
		
		case "PZ_PoterpKrushenie_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_PoterpKrushenie";
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_7":
			dialog.text = "Ma Belize è così vicina! Non ci metteremmo molto, giusto?";
			link.l1 = "Ho fretta. Non posso permettermi deviazioni.";
			link.l1.go = "PZ_PoterpKrushenie_8";
		break;
		
		case "PZ_PoterpKrushenie_8":
			dialog.text = "Nemmeno una rotta breve? Solo fino a Belize? Ti prego, Capitano, non lasciarci qui a marcire!";
			link.l1 = "Va bene, spero di non pentirmene. Tutti a bordo, giusto?";
			link.l1.go = "PZ_PoterpKrushenie_6";
			link.l2 = "C'est la vie. Passate una buona giornata, amici miei.";
			link.l2.go = "PZ_PoterpKrushenie_9";
		break;
		
		case "PZ_PoterpKrushenie_9":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", 10);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_QuestCitizenDialog";
			
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
			
			pchar.questTemp.PZ.Shipwreckers.Decline = true;
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_11":
			dialog.text = "Grazie ancora, Capitano! Siamo solo semplici marinai, quindi non abbiamo molto da offrirvi.";
			link.l1 = "Beh, almeno non abbiamo dovuto deviare troppo dalla nostra rotta.";
			link.l1.go = "PZ_PoterpKrushenie_12";
		break;
		
		case "PZ_PoterpKrushenie_12":
			dialog.text = "Brinderemo alla tua salute e accenderemo una candela per te in chiesa.";
			link.l1 = "È meglio di niente. Salute, ragazzi!";
			link.l1.go = "PZ_PoterpKrushenie_13";
		break;
		
		case "PZ_PoterpKrushenie_13":
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetCitizenType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0;
				sld.location = "None";
			}
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BelizZhitelNovosti", "citiz_4", "man", "man", 1, ENGLAND, 0, false, "quest"));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_BelizZhitelNovosti_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_BelizZhitelNovosti_1":
			dialog.text = "Hai sentito? L'hanno finalmente preso! Le nostre acque sono finalmente al sicuro!";
			link.l1 = "Questa... è una buona notizia? Ma chi hanno preso?";
			link.l1.go = "PZ_BelizZhitelNovosti_2";
			DeleteQuestCondition("PZ_BelizFail");
		break;
		
		case "PZ_BelizZhitelNovosti_2":
			dialog.text = "Matthew Lutter, il pallone gonfiato in persona!";
			link.l1 = "Non sono al corrente – che diavolo ha combinato?";
			link.l1.go = "PZ_BelizZhitelNovosti_3";
		break;
		
		case "PZ_BelizZhitelNovosti_3":
			dialog.text = "Non lo sai?! Beh, di certo non sei inglese, si vede subito. È un pirata che da anni ci saccheggia, a noi e agli spagnoli, sulla sua nave, il Gabbiano.";
			link.l1 = "Saccheggiare sia gli inglesi che gli spagnoli? Questa sì che è strana, eh.";
			link.l1.go = "PZ_BelizZhitelNovosti_4";
		break;
		
		case "PZ_BelizZhitelNovosti_4":
			dialog.text = "In effetti. La guardia costiera non è mai riuscita a mettergli le mani addosso, ma alla fine ha cercato di mordere un osso troppo grosso – è stato fatto fuori da una strana nave mercantile, se puoi crederci.";
			link.l1 = "Divertente, questo. Che c’era di tanto strano in quel mercante?";
			link.l1.go = "PZ_BelizZhitelNovosti_5";
		break;
		
		case "PZ_BelizZhitelNovosti_5":
			dialog.text = "Beh, era solo un enorme galeone maldestro senza scorta! Ma grazie al suo capitano fuori di testa, oggi Lutter canterà la sua ultima canzone – sta per essere impiccato. Dovresti venire a vedere!";
			link.l1 = "Potrei anche farlo, ma per ora ho altre faccende a cui badare.";
			link.l1.go = "PZ_BelizZhitelNovosti_6";
		break;
		
		case "PZ_BelizZhitelNovosti_6":
			DialogExit();
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			
			sld = CharacterFromID("Longway");
			if (!CharacterIsHere("Longway"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			}
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_31";
		break;
		
		case "PZ_Longway_31":
			dialog.text = "Mio Signore Capitano!";
			link.l1 = "Un mercante spagnolo che abbatte un pirata audace... Stai pensando quello che pensa Longway, giusto?";
			link.l1.go = "PZ_Longway_32";
		break;
		
		case "PZ_Longway_32":
			dialog.text = "La Stella del Mattino...";
			link.l1 = "Molto probabilmente – non c’è altro capitano mercante come lui in tutto l’arcipelago.";
			link.l1.go = "PZ_Longway_33";
		break;
		
		case "PZ_Longway_33":
			dialog.text = "Dobbiamo trovarlo subito!";
			link.l1 = "Giusto. Ma non vedo nessun galeone pesante in porto. Proviamo a parlare col Vento-in-pancia prima che lo impicchino. Vediamo se si è meritato quel soprannome.";
			link.l1.go = "PZ_Longway_34";
		break;
		
		case "PZ_Longway_34":
			DialogExit();
			Return_LongwayOfficer();
			if (!CheckAttribute(pchar, "questTemp.PZ.Shipwreckers.Decline")) AddQuestRecord("PZ", "18");
			else AddQuestRecord("PZ", "18_1");
			pchar.questTemp.PZ_Beliz_Komendant = true;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		break;
		
		case "PZ_Beliz_Komendant_8":
			dialog.text = "È ancora vivo? Possiamo parlarci?";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_9";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_9":
			StartInstantDialogNoType("BelizJailOff", "PZ_Beliz_Komendant_10", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_10":
			dialog.text = "Cosa? Oh, sì. È vivo – l’esecuzione non c’è ancora stata. Puoi andare a parlargli – non è mai stato così ciarliero. Ma ultimamente straparla, conversa da solo e dice solo sciocchezze. Quel Sacco di vento è impazzito... Non vedo l’ora di impiccarlo, prima che la sua lingua ci faccia perdere il senno a tutti.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_11";
		break;
		
		case "PZ_Beliz_Komendant_11":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_12":
			dialog.text = "Grazie.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_13";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_13":
			DialogExit();
			pchar.questTemp.jailCanMove = true;
			
			Return_LongwayOfficer();
			
			sld = CharacterFromID("BelizJailOff");
			LAi_SetHuberType(sld);
			sld.Dialog.Filename = "Common_Prison.c";
			sld.Dialog.CurrentNode = "First_officer";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MatthewLutter", "mercen_15", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Matthew";
			sld.lastname = "Lutter";
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_MatthewLutter1";
			ChangeCharacterAddressGroup(sld, "Beliz_prison", "goto", "goto9");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_MatthewLutter1":
			dialog.text = "Ha rubato il mio tesoro!";
			link.l1 = "Matthew Lutter?";
			link.l1.go = "PZ_MatthewLutter2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MatthewLutter2":
			dialog.text = "Il mio tesoro ormai gli appartiene, lo capisci, A LUI! Non c’è niente che possiamo fare! Cosa vuoi da noi?! Vuoi prenderci qualcos’altro? Non è rimasto più niente! Lei morirà! O peggio!";
			link.l1 = "Chi deve morire? Quale tesoro? Lascia stare, è solo colpa tua – sei stato tu ad assaltare quel galeone, mica il contrario.";
			link.l1.go = "PZ_MatthewLutter3";
		break;
		
		case "PZ_MatthewLutter3":
			dialog.text = "No!   Era il contrario! Maledetto quell’hidalgo! È per colpa sua che siamo in questo inferno! È venuto dritto contro di noi e ha sparato a bruciapelo! Poi si è preso lei da noi!";
			link.l1 = "Davvero? Non mi sorprende affatto. Cos'altro puoi dirci su di lui? E... cosa ha portato via? Chi sarebbe 'lei'?";
			link.l1.go = "PZ_MatthewLutter5";
		break;
		
		case "PZ_MatthewLutter5":
			dialog.text = "Ah-ah-ah!!! A-A-A-A!!!";
			link.l1 = "Capisco, sto solo perdendo il mio tempo...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonSoldierDialog");
		break;
		
		case "PZ_BelizPrisonQuestSoldier1":
			dialog.text = "Capitano, se me lo concede... Lutter! Fuori! Fine della corsa, compare.";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongway_UvodyatNaKazn");
		break;
		
		case "PZ_Longway_35":
			dialog.text = "Capitano, dobbiamo scoprire di più su Sotta e Lutter. Interroghiamo la gente in giro.";
			link.l1 = "Buona idea, Longway. Tanto da quell'uomo urlante non abbiamo cavato un ragno dal buco.";
			link.l1.go = "PZ_Longway_36";
		break;
		
		case "PZ_Longway_36":
			dialog.text = "Ma è meglio cominciare da Sotta.";
			link.l1 = "Giusto, è lui quello che cerchiamo. Andiamo.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongwayBack");
		break;
		
		case "PZ_Longway_37":
			dialog.text = "Non sanno proprio un accidente!";
			link.l1 = "Ovviamente. Ma abbiamo già abbastanza elementi per ragionare con la nostra testa. Da quanto ho sentito, Sotta cercherà probabilmente di vendere quelle merci strategiche che ha ricevuto in premio, e presto.";
			link.l1.go = "PZ_Longway_38";
		break;
		
		case "PZ_Longway_38":
			dialog.text = "Proprio così, giusto?";
			link.l1 = "Dovremmo intercettarlo mentre si dirige verso Port Royal o Capsterville. La sola domanda è dove stia puntando e dove dovremmo affrontarlo. Oppure magari lo prenderemo in mare aperto.";
			link.l1.go = "PZ_Longway_39";
		break;
		
		case "PZ_Longway_39":
			dialog.text = "No! Longway voleva dire... Fermentelos è un capitano esperto. Una battaglia in mare aperto potrebbe andare in qualsiasi direzione. Avremmo più possibilità tendendogli un agguato al porto.";
			link.l1 = "Hai ragione, suppongo. Qualunque cosa sia successa davvero tra Matt e lui, Sotta è pericoloso e non va mai sottovalutato.";
			link.l1.go = "PZ_Longway_40";
		break;
		
		case "PZ_Longway_40":
			dialog.text = "Neanche noi possiamo più aspettare!";
			link.l1 = "Giusto di nuovo, Longway. Allora leviamo subito l’ancora, poi penseremo alla prossima mossa.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayBelizDialogBack");
			DelMapQuestMarkCity("Beliz");
		break;
		
		case "PZ_Longway_41":
			dialog.text = "Mio Signore Capitano, la Stella del Mattino è in porto!";
			link.l1 = "Sì, l’ho già notato.";
			link.l1.go = "PZ_Longway_42";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Longway_42":
			dialog.text = "Qual è il tuo piano?";
			link.l1 = "Non ho ancora deciso. Cercare di abbordarli sotto i cannoni della fortezza sarebbe un suicidio. E anche se riuscissimo a catturare il loro grosso galeone, non potremmo fuggire con quello. Hai qualche idea, Longway?";
			link.l1.go = "PZ_Longway_43";
		break;
		
		case "PZ_Longway_43":
			dialog.text = "Sì. Potremmo gettare l’ancora in una cala sicura e avvicinarci al galeone in barca, nascosti dall’oscurità della notte.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				link.l1 = "E la Baia della Mezzaluna, Longway?";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				link.l1 = "Penso che Portland Cove potrebbe andar bene – è abbastanza vicina e relativamente sicura. Che ne pensi?";
			}
			link.l1.go = "PZ_Longway_44";
		break;
		
		case "PZ_Longway_44":
			dialog.text = "Scelta saggia.";
			link.l1 = "Perfetto, è deciso. Ci siamo dimenticati qualcosa?";
			link.l1.go = "PZ_Longway_45";
		break;
		
		case "PZ_Longway_45":
			dialog.text = "Non credo proprio, Mio Signore Capitano. Dobbiamo solo essere ben pronti.";
			link.l1 = "Assolutamente.";
			link.l1.go = "PZ_Longway_46";
		break;
		
		case "PZ_Longway_46":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CabinLock");
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			bQuestDisableMapEnter = false;
			AddQuestRecord("PZ", "21");
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				AddQuestUserData("PZ", "sText", "Half Moon Bay");
				Island_SetReloadEnableGlobal("Nevis", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore43";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				AddQuestUserData("PZ", "sText", "Portland Cove");
				Island_SetReloadEnableGlobal("Jamaica", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore36";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition = "PZ_ZvezdaUhodimNaGlobalkru_Proval";
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan":
			dialog.text = "Chi diavolo sei tu, che diavolo succede? Signor Holmes!";
			link.l1 = "Il signor Holmes non lavora più qui. E abbiamo sprangato tutti i boccaporti per bene. Nessuno ci disturberà per un po', signor Fermentelos.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_2":
			dialog.text = "Cosa? Fermentelos? Il mio nome è Edgardo Sotta!";
			link.l1 = "Uh-huh, questa l'ho già sentita. Sappiamo bene che non è il tuo vero nome, Oliveiro.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_3";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_3":
			dialog.text = "Fermentelos è morto!";
			link.l1 = "A pensarci bene, sembri davvero troppo giovane. Di certo non potevi essere tu il capitano della Stella del Mattino dieci anni fa. Dunque, che fine ha fatto Oliveiro?";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_4";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_4":
			dialog.text = "Ce ne siamo sbarazzati. Era solo un altro guaio da eliminare – proprio come quello che ti sta accanto.";
			link.l1 = "Ebbene, visto che non sei Fermentelos, forse puoi comunque rispondere alle nostre domande. Cerchiamo qualcuno che lui ha portato via al mio amico.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_5";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_5":
			dialog.text = "Non ti dirò nulla! Non mi perdonerà mai per questo.";
			link.l1 = "In questo momento, faresti meglio a preoccuparti se ti perdoneremo...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_SottaFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_AnabelleLutter1":
			dialog.text = "Finalmente è crepato...";
			link.l1 = "That's right. And who are you, madam? Did he hold you against your will? I sympathize; you must have been through a terrible ordeal...";
			link.l1.go = "PZ_AnabelleLutter2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_AnabelleLutter2":
			dialog.text = "Sono Annabel Lutter. E grazie al cielo, non ho dovuto sopportare troppo, ma apprezzo la vostra premura, signore...?";
			link.l1 = "Capitano Charles de Maure. Lutter, dici...";
			link.l1.go = "PZ_AnabelleLutter3";
		break;
		
		case "PZ_AnabelleLutter3":
			dialog.text = "Ah, avrai sentito parlare di Matt? Povero sciocco... Io ero la sua... compagna.";
			link.l1 = "Le mie condoglianze per la vostra perdita, Signora Lutter. Ora siete vedova. Qual era il vostro cognome da nubile, se posso chiedere senza offendere?";
			link.l1.go = "PZ_AnabelleLutter4";
		break;
		
		case "PZ_AnabelleLutter4":
			dialog.text = "Non ne avevo uno. Guardami bene. Mia povera madre era una schiava dalla pelle scura, preda dei pirati. Nessuno ha mai saputo chi fosse mio padre, così non si sono nemmeno presi la briga di darmi un vero nome.";
			link.l1 = "Perché nessuno ti ha mai sfiorata, allora? Non fraintendermi – sono contento che sia andata così. Ma resta... insolito.";
			link.l1.go = "PZ_AnabelleLutter5";
		break;
		
		case "PZ_AnabelleLutter5":
			dialog.text = "You're right. But let's call things by their proper names. I'm not a pampered noblewoman; I'm the daughter of a slave. I won't faint from a heavy conversation.";
			link.l1 = "Ehm, neanch'io sono tipo da moine. Ma continua, ti prego. Perché l'equipaggio non ha mai sfiorato la figlia della schiava? Non conosci tuo padre, e lui non sembrava interessarsene.";
			link.l1.go = "PZ_AnabelleLutter6";
		break;
		
		case "PZ_AnabelleLutter6":
			dialog.text = "Suppongo di no. Se sai di Matt, sai anche che ha lavorato per Levasseur per un po' di tempo?";
			link.l1 = "Sì, ne ho sentito parlare mentre cercavo la Stella del Mattino. Ma che c'entra con tutto questo? Raccontami ogni cosa, ti prego.";
			link.l1.go = "PZ_AnabelleLutter7";
		break;
		
		case "PZ_AnabelleLutter7":
			dialog.text = "Non capisci ancora, vero? Pare che tu non abbia sentito parlare delle... preferenze di Levasseur?";
			link.l1 = "Non l’ho fatto, ma poi, che c’entra questo con...?";
			link.l1.go = "PZ_AnabelleLutter8";
		break;
		
		case "PZ_AnabelleLutter8":
			dialog.text = "Oh, suppongo che dovrò raccontarti tutto quanto. Siediti, se sei di cuore debole, signore. Il fatto è che lui si infila nei letti di molte donne, e...";
			if (pchar.questTemp.FMQT == "end")
			{
				link.l1 = "La sua moglie non gli sta mai lontana, e si infila nel letto di chiunque, quasi senza farci caso.";
				link.l1.go = "PZ_AnabelleLutterKnow1";
			}
			else
			{
				link.l1 = "Oh no.";
				link.l1.go = "PZ_AnabelleLutterDontKnow1";
			}
		break;
		
		case "PZ_AnabelleLutterKnow1":
			dialog.text = " Beh, sai cosa si dice... tale marito, tale moglie. Ma no, sono certa che lui è andato ben oltre, giusto?";
			link.l1 = "E quanto manca?";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutterDontKnow1":
			dialog.text = "Il vostro sarcasmo qui è fuori luogo, signore. Non avete la minima idea di cosa stiamo parlando.";
			link.l1 = "Va bene, va bene, scusa. Continua pure, giusto?";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutter9":
			dialog.text = "Non si tratta solo di tradire la moglie. Prende donne contro la loro volontà. E non è una sola volta, capisci? Rapisce ragazze e le tiene rinchiuse in una delle sue cantine.";
			link.l1 = "Quindi prende ragazze schiave regolarmente? E tu dovevi essere una di loro?";
			link.l1.go = "PZ_AnabelleLutter10";
		break;
		
		case "PZ_AnabelleLutter10":
			dialog.text = "Hai ragione sull’ultima parte. Ma, ahimè, non sulla prima. Non gli servono schiavi. Levasseur è folle – a modo suo, non come il mio Matt. François vuole possedere una donna fino in fondo, corpo e anima. E ovviamente non c’entrava l’amore. Gli servivano donne libere, da spezzare, da piegare. Godeva a osservare come cambiavano i loro sguardi, il modo di muoversi, persino il parlare, col passare del tempo...";
			link.l1 = "Ributtante...";
			link.l1.go = "PZ_AnabelleLutter11";
		break;
		
		case "PZ_AnabelleLutter11":
			dialog.text = "Già ti senti un po' male, eh? Ora immagina cosa hanno passato quelle donne. Di tutto questo ho sentito parlare, e non solo da Matt. Levasseur una volta aveva una nobildonna portoghese...";
			link.l1 = "Hai distolto lo sguardo e sei rimasto zitto. Raccontaci tutto. Ho visto ogni sorta di orrore nel Vecchio Mondo e anche qui nell’Arcipelago. Ormai niente mi stupisce più.";
			link.l1.go = "PZ_AnabelleLutterWant1";
			link.l2 = "Fermati, non voglio sapere che ne è stato di lei. Spero solo che quelle donne non abbiano sofferto troppo a lungo nelle sue grinfie.";
			link.l2.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutterWant1":
			dialog.text = "Ma tu non hai mai sentito nulla di simile. E spero che mai ti capiti di vederlo. Lei fu portata da lui ancora fiera e non piegata, anche se, come mi raccontò Matt, gli uomini di Levasseur la violentarono per tutto il viaggio verso Tortuga dopo aver preso la piantagione del marito vicino a Campeche – lui morì dissanguato dopo che quelle bestie gli spararono a entrambe le ginocchia...";
			link.l1 = "Una donna forte... Ma hai detto che Levasseur di solito non metteva mai le mani sulle donne che voleva per sé.";
			link.l1.go = "PZ_AnabelleLutterWant2";
		break;
		
		case "PZ_AnabelleLutterWant2":
			dialog.text = "Quelle che aveva richiesto espressamente sono state lasciate in pace. Ma la signora Leontina fu un dono. Inatteso, e molto gradito da tutti loro. Così si sono concessi ogni piacere...";
			link.l1 = "Capisco...";
			link.l1.go = "PZ_AnabelleLutterWant3";
		break;
		
		case "PZ_AnabelleLutterWant3":
			dialog.text = "Credo... Matt era diventato uno dei preferiti di Francois. Fu invitato a una delle segrete baldorie di Levasseur... Durante il banchetto, un pirata si lamentò che di donne ce n'erano poche. Levasseur rise e poi...";
			link.l1 = "E poi? Che è successo?";
			link.l1.go = "PZ_AnabelleLutterWant4";
		break;
		
		case "PZ_AnabelleLutterWant4":
			dialog.text = "...poi l'hanno trascinata fuori. Al guinzaglio! Piena di lividi, la schiena graffiata, bendata e imbavagliata. Quando le tolsero il bavaglio, tutto ciò che disse fu...";
			link.l1 = "Qualcosa di orribile, immagino. Gli avrà scagliato addosso tutta la sua maledizione, vero?";
			link.l1.go = "PZ_AnabelleLutterWant5";
		break;
		
		case "PZ_AnabelleLutterWant5":
			dialog.text = "Se solo... Dona Leontina sussurrava piano: 'Cosa desidera il mio padrone?'";
			link.l1 = "Penso che sto per vomitare. Matt ti ha raccontato cosa le è successo dopo?";
			link.l1.go = "PZ_AnabelleLutterWant6";
		break;
		
		case "PZ_AnabelleLutterWant6":
			dialog.text = "Uccisa, naturalmente. Ma non da Levasseur. Lui l’ha gettata via come un cane randagio. Uno dei suoi capitani le ha sparato. Prima di morire, ha pronunciato solo una parola...";
			link.l1 = "Una maledizione? O forse una preghiera?";
			link.l1.go = "PZ_AnabelleLutterWant7";
		break;
		
		case "PZ_AnabelleLutterWant7":
			dialog.text = "No. 'Grazie...'";
			link.l1 = "Essere grati alla morte dopo simili supplizi... Cosa avrà mai sopportato... e altri come lei nella tana di quel mostro...";
			link.l1.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutter12":
			dialog.text = "Levasseur disprezzava in modo particolare gli schiavi e le donne dalla pelle scura – diceva che in loro non c’era nulla da spezzare. Non duravano molto con lui, e neppure gli indiani – tranne alcuni davvero testardi. Ma neanche la ferocia o la ribellione erano una via: ammazzava chi provava a compiacerlo troppo presto, e chi restava ribelle troppo a lungo.";
			link.l1 = "È orribile... Dimmi, Levasseur ha mai avuto donne d’Asia?";
			link.l1.go = "PZ_AnabelleLutter13";
		break;
		
		case "PZ_AnabelleLutter13":
			dialog.text = "No, almeno non che io sappia. Quanto a me... ti ho già detto che a lui non piacevano le donne di pelle scura. Così, quando Matt lavorava per Francois, passeggiava con me per le strade di Tortuga senza nascondersi. Una volta mi ha perfino portata alla residenza.";
			link.l1 = "Ma Levasseur voleva comunque farti diventare uno dei suoi schiavi...";
			link.l1.go = "PZ_AnabelleLutter14";
		break;
		
		case "PZ_AnabelleLutter14":
			dialog.text = "Esattamente... Non so perché gli piacessi così tanto... Quando Matt lo scoprì, fuggì dall’isola appena glielo dissero. Non è mai più tornato a Tortuga. Forse era un po’ matto, ma mi voleva bene. Mi chiamava il suo tesoro...";
			link.l1 = "Quindi era questo che intendeva quando ha detto che Sotta gli aveva rubato il tesoro!";
			link.l1.go = "PZ_AnabelleLutter15";
		break;
		
		case "PZ_AnabelleLutter15":
			dialog.text = "Heh, ha davvero detto così? Ah, Matt... Ma pare che non fossimo destinati a invecchiare insieme. Se Levasseur puntava una donna, avrebbe fatto qualsiasi cosa per averla, senza badare a chi fosse o al prezzo da pagare. Sotta era uno dei suoi capitani, e ha semplicemente obbedito agli ordini.";
			link.l1 = "Capisco. E adesso, che pensi di fare, Annabel?";
			link.l1.go = "PZ_AnabelleLutter16";
		break;
		
		case "PZ_AnabelleLutter16":
			dialog.text = "Fuggire. In un posto dove gli uomini di Levasseur non possano trovarmi. Cambiare nome. Camuffarmi...";
			link.l1 = "Mi auguro che tu abbia successo. Ti auguro ogni bene, Annabel.";
			link.l1.go = "PZ_AnabelleLutter17";
			if (sti(pchar.Money) >= 10000)
			{
				link.l2 = "Avrai bisogno di denaro per trovare un passaggio. Prendi questi. Qui ci sono diecimila pesos.";
				link.l2.go = "PZ_AnabelleLutter17_Peso";
			}
			if (PCharDublonsTotal() >= 100)
			{
				link.l3 = "Ti servirà ben più di qualche moneta. Non tutti vorranno aiutare una ragazza dalla pelle scura, neanche se è una mezzosangue. Tieni, prendi cento dobloni – trova una nave e sparisci.";
				link.l3.go = "PZ_AnabelleLutter17_Dublon";
			}
		break;
		
		case "PZ_AnabelleLutter17":
			dialog.text = "Anche tu! Addio, Capitano.";
			link.l1 = "Addio.";
			link.l1.go = "Exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Peso":
			dialog.text = "Io... non so davvero cosa dire. Nessuno, a parte Matt, mi ha mai trattata con tanta gentilezza.";
			link.l1 = "Forse è un segno. Che troverai pace e vecchiaia serena, da qualche parte, alla fine. Addio.";
			link.l1.go = "Exit";
			AddMoneyToCharacter(pchar, -10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Dublon":
			dialog.text = "Hai ragione. Ti ringrazio davvero per questo. Ti ricorderò nelle mie preghiere finché avrò fiato.";
			link.l1 = "Grazie. Che il vento ti sia favorevole.";
			link.l1.go = "Exit";
			RemoveDublonsFromPCharTotal(100);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_Longway_47":
			dialog.text = "Quell'uomo... No, non è più un uomo. È una bestia. Un mostro. Tortura le donne in quel modo...";
			link.l1 = "So cosa stai pensando, Longway. Ma hai sentito – non ha mai avuto una donna dalla pelle gialla.";
			link.l1.go = "PZ_Longway_48";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Longway_48":
			dialog.text = "Ma lui conosceva tutta la combriccola! Van der Vink, Fermentelos, Sotta... L’abbiamo appena letto nel suo diario. E se quel 'lei' fosse... proprio lei?";
			link.l1 = "Chi può dirlo... Una donna assetata di vendetta contro Fermentelos – è facile capire perché lo pensi. Ma poteva essere qualsiasi donna la cui vita sia stata fatta a pezzi da Oliveiro. Non deve per forza essere tua sorella. E nemmeno una donna dalla pelle gialla.";
			link.l1.go = "PZ_Longway_49";
		break;
		
		case "PZ_Longway_49":
			dialog.text = "State... rifiutando di provarci, Mio Signore Capitano? Proprio all’ultimo...?";
			link.l1 = "No, Longway. Ma come te la immagini? Difficile che Levasseur risponda alle nostre domande. E ficcare il naso a Tortuga in questo modo è troppo pericoloso.";
			link.l1.go = "PZ_Longway_50";
		break;
		
		case "PZ_Longway_50":
			dialog.text = "Allora, che cosa suggerisci?";
			link.l1 = "Aspettiamo il momento giusto. Sappiamo che Levasseur non apprezza donne come tua sorella. Possiamo risparmiare le forze per ora. Pazienza e fermezza. Francois è un osso duro, soprattutto per via della sua 'tartaruga.' Ma con l’aiuto di Svenson, potremo parlargli alle nostre condizioni. Ti ho promesso che ti avrei aiutato a trovare tua sorella e intendo mantenere la parola. Mi credi, Longway?";
			link.l1.go = "PZ_Longway_51";
		break;
		
		case "PZ_Longway_51":
			dialog.text = "Hmm... Sissignore, Mio Signore Capitano. Ma Longway chiede ancora un favore a voi.";
			link.l1 = "Che c'è? Non vorrai mica andartene di nuovo per conto tuo, vero? L’ultima volta non è finita proprio alla grande.";
			link.l1.go = "PZ_Longway_52";
		break;
		
		case "PZ_Longway_52":
			dialog.text = "Affatto, Mio Signore Capitano. Ora capisco che, purtroppo, un uomo come me non può nulla da solo in un mondo governato dai bianchi. Longway vi chiede di attraccare a Capsterville e consegnare una lettera a Georges Gravel, chiedendogli di scoprire qualsiasi cosa mentre vi preparate.";
			link.l1 = "Un'idea saggia, Longway. Così faremo.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToShore");
		break;
		
		case "PZ_Longway_53":
			dialog.text = "Mio Signore Capitano, Longway deve chiedere una cosa...";
			link.l1 = "Hai dimenticato di scrivere la lettera? Puoi semplicemente parlare con Gravel.";
			link.l1.go = "PZ_Longway_54";
		break;
		
		case "PZ_Longway_54":
			dialog.text = "No, la lettera è pronta. Ma Longway ha pensato che sia meglio non andare in giro per la città da solo. Mio Signore Capitano... potresti consegnare tu la lettera a Georges per me? Ti prego?";
			link.l1 = "Sembro forse un messaggero ai tuoi occhi? O sei tu il capitano qui?";
			link.l1.go = "PZ_Longway_55";
		break;
		
		case "PZ_Longway_55":
			dialog.text = "Mio Signore Capitano...";
			link.l1 = "Ah ah ah, sto solo scherzando, Longway! Ricordamelo, dove trovo questo tuo Gravel?";
			link.l1.go = "PZ_Longway_56";
		break;
		
		case "PZ_Longway_56":
			dialog.text = "Lavora in chiesa.";
			link.l1 = "Va bene, ci penso io, giusto?";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToCapstervilleChurch");
			AddLandQuestMark(characterFromId("Charles_Priest"), "questmarkmain");
		break;
		
		// Этап 5
		case "PZ_Mary_Sharptown1":
			dialog.text = "Charles, mio caro Charles, c'è qualcosa che non va? Sembri preoccupato e... stanco, giusto.";
			link.l1 = "Oh, no, no, Mary, sto bene. È solo... questa mia faccenda a Tortuga. Sembra essere un vicolo cieco... di nuovo. E quel testamento di Sharp mi ha proprio sfinito, per l'amor del cielo. Ma lasciamo stare.";
			link.l1.go = "PZ_Mary_Sharptown2";
		break;
		
		case "PZ_Mary_Sharptown2":
			dialog.text = "Cosa? Quale impresa? E cosa c’entra Sharp con tutto questo? Non ci capisco un’acca!";
			link.l1 = "Troppe domande, Mary. Questo non è il posto per simili chiacchiere. Ne parleremo nella stanza della taverna? Proprio come piace a te, lontano da occhi e orecchie indiscrete. Ti racconterò cosa ho combinato nell’ultimo anno.";
			link.l1.go = "PZ_Mary_Sharptown3";
		break;
		
		case "PZ_Mary_Sharptown3":
			dialog.text = "Va bene! Però attento: se stai nascondendo qualcosa, giusto?";
			link.l1 = "Assolutamente no! Andiamo, tanto dobbiamo comunque ammazzare un po' di tempo...";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_Helena_Sharptown1":
			dialog.text = "Che strano, vero, Charles? Questa isola dovrebbe appartenere a me, ma non sento affatto di possederla.";
			link.l1 = "Tu credi?";
			link.l1.go = "PZ_Helena_Sharptown2";
		break;
		
		case "PZ_Helena_Sharptown2":
			dialog.text = "Oh, quel tuo sorriso... Sai proprio come trattare una donna. Ma cosa ti prende? Hai una faccia tutta storta!";
			link.l1 = "Perché? È la mia solita faccia, anche piuttosto affascinante.";
			link.l1.go = "PZ_Helena_Sharptown3";
		break;
		
		case "PZ_Helena_Sharptown3":
			dialog.text = "Charles, posso sentirlo dalla tua voce – ultimamente sei abbattuto.";
			link.l1 = "Ho già troppa carne al fuoco, soprattutto con Longway. Sono esausta. Ma ormai è troppo tardi per mollare, specialmente dopo la promessa che ho fatto a lui e a mio padre.";
			link.l1.go = "PZ_Helena_Sharptown4";
		break;
		
		case "PZ_Helena_Sharptown4":
			dialog.text = "Non capisco... Che c’entra Longway in tutto questo? E quali promesse hai fatto?";
			link.l1 = "Se dobbiamo parlarne, facciamolo in taverna, prendiamo una stanza. Lontano da occhi indiscreti.";
			link.l1.go = "PZ_Helena_Sharptown5";
		break;
		
		case "PZ_Helena_Sharptown5":
			dialog.text = "Va bene, andiamo. Tanto non c’è altro da fare, almeno passiamo un po’ di tempo insieme, giusto?";
			link.l1 = "Apri la strada, tesoro!";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_HelenaMary_Exit":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			WaitDate("", 0, 0, 0, 2, 0);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
			DoQuestReloadToLocation("Pirates_tavern_upstairs", "goto", "goto2", "PZ_Etap5_NaverhuTavernBandits");
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Guarda come dormono stretti l’uno all’altro! Che incanto!";
				link.l1 = "Invidiosa, giusto?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Su, sveglia! Come avete dormito, piccioncini?";
				link.l1 = "Bene, grazie per la domanda. E voi, ragazzi, avete dormito bene?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_2";
			locCameraFromToPos(2.34, 1.92, 1.66, true, -1.66, -0.69, -0.02);
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "È una domanda sciocca, non trovi, giusto?";
				link.l1 = "Proprio così. E una sciocchezza da parte tua, sai? Vuoi sapere perché?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Dicono che hai una lingua affilata, Charles de Maure.";
				link.l1 = "E non solo la mia lingua. Vuoi scoprirlo? Ma dimmi, perché non hai attaccato mentre dormivamo?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_3";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "E perché mai, giusto?";
				link.l1 = "Non conviene far arrabbiare Mary di mattina. Capirai presto il perché, giusto?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Semplice! Era buio, capisci, quindi non riuscivamo a capire chi di voi fosse la ragazza.";
				link.l1 = "Bastardo.";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_4";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "A differenza tua, non temo le donne. Ehi ragazzi, portatela sana e salva, oppure l’Ugonotto ci farà diventare donnicciole anche noi!";
				link.l1 = "Hu... chi?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Almeno io ho l’aspetto di un uomo. Ragazzi, prendete la bionda viva – l’ugonotto la vuole tutta intera.";
				link.l1 = "Hu... chi?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_5";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_NaverhuTavernBandits_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "PZ_Etap5_NaverhuTavernBandits_Win");
			}
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_1":
			DelLandQuestMark(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Chi era quello, Charles? Chi diavolo è quell'ugonotto? È davvero...?";
				link.l1 = "Ce n’è solo una, Mary. E faremmo meglio a...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Charles... che diavolo era quello? Un ugonotto? È l’uomo che penso io?";
				link.l1 = "Temo di sì, Helen. Dobbiamo...";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_2";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Senti questo? Qualcuno si avvicina, giusto. Amici di questi morti, probabilmente.";
				link.l1 = "Allora li raggiungeranno anche loro. Preparatevi...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Senti? Passi in arrivo.";
				link.l1 = "Proprio così. Stai dietro di me.";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_3";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_61";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_Longway_61":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Mio Signore Capitano, signora "+sStr+".";
			link.l1 = "Longway?! Pensi di poter entrare nella nostra stanza così, senza bussare? E se fossimo stati...?";
			link.l1.go = "PZ_Longway_62";
			
			//заранее создаём заглушку для корабля
			sld = GetCharacter(NPC_GenerateCharacter("PZ_ShipStasis", "citiz_46", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			SetSPECIAL(sld, 1, 1, 1, 1, 1, 1, 1);
		break;
		
		case "PZ_Longway_62":
			dialog.text = "Umilmente chiedo scusa, Mio Signore Capitano. Pensavo che avreste chiuso la porta, se foste stato così occupato. Ma Longway l'ha trovata spalancata.";
			link.l1 = "Rotto, non aperto. Ma dimmi, amico mio, perché sei così maledettamente calmo? Ci sono cadaveri sul pavimento, siamo armati, e tu...";
			link.l1.go = "PZ_Longway_63";
		break;
		
		case "PZ_Longway_63":
			dialog.text = "Beh, ci sono abituata.";
			link.l1 = "E non puoi mica discutere con questo, giusto? Ma davvero non hai sentito i rumori della rissa mentre arrivavi qui? Non hai visto quei brutti ceffi entrare nella taverna e salire le scale proprio davanti a te?";
			link.l1.go = "PZ_Longway_64";
		break;
		
		case "PZ_Longway_64":
			dialog.text = "No, Mio Signore Capitano. Non ho visto stranieri nella sala mentre salivo quassù.";
			link.l1 = "È una coincidenza assurda. Allora, che vuoi, Longway?";
			link.l1.go = "PZ_Longway_65";
		break;
		
		case "PZ_Longway_65":
			dialog.text = "Ho urgentemente bisogno di una nave e di un equipaggio, Mio Signore Capitano.";
			link.l1 = "Cosa? Perché? Hai finalmente trovato la pista di Chang Xing? Allora andiamocene subito a prenderla, insieme.";
			link.l1.go = "PZ_Longway_66";
		break;
		
		case "PZ_Longway_66":
			dialog.text = "Non Chang Xing, ahimè. È... Joep van der Vink. Georges Gravel ha mandato un messaggio e l'ho ricevuto mentre passeggiavo per il villaggio, mentre voi... vi riposavate con la signora.";
			link.l1 = "Ay, ho riposato come un re, te lo dico io. Ma perché dovremmo separarci adesso, Longway? Abbiamo una maledetta lista lunga quanto il mare di faccende da sbrigare e bastardi pericolosi da mandare all'altro mondo.";
			link.l1.go = "PZ_Longway_67";
		break;
		
		case "PZ_Longway_67":
			dialog.text = "Van der Vink non è pericoloso quanto Levasseur. Inoltre, l’ho già sconfitto una volta. E lo sconfiggerò di nuovo. Stavolta, per assicurarmi che sia morto per davvero. Non voglio che tutti noi sprechiamo tempo prezioso con lui. Dovreste andare a Tortuga e chiedere alle persone importanti tutto ciò che ci serve sapere. Io prenderò van der Vink da solo. Mio Signore Capitano, non vale la pena che perdiate tempo su questo, anch’io sono stato Capitano una volta. Me la caverò.";
			link.l1 = "Hmm, hai ragione, Longway. Van der Vink forse non è così pericoloso, ma la 'Banten' è una delle navi più veloci dell’Arcipelago. Non basta una nave qualsiasi per inseguirla. E per quanto riguarda l’equipaggio? Come pensi di radunare uomini così in fretta e da solo?";
			link.l1.go = "PZ_Longway_68";
		break;
		
		case "PZ_Longway_68":
			dialog.text = "So il posto giusto e ho una certa reputazione con la Compagnia laggiù. O almeno posso fingere di averla, come ho fatto con Georges. La Compagnia... il signor Rodenburg si affidava a loro quando aveva urgente bisogno di uomini d’arme, equipaggi esperti che non si fanno troppe domande.";
			link.l1 = "Un equipaggio di nave da assoldare, dunque... Ha senso che esista una cosa del genere. E quanto costerà?";
			link.l1.go = "PZ_Longway_69";
		break;
		
		case "PZ_Longway_69":
			dialog.text = "Duemilacinquecento. Subito, adesso, all’istante.";
			link.l1 = "Tutto qui? Per ingaggiare una ciurma di marinai perbene in una taverna, specie per una nave grossa, serve ben altro. Pare che Rodenburg e i suoi uomini abbiano prezzi speciali in posti speciali.";
			link.l1.go = "PZ_Longway_70";
		break;
		
		case "PZ_Longway_70":
			dialog.text = "Intendevo dobloni, Mio Signore Capitano.";
			link.l1 = "COSA?!";
			link.l1.go = "PZ_Longway_70_4";
		break;
		
		case "PZ_Longway_70_4":
			dialog.text = "Avete sentito bene, Mio Signore Capitano. È cosa grave. Non vi chiederei mai simile somma per una sciocchezza.";
			link.l1 = "Sì, ti ho sentito, ma ancora non ci credo. Prezzi speciali, davvero. Accettano anche i pesos?";
			link.l1.go = "PZ_Longway_70_5";
		break;
		
		case "PZ_Longway_70_5":
			dialog.text = "Sì... dai bianchi. Longway potrebbe avere problemi con questo, ma... credo di poterli convincere, se insisto abbastanza. C'è sempre una via.";
			link.l1 = "Be’, questa è una cosa. Ed è solo per l’equipaggio... E poi devi anche arrivare alla tua nave. Pure quella in qualche ‘posto speciale’, vero? Ho paura solo a chiedere quanto ci costerà questa faccenda...";
			link.l1.go = "PZ_Longway_70_6";
		break;
		
		case "PZ_Longway_70_6":
			dialog.text = "Non proprio così, Mio Signore Capitano. L’equipaggio arriva già con la propria nave.";
			link.l1 = "Ma?";
			link.l1.go = "PZ_Longway_70_7";
		break;
		
		case "PZ_Longway_70_7":
			dialog.text = "La 'Meifeng'. Potrebbe diventare il fattore decisivo – nessuna nave nell’Arcipelago corre come lei. E lei... era mia, dunque la conosco bene. Me la presterai, Mio Signore Capitano?";
			if (PCharDublonsTotal() >= 2500)
			{
				link.l1 = "Ecco. Duemilacinquecento dobloni e mezzo. Purché tu mi porti la testa di van der Vink su un vassoio d’oro massiccio, ah ah ah ah!";
				link.l1.go = "PZ_Longway_Dublons_1";
			}
			if (sti(pchar.Money) >= 300000)
			{
				link.l2 = "Non ho così tanti dobloni con me, Longway. E dubito persino di averne così tanti sulla nave – stai parlando di una montagna d’oro. Ma pesos, sì. Trecentomila è proprio quello che ti serve.";
				link.l2.go = "PZ_Longway_Peso_1";
			}
			link.l3 = "Sai che ti dico, Longway... Mi stai davvero chiedendo di spendere tanto oro quanto basta per armare una flotta d’assedio, solo perché tu possa menar le mani con uno scagnozzo qualsiasi?!";
			link.l3.go = "PZ_Longway_Otkaz";
		break;
				
		case "PZ_Longway_Dublons_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Oh... Longway vi ringrazia dal profondo del suo cuore, Mio Signore Capitano! Ma ancora, che ne sarà della 'Meifeng'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "Che domande fai? Mio amico, ti sei forse dato una botta in testa venendo qui? Lei è nella nostra flotta in questo momento!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Devo rifletterci sopra, Longway.  Quanto tempo abbiamo per prendere van der Vink?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
			RemoveDublonsFromPCharTotal(2500);
			pchar.questTemp.PZ_FlagShipDublons = true;
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_Longway_Peso_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Mio Signore Capitano, avete commesso un piccolo errore. Sarebbero duecentocinquantamila pesos.";
			link.l1 = "I did not; it's Charles de Maure's special exchange rate when his friends need help, ha ha. I'm giving you extra so you'll have enough for everything.";
			link.l1.go = "PZ_Longway_Peso_2";
			AddMoneyToCharacter(pchar, -300000);
		break;
		
		case "PZ_Longway_Peso_2":
			dialog.text = "Grazie mille, Mio Signore Capitano... Ma, che ne sarà della 'Meifeng'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "E lei? Amico mio, ti sei forse dato una botta in testa venendo qui? In questo momento fa parte della nostra flotta!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Devo rifletterci, Longway.   Quanto tempo abbiamo per acciuffare van der Vink?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
		break;
		
		case "PZ_Longway_Otkaz":
			dialog.text = "Non c’è altra via, Mio Signore Capitano, vi prego, mantenete la calma...";
			link.l1 = "Oh, non ho ancora cominciato. Ecco il patto. Cinquantamila pesos. Basteranno appena per comprare una brigantina dal cantiere, armarla per la battaglia e persino ingaggiare un equipaggio.";
			link.l1.go = "PZ_Longway_Otkaz_2";
			AddMoneyToCharacter(pchar, -50000);
			
			pchar.questTemp.PZ.LongwayBrig = true; // Лонгвэй будет на бриге
			notification("Longway disapproves", "Longway");
		break;
		
		case "PZ_Longway_Otkaz_2":
			dialog.text = "Ma, Mio Signore Capitano. Può bastare per un capitano bianco! Non tutti vorranno trattare con Longway. Faranno il diavolo a quattro prima di vendermi qualsiasi cosa!";
			link.l1 = "Dunque, sii convincente! Sei piuttosto bravo a mercanteggiare, a giudicare dalla tua... prima offerta. Sei ancora qui? Prendi questi soldi e vai, visto che dici che è così urgente!";
			link.l1.go = "PZ_Longway_Otkaz_3";
		break;
		
		case "PZ_Longway_Otkaz_3":
			dialog.text = "Aye aye, Mio Signore Capitano...";
			link.l1 = "E non guardarmi così. Ci vediamo dopo a Tortuga. Buona fortuna.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "58");
		break;
		
		case "PZ_Longway_Mayfang1":
			dialog.text = "Ehm, no, Mio Signore Capitano. Certo che ricordo. Longway stava solo chiedendo se sei pronto a condividerla con me.";
			link.l1 = "Sì, lo sono. Dopotutto, van der Vink ha le mani sporche quanto gli altri riguardo alle disgrazie di tua sorella. Quindi prenderlo è davvero fondamentale. Ti affido il comando della Meifeng.";
			link.l1.go = "PZ_Longway_Mayfang2";
		break;
		
		case "PZ_Longway_Mayfang2":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "Non ci posso credere... Grazie, Mio Signore Capitano!";
			link.l1 = "Ah, non è nulla. Un tempo era la tua nave, questo non lo dimenticherò mai. Bene, avanti. Uccidi quel figlio di puttana. Io me ne vado a Tortuga.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "59");
			notification("Longway approves", "Longway");
		break;
		
		
		case "PZ_Longway_NoMayfang1":
			dialog.text = "Il tempo stringe, Mio Signore Capitano. Non dovremmo sprecarlo – forse Chang Xing ha bisogno del nostro aiuto...";
			link.l1 = "Lo so, Longway. Ma quanto tempo abbiamo esattamente per prendere van der Vink?";
			link.l1.go = "PZ_Longway_NoMayfang2";
		break;
		
		case "PZ_Longway_NoMayfang2":
			dialog.text = "Un paio di mesi – va avanti sulla rotta abituale per quel tempo prima di sparire per un po’. Così fa sempre, come mi ha scritto Gravel nella sua lettera.";
			link.l1 = "Va bene. Andiamo alla nave, allora...";
			link.l1.go = "PZ_Longway_NoMayfang3";
		break;
		
		case "PZ_Longway_NoMayfang3":
			dialog.text = "Temo che i miei preparativi debbano iniziare subito, Mio Signore Capitano. Così potremo partire senza indugio, appena avrò la Meifeng. Devo trattare prima con gli uomini.";
			link.l1 = "Dove ci incontriamo?";
			link.l1.go = "PZ_Longway_NoMayfang4";
		break;
		
		case "PZ_Longway_NoMayfang4":
			AddQuestRecord("PZ", "60");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			i = FindColony("Pirates");
			if (colonies[i].nation != ENGLAND)
			{
				dialog.text = "Proprio qui. Ma possiamo incontrarci all’arsenale, se preferisci.";
				link.l1 = "E perché sono l’unico che non sapeva che qui si può arruolare un’intera ciurma di uomini armati, basta pagare il prezzo giusto?";
				link.l1.go = "PZ_Longway_NoMayfangIslaTesoro1";
			}
			else
			{
				dialog.text = "Quei mercenari avevano un rifugio sull’Isla Tesoro, ma sono stati costretti a trasferirsi qui.";
				link.l1 = "Capisco il perché. Allora, dove ti trovo a La Vega?";
				link.l1.go = "PZ_Longway_NoMayfangLaVega1";
			}
		break;
		
		case "PZ_Longway_NoMayfangIslaTesoro1":
			dialog.text = "Perché sono in pochi a conoscerla. E ancora meno possono permettersela. Mynheer Rodenburg è stato per molto tempo il loro unico cliente.";
			link.l1 = "Capisco. Va bene, Longway. Ci vediamo laggiù.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToPiratesShipyard");
		break;
		
		case "PZ_Longway_NoMayfangLaVega1":
			dialog.text = "La taverna, Mio Signore Capitano. Dove altro potrei mai trovarmi?";
			link.l1 = "Giusto. Allora ci vediamo dopo, Longway! Stammi bene.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToLaVegaTavern");
		break;
		
		case "PZ_Longway_WaitForShip1":
			dialog.text = "Mio Signore Capitano, devo informarvi che l’equipaggio è pronto. Resta solo una questione da risolvere. Che ne sarà della 'Meifeng'?";
			link.l1 = "Finora non ho ancora scelto una nave degna di te, Longway.";
			link.l1.go = "PZ_Longway_WaitForShip2";
			if ((FindCompanionShips(SHIP_SCHOONER_W)) || (FindCompanionShips(SHIP_BRIG)) || (FindCompanionShips(SHIP_CORVETTE)) || (FindCompanionShips(SHIP_POLACRE)) || (FindCompanionShips(SHIP_XebekVML)) || (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				if (FindCompanionShips(SHIP_SCHOONER_W)) sStr = "War schooner";
				if (FindCompanionShips(SHIP_BRIG)) sStr = "Brig";
				if (FindCompanionShips(SHIP_CORVETTE)) sStr = "Corvette";
				if (FindCompanionShips(SHIP_POLACRE)) sStr = "Polacre";
				if (FindCompanionShips(SHIP_XebekVML)) sStr = "Xebek";
				if (FindCompanionShips(SHIP_BRIGANTINE)) sStr = "Brigantine";
				link.l2 = "'"+sStr+"‘ è vostro.’";
				link.l2.go = "PZ_Longway_NoQuestShip1";
			}
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l3 = "E della 'Meifeng'? Credevi davvero che l’avrei lasciata marcire?";
				link.l3.go = "PZ_Longway_Mayfang3";
			}
			if (FindCompanionShips(SHIP_CURSED_FDM))
			{
				link.l4 = "Ho una... nave speciale per te, Longway. Veloce. E perfino più letale della Meifeng. È un galeone da guerra, il 'Cuore Volante'.";
				link.l4.go = "PZ_Longway_Caleuche1";
			}
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				link.l5 = "Ti piacciono gli sciabecchi, Longway. E le polacche? Specialmente questa qui, la 'Torero'. Non fatta per le regate, certo, ma è una bella bestia potente.";
				link.l5.go = "PZ_Longway_Torero1";
			}
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				link.l6 = "Devo ammettere, non pensavo che un giorno avrei trovato un degno impiego per questo. Che ne pensi di questo galeone? Il possente 'El Casador'!";
				link.l6.go = "PZ_Longway_ElCasador1";
			}
		break;
		
		case "PZ_Longway_NoQuestShip1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			
			// а теперь хором, дети: ненавижу костыли, ненавижу костыли, ненавижу костыли, нена... помогите!!!
			if ((FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_SCHOONER_W)
						{
							//pchar.questTemp.PZ.SchoonerW.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.SchoonerW.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwaySchoonerW = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIG)
						{
							//pchar.questTemp.PZ.Brig.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brig.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrig = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_CORVETTE)
						{
							//pchar.questTemp.PZ.Corvette.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Corvette.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayCorvette = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE)
						{
							//pchar.questTemp.PZ.Polacre.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.Polacre.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayPolacre = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_XebekVML)
						{
							//pchar.questTemp.PZ.Xebek.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Xebek.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayXebek = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIGANTINE)
						{
							//pchar.questTemp.PZ.Brigantine.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brigantine.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrigantine = true;
			}
			
			dialog.text = "Non è la 'Meifeng', Mio Signore Capitano! Che è successo alla Meifeng?";
			link.l1 = "Longway! "+sStr+"  è in pericolo! E anche tua sorella! E tu stai qui a lamentarti perché non hai una nave come questa?! Chiunque sarebbe felice di avere una nave del genere! Prendila sotto il tuo comando  e mostra a van der Vink di che pasta sei fatto.";
			link.l1.go = "PZ_Longway_NoQuestShip2";
		break;
		
		case "PZ_Longway_NoQuestShip2":
			dialog.text = "Bene... Spero che il Cielo mi mandi fortuna. E spero lo stesso per voi su Tortuga. Addio, Mio Signore Capitano.";
			link.l1 = "Ne sono certo. Addio, Longway.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			pchar.questTemp.PZ_NoQuestShip = true;
		break;
		
		case "PZ_Longway_Mayfang3":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "Ehm, no, Mio Signore Capitano. Certo che ricordo. Longway stava solo chiedendo se sei pronto a condividerla con me.";
			link.l1 = "Lo sono. Dopotutto, van der Vink è coinvolto nei guai di tua sorella tanto quanto gli altri della nostra lista. Quindi catturarlo è davvero fondamentale. Ti affido il comando della 'Meifeng'.";
			link.l1.go = "PZ_Longway_Mayfang4";
		break;
		
		case "PZ_Longway_Mayfang4":
			dialog.text = "Non ci posso credere... Grazie, Mio Signore Capitano!";
			link.l1 = "Ah, non è niente. Era la tua nave, lo ricorderò sempre. Bene, avanti. Ammazza quel figlio di puttana. Io me ne vado a Tortuga.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_Longway_Caleuche1":
			dialog.text = "Io... Io non posso comandare QUESTA cosa, Mio Signore Capitano. Longway tiene ancora alla sua vita, all’anima sua, e a quel poco di senno che gli resta.";
			link.l1 = "Ah ah ah, Longway! Dai, non sapevo fossi così superstizioso. Comunque, la maledizione è stata spezzata, quindi non hai nulla da temere.";
			link.l1.go = "PZ_Longway_Caleuche2";
		break;
		
		case "PZ_Longway_Caleuche2":
			dialog.text = "Ah... ma van der Vink lo sa? Appena vede quella nave, scapperà come un coniglio impaurito.";
			link.l1 = "Hai ragione su questo. Va bene, troveremo qualcos'altro per te.";
			link.l1.go = "PZ_Longway_WaitForShip2";
		break;
		
		case "PZ_Longway_Torero1":
			// если "Тореро" у ГГ
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE_QUEST)
						{
							//pchar.questTemp.PZ.Torero.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Torero.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayTorero = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				notification("Longway approves", "Longway");
			}
			
			dialog.text = "Non ho mai comandato una polacca da solo. È interessante, ma ora ciò che conta è la velocità, non la potenza.";
			link.l1 = "Questo è vero, ma resta pur sempre una polacca. Non sarà veloce come la 'Banten', però puoi prendere il vento da angoli che loro neanche si sognano. Persino meglio di quanto potesse mai la 'Meifeng' stessa. Sfrutta questo vantaggio.";
			link.l1.go = "PZ_Longway_Torero2";
		break;
		
		case "PZ_Longway_Torero2":
			dialog.text = "Eppure... la 'Meifeng' era migliore... Peccato che tu l’abbia lasciata marcire, Mio Signore Capitano. Buona fortuna a Tortuga.";
			link.l1 = "Anche a te, Longway. Ti ringrazio.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_ElCasador1":
			// если "Эль Касадор" у ГГ
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_ELCASADOR)
						{
							//pchar.questTemp.PZ.ElCasador.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.ElCasador.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayElCasador = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				notification("Longway approves", "Longway");
			}
			
			dialog.text = "Che sia pure il galeone più bizzarro di tutto l’Arcipelago, Mio Signore Capitano. So condurlo, ma è più lento della 'Banten'...";
			link.l1 = "Beh, non stai gareggiando contro Joep in una regata, giusto?";
			link.l1.go = "PZ_Longway_ElCasador2";
		break;
		
		case "PZ_Longway_ElCasador2":
			dialog.text = "Come volete. Però la 'Meifeng' era migliore... Peccato l’abbiate lasciata marcire, Mio Signore Capitano. Buona fortuna a Tortuga.";
			link.l1 = "Anche a te, Longway. Ti ringrazio.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_WaitForShip2":
			NextDiag.TempNode = "PZ_Longway_WaitForShip1";
			
			dialog.text = "Apprezzo la tua premura, Mio Signore Capitano, ma per favore sbrighiamoci – il tempo non è dalla nostra parte.";
			link.l1 = "Lo so. Ma non vuoi inseguire ombre a vuoto, giusto? Va bene, ti troverò una nave come si deve.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaTortugaCabin_1":
			dialog.text = "Siamo quasi arrivati, Charles. Hai deciso da dove cominciare? Forse avrebbe senso chiedere un po’ in giro per strada...";
			link.l1 = "Forse è così. Ma non per noi – per me. Tu rimani a bordo, Helen.";
			link.l1.go = "PZ_HelenaTortugaCabin_2";
		break;
		
		case "PZ_HelenaTortugaCabin_2":
			dialog.text = "Charles, certo che sono ancora agitata per quei mascalzoni e per quello che hanno detto, e ha senso che resti sotto la protezione dell'equipaggio... Ma il fatto che tu vada da solo nella tana della bestia non mi fa sentire più al sicuro.";
			link.l1 = "Capisco. Ma se le cose vanno storte, è molto più facile fuggire da solo, sapendo che sei al sicuro. È un ordine, Helen. Aspettami qui e cerca di non preoccuparti troppo.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_MaryTortugaCabin_1":
			dialog.text = "Ecco Tortuga, Charles, giusto. Non vedo l'ora di bussare a qualche porta e chiedere che cosa voleva da me quell'asino grasso...";
			link.l1 = "Proprio per questo tu resti a bordo, mia cara.";
			link.l1.go = "PZ_MaryTortugaCabin_2";
			
			pchar.questTemp.MarySexBlock = true;
			pchar.quest.Mary_giveme_sex.over = "yes";
			pchar.quest.Mary_giveme_sex1.over = "yes";
		break;
		
		case "PZ_MaryTortugaCabin_2":
			dialog.text = "Nemmeno per sogno! Pensi davvero che ti lascerò sbarcare da solo?";
			link.l1 = "Penso che se Levasseur decidesse di finire quello che i suoi sgherri non sono riusciti a portare a termine, noi non avremmo alcuna possibilità di resistere. Non voglio provocarlo senza motivo, soprattutto perché il mio bersaglio non è lui, ma Joep van der Vink.";
			link.l1.go = "PZ_MaryTortugaCabin_3";
		break;
		
		case "PZ_MaryTortugaCabin_3":
			dialog.text = "Quindi ora sono in gabbia, giusto?";
			link.l1 = " Non ti sto dando ordini, ti sto chiedendo un favore, Mary.";
			link.l1.go = "PZ_MaryTortugaCabin_4";
		break;
		
		case "PZ_MaryTortugaCabin_4":
			dialog.text = "E se ti succedesse qualcosa in qualche lurido vicolo di quell’isola di merda?";
			link.l1 = "Allora prometto che non farò l’eroe. Sapere che sei al sicuro mi farà correre più veloce. Aspettami sulla nave, e per l’amor di Dio, non scendere a terra, qualsiasi cosa accada.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_RobertMartin1":
			chrDisableReloadToLocation = true;
			
			dialog.text = "Chi sei? Dubito che tu abbia attraversato la spiaggia solo per fare due chiacchiere.";
			link.l1 = "Proprio così. Charles de Maure. Rober Martene?";
			link.l1.go = "PZ_RobertMartin2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_RobertMartin2":
			dialog.text = "Il Charles de Maure? Merda, basta che non mi trascini in qualche porcheria. Sì, sono io. Allora, che vuoi?";
			link.l1 = "Mi hanno detto che siete amico di Joep van der Vink, e...";
			link.l1.go = "PZ_RobertMartin3";
		break;
		
		case "PZ_RobertMartin3":
			dialog.text = "Chi ti ha detto questo? Gli svuoterò le budella. Beh, ci conosciamo e basta. Non voglio grane solo perché ti ha pestato i piedi.";
			link.l1 = "Heh, sei rapido ad abbandonare i tuoi amici...";
			link.l1.go = "PZ_RobertMartin4";
		break;
		
		case "PZ_RobertMartin4":
			dialog.text = "Non pensare questo. Non ho paura di te. Ma perché complicarsi la vita o peggiorarla? Non conosco Joep così bene come ti hanno detto. Lo stai cercando?";
			link.l1 = "Sì, più o meno. So che ha già lasciato Tortuga, ma non farebbe male sapere qualcosa in più su di lui – dove sia stato, con chi abbia parlato. Puoi aiutarmi, giusto?";
			link.l1.go = "PZ_RobertMartin5";
		break;
		
		case "PZ_RobertMartin5":
			dialog.text = "Non ti sarebbe servito comunque, quindi... perché no? Era in un bordello. Il bordello. Credo che tu possa permettertelo, quindi te lo dico.";
			link.l1 = "Un altro bordello? Non ti basta più quello che hai, giusto?";
			link.l1.go = "PZ_RobertMartin6";
		break;
		
		case "PZ_RobertMartin6":
			dialog.text = "Beh, non è proprio una novità, ma pochi ne sono a conoscenza. E ancora meno possono permetterselo. Pare che sia arrivato il tuo momento. Ma attento: qui si accettano solo dobloni. Se tiri fuori dell’argento, ti arriva un calcio nel sedere.";
			link.l1 = "L'avevo immaginato. E dove hai detto che si trova questo bordello?";
			link.l1.go = "PZ_RobertMartin7";
		break;
		
		case "PZ_RobertMartin7":
			dialog.text = "Conosci quell'edificio con le colonne? È proprio quello. E che padrona di casa hanno! Pelle gialla, così bella! Eh, vedo che già sbavi, eh?";
			link.l1 = "Heh-heh, più o meno. Grazie, Rober. Nessun guaio oggi per te – mi sei stato davvero d'aiuto, giusto?";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LighthouseMartinGo");
		break;
		
		case "PZ_MaryTortugaCabin_11":
			dialog.text = "Finalmente sei tornato, Charles! Non sapevo più dove mettermi, giusto!";
			link.l1 = "Non ci metterò molto, Mary. Ho una piccola faccenda da sbrigare... Non ti terrò sulle spine – riguarda Longway. Devo fare un salto in un bordello qui vicino.";
			link.l1.go = "PZ_MaryTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MaryTortugaCabin_12":
			dialog.text = "Sapevo che non avrei dovuto lasciarti andare a terra da solo. O ti sei dimenticato di metterti il cappello e ti si è fusa la testa... Oppure l’hai sbattuta, giusto!";
			link.l1 = "Mary, ascoltami. È possibile che la proprietaria di questo posto sia la sorella di Longway. Per esserne certo dovrei vederla, ma solo questo intendo fare. Non posso farlo senza entrare. Però non voglio che tu pensi qualcosa che non dovresti, giusto?";
			link.l1.go = "PZ_MaryTortugaCabin_13";
		break;
		
		case "PZ_MaryTortugaCabin_13":
			dialog.text = "Sei sicuro di non mentirmi, Charles?";
			link.l1 = "Mary, guarda la cosa da questo punto di vista... Hai mai sentito di un uomo che avverte la sua amata su...?";
			link.l1.go = "PZ_MaryTortugaCabin_14";
		break;
		
		case "PZ_MaryTortugaCabin_14":
			dialog.text = "Fermati subito, Charles, non voglio nemmeno pensarci. Credo in te e mi fido. E spero che non rimarrai lì più del necessario.";
			link.l1 = "Non un minuto di più, tesoro, te lo giuro. Dentro e fuori, vedrai.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_HelenaTortugaCabin_11":
			dialog.text = "Charles! Sei tornato ancora prima di quanto pensassi. Ma che ti è successo? Non hai un bell'aspetto... Sei riuscito a scoprire qualcosa su Joep van der Vink?";
			link.l1 = "Non ancora. Ho scoperto alcune cose, ma per andare oltre... devo andare in un... bordello. Non per quello che pensa la gente, ovviamente.";
			link.l1.go = "PZ_HelenaTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_HelenaTortugaCabin_12":
			dialog.text = "Un bordello? Non sapevo che questi posti offrissero altro oltre all’ovvio.";
			link.l1 = "Devo parlare col padrone, tutto qui. E non è certo un bordello qualunque. Si dice che sia un locale d’alto bordo, riservato solo ai membri della nobiltà...";
			link.l1.go = "PZ_HelenaTortugaCabin_13";
		break;
				
		case "PZ_HelenaTortugaCabin_13":
			dialog.text = "E allora fa proprio per te, tesoro. Oh, sto scherzando. Però, non mi piace molto che tu vada lì. Ma...";
			link.l1 = "Prometto che vado solo per gli affari di Longway. È molto possibile che la proprietaria di quel posto sia sua sorella. Non ci starò a lungo.";
			link.l1.go = "PZ_HelenaTortugaCabin_14";
		break;
		
		case "PZ_HelenaTortugaCabin_14":
			dialog.text = "Come desideri. Non sei tenuto a raccontarmi certe cose. Non ti ho mai promesso che non sarei andata a letto con un altro uomo. Eppure, non lo faccio. Perché per me è una cosa scontata.";
			link.l1 = "In altre circostanze, ti avrei portato con me, ma...";
			link.l1.go = "PZ_HelenaTortugaCabin_15";
		break;
		
		case "PZ_HelenaTortugaCabin_15":
			dialog.text = "Grazie, ma no grazie. Charles, non preoccuparti. Non sono una sciocca gelosa, giusto? Beh, magari gelosa sì, ma non scema. E ti credo. Sciocca io!";
			link.l1 = "Grazie, Helen. Torno subito.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_PredupredilNashuDevushku":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.PZ_PredupredilNashuDevushku = true;
		break;
		
		case "PZ_ElitaShluha_1":
			dialog.text = "Oh, una nuova faccia nel nostro locale? Benvenuto, monsieur. Cibo, vino invecchiato, un bagno caldo – tutto ti aspetta se puoi permetterti di trascorrere un po’ di tempo con una di noi.";
			link.l1 = "Grazie dell'accoglienza, mademoiselle. Ma non è per questo che sono qui. Sto cercando una persona...";
			link.l1.go = "PZ_ElitaShluha_2";
			
			// Убираем Мартэна с Маяка
			sld = characterFromID("PZ_RobertMartin");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			for (i=1; i<=3; i++)
			{
				sld = characterFromID("PZ_MayakPiraty_"+i);
				sld.lifeday = 0;
			}
			
			sld = characterFromID("PZ_RobertMartin_CloneMayakShip");
			sld.lifeday = 0;
			
			locations[FindLocation("Mayak6")].DisableEncounters = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak6")], false);
			RemoveGeometryFromLocation("Mayak6", "smg");
		break;
		
		case "PZ_ElitaShluha_2":
			dialog.text = "It is only with the heart that one can see rightly; what is essential is invisible to the eye.";
			link.l1 = "Bello. Quelle frasi non le avevo mai sentite prima, sai?";
			link.l1.go = "PZ_ElitaShluha_3";
		break;
		
		case "PZ_ElitaShluha_3":
			dialog.text = "Qui ci insegnano qualcosa, non siamo solo bambole. La padrona pensa che sia fondamentale per la nostra locanda.";
			link.l1 = "La locandiera! È lei che cerco. Ho sentito dire che ha la pelle gialla. Dimmi, è vero? E come si chiama, di grazia?";
			link.l1.go = "PZ_ElitaShluha_4";
		break;
		
		case "PZ_ElitaShluha_4":
			dialog.text = "È vero. Ma ha più cervello per gli affari di tante donne bianche. Si chiama Belle Etoile. Ma basta chiacchiere.";
			link.l1 = "Basta parlare, dici? Io sono qui proprio per parlare. Farò ancora qualche domanda e poi me ne andrò.";
			link.l1.go = "PZ_ElitaShluha_5";
		break;
		
		case "PZ_ElitaShluha_5":
			dialog.text = "E quale sarebbe il guadagno per l’establishment? Qui non si paga per i corpi, ma per il tempo. Vuoi parlare? Sei il benvenuto. Ma il denaro prima, mio caro. E sussurreremo in una stanza, lontano da orecchie indiscrete. Non mi importa cosa facciamo là dentro – non mi importa neanche se accendiamo candele e preghiamo. Una volta un cliente mi ha chiesto di aiutarlo a scrivere una poesia. Un altro voleva solo raccontarmi le sue disgrazie e mi chiamava il suo buon amico. E un terzo – voleva solamente accendere candele, così poi...";
			link.l1 = "Beh, non voglio saperlo – ho già sentito cose spiacevoli di recente. Quanto ti devo?";
			link.l1.go = "PZ_ElitaShluha_6";
		break;
		
		case "PZ_ElitaShluha_6":
			dialog.text = "Duecentocinquanta dobloni. Non si contratta. Se capiamo che abbiamo davanti un poveraccio che fa solo finta, lo buttiamo fuori senza rimpianti. E se invece è ricco ma spilorcio, alziamo il prezzo – pagherà lo stesso.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Ecco a te, duecentocinquanta pezzi d’oro.";
				link.l1.go = "PZ_ElitaShluha_7";
			}
			link.l2 = "Accidenti, qui costa più di quel bordello in Giamaica. Posso tornare dopo, quando avrò racimolato un po’ d’oro, giusto?";
			link.l2.go = "PZ_ElitaShluha_Otkaz_1";
		break;
		
		case "PZ_ElitaShluha_7":
			dialog.text = "Bene. Da dove vogliamo cominciare? Cena, con o senza candele, bagno o conversazione?";
			link.l1 = "Non ho molto tempo, quindi andiamo subito alle mie domande. Guida tu.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Otkaz_1":
			dialog.text = "Ma certo che puoi. La pazienza è una delle virtù di una cortigiana. Cacciare via uno straccione è un conto. Ma permettere a un signore benestante come te di andare a recuperare il denaro, o anche solo di farselo prestare, è tutta un’altra storia.";
			link.l1 = "Le virtù d’una cortigiana... Che ironia. Torno subito.";
			link.l1.go = "PZ_ElitaShluha_Otkaz_2";
		break;
		
		case "PZ_ElitaShluha_Otkaz_2":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
			npchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
			npchar.dialog.currentnode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again":
			dialog.text = "Bentornato, monsieur! Allora, chi sei tu? Un vero signore benestante oppure solo un fanfarone?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Ma certo, sono un gentiluomo benestante, mademoiselle. Ecco il vostro oro – tutti e duecentocinquanta dobloni. Non c’è bisogno di contarli.";
				link.l1.go = "PZ_ElitaShluha_Again_1";
			}
			link.l2 = "Sono ancora a corto, abbi solo un po' di pazienza.";
			link.l2.go = "exit";
			NextDiag.TempNode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again_1":
			dialog.text = "Non si fa il conto qui. Hmm, alcune monete sembrano piegate e spezzate – la padrona non gradirà, ma almeno è tutto vero oro.";
			link.l1 = "Che... persona graziosa, davvero.";
			link.l1.go = "PZ_ElitaShluha_Again_2";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Again_2":
			dialog.text = "Esatto. Madame Etoile può essere dolce e premurosa, può essere severa, e può essere spietata. Ecco perché noi non contiamo, tra l'altro. La padrona non viene sempre pagata subito, ma il suo dovuto lo ottiene sempre. Se non in oro, allora in sangue. Ogni casa di tolleranza ha bisogno di protettori e sostenitori. E i nostri sono all’altezza della reputazione del locale.";
			link.l1 = "Ho già pagato, quindi mostrami la strada.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
		break;
		
		case "PZ_ElitaShluha_IdemVKomnatu":
			DialogExit();
			pchar.PZ_ElitaShluha = npchar.id;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload3", "PZ_ElitaShluha_VKomnate", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			bDisableCharacterMenu = true;
		break;
		
		case "PZ_ElitaShluha_8":
			dialog.text = "Dunque, quali domande avete, monsieur? Proverò a saziare la vostra... curiosità.";
			link.l1 = "Sapete cosa mi incuriosisce, mademoiselle: la vostra padrona, Madame Etoile.";
			link.l1.go = "PZ_ElitaShluha_9";
		break;
		
		case "PZ_ElitaShluha_9":
			dialog.text = "Che dire di lei? Resta un enigma, persino per noi. Pur preoccupandosi della nostra salute, sicurezza e benessere, non si mescola mai con noi e non si lascia mai avvicinare veramente.";
			link.l1 = "Forse non ama le chiacchiere lunghe. Dimmi, parla con accento?";
			link.l1.go = "PZ_ElitaShluha_10";
		break;
		
		case "PZ_ElitaShluha_10":
			dialog.text = "No, perché pensi questo? Solo perché ha la pelle gialla? Parla un francese più puro della seta, e altre lingue ancora. E sa tenere una conversazione brillante su qualsiasi argomento con ospiti e chiunque conti, per un’ora intera.";
			link.l1 = "Ma guarda un po'. Interessante... È qui adesso? Se sì, entrerò a vederla senza far sprecare altro del vostro... preziosissimo tempo, così potrete tornare alle vostre occupazioni.";
			link.l1.go = "PZ_ElitaShluha_11";
		break;
		
		case "PZ_ElitaShluha_11":
			dialog.text = "Non c’è molto a cui tornare – anche se la nostra padrona sogna di far diventare questo posto il migliore di tutto l’Arcipelago. Un ritrovo per pochi eletti, dove né mercanti, né nobili, né gente istruita proverebbero vergogna a varcar la soglia – perché qui offriamo assai più che solo i nostri corpi.";
			link.l1 = "Ma non ci riesce proprio bene, vero?";
			link.l1.go = "PZ_ElitaShluha_12";
		break;
		
		case "PZ_ElitaShluha_12":
			dialog.text = "Come dire... Lei ci vede non solo come merce, come fanno nei bordelli più scadenti, ma come piccoli progetti. Veste ognuna di noi con abiti costosi, ci cura, ci istruisce – investe su ciascuna. E se fossimo in una grande città del Vecchio Mondo, avrebbe fatto fortuna! Ma qui... Anche il più abile dei mercanti resta a mani vuote, se la merce costa così tanto che quasi nessuno può permettersela. Anche abbassando i prezzi, la rovina resta dietro l’angolo.";
			link.l1 = "Mi dispiace sentire questa cosa. Allora, dove si trova adesso la tua padrona?";
			link.l1.go = "PZ_ElitaShluha_13";
		break;
		
		case "PZ_ElitaShluha_13":
			dialog.text = "Qui la vita non va poi così male, te lo dico io. Ma ce la dobbiamo sudare ogni giorno, e stare dietro alle sue pretese... Quanto alla signora, è partita per Espanola, vuole valutare se convenga trasferirci tutti a Port-au-Prince – in fondo è lì che si incrociano più rotte, e il nostro commercio non resterà fermo a marcire o a subire perdite continue, almeno.";
			link.l1 = "Ah davvero? E non era forse Levasseur a mettere i denari qui per mantenere la sua lurida stabilità?";
			link.l1.go = "PZ_ElitaShluha_14";
		break;
		
		case "PZ_ElitaShluha_14":
			dialog.text = "Non troppo. È venuto da noi dicendo che avrebbe investito sul serio solo se fossimo andati ogni tanto a casa sua. Ma la signora ha rifiutato di brutto. Così tanto che Sua Grazia è rimasto spiazzato per un attimo. Non li ho mai visti così, né lei né lui.";
			link.l1 = "Heh-heh, guarda un po'. Sembra che sappia... Coraggiosa, davvero coraggiosa da parte sua.";
			link.l1.go = "PZ_ElitaShluha_15";
		break;
		
		case "PZ_ElitaShluha_15":
			dialog.text = "Sai una cosa? Visto che ci intendiamo così bene, ti confido un'altra cosa... ma è un gran segreto, quindi non ne parlare con nessuno, giusto?";
			link.l1 = "Oh no, mademoiselle. Vi assicuro, non ho alcuna intenzione di nuocere alla vostra signora. Vi prego, proseguite pure.";
			link.l1.go = "PZ_ElitaShluha_16";
		break;
		
		case "PZ_ElitaShluha_16":
			dialog.text = "Non so nemmeno se potresti ferirla, perché Belle Etoile si allena con la spada ogni giorno e non trova rivali degni in tutta la città. Oltre a Port-au-Prince, ha intenzione di chiedere soldi nientemeno che a Marcus Tyrex in persona! O meglio, di farsi prestare un po' d'oro da lui. Riesci a crederci?";
			link.l1 = "Sì, e sento che oggi avrò una conversazione molto difficile con un’altra donna che si esercita spesso con la spada... Beh, grazie per aver condiviso, mademoiselle. Buona giornata e che tu abbia clienti generosi.";
			link.l1.go = "PZ_ElitaShluha_17";
		break;
		
		case "PZ_ElitaShluha_17":
			dialog.text = "Grazie.   Ma perché tutta questa fretta? Hai già pagato tutto, e non ci siamo nemmeno intrattenuti così a lungo.   E poi, c'è qualcosa di raffinato in te, monsieur. Qualcosa di molto più raro dei soliti ricconi che passano di qui.   Allora, vogliamo davvero godere della reciproca compagnia?";
			link.l1 = "Sai... ma al diavolo tutto, giusto? Perché dovrei fingere e raccontarmi bugie come se non lo volessi davvero? Un'occasione con una donna come te non capita quasi mai.";
			link.l1.go = "PZ_ElitaShluha_YesSex";
			link.l2 = "Oh, mi rincresce dover dire di no, mademoiselle. Sono venuto qui solo per parlare. Inoltre... c’è già qualcuno che mi aspetta.";
			link.l2.go = "PZ_ElitaShluha_NoSex";
		break;
		
		case "PZ_ElitaShluha_NoSex":
			dialog.text = "Come se mai avesse fermato qualcuno. In tal caso, meriti rispetto, monsieur. Sono davvero felice per il tuo 'qualcuno'.";
			link.l1 = "Grazie ancora, signorina. Addio.";
			link.l1.go = "PZ_ElitaShluha_NoSex_2";
		break;
		
		case "PZ_ElitaShluha_NoSex_2":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_ElitaShluha_YesSex":
			dialog.text = "Grazie. Che ne dici di un bel bagno caldo insieme, per cominciare?";
			link.l1 = "Tutte e due le mani a favore.";
			link.l1.go = "PZ_ElitaShluha_YesSex_2";
		break;
		
		case "PZ_ElitaShluha_YesSex_2":
			DialogExit();
			LAi_SetStayType(pchar);
			DoQuestCheckDelay("PlaySex_1", 1.0);
			DoQuestCheckDelay("PZ_ElitaShluha_Fuck", 1.0);
		break;
		
		case "PZ_ElitaShluha_After":
			dialog.text = "È stata un’esperienza magica, monsieur. Non pensavo che un uomo potesse sorprendermi così. Sai proprio come far godere una donna...";
			link.l1 = " Dipende dalla donna. ";
			link.l1.go = "PZ_ElitaShluha_After_2";
		break;
		
		case "PZ_ElitaShluha_After_2":
			dialog.text = "Te ne penti?";
			link.l1 = "In questo momento, di certo no. Addio, mademoiselle.";
			link.l1.go = "PZ_ElitaShluha_After_3";
		break;
		
		case "PZ_ElitaShluha_After_3":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			LAi_SetPlayerType(pchar);
			pchar.questTemp.PZ.EliteWhoreFucked = true; // флаг того, что секс был (понадобится для диалога с Тираксом)
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_KlemanLebren_1":
			dialog.text = "Guarda dove metti i piedi, pagliaccio!";
			link.l1 = "Attento a come parli!";
			link.l1.go = "PZ_KlemanLebren_2";
		break;
		
		case "PZ_KlemanLebren_2":
			dialog.text = "Stavo attenta a dove mettevo i piedi mentre tu contavi le nuvole.";
			link.l1 = "Potevi benissimo aggirare se solo avessi guardato, giusto?";
			link.l1.go = "PZ_KlemanLebren_3";
		break;
		
		case "PZ_KlemanLebren_3":
			dialog.text = "Perché dovrei girarti intorno?!";
			link.l1 = "Propongo di scoprirlo fuori dalla città, chi deve cosa e a chi.";
			link.l1.go = "PZ_KlemanLebren_4";
		break;
		
		case "PZ_KlemanLebren_4":
			dialog.text = "Mm-mm, no. Non sapevo che la Vostra Signoria si disgustasse così tanto dal tocco accidentale di un semplice uomo.";
			link.l1 = "Come, scusa?";
			link.l1.go = "PZ_KlemanLebren_5";
		break;
		
		case "PZ_KlemanLebren_5":
			dialog.text = "Hmm, scusatemi. Non volevo insistere su di voi.";
			link.l1 = "Così va meglio.";
			link.l1.go = "PZ_KlemanLebren_6";
		break;
		
		case "PZ_KlemanLebren_6":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "", "", "", "", -1);
			npchar.location = "None";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				DelLandQuestMark(sld);
				if (CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
				{
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
				}
				else
				{
					ChangeCharacterAddressGroup(sld, "Tortuga_town", "rld", "loc0");
					sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
					sld.dialog.currentnode = "PZ_MaryRazgovorOBordeli_Bad_1";
					LAi_SetStayType(sld);
					CharacterTurnToLoc(sld, "quest", "quest1");
					sld.talker = 5;
					chrDisableReloadToLocation = true;
					LAi_LocationFightDisable(loadedLocation, true);
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				DelLandQuestMark(sld);
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_1":
			dialog.text = "Se fossi arrivato mezz'ora più tardi, Charles, avrei già fatto piovere le nostre palle di cannone su questo lurido covo, giusto! Hai trovato quello che cercavi? È lei, la sorella di Longway? L'hai vista?";
			link.l1 = "Shh, Mary, non dire certe cose. No, non ho avuto modo di incontrare Chang Xing...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_2";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_2":
			dialog.text = "E allora che diavolo ti ha fatto tardare così tanto?! Che ci facevi laggiù?";
			link.l1 = "Non hai nulla da temere. Appena ho scoperto tutto quel che potevo, ho lasciato quel posto, proprio come ti avevo promesso.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_3":
			dialog.text = "Sputa il rospo, giusto!";
			link.l1 = "Il proprietario al momento non si trova a Tortuga. Qui la richiesta dei suoi servigi è bassa, poiché assume signore ben istruite in abiti costosi, e accettano solo oro come pagamento...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_4":
			dialog.text = "Li hai pagati anche tu?!";
			link.l1 = "Altrimenti non avrebbero nemmeno sprecato una parola con me. Con un modo di fare simile, non c’è da stupirsi se la clientela scarseggia. La padrona ha deciso di spostare i suoi affari a Port-au-Prince, sperando di attirare una clientela più ricca. Ma di soldi ne ha pochi, si vede subito: si è rivolta a quel Marcus Tyrex per un prestito...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_5":
			dialog.text = "La conosce?";
			link.l1 = "Lo scopriremo quando saremo a La Vega. E se ci muoviamo e la smettiamo con queste chiacchiere inutili, beccheremo questa donna d'Oriente, chiunque sia.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_6":
			dialog.text = "Non era necessario andare in quel bordello, Charles. Sono sicura che avremmo potuto scoprire tutto questo nella taverna o per strada, se ci fossimo impegnati abbastanza, giusto.";
			link.l1 = "La prossima volta ti porto con me, così non ti riempi quella bella testolina rossa di sciocchezze, eh? Ora, occupiamoci delle cose serie.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_1":
			dialog.text = "Oh, vedo che sono un po' in ritardo, giusto! Beh, aspetta un attimo, mascalzone...";
			link.l1 = "Mary, che diavolo ci fai qui?! Ti avevo detto di restare sulla barca!";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_2":
			dialog.text = "Quindi non ti avrei mai impedito di divertirti con le puttane?! Non provare nemmeno a negarlo, Charles! L'equipaggio ti ha visto là, giusto! Come hai potuto?!";
			link.l1 = "Proprio come pensavo. Forse avrei dovuto portarli con me, così avrebbero visto cosa stavo facendo – o meglio, cosa non stavo facendo – e non avrebbero fatto tanto rumore per nulla...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_3":
			dialog.text = "Accusi i nostri ragazzi di mentire? Dopo quello che hai combinato tu stesso, brutto bastardo?";
			link.l1 = "Li accuso solo d'una stupidità senza pari. Senza capire la situazione, loro...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_4":
			dialog.text = "Oh-oh, Charles, non credo proprio che a te e alle tue puttane sarebbe piaciuto il modo in cui avrei sistemato la faccenda, se fossi arrivata in tempo a quella tana. Ma ti è andata bene – ho dovuto remare questa maledetta barca tutta da sola...";
			link.l1 = "Dicono che il duro lavoro fisico scacci i pensieri inutili dalla testa. Ma tu ne hai ancora troppi, quindi remi pure tu al ritorno.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_5":
			dialog.text = "Non mi muovo, giusto!";
			link.l1 = "Mary, non intendo discutere di questo qui davanti agli uomini di Levasseur. Calmati, guardati intorno e valuta la situazione. Non è né il momento né il posto, giusto?";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_6":
			dialog.text = "Al diavolo te. Ho ancora la mia roba in cabina... Ma non credere che prenderò ancora i remi in mano, giusto! Un po' di nobiltà ti sarà pure rimasta!";
			link.l1 = "Sono una canaglia e un bruto, ricordi? Lo dimostrerò sulla nave, ma prima ci devo arrivare. Quindi le tue suppliche sono vane.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "rld", "loc1", "OpenTheDoors", -1);
			
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_8":
			dialog.text = "Tutta la ciurma ride di te, giusto!";
			link.l1 = "Beh, forse anche tu hai attirato qualche sguardo. Non vedevano un simile spettacolo da parecchio tempo. Ora che ti sei un po’ calmato, lascia che ti racconti cos’è successo.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_9";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_9":
			dialog.text = "Charles, ormai ho sentito tutto. Voglio solo sapere una cosa: non ero abbastanza per te? Cosa ti manca con me?";
			link.l1 = "È scortese, ma risponderò con una domanda: ti ho mai dato una vera ragione per non fidarti di me? Eh? Non mi pare proprio. Quindi respira e ascoltami. Su Joep van der Vink non ho scoperto molto, solo che era stato in un bordello. Non quello vicino alla 'Cornacchia Canterina', ma un altro vicino al molo. Non lo conoscevo prima... a differenza, pare, dei nostri marinai, che invece ti hanno informato subito. Anche se a loro non sarebbe stato permesso andarci...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_10";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_10":
			dialog.text = "Che razza di bordello non fa entrare i marinai, giusto?";
			link.l1 = "Un bordello dove lavorano dame vestite di seta che hanno più del semplice vento in testa. E i loro servigi si pagano solo in dobloni d’oro. Non è capriccio di qualcuno qualunque, ma ordine della loro enigmatica padrona, Belle Etoile.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_11";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_11":
			dialog.text = "Misterioso, giusto.";
			link.l1 = "Non è solo questo. Lei è asiatica.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_12";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_12":
			dialog.text = "Asiatica? La maitresse del bordello a Tortuga?";
			link.l1 = "Potrebbe essere Chang Xing. Ecco perché ci sono andato – volevo vedere lei coi miei occhi. Tutto qui.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_13";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_13":
			dialog.text = "Com’è fatta lei?";
			link.l1 = "Non ne ho la minima idea. Lei non c’era, così mi sono ritrovato a conversare con un’altra... stella.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_14";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_14":
			dialog.text = "Anche lei era asiatica, giusto?";
			link.l1 = "No, era bianca. Mi ha detto che Belle Etoile non va tanto bene ultimamente, così ha deciso di trasferirsi a Port-au-Prince. Ha senso, lì la gente ha più soldi. La padrona deve essere a corto di denaro se ha bisogno di un prestito per aprire un commercio a Espanola, che vuole prendere da Tyrex. Quindi, se ci sbrighiamo verso La Vega, possiamo intercettarla prima che Marcus la trovi.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_15";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_15":
			dialog.text = "Me ne frego di lei, di Marcus o di chiunque altro, giusto. Charles, dimmi solo una cosa: sei mai stato con qualcuna delle ragazze del suo bordello?";
			link.l1 = "Non mi serve nient’altro, Mary. Ho già te, la ragazza migliore del mondo. Non capisco perché non lo vedi, giusto?";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_16";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_16":
			dialog.text = "In realtà è facilissimo scoprire la verità, giusto, ehehe. Se non sei stato con nessuno, adesso devi avere un sacco di energia. Ed è proprio quello che andremo a verificare ora, giusto!";
			link.l1 = "Mary, per favore...";
			link.l1.go = "exit";
			AddDialogExitQuest("cabin_sex_go");
			pchar.questTemp.PZ_MaryRazgovorOBordeli = true;
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_17":
			DeleteAttribute(pchar, "questTemp.PZ_MaryRazgovorOBordeli");
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				if (IsCharacterPerkOn(pchar, "Medic"))
				{
					notification("Excellent Health", "Medic");
					dialog.text = "(Eccellente salute) Ugh... Pare che non mentivi, Charles, giusto...";
					link.l1 = "Non ho alcun motivo per ingannarti, mio caro...";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
				}
				else
				{
					notification("Perk check failed", "Medic");
					dialog.text = "Charles, ma... sei davvero serio?! Che diavolo era quello?";
					link.l1 = "Oh, questo caldo mi sta facendo a pezzi. Ehm.";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_19";
				}
			}
			else
			{
				dialog.text = "Ugh... Sembra proprio che non mentivi, Charles, giusto...";
				link.l1 = "Non ho alcun motivo di ingannarti, mio caro...";
				link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_18":
			dialog.text = "Ma quella traversata in scialuppa non la dimenticherò tanto presto!";
			link.l1 = "Ah!";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_19":
			dialog.text = "Non ti sei mai lamentato prima d’ora, giusto?";
			link.l1 = "Prova tu a scorrazzare per quest'isola maledetta...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_20";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_20":
			dialog.text = "E i bordelli, giusto! Hai davvero...";
			link.l1 = "Mary, mi dispiace.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_21";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_21":
			dialog.text = "Cosa?! Allora tu sei...";
			link.l1 = "Non me ne pento, affatto. Merda. Voglio dire, non c'era nessuno tranne te, te l'ho detto. Non riuscivo solo... a trovare pace nella testa, tutto qui. Non è facile, sai, con i cannoni di La Roche puntati addosso.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_22";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_22":
			dialog.text = "È una bella scusa, Charles. Va bene, ti credo. Stavolta... Ma sappi che sono ancora arrabbiata con te, giusto!";
			link.l1 = "Mi guadagnerò il tuo perdono, lo prometto.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_1":
			dialog.text = "Allora, stallone, cosa hai scoperto? Ne valeva la pena rischiare il mio favore, giusto?";
			link.l1 = "Non riesco proprio a capire se stai scherzando o fai sul serio. Ma alla fine è servito – anche se non ho visto la padrona con i miei occhi. È asiatica e si fa chiamare Belle Etoile – una stella meravigliosa. Non è certo il suo vero nome, ovviamente...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_2":
			dialog.text = "E per questo, dovevi proprio andare in un bordello? Non potevi scoprirlo in una locanda? Ш: In città di questa tana non si parla mai. Perché? Bella domanda. Chiedilo alla stessa Belle Etoile — è già partita per l’Espanola.";
			link.l1 = "Non ne parlano mai davvero in città, di questo posto. Perché? Domanda interessante. Chiedilo pure a Belle Etoile in persona – è corsa via a Espanola.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_3":
			dialog.text = "Tortuga non le bastava?";
			link.l1 = "Qui il commercio pare vada male. Non si serve di comuni ragazze di porto, ma di dame ben vestite e istruite.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_4":
			dialog.text = "E per quale motivo dovrebbero farlo?";
			link.l1 = "Questa è un’altra bella domanda. In ogni caso, il nostro uccellino ha deciso di spiccare il volo verso Port-au-Prince, feudo di de Mussac. Ma il prestito per questa impresa doveva venire nientemeno che da Tyrex.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_5":
			dialog.text = "Voglio che questa storia finisca in fretta. Non perdiamo tempo e mettiamo subito la prua verso La Vega.";
			link.l1 = "Ecco cosa faremo.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_1":
			dialog.text = "Sei un uomo coraggioso, Charles, questo te lo riconosco. Ti presenti così, con la faccia tosta e l’aria innocente, come se nulla fosse successo.";
			link.l1 = "Immagino che uno dei marinai abbia spifferato, eh? E senza nessun contesto, ovviamente. Perché non è successo davvero nulla... almeno non quello che pensi tu.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_2":
			dialog.text = "Sono contenta che tu non l'abbia negato, Charles.";
			link.l1 = "Stavo per raccontarti tutto, Helen.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_3":
			dialog.text = "Non farlo, Charles. I dettagli non mi importano molto. Ma le ragioni sì. Dimmi, c’è qualcosa che non va in me?";
			link.l1 = "Iniziamo dalle ragioni. Ho scoperto che a Tortuga ci sono due bordelli. Uno è ben conosciuto. Dell’altro... la gente sa, ma pochi vogliono parlarne. Appartiene a una donna d’Asia...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_4":
			dialog.text = "Te lo stai inventando strada facendo, giusto?";
			link.l1 = "Perché diavolo dovrei farlo, Helen?! Se non mi credi, te lo confermeranno laggiù, giusto?";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_5":
			dialog.text = "Primo, mi hai detto di non mettere piede a terra, quindi non ci posso proprio andare. Secondo, chi diavolo credi che io sia?! Non mi avvicinerò mai a un posto simile! Terzo... vai avanti, su.";
			link.l1 = "Bene. Ho deciso di andare là solo per vedere Madame Étoile coi miei occhi. Era la mia unica intenzione, maledizione!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_6":
			dialog.text = "Suppongo di sì. L’hai incontrata?";
			link.l1 = "No. Se n'è andata a Española. Qui le cose non le andavano bene, così ha deciso di tentare la fortuna a Port-au-Prince. Là, le sue signore vestite di seta e istruite possono portarle più guadagno che a Tortuga...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_7":
			dialog.text = "Vestito bene e istruito? Ehi, guarda cosa può riservarti la vita. Però dovresti apprezzarli per come sono, giusto?";
			link.l1 = "Helen, basta così. Non ho fatto nulla per meritare la tua diffidenza.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_8";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_8":
			dialog.text = "Vero. Se avessi cercato di ingannarmi, non saresti così tranquillo. Ma avresti dovuto avvertirmi dei tuoi piani, Charles.";
			link.l1 = "Hai ragione, tesoro. Ma ho pensato di risparmiare un po' di tempo. Ho sbagliato, giusto?";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_9";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_9":
			dialog.text = "D'accordo. E adesso? Tracciamo una rotta per Port-au-Prince?";
			link.l1 = "La Vega. Non sorprenderti, Helen. Madame Belle Etoile non se la passa bene. Aveva bisogno di un prestito per trasferire il suo commercio a Port-au-Prince, così ha deciso di farselo dare da Marcus. Se ci sbrighiamo, possiamo ancora trovarla lì. Quindi non perdiamo tempo.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_NaLaVega":
			DialogExit();
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) 
			{
				AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
				QuestSetCurrentNode("Terrax", "PZ1");
			}
			else 
			{
				AddLandQuestMark(characterFromId("Vensan"), "questmarkmain");
				QuestSetCurrentNode("Vensan", "PZ1");
			}
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			Island_SetReloadEnableGlobal("Tortuga", true);
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				AddPassenger(pchar, sld, false);
				Return_MaryOfficer();
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				AddPassenger(pchar, sld, false);
				Return_HelenaOfficer();
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku")) AddQuestRecord("PZ", "31");
		break;
		
		case "PZ_KlemanLebren_7":
			dialog.text = "Non posso credere che un bastardo come te e la tua marmaglia ci abbiate battuto!";
			link.l1 = "Tu...";
			link.l1.go = "PZ_KlemanLebren_8";
		break;
		
		case "PZ_KlemanLebren_8":
			dialog.text = "Oh, mi riconosci?";
			link.l1 = "Ci siamo già incontrati?";
			link.l1.go = "PZ_KlemanLebren_9";
		break;
		
		case "PZ_KlemanLebren_9":
			dialog.text = "Cosa?! Mi stai prendendo per il culo?!";
			link.l1 = "Non riesco a ricordare tutta la feccia selvaggia che incontro. Faresti meglio a dirci chi ti ha mandato a ucciderci. O forse volevano solo sbarazzarsi di te?";
			link.l1.go = "PZ_KlemanLebren_10";
		break;
		
		case "PZ_KlemanLebren_10":
			dialog.text = "Non dirò nulla a uno come te. Ti credi così dannatamente superiore! Vediamo se sarai ancora così sicuro dopo questa nostra piccola pausa.";
			link.l1 = "Peccato. Fai schifo, ma avrei potuto semplicemente scaricarti su un'altra isola. Ora tutto ciò che posso fare è mandarti dall'altra parte.";
			link.l1.go = "PZ_KlemanLebren_11";
		break;
		
		case "PZ_KlemanLebren_11":
			pchar.questTemp.PZ.HeavyFrigateAbordage = true; // флаг - абордаж был
			
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_Tichingitu_11":
			dialog.text = "Mi avete chiamato, Mio Signore Capitano?";
			link.l1 = "Sì, compare. Riporta i danni.";
			link.l1.go = "PZ_Tichingitu_12";
		break;
		
		case "PZ_Tichingitu_12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "There's a violent storm. The ship is creaking and cracking; it's wobbling badly.";
			link.l1 = "Sì, ho notato. Tichingitu, mio amico. Io e il "+sStr+" scenderò a terra. Tu rimani al comando. Inizia subito le riparazioni – finché la tempesta infuria, andare al cantiere non ha senso. E poi, non resteremo qui a lungo.";
			link.l1.go = "PZ_Tichingitu_13";
		break;
		
		case "PZ_Tichingitu_13":
			dialog.text = "Farò sembrare tutto più bello.";
			link.l1 = "Perfetto, grazie. Allora andiamo in città senza nessun pensiero, giusto?";
			link.l1.go = "PZ_Tichingitu_14";
		break;
		
		case "PZ_Tichingitu_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_Matros_1":
			dialog.text = "Monsieur le Capitaine? Un onore, davvero. Ma di solito in questi momenti chiamate Alonso. Va tutto bene, se posso permettermi?";
			link.l1 = "Sì, tutto a posto. Ma il nostro Alonso è bravo solo a sfasciare, non certo ad aggiustare. In tutti i sensi, mio Signore Capitano. Quanto è messa male la nave?";
			link.l1.go = "PZ_Matros_2";
		break;
		
		case "PZ_Matros_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Alonso direbbe che fa schifo, anche se non stiamo affondando. Hai parlato di riparazioni – cominciamo, giusto?";
			link.l1 = "Sì, fai quel che puoi. Ma non pensare di metterti comodo: presto molleremo gli ormeggi, appena avrò sbrigato i miei affari in città. Io e "+sStr+" Non ci sarò, quindi se succede qualcosa, prendi tu tutte le decisioni. Ascolta Alonso in ogni cosa.";
			link.l1.go = "PZ_Matros_3";
		break;
		
		case "PZ_Matros_3":
			dialog.text = "Come comanda, Mio Signore Capitano.";
			link.l1 = "A riposo.";
			link.l1.go = "PZ_Matros_4";
		break;
		
		case "PZ_Matros_4":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			bQuestDisableMapEnter = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_AnriTibo_1":
			dialog.text = "Salute, monsieur! Benvenuto a Port-au-Prince.";
			link.l1 = "E buon dì a voi, monsieur. Chi siete, e a quale vento devo questa accoglienza? Non posso dire d’aver voglia di far gran discorsi sotto questa pioggia, dopo un simile temporale.";
			link.l1.go = "PZ_AnriTibo_2";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_ChangShin", "Mei_Shin", "woman", "towngirl2", 30, FRANCE, 0, false, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_41", "", "", 0);
			sld.name = "Чанг";
			sld.lastname = "Шин";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto16");
			EquipCharacterByItem(sld, "blade_41");
			GiveItem2Character(sld, "cirass8");
			EquipCharacterByItem(sld, "cirass8");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload8_back", "none", "", "", "", -1);
		break;
		
		case "PZ_AnriTibo_2":
			dialog.text = "Oh, non vi ruberò troppo tempo, Monsieur de Maure.";
			link.l1 = "Ti conosco, per caso?";
			link.l1.go = "PZ_AnriTibo_3";
		break;
		
		case "PZ_AnriTibo_3":
			dialog.text = "Oh, no, ma tutto l’arcipelago sa chi siete. Ah, dove sono le mie buone maniere! Henri Thibaut, al vostro servizio. Sono il messo di Sua Signoria, Monsieur de Mussac. Appena ha avvistato la vostra nave, m’ha ordinato di darvi il più caloroso benvenuto possibile, monsieur.";
			link.l1 = "Beh, questo spiega molte cose. Lieto di conoscerla, Monsieur Thibaut.";
			link.l1.go = "PZ_AnriTibo_4";
		break;
		
		case "PZ_AnriTibo_4":
			dialog.text = "E il piacere è tutto mio, Monsieur de Maure! Vi prego, seguitemi. Non è degno che un uomo del vostro rango e la sua splendida compagna restino rinchiusi in questa taverna puzzolente. Sua Signoria vi ha assegnato una casa in città e m'ha ordinato d'assistervi in ogni modo possibile. Vi prego, non dimenticate di trasmettere i suoi più cordiali saluti a Sua Eccellenza Poincy in seguito.";
			link.l1 = "In realtà, il mio incarico è di quelli riservati. Sa, Monsieur Thibaut, credo che...";
			link.l1.go = "PZ_AnriTibo_5";
		break;
		
		case "PZ_AnriTibo_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_HelenaPortPax1", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_MaryPortPax1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_HelenaPortPax1":
			dialog.text = "Charles. Chiedo raramente qualcosa, e ancora meno di disturbarti, ma possiamo approfittare della loro offerta? Sono stufo di bagnarmi sotto la pioggia. Inoltre mi sento la testa che gira e la nausea.";
			link.l1 = "Heh-heh, sei proprio sicuro che sia solo la pioggia?";
			link.l1.go = "PZ_HelenaPortPax2";
		break;
		
		case "PZ_HelenaPortPax2":
			dialog.text = "Morditi la lingua, Charles! Comunque, voglio riposare. Su un bel letto grande, senza onde.";
			link.l1 = "D'accordo. Ci asciughiamo, ci riposiamo un momento, e poi torniamo subito agli affari, giusto?";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_MaryPortPax1":
			dialog.text = "Possiamo riposarci un po' in questa casa? Non mi sento bene, e sono anche... stanca, Charles. Giusto?";
			link.l1 = "Mary, cara, capisco, ma forse dovremmo andare in taverna. Qui c’è puzza di guai, giusto?";
			link.l1.go = "PZ_MaryPortPax2";
		break;
		
		case "PZ_MaryPortPax2":
			dialog.text = "Cosa potrebbe mai succedermi? Non siamo nemmeno a Tortuga.";
			link.l1 = "È proprio questo che mi fa tremare.";
			link.l1.go = "PZ_MaryPortPax3";
		break;
		
		case "PZ_MaryPortPax3":
			dialog.text = "Per favore? Se proprio, monterò una difesa nella stanza — proprio come... quella volta, giusto. Tu mi conosci meglio di chiunque altro, Charles, quindi sai che so cavarmela.";
			link.l1 = "Va bene, va bene. Speriamo che questa volta non vada come allora, giusto?";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_AnriTibo_6":
			StartInstantDialog("Tibo", "PZ_AnriTibo_7", "Quest\CompanionQuests\Longway.c");
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		break;
		
		case "PZ_AnriTibo_7":
			dialog.text = "Sapevo che avrebbe cambiato idea, monsieur! Per quanto riguarda le sue preoccupazioni, capisco benissimo. Ma, vede, Sua Eccellenza Poincy e il governatore sono vecchi amici, quindi lei è un ospite gradito nella nostra città, Monsieur de Maure!";
			link.l1 = "Oh, bene... Allora, portaci pure alla casa, dunque.";
			link.l1.go = "PZ_AnriTibo_8";
		break;
		
		case "PZ_AnriTibo_8":
			dialog.text = "Certamente, monsieur! Seguitemi, per favore.";
			link.l1 = "Grazie.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_GoToTiboHouse");
		break;
		
		case "PZ_AnriTibo_9":
			dialog.text = "Monsieur, il governatore vi attende. Ha chiesto che vi rechiate da lui appena possibile – desidera parlarvi in privato.";
			link.l1 = "Lo sa già, giusto?";
			link.l1.go = "PZ_AnriTibo_10";
		break;
		
		case "PZ_AnriTibo_10":
			pchar.questTemp.PZ.PortPaxMayorTalk = true; // флаг для разговора с губернатором
			
			dialog.text = "Certo che lo sa! Ecco perché ti sta aspettando. Lascia che la tua amata dorma dolcemente mentre tu vai a trovare monsieur de Mussac. Una tempesta non fermerà il famoso Charles de Maure, vero? Ma Sua Signoria, come capirai, non ha molto tempo da perdere tra un appuntamento e l'altro...";
			link.l1 = "Beh, è vero, Monsieur Thibaut.";
			link.l1.go = "PZ_AnriTibo_11";
			
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_Escort_"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
		break;
		
		case "PZ_AnriTibo_11":
			StartInstantDialog("PZ_PoP_Escort_1", "PZ_AnriTibo_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_AnriTibo_12":
			dialog.text = "Vi mostreremo la via, Capitano.";
			link.l1 = "Oh, dunque ho persino una scorta d’onore... Allora, mostrami la via.";
			link.l1.go = "PZ_AnriTibo_13";
		break;
		
		case "PZ_AnriTibo_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "PZ_PoP_EscortToGuber");
		break;
		
		case "PZ_Longway_71":
			dialog.text = "Mio Signore Capitano!";
			link.l1 = "Longway! Alla nave! Adesso!";
			link.l1.go = "PZ_Longway_72";
		break;
		
		case "PZ_Longway_72":
			dialog.text = "Ma io ho visto Chang Xing!";
			link.l1 = "Cosa?! Dove? Quando? È sulla vostra nave?";
			link.l1.go = "PZ_Longway_73";
		break;
		
		case "PZ_Longway_73":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "No! Qui in città, Longway l'ha vista da lontano. Non c'era tempo per raggiungerla – stava salendo su un galeone che è appena salpato!";
			link.l1 = "Raggiungeremo il galeone! Ma dimmi – hai visto "+sStr+"   da qualche parte?";
			link.l1.go = "PZ_Longway_74";
		break;
		
		case "PZ_Longway_74":
			dialog.text = "No! È successo qualcosa?";
			link.l1 = "Sì, qualcosa è successo! Lei è in pericolo! Hai visto il nipote di Levasseur? Si chiama Henri Thibaut! Un tipo sgradevole, magro, con i capelli lunghi e un baffetto ridicolo!";
			link.l1.go = "PZ_Longway_75";
		break;
		
		case "PZ_Longway_75":
			dialog.text = "(in Mandarino) Non serve parlare di baffi buffi, Mio Signore Capitano... (in francese stentato) L'ho visto! Lui e quei mercenari sono saliti pure loro su quella stessa galeone.";
			link.l1 = "Inseguiamolo subito!";
			link.l1.go = "PZ_Longway_76";
		break;
		
		case "PZ_Longway_76":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "La vostra nave cade a pezzi, Mio Signore Capitano!";
			link.l1 = "Non me ne importa un accidente! "+sStr+"La vita di [[[VAR1]]] è appesa a un filo!";
			link.l1.go = "PZ_Longway_77";
		break;
		
		case "PZ_Longway_77":
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang"))
			{
				dialog.text = "La... 'Tua Meifeng' ci farà strada!";
				link.l1 = "Oh, lo farà! Sbrigati!";
				link.l1.go = "PZ_Longway_78";
			}
			else
			{
				dialog.text = "Non ci gettare in un assalto suicida. Usa la nave che mi hai fornito prima, Mio Signore Capitano!";
				link.l1 = "Buona idea, Longway! Sbrighiamoci!";
				link.l1.go = "PZ_Longway_78";
			}
		break;
		
		case "PZ_Longway_78":
			DialogExit();
			chrDisableReloadToLocation = false;
			Island_SetReloadEnableGlobal("Hispaniola2", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			pchar.GenQuest.AbordageInStorm = true;	//Разрешить абордаж во время шторма
			SetLocationCapturedState("PortPax_town", false);

			LAi_LoginInCaptureTown(npchar, false);
			AddPassenger(pchar, npchar, false);
			Return_LongwayOfficer();
			
			if (GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				AddPassenger(pchar, sld, false);
				Return_TichingituOfficer();
			}
			
			PChar.quest.PZ_PoP_Pogonya.win_condition.l1 = "location";
			PChar.quest.PZ_PoP_Pogonya.win_condition.l1.location = "Hispaniola2";
			PChar.quest.PZ_PoP_Pogonya.win_condition = "PZ_PoP_Pogonya";
			
			SeaAI_SwapShipsAttributes(pchar, CharacterFromID("PZ_ShipStasis"));
			AddCharacterGoodsSimple(pchar, GOOD_GRAPES, 300);
			AddCharacterGoodsSimple(pchar, GOOD_BOMBS, 200);
			AddCharacterGoodsSimple(pchar, GOOD_POWDER, 350);
			AddCharacterGoodsSimple(pchar, GOOD_FOOD, 150);
			AddCharacterGoodsSimple(pchar, GOOD_RUM, 50);
			AddCharacterGoodsSimple(pchar, GOOD_FOOD, 700);
			SetCrewQuantityFull(pchar);
			pchar.ship.HP = sti(pchar.ship.HP) / 2;
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) / 2;
			AddCrewMorale(Pchar, 100);
			ChangeCrewExp(pchar, "Sailors", 100);
			ChangeCrewExp(pchar, "Cannoners", 100);
			ChangeCrewExp(pchar, "Soldiers", 100);
			
			//Вражина
			sld = characterFromId("PZ_RobertMartin");
			sld.nation = PIRATE;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				GiveItem2Character(sld, "blade_31");
				EquipCharacterByItem(sld, "blade_31");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				GiveItem2Character(sld, "pirate_cutlass");
				EquipCharacterByItem(sld, "pirate_cutlass");
			}
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS16, 50, 50, 50);
			sld.AlwaysEnemy = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			sld.ShipHideImmortal = 800;
			Group_FindOrCreateGroup("PZ_RM_Attack");
			Group_SetType("PZ_RM_Attack", "pirate");
			Group_AddCharacter("PZ_RM_Attack", "PZ_RobertMartin");
			Group_SetGroupCommander("PZ_RM_Attack", "PZ_RobertMartin");
			Group_SetTaskAttack("PZ_RM_Attack", PLAYER_GROUP);
			Group_SetAddress("PZ_RM_Attack", "Hispaniola2", "quest_ships", "Quest_ship_1");
			Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), sti(pchar.index));
		break;
		
		case "PZ_RobertMartin_8":
			dialog.text = "Ancora tu... Lo sapevo che dovevo rifiutare e lasciare che qualcun altro si occupasse della tua donna.";
			link.l1 = "Dove sta lei?! Dimmi subito! No... Taci la bocca. Parlerai solo nella stiva, in catene! Mi senti?!";
			link.l1.go = "PZ_RobertMartin_9";
		break;
		
		case "PZ_RobertMartin_9":
			dialog.text = "...";
			link.l1 = "La sua lama. Se non cominci a cantare subito, ti faccio a pezzi con quella.";
			link.l1.go = "PZ_RobertMartin_10";
			/*RemoveAllCharacterItems(npchar, true);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) GiveItem2Character(pchar, "blade_31");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) GiveItem2Character(pchar, "pirate_cutlass");*/
		break;
		
		case "PZ_RobertMartin_10":
			dialog.text = "Tu... sei completamente fuori di testa, maledizione!..";
			link.l1 = "Ora vedrai il mio lato più sgradevole...";
			link.l1.go = "PZ_RobertMartin_11";
		break;
		
		case "PZ_RobertMartin_11":
			DialogExit();
			LAi_ReloadBoarding();
		break;
		
		case "PZ_RobertMartin_13":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Tutto qui?";
			link.l1 = "Te lo domando ancora! Dov’è "+sStr+"?! Dov’è la donna cinese?! Dov’è Henri Thibaut?!";
			link.l1.go = "PZ_RobertMartin_14";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_14":
			dialog.text = "(sputa sangue) Colpisci come una donzella.";
			link.l1 = "Brutta sgualdrina! Ti farò sputare ogni parola a calci e pugni!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_16":
			dialog.text = "Patetico. Anche se... lo dico. Perché no, ah ah. Sono tutti sull’altra nave, proprio sulla rotta per Tortuga. Sei arrivato troppo tardi.";
			link.l1 = "Se anche solo un capello dovesse cadere dalla sua testa...";
			link.l1.go = "PZ_RobertMartin_17";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_2", "", 0.3);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 1.00, 5.13, 7.23);
		break;
		
		case "PZ_RobertMartin_17":
			dialog.text = "E di chi sarebbe la colpa, eh?! Hai ucciso Edgardo Sotta! Per la prima volta in vita sua, Levasseur voleva assaggiare una ragazza e non l’ha avuta subito! Prima volta che la nostra ciurma ha mancato un suo ordine diretto! Quell’uomo può far paura quanto il diavolo...";
			link.l1 = "Allora sarò più spaventoso del diavolo in persona e ti farò vivere un inferno tutto tuo se non mi dici quello che voglio sapere, mi senti?!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) link.l1.go = "PZ_RobertMartin_Mary_1";
			else link.l1.go = "PZ_RobertMartin_Helena_1";
			//if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) link.l1.go = "PZ_RobertMartin_Helena_1";
		break;
		
		case "PZ_RobertMartin_Mary_1":
			dialog.text = "Non me ne frega niente delle tue disgrazie – tanto sono già condannato, basta guardare quegli occhi da pazzo che ti ritrovi. Però, ti riconosco un certo coraggio, de Maure.";
			link.l1 = "Che diavolo stai blaterando?";
			link.l1.go = "PZ_RobertMartin_Mary_2";
		break;
		
		case "PZ_RobertMartin_Mary_2":
			dialog.text = "Levasseur preferisce le bionde. Ma io ho sempre avuto un debole per le rosse, proprio come te, eh eh eh... Che peperina che sei!";
			link.l1 = "Hai ragione, non vedrai la fine di questa giornata...";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_Helena_1":
			dialog.text = "Non me ne frega un accidente di quello che vuoi tu. Ma lascia che ti dica cosa vuole Levasseur: belle ragazze bionde, ah ah ah ah ah ah ah ah ah! Prima di tutto, ha preso lei...";
			link.l1 = "A-AH!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_19":
			dialog.text = "Frignare e pestare un uomo disarmato – che miseria. Questo è tutto ciò che sai fare. Hai perso, de Maure! Vuoi sapere quando hai perso davvero, povero idiota?";
			link.l1 = "Istruiscimi. Ma se non mi stupisci, perderai un dito. O un orecchio. O quei denti marci dalla tua bocca puzzolente. O magari qualcos’altro. La scelta è tua...";
			link.l1.go = "PZ_RobertMartin_20";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_3", "", 0.3);
			//locCameraFromToPos(-1.75, 14.14, -0.31, true, 1.26, 11.00, -4.00);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 0.66, 5.00, 8.26);
		break;
		
		case "PZ_RobertMartin_20":
			dialog.text = "Heh-heh, io ho qualcosa che tu non hai. Pensi forse che Levasseur non sapesse cosa tramava quel vecchio volpone di Poincy contro di lui? François sa tutto, tutto! Persino i baroni della Confraternita non osano sfidarlo. E tu, furbetto, l’hai fatto. Ma...";
			link.l1 = "Ma che diavolo?! Non ti azzardare a tirarla per le lunghe, maledetto! Parla subito, o ti spacco le dita una ad una!";
			link.l1.go = "PZ_RobertMartin_21";
		break;
		
		case "PZ_RobertMartin_21":
			dialog.text = "Ahah, coraggioso Capitano de Maure! Ma va bene. Io, Henri e la donna dalla pelle gialla abbiamo deciso che era meglio farvi fuori qui. E dare la colpa a Tyrex, così quei vecchi babbei della Confraternita si scannano tra loro! Oppure a de Mussac – ha ficcato il naso dove non doveva... Lo sai, tutti ridevano di me perché comandavo un galeone, ma lui ha affrontato la tempesta senza battere ciglio, altro che la tua carretta.";
			link.l1 = "Basta! Dove Levasseur nasconde le sue vittime?";
			link.l1.go = "PZ_RobertMartin_22";
		break;
		
		case "PZ_RobertMartin_22":
			dialog.text = "Allora conosci il suo luogo segreto, la prigione sotterranea? Oh sì, lui è il vero signore delle segrete, ah-ah-ah! Ma pensi davvero di poterlo sfidare? Ne dubito. Vuoi abbattere la bestia? Allora diventa tu stesso la bestia. Vediamo se riesci a spezzarmi come François spezza quelle ragazze. Come presto spezzerà la tua...";
			/*if (!CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "Alo-o-on-s-o-o!!!";
				link.l1.go = "PZ_RobertMartin_23";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "PZ_LongwayKaznDialog_1";
			}*/
			link.l1 = "Alo-o-on-s-o-o!!!";
			link.l1.go = "PZ_RobertMartin_23";
		break;
		
		case "PZ_RobertMartin_23":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_Fade("PZ_AlonsoKazn", "");
		break;
		
		case "PZ_LongwayKaznDialog_1":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			DoQuestCheckDelay("PZ_LongwayKazn_1", 1.0);
		break;
		
		case "PZ_LongwayKaznDialog_2":
			dialog.text = "";
			link.l1 = "Ti avevo detto di lasciar perdere, accidenti!..";
			link.l1.go = "PZ_LongwayKaznDialog_3";
		break;
		
		case "PZ_LongwayKaznDialog_3":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_LongwayKazn_3", "");
		break;
		
		case "PZ_LongwayKaznDialog_4":
			dialog.text = "Permettetemi, Mio Signore Capitano.";
			link.l1 = "Longway? Permettere cosa?";
			link.l1.go = "PZ_LongwayKaznDialog_5";
		break;
		
		case "PZ_LongwayKaznDialog_5":
			dialog.text = "Gli uomini bianchi torturano la carne. La mia gente sa che bisogna prima infierire sull’anima misera, farla impazzire con un dolore sottile e costante. Non puoi semplicemente prendere e straziare senza preparazione. Serve sempre un tocco particolare. Qui serve... uno come Lynchy.";
			link.l1 = "Lynchy?";
			link.l1.go = "PZ_LongwayKaznDialog_6";
		break;
		
		case "PZ_LongwayKaznDialog_6":
			dialog.text = "Sì, Mio Signore Capitano. Morte per mille tagli.";
			link.l1 = "Sei impazzito?! Ti sei rotto la testa? Di che morte vai farneticando?! Prima devo farlo parlare!";
			link.l1.go = "PZ_LongwayKaznDialog_7";
		break;
		
		case "PZ_LongwayKaznDialog_7":
			dialog.text = "Longway sa, Mio Signore Capitano. Sa cosa deve fare. Questo bastardo mi dirà tutto. Dammi tempo...";
			link.l1 = "Tempo? Tempo?! Va bene... Fallo. Ti prego soltanto, ti supplico, strappagli tutto, ogni cosa!";
			link.l1.go = "PZ_LongwayKaznDialog_8";
		break;
		
		case "PZ_LongwayKaznDialog_8":
			DialogExit();
			LAi_SetActorType(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_LongwayKazn_4", 1.5);
		break;
		
		case "PZ_LongwayKaznDialog_9":
			dialog.text = "Uccidimi, ti prego... Uccidimi! Che altro vuoi ancora da me?!";
			link.l1 = "Nient’altro. Chiudi quella bocca e crepa.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayKazn_11");
		break;//
		
		case "PZ_LongwayKaznDialog_9_1":
			DialogExit();
			sld = CharacterFromID("PZ_RobertMartinPlennik")
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_11":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Colpo pulito, Mio Signore Capitano. Avevo detto che avrebbe funzionato.";
			link.l1 = "Già. Bel lavoro. Allora, verso la segreta. Su tutte le vele! Rotta su Tortuga. E che Dio abbia pietà di questa maledetta città se solo un capello cade da "+sStr+" testa...";
			link.l1.go = "PZ_LongwayKaznDialog_12";
		break;
		
		case "PZ_LongwayKaznDialog_12":
			DialogExit();
			ResetSound();
			chrDisableReloadToLocation = false;
			EndQuestMovie();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			locCameraTarget(PChar);
			locCameraFollow();
			AddQuestRecord("PZ", "39");
			
			LAi_SetPlayerType(pchar);
			npchar.greeting = "Longway";
			Return_LongwayOfficer();
			
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_2", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_3", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_3", true);
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", false);
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			DeleteAttribute(pchar, "GenQuest.AbordageInStorm");
			
			PChar.quest.PZ_Etap6_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Etap6_Start.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_Etap6_Start.win_condition = "PZ_Etap6_Start";
			locations[FindLocation("Shore58")].DisableEncounters = true;
			SetTimerCondition("PZ_Etap6_Opozdal", 0, 0, 7, false);
			DelMapQuestMarkCity("PortPax");
			AddMapQuestMarkShore("Shore58", true);
			pchar.questTemp.PZ_FlagMartinInfo = true;
			
			// Компаньон-заглушка входит в состав нашей экскадры
			sld = CharacterFromID("PZ_ShipStasis");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, true);
			SetShipRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.ship.HP = sti(sld.ship.HP) / 2;
			
			//
			makearef(arTmp, pchar.questTemp.PZ_PoP_More.ShipPos);
			QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
			DeleteAttribute(pchar, "questTemp.PZ_PoP_More.ShipPos");
			QuestToSeaLogin_Launch();
		break;
		
		case "PZ_AlonsoKaznDialog_1":
			dialog.text = "Dio mio... Mai visto né sentito così, Mio Signore Capitano.";
			link.l1 = "È tutto tuo, Alonso! Dai, mostrami cosa fa la Santa Inquisizione agli ugonotti e ai loro scagnozzi... E io guarderò... Poi potrai fare di lui ciò che ti pare.";
			link.l1.go = "PZ_AlonsoKaznDialog_2";
		break;
		
		case "PZ_AlonsoKaznDialog_2":
			dialog.text = "Aye aye, Mio Signore Capitano...";
			link.l1 = "";
			link.l1.go = "PZ_AlonsoKaznDialog_3";
		break;
		
		case "PZ_AlonsoKaznDialog_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_AlonsoKazn_2", -1);
		break;
		
		case "PZ_AlonsoKaznDialog_4":
			dialog.text = "Non ci vorrà molto, mio Signore Capitano...";
			link.l1 = "Fallo, per l’amor del cielo!";
			link.l1.go = "PZ_AlonsoKaznDialog_5";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			//LAi_ActorAnimation(npchar, "Barman_idle", "1", 5);
		break;
		
		case "PZ_AlonsoKaznDialog_5":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_AlonsoKazn_3", 1.5);
		break;
		
		case "PZ_AlonsoKaznDialog_6":
			dialog.text = "Alzati, pezzo di merda. Ho detto alzati!";
			link.l1 = "È morto? Morto davvero?!";
			link.l1.go = "PZ_AlonsoKaznDialog_7";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
		break;
		
		case "PZ_AlonsoKaznDialog_7":
			dialog.text = "Sembra proprio di sì, capo...";
			link.l1 = "Che diavolo hai combinato?!";
			link.l1.go = "PZ_AlonsoKaznDialog_8";
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
		break;
		
		case "PZ_AlonsoKaznDialog_8":
			dialog.text = "Chi avrebbe mai pensato che questo bruto fosse in realtà un povero codardo! Si è pure sporcato le mutande, lurido bastardo! Maledizione, il fuoco era superfluo...";
			link.l1 = "Tu... Bene, gettatelo in pasto ai pesci. Rotta su Tortuga. Se serve, la smantello pietra dopo pietra – prima La Roche, poi... Poi che Dio mi assista se non la trovo ancora viva...";
			link.l1.go = "PZ_AlonsoKaznDialog_9";
		break;
		
		case "PZ_AlonsoKaznDialog_9":
			DialogExit();
			ResetSound();
			chrDisableReloadToLocation = false;
			EndQuestMovie();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			locCameraTarget(PChar);
			locCameraFollow();
			AddQuestRecord("PZ", "38");
			
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_2", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_3", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_3", true);
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", false);
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			DeleteAttribute(pchar, "GenQuest.AbordageInStorm");
			
			PChar.quest.PZ_Etap6_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Etap6_Start.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_Etap6_Start.win_condition = "PZ_Etap6_Start";
			locations[FindLocation("Shore58")].DisableEncounters = true;
			SetTimerCondition("PZ_Etap6_Opozdal", 0, 0, 7, false);
			DelMapQuestMarkCity("PortPax");
			AddMapQuestMarkShore("Shore58", true);
			
			// Компаньон-заглушка входит в состав нашей экскадры
			sld = CharacterFromID("PZ_ShipStasis");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, true);
			SetShipRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.ship.HP = sti(sld.ship.HP) / 2;
			
			//
			makearef(arTmp, pchar.questTemp.PZ_PoP_More.ShipPos);
			QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
			DeleteAttribute(pchar, "questTemp.PZ_PoP_More.ShipPos");
			QuestToSeaLogin_Launch();
		break;
		
		case "PZ_Norman1":
			dialog.text = "Finalmente. Questo trono ora è mio. Su questa roccia costruirò...";
			link.l1 = "Che cazzo... Sul serio?";
			link.l1.go = "PZ_Norman2";
		break;
		
		case "PZ_Norman2":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Shark";
			
			dialog.text = "... la mia Chiesa. Adesso sono il Papa di Roma. Non bestemmiare nella Casa di Dio!";
			link.l1 = "E io che pensavo... Ebbene, Vostra Santità, vorreste compiacervi di dire al vostro fedele dove si trova la "+sTemp+" adesso?";
			link.l1.go = "PZ_Norman3";
		break;
		
		case "PZ_Norman3":
			dialog.text = "È partito per una sacra missione. Una nuova crociata, se così vuoi chiamarla. Prenderà l’oro dagli infami e lo porterà a me.";
			link.l1 = "A te, giusto. Ti ha detto quando sarebbe tornato?";
			link.l1.go = "PZ_Norman4";
		break;
		
		case "PZ_Norman4":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "Fra un mese. Forse anche più tardi. Attendo il suo ritorno, insieme al resto del nostro branco.";
			link.l1 = "Quindi è davvero in mare. Meglio che me ne vada prima di beccarmi la tua stessa sventura.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_NormanBlock":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "Li purificherò tutti nelle fiamme sacre...";
			link.l1 = "La tua testa avrebbe proprio bisogno di una bella purificazione...";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoro1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				// ох, какой же костыль, м-м-мать...
				sld = characterFromId("Mary");
				if (sld.location != "Pirates_townhall")
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "with Marcus";
					else sTemp = "with Steve";
					
					dialog.text = "Charles! Cosa posso fare per voi?";
					link.l1 = "Ciao, Helen! Desidero parlarti "+sTemp+" È di sopra? O si trova nella taverna?";
					link.l1.go = "PZ_HelenaIslaTesoroGood1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
					else sTemp = "Steve";
					
					dialog.text = "Charles! E... Ah, che piacevole sorpresa. Cosa posso fare per voi due?";
					link.l1 = "Ciao, Helen. Dove si trova "+sTemp+"?";
					link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
				else sTemp = "Shark";
				
				dialog.text = TimeGreeting()+", Charles. Cosa ti porta da queste parti?";
				link.l1 = TimeGreeting()+", Helen. Sto cercando la "+sTemp+" Sai dove si trova?";
				link.l1.go = "PZ_HelenaIslaTesoroBad1";
			}
		break;
		
		case "PZ_HelenaIslaTesoroGood1":
			dialog.text = "È fuori, ma temo che sarà via a lungo – è salpato, per essere precisi.";
			link.l1 = "Maledizione. È successo qualcosa? Ha detto quando sarebbe tornato?";
			link.l1.go = "PZ_HelenaIslaTesoroGood2";
		break;
		
		case "PZ_HelenaIslaTesoroGood2":
			dialog.text = "Non l’ha fatto, ma non è nulla di grave – ha una buona pista, come sempre. Di solito torna in un mese, due al massimo. Capisco com’è, a volte anch’io sento la mancanza del ponte della nave...";
			link.l1 = "Si può sempre andare per mare. Sarebbe bello farlo insieme, un giorno – tu sulla 'Arcobaleno', io sulla...";
			link.l1.go = "PZ_HelenaIslaTesoroGood3";
		break;
		
		case "PZ_HelenaIslaTesoroGood3":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			dialog.text = "Lo farei. Ma la tua... fidanzata potrebbe non gradire. E non voglio fare la candela, giusto?";
			link.l1 = "Ehm, scusa, Helen, non volevo offenderti. Grazie per la chiacchierata. Ci vediamo dopo.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steve";
			
			dialog.text = "Charles, sei tornato. C’è qualcos’altro in cui posso esserti d’aiuto?";
			link.l1 = "No, grazie, Helen. Volevo solo controllare se "+sTemp+" si è fatto vedere.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroBad1":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			else sTemp = "Steven";
			
			dialog.text = "Sarei sorpreso se foste venuto a cercarmi. Quanto a "+sTemp+", è fuori in mare.";
			link.l1 = "Oh, davvero? Ti ha detto quando sarebbe tornato?";
			link.l1.go = "PZ_HelenaIslaTesoroBad2";
		break;
		
		case "PZ_HelenaIslaTesoroBad2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			dialog.text = "A quanto pare, si è stufato di comandare questa fogna e deve ricordare a se stesso d’essere ancora il capitano d’una nave. Non è la prima volta. Di solito torna dopo un mese, o forse un mese e mezzo.";
			link.l1 = "Maledizione, quindi i baroni non stanno sempre fermi come statue? Grazie, Helen. Addio.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroBadBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steven";
			
			dialog.text = ""+sTemp+"non è ancora tornato, Charles";
			link.l1 = "Capisco, solo un controllo.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere1":
			dialog.text = "È un uomo libero, giusto? Può salpare quando gli pare.";
			link.l1 = "Ma certo che può. Allora, dove si trova?";
			link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere2";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "the Shark";
			
			dialog.text = "Ma Charles, se non è sull’isola, allora è andato a saccheggiare gli spagnoli. E adesso, se permetti, ho parecchio da fare. Passa ogni tanto a vedere – di solito, il "+sTemp+" ritorna tra circa un mese, a volte anche un po' più tardi.";
			link.l1 = "Bene, Helen, grazie. Troveremo qualcosa da fare.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodMaryHereBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			dialog.text = "Non è il momento adesso. Magari torna un’altra volta, Charles?";
			link.l1 = "Certo, Helen. Scusa se ti disturbo. Stammi bene.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_Longway_81":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				dialog.text = "Siamo in posizione, Mio Signore Capitano. Ricorda la strada?";
				link.l1 = "Certo, Longway. Speriamo solo di non lasciarci l’anima in quella maledetta prigione sotterranea...";
				link.l1.go = "PZ_Longway_FlagMartinInfo_1";		//Sinistra
			}
			else
			{
				dialog.text = "Siamo in posizione, Mio Signore Capitano. Avete un piano?";
				link.l1 = "Ci sto ancora lavorando... Perché, hai qualche idea in testa?";
				link.l1.go = "PZ_Longway_NotMartinInfo_1";		//Rebbebion
			}
			DelLandQuestMark(npchar);
			LAi_SetCheckMinHP(npchar, 1, true, "");		//На 6 эпизод даём Лонгвею бессмертие
			
			LocatorReloadEnterDisable("Tortuga_town", "houseS4", false);
		break;
		
		case "PZ_Longway_NotMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ebbene, credo che se ci sbrighiamo verso Chang Xing...";
			link.l1 = "Longway... Capisco quanto tu desideri rivedere tua sorella, ma "+sStr+" è in pericolo di morte in questo preciso momento, e non è solo un modo di dire! Devi capire che salvarla è la priorità assoluta!";
			link.l1.go = "PZ_Longway_NotMartinInfo_2";
		break;
		
		case "PZ_Longway_NotMartinInfo_2":
			dialog.text = "Mio Signore Capitano, dubito che comprendiate davvero cosa io abbia sopportato in questi dieci anni. E cosa sto sopportando proprio ora.";
			link.l1 = "Sai, in un certo senso sì. Mio fratello è rinchiuso in prigione. E anche se finora non gli hanno fatto del male, da un momento all'altro potrebbero fargli qualsiasi cosa vogliano.";
			link.l1.go = "PZ_Longway_NotMartinInfo_3";
		break;
		
		case "PZ_Longway_NotMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ma dove andresti se fossi solo una dama "+sStr+" chi aveva bisogno di essere salvato?";
			if (CheckAttribute(pchar, "questTemp.FMQT.GiveDiamonds") && !CheckAttribute(pchar, "questTemp.FMQT_ObchistilSunduk"))
			{
				link.l1 = "C’è un posto... una persona... Ma non preoccuparti di questo, Longway – devo occuparmene io stesso.";
				link.l1.go = "PZ_GoMarceline1";
			}
			link.l2 = "In verità, neppure so dove andare. Se ficco il naso dappertutto senza badare, attirerò l’attenzione, e poi "+sStr+" è sicuramente spacciato. Quindi... davvero non so che pensare.";
			link.l2.go = "PZ_GoTogether1";
		break;
		
		case "PZ_GoMarceline1":
			dialog.text = "Cosa? Perché mai?";
			link.l1 = "Non ti lasceranno mica entrare così facilmente – è roba da gente di alto rango, dannazione. Allora, vado io da sola. Intanto, tu vai da tua sorella. Ti raggiungo appena posso. Buona fortuna, Longway!";
			link.l1.go = "PZ_GoMarceline2";
			RemovePassenger(pchar, npchar);
		break;
		
		case "PZ_GoMarceline2":
			dialog.text = "Aye! Grazie, Mio Signore Capitano. E buona fortuna anche a voi!";
			link.l1 = "Oh, grazie – oggi ne ho proprio bisogno. Ne abbiamo tutti bisogno.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineLongwayGo");
		break;
		
		case "PZ_GoTogether1":
			dialog.text = "Mio Signore Capitano...";
			link.l1 = "Lascia perdere. Andiamo da tua sorella, Longway. Se ci separiamo ora – siamo spacciati. Sbrighiamoci a raggiungerla e scopriamo dove si nasconde Levasseur. Poi torneremo insieme – in questo momento ho bisogno di tutta l'aiuto possibile. Spero solo di non arrivare troppo tardi.";
			link.l1.go = "PZ_GoTogether2";
		break;
		
		case "PZ_GoTogether2":
			dialog.text = "Non tarderemo, Mio Signore Capitano. Non perdiamo altro tempo a discutere o a indugiare. Andiamo da Chang Xing!";
			link.l1 = "Hai ragione, sbrighiamoci.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_FrenchSoldier1":
			dialog.text = "Dove diavolo stai andando? Sai almeno dove porta quella porta?";
			link.l1 = "So perfettamente cosa faccio. Vado lì per affari, non per oziare o rubare.";
			link.l1.go = "PZ_FrenchSoldier2";
		break;
		
		case "PZ_FrenchSoldier2":
			dialog.text = "Che affari? Madame Levasseur al momento non riceve nessuno. E poi è donna sposata – non sta bene che la gente le ronzi attorno, capisci?";
			link.l1 = "Sposata, giusto. Però ogni tanto fa delle ricezioni, eh? Anche private. Stavolta è una di quelle. Mi sta aspettando, e io vado di fretta.";
			link.l1.go = "PZ_FrenchSoldier3";
		break;
		
		case "PZ_FrenchSoldier3":
			dialog.text = "Mi avrebbe avvertito, se fosse stato così.";
			link.l1 = "Sono un tipo speciale di ospite – di quelli che non hanno bisogno di presentazioni.";
			link.l1.go = "PZ_FrenchSoldier4";
		break;
		
		case "PZ_FrenchSoldier4":
			dialog.text = "Aye, quel tipo d’ospite che farà ordinare a Sua Signoria di farmi fucilare. O peggio, la Signora in persona mi scuoierà viva.";
			link.l1 = "Sono già stato ospite della Madame Marceline. Ti assicuro, soldato, che dopo non ti accadrà nulla.";
			link.l1.go = "PZ_FrenchSoldier5";
		break;
		
		case "PZ_FrenchSoldier5":
			dialog.text = "Ma certo, chiudere gli occhi e lasciar entrare chiunque – questo è il mestiere della guardia cittadina.";
			link.l1 = "Non ho tempo per queste sciocchezze, testone di un mulo...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_FrenchSoldierFight");
		break;
		
		case "PZ_Marceline1":
			dialog.text = "Tu...";
			// начинаем проверять результат прохождения "Почти как дома"
			switch (pchar.questTemp.FMQT.Marceline)
			{
				// поделили алмазы и "охладили трахание, углепластики" (с)
				case "Fuck":
					link.l1 = "Oh sì, madama. Il vostro cavaliere è lieto di rivedervi. Vedo che siete sorpresa di incontrarmi. La gioia di questa riunione... non è reciproca?";
					link.l1.go = "PZ_MarcelineFuck1";
				break;
				
				// поделили алмазы, без трахания и углепластиков
				case "NoFuck":
					link.l1 = "Sì, l'ho fatto. Mi rendo conto di non essere forse l'uomo più bello o degno di quest'isola, come avete sottolineato alla nostra ultima conversazione, ma almeno sapete che sono un uomo onesto. Ascoltatemi, signora – non vi ruberò troppo del vostro... prezioso tempo.";
					link.l1.go = "PZ_MarcelineNoFuck1";
				break;
				
				// "сошлись вот где-то посередине" (с)
				case "Deception":
					link.l1 = "Zitta, per l’amor di Dio, smettila con queste urla, signora. Non sono qui per vendicarmi perché hai ingannato il tuo cavaliere e sei fuggita col tesoro del drago. E ti assicuro: se volessi ucciderti, ti sparerei e scapperei a gambe levate. Questa è Tortuga, dopotutto! Ma credo tu sappia già che una simile bassezza non fa per me.";
					link.l1.go = "PZ_MarcelineDeception1";
				break;
			}
		break;
		
		case "PZ_MarcelineFuck1":
			dialog.text = "Oh, no! Pensavo solo che... Beh, non importa! Vede, le lingue maligne sparlano di me - una povera donna che, anche volendo, non potrebbe né far male a qualcuno né difendersi dai nemici. E poi, è passato così tanto tempo... Credevo fosse venuto da me con cattive intenzioni, non con cuore buono. Sono lieta d'aver sbagliato. È dura vivere quando tutto intorno ci sono solo maldicenti.";
			link.l1 = "Come potrei? Anche se avessi sentito qualcosa del genere, non ci crederei nemmeno per un istante. Ma hai ragione – non sono venuto qui solo per vederti. Anche se mi fa piacere. So che suonerà strano, ma... stavolta è il tuo cavaliere ad aver bisogno del tuo aiuto, madama.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineNoFuck1":
			dialog.text = "E sei molto più sensibile di quanto pensassi. Tuttavia, non sei senza colpe, Monsieur de Maure – mi aspettavo fossi più... raffinato. Anzi... o sei sempre stato così, oppure l’Arcipelago ti ha già guastato. Dovresti imparare di nuovo il modo giusto di parlare a una dama. Ma hai ragione – sei un uomo onesto, benché... semplice.";
			link.l1 = "E voi siete una donna fiera e vendicativa. I vostri occhi, le vostre parole e... le vostre azioni lo gridano forte. Se qualcuno può capirmi, siete voi. Così come io, un tempo, vi compresi. Dunque, lasciamo il passato dove sta. Potete aiutarmi, madama?";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineDeception1":
			dialog.text = "Oh... Lo ammetto, non sono stata gentile con te allora. Ma solo perché non ero del tutto sicura di te, niente di più! Avresti portato via tutti i diamanti? O condotto mio marito lì, dicendo di aver saputo dai nostri servi che avevo rubato da lui, negando il tuo coinvolgimento? In fondo, tutti cercano il suo favore, non una povera donna come me... Ora capisco che mi sbagliavo su di te. Ti prego, accetta le mie scuse... mio cavaliere.";
			link.l1 = "Non so più se siano sinceri o meno.  Ma non importa.  Ho bisogno del vostro aiuto, Madame Marceline.  È una questione di vita o di morte.  Vi prego, non rifiutate.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_Marceline2":
			dialog.text = "Il mio aiuto...? Non sono certo l'ultima donna in città, ma la mia influenza non è così grande come tutti voi pensate. Sono una regina che regna, non che comanda. Ma ti ascolterò. Cosa può fare la mia umile persona per te?";
			link.l1 = "Capisco che l’argomento non sia piacevole per voi, signora, ma sto cercando vostro marito e mi occorre trovarlo al più presto. La verità è che...";
			link.l1.go = "PZ_Marceline3";
		break;
		
		case "PZ_Marceline3":
			dialog.text = "È uno scherzo? Non si trova alla residenza in questo momento? Allora è fuori per affari. Non posso aiutarvi, Monsieur de Maure.";
			link.l1 = "Hai distolto lo sguardo. Tu sai. Anch'io so. Devo solo arrivarci, ormai. Ti prego, non fingere sia la prima volta che senti parlare del sotterraneo – sei troppo furbo per non sapere.";
			link.l1.go = "PZ_Marceline4";
		break;
		
		case "PZ_Marceline4":
			dialog.text = "Oh, mi sa che questa chiacchierata mi farà venire un altro capello grigio. Come se non bastassero già le prime rughe. Ma che diamine ci stai facendo passare, Francois...";
			link.l1 = "Una ciocca grigia aggiungerà soltanto nobiltà al vostro aspetto, senza portar via la vostra bellezza. Ma una brava ragazza, innocente, è caduta nelle grinfie di vostro marito. Ora rischia di perdere la sua bellezza, la salute, persino la vita!... Voi sapete che fine fanno quelli che rimangono intrappolati là dentro. Vi prego, signora. Marceline... Aiutate il vostro cavaliere.";
			link.l1.go = "PZ_Marceline5";
		break;
		
		case "PZ_Marceline5":
			dialog.text = "Non sono più davvero il tuo cavaliere, giusto? Dai, non sono stupida. Ma... ti aiuterò, de Maure. In fondo, non poteva durare per sempre. E prima o poi sarebbe venuto tutto a galla. Quello che conta per me ora è uscire al momento giusto, e nel modo giusto. E... non posso condannarti a soffrire per l'eternità a causa di quello che mio ‘marito’ farà alla tua... conoscenza.";
			link.l1 = "Forse non sono più il vostro cavaliere, madama. Ma neppure voi siete mai stata la mia dama, sin dall'inizio. Tuttavia, vi sarò grato per tutta la mia vita. Allora, dove si trova questo luogo?";
			link.l1.go = "PZ_Marceline6";
		break;
		
		case "PZ_Marceline6":
			dialog.text = "Bene, mi fiderò della tua parola, Charles. Nelle segrete della città. C’è una grossa botte in uno dei vicoli ciechi, e accanto ad essa si apre un passaggio che conduce al covo di quel demonio. Non sono entrato. L’ho seguito solo una volta, tanto tempo fa. E mi sono spaventato quando ho sentito le urla disumane di quelle povere anime.";
			link.l1 = "Oggi avete salvato molte vite, signora. Non solo quella della mia cara, ma anche di tutti coloro che sarebbero potuti cadere per mano di vostro marito in futuro. Vi ringrazio.";
			link.l1.go = "PZ_Marceline7";
		break;
		
		case "PZ_Marceline7":
			dialog.text = "Ah, lasciami con queste tue parole vuote, monsieur. Mi hai chiesto davvero tanto. E io ho rischiato la pelle. Ora cerca di non morire nella tana del drago... mio cavaliere.";
			link.l1 = "Farò del mio meglio. Addio, Marceline.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineOver");
		break;
		
		case "PZ_ElitaShluha_18":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "So, you're a bandit, monsieur...? We don't hire new girls like this; we all came here voluntarily. I'm going to have to ask you and your... accomplice to step out. And I'll make sure this girl gets treatment - otherwise, I'll report you to the authorities!";
				link.l1 = "Noi non siamo briganti. Ma questa ragazza può tener testa a chiunque di loro. Non porta la lama solo per bellezza. È solo ferita. Quest’uomo è un mio compare e anche fratello della tua padrona. Quindi, facci vedere lei.";
				link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl1";
			}
			else
			{
				dialog.text = "Bene rivederla, monsieur! Ma sa che qui non accogliamo ospiti... di bassa lega. Anche se qualcuno li raccomanda e paga per loro. Soprattutto lavoranti con la pelle gialla o schiavi negri. Temo che il suo amico dovrà andarsene.";
				link.l1 = "Non dire queste cose davanti alla tua padrona. Anche lei ha la pelle gialla. E lui non è un bracciante, ma suo fratello. Non intralceresti un ricongiungimento di famiglia, vero?";
				link.l1.go = "PZ_ElitaShluha_WithLongway1";
			}
		break;
		
		case "PZ_ElitaShluha_18_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "It's getting worse by the hour. First the mad yellow laborer and now you. No, monsieur, we don't pay for the girls who are brought to us by force; they are all here of their own free will.";
				link.l1 = "Ho salvato questa ragazza, e non la farò mai sgobbare in un posto indegno di lei . Un manovale, dici?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl1";
			}
			else
			{
				dialog.text = "Oh monsieur, che tempismo sfortunato! Oggi non accettiamo più ospiti - può vedere da sé cosa è successo qui.";
				link.l1 = "Ecco perché sono qui. È stato un uomo dalla pelle gialla a orchestrare tutto questo, vero?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl1";
			}
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl1":
			dialog.text = "Sì, monsieur, un bracciante! Non riuscivamo quasi a capire cosa blaterasse! Quel pezzente si è precipitato dentro e ha preteso di vedere la signora. Ci ha giurato di essere suo fratello. Abbiamo chiamato aiuto, ma...";
			link.l1 = "Non è certo un ostacolo per lui. E poi che è successo?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl2":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "Come si è visto, non mentiva. La signora è uscita da noi e lo ha riconosciuto. Anzi, stanno ancora chiacchierando nei suoi alloggi sontuosi.";
			link.l1 = "Chi può sapere cosa gli passa per la testa, però. Entriamo là dentro - la salveremo se sarà necessario. Non fare storie - rovineresti la reputazione di questo posto.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl1":
			dialog.text = "Proprio così, monsieur. Ha detto d’essere il fratello della signorina.";
			link.l1 = "E non l’hai fatto entrare...";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl2":
			dialog.text = "Ma certo che no! La signora è vestita con una raffinatezza squisita e parla senza alcun accento, mica come quel manovale. Abbiamo provato a scacciarlo, e lui ha steso tutte le guardie, puoi crederci?!";
			link.l1 = "Posso ben immaginare. E adesso dove si trova lui?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl3";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl3":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "Lui e la signora stanno ancora confabulando su qualcosa, ma non riusciamo a capire di che si tratti – probabilmente usano la loro lingua.";
			link.l1 = "Vado io da loro. Forse la vostra signora ha bisogno d’aiuto. Non chiamate le guardie: se si viene a sapere, nessuno busserà mai più alla vostra porta.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_WithLongway1":
			dialog.text = "Un fratello? La padrona ha almeno un po' di decoro, cosa che non posso dire di questo suo ‘fratello’. Non serve confonderle la testa né imbrogliarla con questo manovale. Portalo via.";
			link.l1 = "Te l'ho già detto, si sono persi di vista tanto tempo fa. Lui è solo più sfortunato. Pagheremo noi stessi la locanda per il nostro tempo. Avvisa subito la padrona.";
			link.l1.go = "PZ_ElitaShluha_WithLongway2";
		break;
		
		case "PZ_ElitaShluha_WithLongway2":
			dialog.text = "Non ha nulla di cui preoccuparsi con te. E la tua insistenza non mi piace affatto. Ragazzi! Buttatelo fuori, questo bracciante! E anche il suo padrone svanito, fuori di qui!";
			link.l1 = "Maledizione! Quanta superbia per una cortigiana!";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl1":
			dialog.text = "Neanche per sogno! Lasciare la padrona sola in compagnia di tutta questa strana gente che ti porti dietro? Solo se ci vai da solo, monsieur. E i tuoi... amici aspetteranno fuori – qui abbiamo un locale rispettabile.";
			link.l1 = "Perché ti preoccupi per lei? Tutti sanno che è una delle migliori spadaccine di Tortuga. E i miei amici sono più onesti della maggior parte della feccia che vive qui.";
			link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl2";
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl2":
			dialog.text = "Ragazzi! Qui c'è un bandito ferito e un lurido pezzente! Vogliono qualcosa dalla nostra padrona! Sistemiamoli!";
			link.l1 = "Che dedizione, maledizione...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ChangShin1":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			
			// итак, снова проверка по результатам прохождения. Лонгвэй с нами, тян ещё в пыточной
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Immagino che tu sia Charles de Maure? E questa... Oh.";
				link.l1 = "E tu devi essere Belle Etoile. O forse dovrei dire Chang Xing? E sì, questo è tuo fratello. Ti cerca da più di dieci anni. Io e lui abbiamo molte, moltissime domande per te. E poco tempo.";
				link.l1.go = "PZ_ChangShin_WithLongway1";
			}
			// пришли с Лонгвэем и тян
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				dialog.text = "Santo cielo, sei viva. Ti sei trovata un bel difensore, anche se è arrivato un po' tardi. Meglio di quello che, a quanto pare, pensa che sia io a doverlo proteggere, e ora ti sta accanto. Il cielo ti guarda benevolo, mia cara.";
				link.l1 = "Vedo che hai già capito. Tanto meglio, non serve spiegare. Ma dimmi, di cosa sorridi, Chang Xing? Ti piace osservare la sofferenza delle altre ragazze, vero? In fondo, sei tu che le vendi.";
				link.l1.go = "PZ_ChangShin_WithLongwayAndGirl1";
			}
			// Лонгвэй с нами, тян на небесах
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
				dialog.text = "Charles de Maure, giusto? Ho sentito che volevi vedermi. Allora, che ti turba? Il servizio nella nostra locanda non ti è piaciuto l’ultima volta che sei passato, eh?";
				link.l1 = "Sono appena arrivato da un altro dei tuoi locali, Chang Xing. "+sStr+", mio amante, è morto. E so che anche tu hai avuto la tua parte in questo.";
				link.l1.go = "PZ_ChangShin_GirlDied1";
			}
		break;
		
		case "PZ_ChangShin_WithLongway1":
			dialog.text = "Chang Xing... È passato tanto tempo da quando ho sentito quel nome. Tanto tempo. Voi bianchi... sempre di fretta. Che ne dite di una bella riunione di famiglia senza correre? Ma a me non importa. Ho smesso di contare sugli altri anni fa. Perché non dici nulla, fratello mio? Non sei contento di vedere tua sorella? Eppure mi hai cercata senza tregua, no?";
			link.l1 = "Abbiamo altre faccende urgenti e ben più gravi da sbrigare. Parla pure con tua sorella, Longway. Ma non scordare che ci resta ancora molta strada da fare. Dobbiamo muoverci in fretta. E anch’io ho delle domande da farle.";
			link.l1.go = "PZ_Longway_SisterDialog1";
		break;
		
		case "PZ_Longway_SisterDialog1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "(In Mandarino) Longway, eh? A parte il nome, non sei cambiato poi tanto... Chang Tu.";
			link.l1 = "(In mandarino) Ma sei cambiata tanto, sorella. Cos'è successo? Il tuo sguardo era caldo come il sole a mezzogiorno. Ora è gelido e non mostra altro che disprezzo. E la tua voce? Amavo farti ridere e sentire quelle campanelle d’argento tintinnare... Ora è più fredda di un Goango d'inverno. E porti i loro abiti. E vendi tu stessa le donne, anche se una volta sei stata rapita dai Fermentelos.";
			link.l1.go = "PZ_Longway_SisterDialog2";
		break;
		
		case "PZ_Longway_SisterDialog2":
			dialog.text = "Vieni qui a farmi la predica, anche se un tempo servivi Rodenburg, uno dei peggiori furfanti dell’arcipelago? Pensi che non sapessi tutto di te? L’ho sempre saputo. Non sta a te giudicare ciò che sono diventata e perché, mio povero fratello maggiore smarrito.";
			link.l1 = "Allora lasciami scoprire, Xing! E dimmelo. Se sapevi che ero sull’Arcipelago, perché non hai voluto incontrarmi dopo tutti questi anni? Ho speso tutta la mia vita a cercarti...";
			link.l1.go = "PZ_Longway_SisterDialog3";
		break;
		
		case "PZ_Longway_SisterDialog3":
			dialog.text = "Perché né tu né il Cielo mi avete protetto dalla più orrenda delle sventure. E allora ho capito che in questo mondo nessuno ha davvero bisogno di nessun altro. Possiamo contare solo su noi stessi. Va bene, te lo racconterò, se davvero lo vuoi sapere. Ma parlerò nella sua lingua. Son sicuro che anche a lui piacerebbe ascoltare. Capisci il francese, vero, Tu?";
			link.l1 = "(in francese stentato): Oui, je parle questa lingua.";
			link.l1.go = "PZ_Longway_SisterDialog4";
		break;
		
		case "PZ_Longway_SisterDialog4":
			dialog.text = "Ah ah ah, oh, Cielo! Il tuo accento è spaventoso. Non è colpa tua, però – la pronuncia e la scrittura francese sono davvero rognose.";
			link.l1 = "Ridi in modo diverso adesso, sorella...";
			link.l1.go = "PZ_ChangShin_WithLongway3";
		break;
		
		/*case "PZ_Longway_SisterDialog5":
			Return_LongwayOfficer();
			
			StartInstantDialog("PZ_ChangShin", "PZ_ChangShin_WithLongway3", "Quest\CompanionQuests\Longway.c");
		break;*/
		
		case "PZ_ChangShin_WithLongway3":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			dialog.text = "Mio caro fratello vuol sapere cosa mi è successo in tutti questi anni. Penso che anche a te farebbe bene ascoltare – come hai detto, hai delle domande. Quindi non preoccuparti – ti racconterò tutto, ma in francese.";
			link.l1 = "Dimmi solo l'essenziale – quando Longway mi ha raccontato la sua storia, ci sono volute ore intere. E adesso vado di fretta.";
			link.l1.go = "PZ_ChangShin_WithLongway4";
		break;
		
		case "PZ_ChangShin_WithLongway4":
			dialog.text = "Siate pazienti. Ho tenuto tutto dentro per più di un anno. E se mi interrompete, non risponderò a nessuna delle vostre domande.";
			link.l1 = "Va bene... Allora vai avanti.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl1":
			dialog.text = "Dove sono finite le tue buone maniere, Charles de Maure? Mi avevano detto che eri un uomo d’eccelsa educazione, un vero cavaliere con le dame. Solo chiacchiere, eh? In realtà... un fallimento? Proprio come pensavo. E ti sbagli: io odio uomini e donne allo stesso modo. Anzi, non mi fido di nessuno, non mi sorprendo mai, non mi aspetto nulla. Ti schiaccerei volentieri le palle, se solo riuscissi a metterti le mani addosso. Però... sentire il mio vero nome dopo tutti questi anni è stato... quasi rinvigorente.";
			link.l1 = "Sono un uomo per le dame, non per streghe come te. E poi, cosa ti aspettavi, visto che sei coinvolta nel tormentare la persona a cui tengo di più? Faccio fatica a trattenermi dal farti qualcosa anch’io, e non solo per lui, sia chiaro. Longway è mio amico. E tu sei la sua famiglia. Ti cerca da più di dieci anni. Merita di parlarti.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl2":
			dialog.text = "Che tenerezza. E che peccato che non me ne importi affatto. Ma adesso non te la caverai così facilmente, vero, Tu? Non solo per averti ucciso, e voi tutti per essere arrivati tardi, ma perché... Sì, forse meriti di sapere. Mi hai conosciuta quando non ero così, fratello.";
			link.l1 = "Non importa cosa ti sia successo... hai sempre avuto una scelta, Chang Xing.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl3";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl3":
			dialog.text = "Sei ancora giovane e non sai come va il mondo, Charles de Maure. C’è una sola vera scelta nella vita: vivere o morire. Penso che ti farebbe bene sapere tutto, anche a te. Racconterò la mia storia in francese. Lo parli, vero, Tu?";
			link.l1 = "Con un accento. Ma lo comprende benissimo. Puoi iniziare.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_GirlDied1":
			dialog.text = "E dove sei stato per tutto questo tempo? Espanola è soltanto a un giorno o due da qui. Anche la sua morte è colpa tua. E tu. Sei arrivato con più di dieci anni di ritardo. I nostri salvatori, i nostri protettori. Più presto una donna impara a difendersi, meglio è. Alcune lo fanno in tempo, altre no. E qualcuna non ha abbastanza cervello per capirlo.";
			link.l1 = "Attento a ogni parola che proferisci adesso. Non ti ho ancora fatto a brandelli solo per rispetto al mio amico, tuo fratello. Non hai la minima idea di ciò che ha sofferto per causa tua.";
			link.l1.go = "PZ_ChangShin_GirlDied2";
		break;
		
		case "PZ_ChangShin_GirlDied2":
			dialog.text = "Dubito fortemente che abbia mai vissuto qualcosa anche solo lontanamente simile a ciò che ho passato io.";
			link.l1 = "Allora, raccontaci.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin2":
			dialog.text = "Ebbene, che dire, allora ero giovane, stupida e ingenua. E anche intollerante. Ti ha già raccontato di quando fui rapita da Oliverio Fermentelos dopo che uccise i miei genitori... e me stessa?";
			link.l1 = "Giusto.";
			link.l1.go = "PZ_ChangShin3";
		break;
		
		case "PZ_ChangShin3":
			dialog.text = "Mi ha fatto la corte e mi ha confessato i suoi sentimenti, ma io l’ho respinto. E fu allora che massacrò la nostra famiglia e mi rapì. E poi...";
			link.l1 = "Posso intuire.";
			link.l1.go = "PZ_ChangShin4";
		break;
		
		case "PZ_ChangShin4":
			dialog.text = "Vorrei che tu potessi. Poi mi ha confessato ancora i suoi sentimenti, acceso e in lacrime, dicendo che era l’unica via, perché la mia famiglia non mi avrebbe mai lasciata andare con lui.";
			link.l1 = "Follia...";
			link.l1.go = "PZ_ChangShin5";
		break;
		
		case "PZ_ChangShin5":
			dialog.text = "Heh, una parola per riassumere tutta la mia vita da allora. L'ho respinto ancora una volta. E la storia è andata avanti così per un po'. Ma era ovvio che non poteva durare per sempre, perché ero del tutto in suo potere.";
			link.l1 = " Dunque è successo davvero? ";
			link.l1.go = "PZ_ChangShin6";
		break;
		
		case "PZ_ChangShin6":
			dialog.text = "Certo. Mi ha presa con la forza, brutalmente e senza un briciolo di pietà. Non che importi mai agli stupratori, ma non era stato proprio lui, poco prima, a piangere dichiarandomi un grande amore? Bah! Quell’amore era svanito, pare. E tutto questo continuava ogni giorno, come fosse una dannata abitudine. All’inizio ho urlato e mi sono ribellata, poi ho smesso – che senso aveva, dopotutto...?";
			link.l1 = "Ma Fermentelos ha avuto quello che si meritava, e tu sei finito qui. Come ci sei arrivato?";
			link.l1.go = "PZ_ChangShin7";
		break;
		
		case "PZ_ChangShin7":
			dialog.text = "Beh, alla fine si è stancato di me. Strano, vero? Ha ucciso i miei e quelli di Tu, mi ha rapita, mi ha disonorata più volte, solo per gettarmi via alla fine. È venuto in questo Arcipelago e mi ha venduta come schiava a Levasseur.";
			link.l1 = "Non lo augurerei nemmeno al mio peggior nemico. Allora, come hai fatto a sopravvivere? E come sei riuscita a tornare libera, in primo luogo? Da quel che si dice, Levasseur non lasciava mai uscire una donna dal suo covo. Sparivano, sempre.";
			link.l1.go = "PZ_ChangShin8";
		break;
		
		case "PZ_ChangShin8":
			dialog.text = "Così stanno le cose ora. Levasseur era diverso allora. No, è sempre stato una bestia. Ma all’inizio rapiva solo di tanto in tanto qualche giovane colono, li violentava nel suo sotterraneo, poi li faceva sparire subito per non dover pagare il loro silenzio. Solo raramente li tratteneva più di qualche giorno, in quegli anni. Con me, invece, fu diverso fin dall’inizio.";
			link.l1 = "Perché eri uno schiavo, giusto?";
			link.l1.go = "PZ_ChangShin9";
		break;
		
		case "PZ_ChangShin9":
			dialog.text = "Esattamente. Il vero desiderio di Levasseur non era solo la carne. E nemmeno quel brivido fugace di potere sulle sue vittime – ché l’intera isola già gli appartiene. Ma...";
			link.l1 = "... il piacere di vederli spezzarsi – la loro volontà, il loro sguardo, la loro voce, il loro comportamento.";
			link.l1.go = "PZ_ChangShin10";
		break;
		
		case "PZ_ChangShin10":
			dialog.text = "Sì. Vedo che ti sei informato, Capitano. Ma per quanto riguarda lui, non sono mai stata un suo divertimento – Fermentelos mi aveva già consegnata a pezzi. E Levasseur non mi ha mai trovata bella – non apprezza le donne d’Oriente. Non so perché, ma questa cosa mi ha segnata tanto – so di essere attraente, ma non riesco a credermi davvero bella. E non ci credo nemmeno quando la gente me lo dice. Nemmeno ora, mentre mi alleno, indosso sete e mi profumo con essenze pregiate. Non che mi serva l’approvazione del mio carnefice, ma...";
			link.l1 = "Ebbene, ripeterò la mia domanda: come hai fatto a sopravvivere? Quando una donna lo annoia, se ne sbarazza senza indugio. E tu dici che con te era già annoiato dall’inizio.";
			link.l1.go = "PZ_ChangShin11";
		break;
		
		case "PZ_ChangShin11":
			dialog.text = "Immagino che il fatto di averlo annoiato fin dall’inizio abbia avuto qualche effetto. E poi, ero una schiava – non potevo andare da nessuna parte, né dire una sola parola. Le schiave vengono trattate così da millenni. Così ha cominciato a pensare a come rendere ‘divertente’ per sé il tempo passato con me.";
			link.l1 = "Immagino che sia così che sono nate le sue dipendenze, nella forma che conosciamo ora.";
			link.l1.go = "PZ_ChangShin12";
		break;
		
		case "PZ_ChangShin12":
			dialog.text = "Proprio così. All'inizio erano botte, sputi e altre umiliazioni. E scherni – per il mio aspetto, per la mia origine, per il mio sangue. Poi sono arrivati i primi tormenti – coltelli, tenaglie, una padella rovente... Ecco perché indosso sempre abiti chiusi – il mio corpo è pieno di cicatrici, bruciature, mutilazioni. Ecco perché non mi spoglierò mai più davanti a un uomo. Mai più. Solo allora ho capito quello che avrei dovuto capire già quando Fermentelos mi rapì.";
			link.l1 = "Che diavolo è stato?";
			link.l1.go = "PZ_ChangShin13";
		break;
		
		case "PZ_ChangShin13":
			dialog.text = "Che io non dovrei più essere una marionetta indifesa. Al contrario, dovrei avere io il timone della mia vita. Per me, era così: una donna può cambiare il proprio destino solo se tiene gli uomini vicino a sé sotto il suo controllo.";
			link.l1 = "Non direi che Levasseur possa essere domato.";
			link.l1.go = "PZ_ChangShin14";
		break;
		
		case "PZ_ChangShin14":
			dialog.text = "E non avresti torto. Ma è possibile influenzarlo, se con grande cautela. Levasseur odia allo stesso modo sia l'obbedienza cieca fin dall'inizio che le discussioni o le suppliche. Anche l'adulazione lo infastidisce – forse perché capisce bene che razza di porco sia in realtà. Questo l'ho capito subito, a prezzo di sofferenze atroci. Però, quando dopo una serata di torture e violenza si sentiva finalmente soddisfatto, allora si poteva parlargli piano. Non sono nata nobile, ma non mi manca certo l'intelletto.";
			link.l1 = "E di cosa avete parlato?";
			link.l1.go = "PZ_ChangShin15";
		break;
		
		case "PZ_ChangShin15":
			dialog.text = "Ho stuzzicato la sua curiosità. Gli ho suggerito idee di tortura, consigliato quali strumenti sarebbe meglio non usare e da quali invece iniziare. All’inizio, ovviamente, ha sperimentato tutto su di me. Ma poi... ha cominciato a rispettarmi, a modo suo, tutto distorto. Cosa gli passa per la testa? Ho provato a capire come sia diventato così, ma mi ha massacrato di nuovo a metà tra la vita e la morte. Poi ha portato il suo medico personale.";
			link.l1 = "Questo è ancora più strano e ripugnante di tutto ciò che avevo già sentito su di lui.";
			link.l1.go = "PZ_ChangShin16";
		break;
		
		case "PZ_ChangShin16":
			dialog.text = "Non pretendeva più che mi concedessi a lui. Mi chiamava allieva. Ma diceva sempre che, come suo progetto, ero un fallimento totale. Forse per tenermi all’erta. Così iniziò a insegnarmi la scherma e le lingue. Anche se mi teneva in cantina, ero io – non sua moglie – a ricevere tutti gli abiti costosi.";
			link.l1 = "Un progetto, davvero. Vede, c’è un bel parallelo con il modo in cui comanda questo posto.";
			link.l1.go = "PZ_ChangShin17";
		break;
		
		case "PZ_ChangShin17":
			dialog.text = "Non ci avevo pensato, hmm. E il tuo paragone non mi piace affatto, perché io non torturo le mie sottoposte. Né permetto ai clienti di farlo. Anche se odio quelle sgualdrine e invidio la loro bellezza. Non ho proprio nulla a che vedere con quel porco, tienilo bene a mente.";
			link.l1 = "Allora, come ti sei procurato questo bordello?";
			link.l1.go = "PZ_ChangShin18";
		break;
		
		case "PZ_ChangShin18":
			dialog.text = "Da Levasseur, ovviamente. Per un po' mi ha tenuto nella sua dimora. Ogni tanto, chiedeva pure consiglio su come spezzare questa ragazza o quell'altra. In fondo, ero speciale per lui, anche se non l’avrebbe mai ammesso. Ero la prima. Ho visto tutto.";
			link.l1 = "Chi ha imparato da chi, questa volta?";
			link.l1.go = "PZ_ChangShin19";
		break;
		
		case "PZ_ChangShin19":
			dialog.text = "Non sono così! Detesto con tutta l’anima chi ha avuto tutto servito su un vassoio! Non è giusto! Questo bordello è stata una mia idea! Le mie ragazze sono figlie di mercanti, funzionari e nobili che a volte sono capitati nelle grinfie di Levasseur. Gli ho chiesto di consegnarmele. Tortura e umiliazione in una segreta sono una cosa. Ma la vita pubblica di cortigiana per gente come loro è tutt’altra storia!";
			link.l1 = "Non direi che le tue lavoratrici sembrano così umiliate, miserabili e distrutte.";
			link.l1.go = "PZ_ChangShin20";
		break;
		
		case "PZ_ChangShin20":
			dialog.text = "Perché sanno bene cosa Levasseur o anche io faremmo loro se solo osassero fiatare. Ma in parte hai ragione, mio Signore Capitano. Il vino, il cibo, le sete, l’assenza delle torture quotidiane... molti hanno iniziato a vedermi come un salvatore. Stolti dannati! Qui sono in pochi a non essere contenti di restare. Alcuni li ha ceduti via con il cuore pesante. E rideva, dicendo che potevo sempre restituirglieli in cambio di una soluzione ai debiti della mia casa. Ma io ho sempre rifiutato. Almeno così sarebbero tornati con dell’oro invece che morire nel buio della cantina per niente. Sarebbe troppo facile, per loro, uscirsene così.";
			link.l1 = "Che peccato che non tutti si siano sentiti umiliati, passando da chiostri peggio dell’Inquisizione a una gabbia dorata come il vostro bordello...";
			link.l1.go = "PZ_ChangShin21";
		break;
		
		case "PZ_ChangShin21":
			dialog.text = "Mi giudichi? Io non volevo solo sopravvivere, ma costruire un commercio fiorente. Senza nemmeno rendersene conto, Levasseur mi era debitore. Anche se non ero più schiavo, non poteva lasciarmi andare. Dovevo comunque lavorare per lui e servire i suoi scagnozzi. Soprattutto quel suo nipote smilzo, che sbavava su di me ogni volta che mi vedeva. Ma non avrebbe mai osato aggredirmi o rivolgersi a me in modo sconveniente. Ripugnante. E sai, anche se mi chiamava una delusione, ero più utile di Thibaut e Martene messi insieme. Li accompagnavo spesso per suo ordine, proprio come quella volta a Port-au-Prince.";
			link.l1 = "Questo spiega molte cose...";
			link.l1.go = "PZ_ChangShin22";
		break;
		
		case "PZ_ChangShin22":
			dialog.text = "Esatto. Ascolta. Non ho torturato la tua amata. Come non ho mai torturato nessuna ragazza con queste mani, anche se a volte ho dato qualche consiglio a Levasseur. Ma già che ci siamo...";
			link.l1 = "Cosa?";
			link.l1.go = "PZ_ChangShin23";
		break;
		
		case "PZ_ChangShin23":
			dialog.text = "Come forse già sapete, Levasseur a volte ordina di portargli una certa ragazza che è stata vista a Tortuga, poi sparita dall’isola. Oppure qualcuno lo sorprende portandogli una sconosciuta, sperando di guadagnarsi il suo favore, come è successo con me. Rapire la tua amata... quella fu una mia idea.";
			link.l1 = "Cosa hai appena detto...?";
			link.l1.go = "PZ_ChangShin24";
		break;
		
		case "PZ_ChangShin24":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "At first, we were considering capturing that blonde who used be so close to you. But since she is untouchable now, and because we have already promised him a girl, you redhead had to do.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "I heard rumors about your gorgeous companion who never leaves your side. Considering Levausser's love for blondes, I had very little trouble selling him this idea.";
			dialog.text = "Sotta, il suo cane, doveva portargli la mulatta, la moglie di Lutter. Ma tu hai fatto fuori Sotta, quindi — niente mulatta per il grande uomo. Levasseur era furioso. Ha massacrato tutti — Thibaut, Martene, persino me. Non so chi mi ha fatto più rabbia: lui, perché mi ha picchiato di nuovo, o tu, che hai causato tutto questo..."+sStr+"";
			link.l1 = "Quindi non è nemmeno per causa sua... Sei stato tu a farlo.";
			link.l1.go = "PZ_ChangShin25";
		break;
		
		case "PZ_ChangShin25":
			dialog.text = "Non oso nemmeno sperare nel vostro perdono, e, anzi, non ne ho affatto bisogno. Se desiderate il sangue, sangue avrete. E ve ne pentirete amaramente. Ma la comprensione, quella non la rifiuterò. Mi sarebbe d’aiuto, per la prima volta in dieci lunghi anni. Tutto ciò che ho fatto è stato soltanto tentare, giorno dopo giorno, di fuggire da Tortuga. Avete domande per me, Charles de Maure?";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "Ma tu hai avuto parte nel rapimento. E sai dove Levasseur tiene le sue vittime. Dimmi dov’è. E se il peggio non è ancora accaduto – forse, ma solo forse, penserò bene se non vendicarmi di te.";
				link.l1.go = "PZ_ChangShinDontKnow1";
			}
			else
			{
				link.l1 = "Ebbene, tutto sta finalmente andando al suo posto...";
				link.l1.go = "PZ_ChangShin26";
			}
		break;
		
		case "PZ_ChangShinDontKnow1":
			dialog.text = "So perché c’ero anch’io. E se pensi che io sia morbosamente e reciprocamente legata a lui, ti sbagli di grosso. Sarei felice di vedere qualcuno infilzare quel porco allo spiedo.";
			link.l1 = "Non ho tempo, Chang Xing. Dov’è?";
			link.l1.go = "PZ_ChangShinDontKnow2";
		break;
		
		case "PZ_ChangShinDontKnow2":
			dialog.text = "Conosci la prigione sotterranea sotto le strade della città? È lì che devi andare. In uno dei vicoli ciechi troverai una grande botte di vino, e accanto a essa comincia un passaggio segreto verso la sua stanza dei piaceri, come lui ama chiamarla a volte.";
			link.l1 = "Bene, tutto finalmente si sta mettendo insieme...";
			link.l1.go = "PZ_ChangShin26";
		break;
		
		case "PZ_ChangShin26":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip")) StartInstantDialog("Longway", "PZ_Longway_SisterDialog6", "Quest\CompanionQuests\Longway.c");
			else
			{
				dialog.text = "Bene per te. Ora vattene. Per quanto abbia desiderato parlare dopo tutti questi anni, sapere che conosci tutti i miei segreti, sai cosa mi hanno fatto – mi rivolta lo stomaco. Guardarti ormai mi fa solo infuriare. Ah, e Tu resta con me.";
				link.l1 = "Perché mai?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet1";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet1":
			dialog.text = "Forse perché sono la sua famiglia? E perché vedo come si comporta con te – uno sventurato sussurrone, abbattuto, che non ha nemmeno avuto il tempo di imparare bene la lingua e parlare come si deve. Eppure, mi ha detto che eravate amici. Si vede proprio che l’hai cambiato tu. Almeno io farò di lui un vero uomo.";
			link.l1 = "E sei davvero soddisfatto di te stesso? In cosa lo trasformerai? In una creatura crudele e amareggiata che commercia in vite umane?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet2";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet2":
			StartInstantDialog("Longway", "PZ_Longway_SisterDialog_Ubezhdaet3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet3":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				dialog.text = "Mio Signore Capitano, vi prego, fermatevi. Vi chiedo di lasciare mia sorella in pace. E... io resterò con lei.";
				link.l1 = "Tu... cosa? Longway... ma perché? Non vedi in cosa si è trasformata?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet4";
			}
			else
			{
				dialog.text = "Tu sei diverso? Sei cambiato col tempo. In peggio. All’inizio eri gentile e comprensivo. Poi sei diventato sgarbato, peggio persino di Rodenburg. E quando avevo bisogno di una nave decente per inseguire Van der Vink, mi hai rifilato una carretta!";
				link.l1 = "Longway...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet8";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Una volta sono salpato e ho passato tutti questi anni solo per trovare e salvare mia sorella. E ora lei è qui, al sicuro. La mia missione è compiuta. E... Il mio nome è Chang Tu. Longway è il nome datomi dal traditore Van Merden, se te ne fossi dimenticato. Ma Chang Tu è un uomo libero. Il lungo viaggio di Chang Tu è finalmente finito.";
			link.l1 = "Ti renderà uno schiavo come fece una volta Rodenburg. Ti schiaccerà perché siete di sangue. E tu starai così dalla parte di chi ha fatto questo a me e "+sStr+"     tanto dolore?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet5";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "In questo momento sei tu che metti alle strette Chang Tu. Ti prego, lasciami andare. Sono davvero stanco. Sei un brav'uomo, Capitano – che il Cielo ne sia testimone. Ma tu non sei famiglia per me. Lei lo è. Se non resto, allora tutti questi anni saranno stati vani. Ora sarò io la sua stella polare e riaccenderò il suo fuoco spento – caldo e confortante, non una fiamma che consuma ogni cosa al suo passaggio.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				link.l1 = "Hmm, hai ragione. Forse sto forzando troppo adesso. Beh, ti ho sempre rispettato. Ti auguro di ritrovare finalmente tua sorella. Ma ti avverto, con lei non troverai la pace.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva")) 
				{
					pchar.questTemp.PZ_LongwayHochetMira = true;
					link.l1.go = "PZ_Longway_SisterDialog_ReactiaDevushek";
				}
				
			}
			else
			{
				link.l1 = "Non puoi abbandonarmi adesso! Devo ancora salvare "+sStr+" dal Levasseur! Vuoi che ci vada da sola? Aiutami, Longway. E poi ti lascerò andare. Te lo prometto.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet6":
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Posso cavarmela da sola. Non devi più preoccuparti per me. Grazie.";
				link.l1 = "Pare che tua sorella sia furibonda perché abbiamo scelto di separarci senza spargimenti di sangue.";
			}
			else
			{
				dialog.text = "Ci arriverete, Mio Signore Capitano. Siete l’uomo più saggio che abbia mai posato gli occhi. Quell’insetto, che sa solo tormentare le donne, non è nulla per voi. Vi supplico, non costringetemi. Mia sorella ha mille parole da sussurrarmi! E... il mio nome è Chang Tu.";
				link.l1 = "Ti rendi conto che lasciandomi adesso, mi stai tradendo?! E soprattutto restando con lei – la donna che ha dato inizio a tutto questo!";
			}
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet7";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Non temete, Capitano. Anche se parla di me senza rispetto, io sono il fratello maggiore e suo unico parente rimasto. Potete andare. Non la lascerò uccidervi. Addio.";
				link.l1 = "Addio... Chang Tu.";
				DeleteAttribute(pchar, "questTemp.PZ_LongwayRyadom");
				AddDialogExitQuest("PZ_BrothelTeleportVZal");	//Мирно разошлись
			}
			else
			{
				dialog.text = "Ho detto tutto ciò che avevo da dire. Addio, Capitano. E che il vento ti sia favorevole. Chang Tu sarà sempre un uomo libero. Non dimenticarlo.";
				link.l1 = "E questo è ciò che ricevo dopo aver rinunciato a tutto e averti aiutato nella tua dannata ricerca?! Dopo quello che stanno facendo a "+sStr+" adesso?! Sei un traditore, Chang Tu. E morirai come tale, tu e il tuo compare, maledetti serpenti!";
				link.l1.go = "exit";
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				AddDialogExitQuest("MainHeroFightModeOn");
				AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8":
			dialog.text = "Il mio nome è Chang Tu. Longway è morto. L’hai ucciso tu. Non sei più il mio Capitano. E adesso morirai tu. La mia famiglia troverà finalmente pace, e la nostra stella splenderà luminosa nel cielo notturno.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
			{
				link.l1 = "(Affidabile) (Comando) Longway... Chang Tu. Fermati. Lo so che non sono stato il Capitano perfetto per te. Ma vuoi davvero spargermi le budella per questo? Dopo tutto quello che abbiamo passato? Prima Rodenburg, ora la ricerca di tua sorella.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet9";
				notification("Trustworthy", "Trustworthy");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
			}
			else
			{
				link.l1 = "Longway, io sono il tuo Capitano. Non sono la tua famiglia, né la tua balia. Do ordini, non mi preoccupo se ti ho offeso senza volerlo. Rivendichi come fossimo vecchi coniugi, per mille diavoli...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet15";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
			}
			link.l2 = "Sì. Ora lo vedo chiaro. Sei marcio fino al midollo, pensi solo a te stesso... proprio come tua sorella, Longway. La mia famiglia vedrà la luce di domani. La tua - marcirà all'inferno. Vai al diavolo!";
			link.l2.go = "PZ_Longway_SisterDialog_Ubezhdaet8_1";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetFightMode(pchar, true);
			DoQuestCheckDelay("PZ_ChangShinAndLongwayFightMe", 0.5);
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet9":
			dialog.text = "Se devo scegliere tra te e la mia famiglia – sceglierò sempre la famiglia, anche se il cuore mi si spezza, mio Signore Capitano.";
			link.l1 = "Una famiglia che non ha mosso un dito mentre tu la cercavi per tutti questi anni? Ah, ma poi sarebbe arrivato il momento giusto, eh! Io invece ho buttato via tutto per aiutarti. Sei qui, davanti a me, solo per questo. Diavolo, sono più famiglia io per te che lei, amico mio!";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet10";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet10":
			dialog.text = "Hai ragione. Come sempre, hai ragione. Mi perdonerai, Mio Signore Capitano?";
			link.l1 = "Non c’è nulla da perdonare! Hai ragione su una cosa – non sono sempre stato il Capitano che meriti. Direi che ora siamo pari. Dimmi, come preferisci che ti chiami da adesso in poi? Longway? Oppure Chang Tu?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet11";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet11":
			dialog.text = "Che sia Longway. Ormai mi sono abituato che mi chiamate così.";
			link.l1 = "Allora lasciamo perdere ogni diverbio, e bentornato a bordo, Longway.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet12";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet12":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_Ubezhdaet13", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet13":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			dialog.text = "Tu! Che stai blaterando?! Perché ti sei fermato?! Uccidilo! Per lui resterai sempre solo uno schiavo! La tua famiglia sono io, solo io!";
			link.l1 = "È così furiosa, vero, Longway? Non sei più la sua famiglia, Xing. Questo è finito quando hai saputo dell’arrivo di Longway nell’arcipelago e hai scelto di far finta di niente. Ce ne andiamo.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet14";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet14":
			dialog.text = "Credo di non aver mai avuto davvero una possibilità di strappargli quella mentalità da schiavo. Non posso salvarlo. Allora vi ammazzerò entrambi con le mie stesse mani.";
			link.l1 = "Sei tu quello che non può essere salvato, qui. Sai, sono stata fin troppo comprensiva e indulgente con te. Ma questo è persino meglio. Credo che perfino Longway abbia capito che razza di serpe sei. Non piangerà troppo per te.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet15":
			dialog.text = "Non è il momento per scherzi! Nascondi la tua paura e il tuo fallimento dietro queste battute! E questo mi convince ancora di più. Difenditi, de Maure! Perché Chang Tu non ha alcuna intenzione di risparmiarti.";
			link.l1 = "Mi dispiace che sia finita così. Ma se è così che la vuoi, allora sia. In tal caso, non aspettarti nessuna pietà da parte mia.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaDevushek":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_Longway_SisterDialog_ReactiaMary", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Charles, ascolta...";
				link.l1 = "Helene?";
			}
			else
			{
				dialog.text = "Charles, Longway, basta...";
				link.l1 = "Helen, sarebbe meglio se ti mettessi dietro di me, ora. Mi sentirei più sicuro così, nel caso ci attacchino.";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena2":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "I'm so tired; I can hardly stand. I just want to get out of here. We're not going to drag Longway back to the ship if he doesn't want to come, are we? I'll be your navigator and first mate, my Captain. Hopefully, your most trusted and beloved too. Besides, he's got a point - we're not his family. She is, for better or worse.";
				link.l1 = "But what about her? She's the reason you were tortured; it was all her idea. And she's the one who kidnapped you.";
			}
			else
			{
				dialog.text = "Ma non lo faranno, giusto? Andiamocene subito, e basta. Se davvero pensa questo di noi dopo tutto quello che abbiamo fatto per lui, non serve a nulla provare a fargli cambiare idea. I fatti contano più delle parole. Se vuole restare con sua sorella, che resti.";
				link.l1 = "Helen, hai sofferto così tanto a causa sua...";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena3":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Lascia che quella demone resti coi suoi mostri. Presto divoreranno la sua anima. E le nostre meritano finalmente un po’ di pace. Andiamo.";
				link.l1 = "Già. Immagino che dovremmo farlo. Andiamocene da qui, mio angelo. E tu — Longway, o Chang Tu — addio.";
			}
			else
			{
				dialog.text = "Ma non sono morta. E il peggio non è successo. Sono qui, con te, ed è questo che conta. E Levasseur è morto. Senza di lui, lei non è nessuno. Il suo covo va in rovina e presto affonderà. E loro affonderanno con lui. Andiamo, mio capitano. Qui non c’è più niente da fare per noi.";
				link.l1 = "Non discuterò, Helen.";
			}
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena4":
			StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena5":
			dialog.text = "Dove stai andando?";
			link.l1 = "Cosa c’è, ti sorprende che non abbiamo voglia di sventrare te e tua sorella, Longway? Ecco la differenza tra noi. E tu ancora pensi che io sia il cattivo... Ma va bene, ascolta. Se vuoi ammazzarmi, dovrai farlo anche con Helen. Lei è ferita, sanguina. Vuoi davvero questo?";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena6":
			dialog.text = "Mh-mh.";
			link.l1 = "Vedo il dubbio nei tuoi occhi, anche se non ti mancano motivi per odiarmi. Ma prendiamo esempio da Helen, d'accordo? Nessuno nella nostra ciurma è più gentile o capace di perdonare di lei. Ce ne andiamo. E se dentro di te c'è rimasto un briciolo di bontà o di senno, non ci ostacolerai.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena7";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena7":
			dialog.text = "Sia come vuoi. Chiedo venia. Ma tu non sei più il mio Capitano.";
			link.l1 = "Me la caverò in qualche modo. Auguro il meglio a te e a tua sorella, nonostante ciò che ha fatto. Addio, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary":
			dialog.text = "Forza, Charles, è l’ora di schiacciare questa rivolta.";
			link.l1 = "Dio solo sa che non volevo farlo... e ancora adesso non lo voglio.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary2":
			dialog.text = "Non lo fai?! Charles, ascoltami. Hai fatto così tanto per lui, e cosa hai ricevuto in cambio? Tradimento e parole cattive, giusto! Davvero vuoi lasciar correre così?";
			link.l1 = "Non voglio spargere il sangue di Longway. Non ho dimenticato che un tempo eravamo amici.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary3":
			dialog.text = "Al diavolo amici così – sono peggio dei nemici, giusto! Charles, guardami. Guarda cosa mi è successo... tutto per colpa di sua sorella, che mi ha derisa, insultata e umiliata durante il viaggio verso quest’isola maledetta!";
			link.l1 = "Mary, capisco – sei davvero, davvero furiosa in questo momento, giusto?";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary4";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary4":
			dialog.text = "Oh no, Charles, non sono solo arrabbiata, no... sono furiosa! E non solo per quello che quel miserabile bastardo ti ha detto! Guardami ancora, Charles—e immagina quante altre ragazze dovranno passare tutto questo, se non lo fermiamo. Qui e ora.";
			link.l1 = "Non faranno più del male a nessuno. Levasseur è morto.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary5";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary5":
			dialog.text = "Charles, hai davvero ascoltato le bestemmie che ha tirato fuori quella lì? È colpevole quanto quel porco puzzolente per tutto ciò che è successo in quella cantina. E ora guarda Longway – o come diavolo si fa chiamare adesso. Hai visto con che velocità lei l’ha tirato dalla sua parte, giusto? Chissà quali altre schifezze riuscirà a ficcargli in testa a quel traditore. Pensi davvero che quella strega farà fatica a spingerlo sulla strada di Levasseur? Non pensare a cosa sia adesso, Charles. Immagina che razza di bestia potrebbe diventare tra un anno... o magari anche solo tra un mese. Lo sai che ho ragione, giusto?";
			link.l1 = "Per quanto mi dispiaccia ammetterlo, non ho nulla da obiettare, Mary...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary6":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_ReactiaMary7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary7":
			dialog.text = "Ah-ah-ah! Che spettacolo, davvero. Da tempo non ridevo così di gusto. E poi, ha fegato, devo ammetterlo.";
			link.l1 = "Taci quella bocca, puttana.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary8";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary8":
			dialog.text = "Divertente, vero, de Maure? Mi piacerebbe vedere Tu farti a pezzi con le mie stesse mani. E la tua donna è assetata di sangue quanto me. Benissimo. Non resterò a guardare — mi sono addestrato con Levasseur e con le canaglie più feroci di Tortuga. Vediamo quale coppia resta in piedi.";
			link.l1 = "Non hai avuto un gran maestro. E hai fatto arrabbiare Mary. Sei spacciato. Anche se io non fossi qui, tu e il tuo compare non avreste alcuna speranza contro di lei.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog6":
			dialog.text = "Sì. Finalmente. Longway può parlare ancora con sua sorella, Mio Signore Capitano? Solo per poco.";
			link.l1 = "Certo. Ma sbrigati – il tempo stringe.";
			link.l1.go = "PZ_Longway_SisterDialog7";
		break;
		
		case "PZ_Longway_SisterDialog7":
			dialog.text = "Longway, fallo in fretta.";
			link.l1 = "Bene.";
			link.l1.go = "PZ_Longway_SisterDialog7_1";
		break;
		
		case "PZ_ChangShin26":
			StartInstantDialog("СhangShin", "PZ_Longway_SisterDialog7_1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog7_1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "E cosa volevi dirmi, fratello mio?";
			link.l1 = "Quel Longway è molto deluso da te, Xing.";
			link.l1.go = "PZ_Longway_SisterDialog8";
		break;
		
		case "PZ_Longway_SisterDialog8":
			dialog.text = "(In Mandarino) Perché non parli la nostra lingua, visto che volevi ricominciare la conversazione, Tu? Ti vergogni di lui? Se fossi in te, mi vergognerei di più per il tuo accento.";
			link.l1 = "No. Longway non tiene più segreti da Mio Signore Capitano. Non più.";
			link.l1.go = "PZ_Longway_SisterDialog9";
		break;
		
		case "PZ_Longway_SisterDialog9":
			dialog.text = "(in francese) Prima Rodenburg, ora de Maure. Hai sempre bisogno di un ‘monsieur’. In oltre una dozzina d’anni qui non hai concluso nulla. Non riesci nemmeno a imparare una delle loro lingue. E sono molto più semplici della nostra! Se qualcuno è una delusione, quello sei tu.";
			link.l1 = "Ma io non traffico in donne. Non partecipo al loro rapimento né alle loro torture.";
			link.l1.go = "PZ_Longway_SisterDialog10";
		break;
		
		case "PZ_Longway_SisterDialog10":
			dialog.text = "Parli sul serio? Vuoi che elenchi le tue prodezze per Rodenburg? Quello che ho fatto io sarebbe roba da bambini in confronto.";
			link.l1 = "Avevo uno scopo – trovarti. Ma tu nemmeno volevi vedermi. E quando ti ho trovata, ho visto un mostro, non la calda stella che un tempo illuminava la mia strada.";
			link.l1.go = "PZ_Longway_SisterDialog11";
		break;
		
		case "PZ_Longway_SisterDialog11":
			dialog.text = "Un mostro? Beh, forse hai ragione. Non sono più la ragazza allegra che conoscevi. Se fossi rimasta così, la vita mi avrebbe già masticata e sputata. Ho dovuto farmi i denti da sola. La mia stella si è spenta da tanto tempo. Ma sono ancora tua sorella, Tu.";
			link.l1 = "No. Tu non sei più mia sorella.";
			link.l1.go = "PZ_Longway_SisterDialog12";
		break;
		
		case "PZ_Longway_SisterDialog12":
			dialog.text = "Mi abbandoni così facilmente dopo tutti questi anni? Eh... E chissà, forse sarei ancora lo stesso se fossi tornato a casa in tempo per far fuori Fermentelos quel giorno?";
			link.l1 = "Hai ragione. È anche in parte colpa mia. È una mia responsabilità. E la farò finita. Ti darò pace. Metterò fine a questa misera esistenza.";
			link.l1.go = "PZ_Longway_SisterDialog13";
		break;
		
		case "PZ_Longway_SisterDialog13":
			dialog.text = "Davvero vuoi uccidere tua sorella, Chung Tu? Non che tu ci riesca, ma il fatto resta...";
			link.l1 = "Tu non sei più mia sorella. Xing è morta dieci anni fa. E oggi è il giorno in cui Chung Tu trova la sua fine, per sempre. D’ora in avanti, il mio nome sarà... Longway.";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_FlagMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Prima di tutto, salviamo Chang Xing.";
			link.l1 = "Cosa?! Non mi pare che tu abbia capito, amico mio. Tua sorella non è in pericolo imminente, ma "+sStr+" è. E devo forse rammentarti che anche Chang Xing porta il suo carico di colpe, proprio come Martene e Thibaut?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Non è vero! Lei è...";
			link.l1 = "Hai la minima idea di cosa Levasseur potrebbe star facendo a "+sStr+" mentre stiamo qui a litigare?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_3";
		break;
		
		case "PZ_Longway_FlagMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ma Chang Xing è tutto ciò che mi resta, Capitano... La vostra famiglia è ancora intera...";
			link.l1 = +sStr+"  forse non è mia moglie, ma mi è cara come il sangue del mio sangue.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_4";
		break;
		
		case "PZ_Longway_FlagMartinInfo_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing è la mia ultima stella che mi guida, Mio Signore Capitano. E poi, mi devi ancora qualcosa per aver strappato quella confessione a Robert Marten.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "Andremo a cercare tua sorella, lo prometto. Ma Levasseur non le ha messo un dito addosso per tutto questo tempo. "+sStr+" è in pericolo ben peggiore di Chang Xing. Aiutami a salvarla prima, e ti sarò debitore per tutta la vita.";
				link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
				{
					if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
					{
						link.l1 = "(Fidato) (Comando) Andremo a cercare tua sorella, te lo prometto. Ma Levasseur non l'ha mai sfiorata in tutto questo tempo. "+sStr+" è in pericolo ben più grave di Chang Xing. Aiutami a salvarla prima, e ti sarò debitore per la vita intera.";
						link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
						notification("Trustworthy", "Trustworthy");
						notification("Skill Check Passed", SKILL_LEADERSHIP);
					}
					else
					{
						link.l1 = "Ascoltami! Tua sorella è al sicuro. Ma "+sStr+" è ora nelle grinfie d’un porco, che potrebbe torturarla proprio in questo momento – o peggio! Davvero credi che Levasseur lascerebbe a tua sorella un locale tanto distinto, se la trattasse come le altre povere disgraziate del suo sotterraneo?";
						link.l1.go = "PZ_Longway_FlagMartinInfo_netVD1";
						if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
						if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
					}
				}
			}
			link.l2 = "Non sprecherò il mio tempo in discussioni inutili. Ognuno di noi ha le proprie priorità. Separiamoci di nuovo. Che il mio Dio mi assista e il tuo protegga te.";
			link.l2.go = "PZ_Longway_FlagMartinInfo_Razdelimsya";
			link.l3 = "Hai ragione. Ti devo un favore. Va bene, facciamo come vuoi tu. Inoltre, senza di te forse non ce la farei contro Levasseur e la sua feccia. Ma se succede qualcosa a "+sStr+" mentre ci occupiamo di tua sorella... ";
			link.l3.go = "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya";
		break;
		
		case "PZ_Longway_FlagMartinInfo_Razdelimsya":
			dialog.text = "Grazie per la comprensione, Mio Signore Capitano. Che la sorte vi assista!";
			link.l1 = "E a te, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya":
			dialog.text = "Minacce vuote non spaventano nessuno, Mio Signore Capitano. Dobbiamo muoverci, così arriveremo in tempo per tutto.";
			link.l1 = "Spero che il tuo Dio abbia orecchie per ascoltare. Andiamo!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_Longway_FlagMartinInfo_netVD1":
			dialog.text = "Per rispetto, Mio Signore Capitano, questa volta chiudo un occhio. Ma solo questa volta. La prossima ti colpirò. Ora vado a cercare mia sorella, con o senza il tuo permesso.";
			link.l1 = "Non sprecherò altro tempo a discutere con te, Longway. Alla fine, tutti noi abbiamo qualcosa che custodiamo più di ogni altra cosa.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie":
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD1":
			dialog.text = "Mm-hmm, va bene, Mio Signore Capitano. Ma allora dobbiamo sbrigarci.";
			link.l1 = "Giusto. Grazie, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_VD2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD2":
			pchar.questTemp.PZ_LongwayRyadom = true;
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_TortureRoom_Levasser_1":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Vediamo un po’, chi diavolo abbiamo qui... Maledizione. Charles de Maure e il suo bastardo dagli occhi a fessura.";
				link.l1 = "Qui c’è solo un cane bastardo. Vuoi vederlo? Guardati nello specchio, bastardo ugonotto. Oppure dai un’occhiata a tuo nipote. Anche se lui somiglia più a un topo rognoso.";
				link.l1.go = "PZ_TortureRoom_Levasser_2";
			}
			else
			{
				dialog.text = "Ti avevo detto di non scocciarmi! Ah, Charles de Maure, hehehe. Che fastidioso insetto sei, eh.";
				link.l1 = "È così che sono fatta. Ora chiudi quella maledetta bocca e...";
				link.l1.go = "PZ_TortureRoom_Levasser_1_1";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne") || CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo") || CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal")) Achievment_Set("ach_CL_130");
			}
			locCameraSleep(true);
			sld = CharacterFromID("Tibo");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_1_1":
			dialog.text = "Non sei sulla tua nave, cucciolo! Su quest’isola c’è un solo uomo, ed è il sottoscritto!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
		break;
		
		case "PZ_TortureRoom_Levasser_2":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_3":
			dialog.text = "Come osi, feccia!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_4";
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_4":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_5":
			dialog.text = "Calmati, figliolo! Monsieur de Maure sta per ricevere una lezione di buone maniere.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_6":
			if (!CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Ti ho forse dato il permesso di strillare?!";
			}
			else
			{
				dialog.text = "Dove si è spento tutto quel fuoco, eh, bella mia? Ah, credo di aver capito...";
			}
			link.l1 = "Lasciala stare, bastardo!";
			link.l1.go = "PZ_TortureRoom_Levasser_7";
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Mary"));
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Helena"));
		break;
		
		case "PZ_TortureRoom_Levasser_7":
			dialog.text = "Heh-heh-heh... Puoi urlare e insultarmi quanto ti pare, ma ti vedo tremare come una foglia nella tempesta. Vedo il terrore nei tuoi occhi. Tu e Henri avete questo in comune. Senza offesa, nipote.";
			link.l1 = "Hai ragione, è paura. Ma non di te, feccia.";
			link.l1.go = "PZ_TortureRoom_Levasser_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_7_1":
			dialog.text = "Ma certo, ma certo. Tutto già sentito – che tu non hai paura di nessuno, de Maure. Me l'ha detto lei. ‘O-oh, Charles verrà, Charles mi salverà... Charles di qua, Charles di là...’ Beh, Charles è arrivato. Charles ha il posto migliore in prima fila. Henri, fai sentire il nostro ospite... a casa sua.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_8";
		break;
		
		case "PZ_TortureRoom_Levasser_8":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_9", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_9":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Non ce n’è bisogno, zio. Temo che stavolta tu abbia davvero esagerato...";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Zio, avrò bisogno del tuo aiuto per questa faccenda...";
				}
				else
				{
					dialog.text = "Devo finirlo subito, zio, oppure lasciargli vedere prima lo spettacolo?";
				}
			}
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_10";
			LAi_SetActorType(npchar);
			//LAi_ActorTurnToCharacter(npchar, CharacterFromID("Levasser"));
			LAi_ActorTurnToLocator(npchar, "goto", "goto8");
			locCameraFromToPos(-15.67, 2.57, -1.23, true, -17.49, 1.42, -3.26);
		break;
		
		case "PZ_TortureRoom_Levasser_10":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_11", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_11":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Non sono stata io, è stato il nostro cavaliere bianco qui presente che ci ha messo una vita ad arrivare in soccorso. Sembra che lo spettacolo sia finito, ah-ah-ah-ah!";
				link.l1 = "Dio, no...";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Me l’aspettavo. Come hai fatto ad arrivare vivo a quest’età? E comunque, stessa domanda per te, de Maure.";
					link.l1 = "Non hai la minima idea di quante domande ho per te, macellaio!";
				}
				else
				{
					dialog.text = "Vorrei che la nostra piccola recita avesse spettatori... Ma dubito che Monsieur Testardo qui ci concederà questo piacere.";
					link.l1 = "L’unico piacere che avrà qualcuno qui sarà il mio, sventrandoti come il porco che sei, macellaio!";
				}
				link.l1.go = "PZ_TortureRoom_Levasser_14";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				locCameraFromToPos(-16.74, 2.58, -0.51, true, -13.13, -0.72, 2.49);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
			{
				locCameraFromToPos(-18.38, 1.77, 2.73, true, -20.53, 0.01, 0.32);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
			{
				locCameraFromToPos(-16.97, 2.09, 3.98, true, -20.02, -0.17, 2.28);
			}
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_12":
			dialog.text = "Forza, avanti, prendila in braccio! Ah-ah-ah!";
			link.l1 = "Maledetti bastardi, vi farò rimpiangere d'essere venuti al mondo!";
			link.l1.go = "PZ_TortureRoom_Levasser_13";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_13":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				Return_LongwayOfficer();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PZ_TortureRoom_Levasser_DevushkaMertva5");
		break;
		
		case "PZ_TortureRoom_Levasser_14":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Macellaio? Io mi considero più un artista, un pittore... almeno potresti provare a vedere la cosa come arte... Guarda.\nTi piace il mio lavoro? Una vera opera d’arte, questa. A dirla tutta, preferisco le bionde, ma lei... alla fine le ho perdonato quel colore di capelli così brutto. Non era solo quello – la ragazza era fuoco vivo! Ho rischiato di scottarmi. Si è battuta, ha morso, ringhiava come una bestia selvaggia! Mi ha ricordato una selvaggia dalla pelle rossa, con cui mi sono divertito parecchio, anche se non per molto...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Macellaio? Io mi considero più un artista, un pittore – potresti almeno provare a guardarla come arte... Osserva.\nVedi, non ho ancora finito con lei – su questa tela c’è ancora tanto spazio vuoto. Non solo è bellissima, ma dura come la roccia e fredda come il ghiaccio. Ho dovuto persino sudare un po’ per farla gridare. Ha resistito fino alla fine, solo per non concedermi il piacere di sentire la sua dolce voce.";
			}
			link.l1 = "Lasciala subito, bastardo degenerato.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya13");
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_15":
			dialog.text = "Dove pensi di andare? Questo pezzo di carne ormai è roba mia. Come tutto ciò che gli sta intorno – questa città, questa fortezza... Io sono Tortuga. E tu e Poincy, quel vecchio tacchino puzzolente, non cambierete mai nulla.";
			link.l1 = "Levasseur, tu...";
			link.l1.go = "PZ_TortureRoom_Levasser_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_16":
			dialog.text = "Per voi è il Signor de René de Buaduflé de Lettre.";
			link.l1 = "Non me ne frega un accidente. Sfodera la lama e mostrami cosa vali davvero in battaglia – contro un uomo, non contro una povera ragazza indifesa.";
			link.l1.go = "PZ_TortureRoom_Levasser_17";
		break;
		
		case "PZ_TortureRoom_Levasser_17":
			dialog.text = "E che uomo sei! Ma hai ragione, anch’io sono stufo di tutte queste chiacchiere. Voglio tornare dalla mia dama... Ma ti farò un’ultima domanda. Come sei arrivato qui? Chi ha spifferato dove si trova questo posto? Solo una manciata di persone lo conosce.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "Il vostro amico comune, Martene, ha cantato come un usignolo. Anzi, a dire il vero, ha strillato più come un porco al macello...";
				link.l1.go = "PZ_TortureRoom_Levasser_FlagMartinInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo"))
			{
				link.l2 = "Forse è meglio tenertelo nascosto. Temo possa ferire il tuo orgoglio, Signor de René... qualcosa del genere.";
				link.l2.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l3 = "Una delle tue vittime, Levasseur.";
				link.l3.go = "PZ_TortureRoom_Levasser_FlagShinInfo_1";
			}
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_1":
			dialog.text = "Bugiarro, mascalzone! Nessuno esce vivo da queste mura!";
			link.l1 = "Usa la tua memoria, avanti. Ce n’era uno. Chang Xing.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagShinInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_2":
			dialog.text = "Impossibile. Non lei. Alcune delle mie trovate più nere sono nate proprio grazie a quella diavoletta. Oh-oh, ci siamo istruiti a vicenda, eh eh. Alla fine ha deciso di pentirsi? Ne dubito. Gliel’ho strappata via l’anima tanto tempo fa!";
			link.l1 = "Ora ti svuoterò fino all’osso. Una goccia dopo l’altra.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMartinInfo_1":
			dialog.text = "E tu osi chiamarmi macellaio, miserabile ipocrita! Eh-eh... Ma finché lui brucia all’Inferno, io non ho nulla da temere.";
			link.l1 = "Vi aspetta laggiù. E anche quel tuo nipote, farabutto com’è. Non deludiamolo, eh.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1":
			dialog.text = "Che ne dici se rovino ancora un po’ questo giocattolo? Le apro il ventre o la gola, e la guardo dissanguarsi mentre tu cerchi di raggiungerla...";
			link.l1 = "Qualunque cosa tu dica, Levasseur, qualunque cosa... Tua moglie ti manda i suoi saluti. E con quelli, un inchino d’addio.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2":
			dialog.text = "COSA?! Kha-kha... Maledetta Marceline... Miserabile puttana, puttana, puttana, puttana!";
			link.l1 = "Proprio così. Siete fatti l’uno per l’altra. Lei però ha la testa sulle spalle, almeno a prima vista.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3":
			dialog.text = "Le metterò la testa di gallina su una picca. Ma prima... oh-oh, molte, molte cose capiteranno a quella sgualdrina... Persino il mio nuovo giocattolo avrà un po' di tregua. Aspetta! Ho un’idea migliore. La presterò a Henri. Solo per un po’, s’intende.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5":
			dialog.text = "Davvero? Grazie, zio!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6";
			CharacterTurnByChr(npchar, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7":
			dialog.text = "Meritatelo prima – dammi una mano con questa faccenda, eh?";
			link.l1 = "Sta per perdere la testa.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
			CharacterTurnByChr(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_Bitva":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				Return_LongwayOfficer();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
			LAi_SetImmortal(sld, true);
			
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_Etap6TortugaPytochnaya19");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		
		case "PZ_TortureRoom_Longway_1":
			dialog.text = "Mio Signore Capitano... Longway porge le sue condoglianze. Abbiamo fatto tutto ciò che era in nostro potere.";
			link.l1 = "Non tutto, neanche lontanamente abbastanza.";
			link.l1.go = "PZ_TortureRoom_Longway_2";
		break;
		
		case "PZ_TortureRoom_Longway_2":
			dialog.text = "Longway andrà a cercare Chang Xing. Verrete con me, Mio Signore Capitano?";
			link.l1 = "Va bene, vengo con te, Longway. Ma ricorda: anche tua sorella ha avuto un ruolo bello grosso in questo macello di sangue. Dovrà sudare parecchio per farmi cambiare idea e risparmiarla. E tu non le darai certo una mano. Su, muoviamoci, è ora di mettere fine a tutto questo.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Longway_3":
			DialogExit();
			Return_LongwayOfficer();
			chrDisableReloadToLocation = false;
		break;
		
		case "PZ_TortureRoom_Devushka_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Charles, lo sapevo, giusto! Sapevo che saresti arrivato! Lo fai sempre, vero?";
					link.l1 = "Non vorrei metterlo alla prova per la quarta volta, Mary... Quei mascalzoni, loro...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Oh, Mio Capitano, non immagini quanto arrivi a proposito. Quei... quei mostri...";
					link.l1 = "È finita, Helen. Va tutto bene, è tutto finito. Santo cielo, cosa ti hanno fatto...";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Charles, sei qui! Lo sapevo, lo sapevo, giusto!";
					link.l1 = "Correvo a vele spiegate, cercando di salvarmi la pelle, Mary. Tu... loro ti hanno...?..";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Mio Capitano... Siete qui... Avevo quasi perso ogni speranza...";
					link.l1 = "Sono arrivato il più in fretta possibile, Helen. Mi dispiace per tutto questo tempo.";
				}
				locCameraFromToPos(-15.32, 1.24, 1.31, true, -14.25, -1.00, -1.50);
			}
			link.l1.go = "PZ_TortureRoom_Devushka_2";
		break;
		
		case "PZ_TortureRoom_Devushka_2":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "No, Charles, no. Ci hanno provato, ma li ho respinti come meglio potevo. Ecco perché mi hanno conciata così male... Per favore, Charles, andiamocene via di qui... giusto?";
					link.l1 = "Subito, mia cara. Un’ultima faccenda da sbrigare.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Non l’hanno fatto loro, Charles! No, non l’hanno fatto. Il resto guarirà. Ti prego, portami via da questo posto.";
					link.l1 = "Ma certo, mia cara. Resta solo una cosa da fare qui.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "No, Charles, no. Ci hanno provato, ma sei arrivato proprio in tempo. Come quella volta. Quante volte ormai, eh?";
					link.l1 = "Non li ho mai contati, Mary. E mai lo farò.";
					link.l1.go = "PZ_TortureRoom_Devushka_2_1";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Sei arrivato... proprio in tempo. Il peggio non è successo. Ora, ti prego, andiamocene via da qui. Ovunque, purché lontano.";
					link.l1 = "Alzati, Helen. Sali di sopra. Devo occuparmi prima di questo lurido bastardo.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
		break;
		
		case "PZ_TortureRoom_Devushka_2_1":
			dialog.text = "E non smetterò di contare mai. Ora andiamocene da questo posto, ve ne prego.";
			link.l1 = "Ma certo, mia cara. Qui non ci resta più nulla da fare. Tranne una cosa.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Devushka_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) AddPassenger(pchar, npchar, false);
			LAi_SetPlayerType(pchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		break;
		
		case "PZ_TortureRoom_Levasser_18":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "E allora, kha-kha, non hai le palle, moccioso? Chiedi al tuo porco dal culo giallo di darti una mano...  Oppure fallo da solo, così potrai raccontare a Poincy quanto sei coraggioso.";
				link.l1 = "Preferirei raccontare a tutti che razza di codardo di merda sei stato, piuttosto.";
			}
			else
			{
				dialog.text = "Cosa, vuoi davvero guardarmi mentre dissanguo fino alla morte? Ti sta piacendo, eh? Racconterai alla tua donna che eroe sei stato. Vedi quello scheletro lassù sul muro? La moglie del banchiere di Santiago... Anche il suo uomo si credeva un eroe, ma alla fine era solo bravo a urlare – quando l’ho fatto girare su quella ruota...";
				link.l1 = "Potrei rotolare la tua carcassa sopra, lurido, ma temo che il peso del tuo culo la sfonderebbe.";
			}
			link.l1.go = "PZ_TortureRoom_Levasser_19";
		break;
		
		case "PZ_TortureRoom_Levasser_19":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Codardo? Oh, kha-kha, andiamo...";
				link.l1 = "La crudeltà non è l’opposto della codardia. Ma uno come te non saprebbe mai la differenza.";
				link.l1.go = "PZ_TortureRoom_Levasser_20";
			}
			else
			{
				dialog.text = "Molto astuto. Ricorda le mie parole, de Maure: morirai proprio come quel gran pezzo grosso, con la gola spezzata dalle tue stesse urla e le orecchie sorde dal pianto dei tuoi...";
				link.l1 = "Brucia all’Inferno, feccia.";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
			}
		break;
		
		case "PZ_TortureRoom_Levasser_20":
			dialog.text = "Eh, non sono certo un gran filosofo, lo ammetto. Vedi quello scheletro appeso al muro, de Maure? È tutto ciò che resta della moglie del banchiere di Santiago. Anche lui amava fare il gradasso, ma tutto finisce quando cominci a torcergli il corpo sulla ruota. Poi rimane solo l'urlo, che quasi mi ha reso sordo...";
			link.l1 = "Sbrighiamocela e basta.";
			link.l1.go = "PZ_TortureRoom_Levasser_21";
		break;
		
		case "PZ_TortureRoom_Levasser_21":
			StartInstantDialog("Longway", "PZ_TortureRoom_Levasser_22", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_22":
			dialog.text = "Aspetta un momento, Mio Signore Capitano... Non avere tanta fretta.";
			link.l1 = "Che succede, Longway?";
			link.l1.go = "PZ_TortureRoom_Levasser_23";
		break;
		
		case "PZ_TortureRoom_Levasser_23":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Non ucciderlo. Troppo facile. Merita qualcosa di molto peggiore.";
			link.l1 = "Sei furioso per tua sorella, amico mio. E io ribollo d’ira per quello che lui le ha fatto "+sStr+"... e cosa avrebbe potuto farle. Ma io non sono una bestia come lui. Potrei bruciarlo con i carboni di quel braciere, spezzargli le ossa su quella ruota... Potrei incatenarlo e lasciarlo crepare dissanguato. Ma non posso rischiare che qualche suo sgherro venga a salvarlo. Non posso permettermi quel rischio.";
			link.l1.go = "PZ_TortureRoom_Levasser_24";
		break;
		
		case "PZ_TortureRoom_Levasser_24":
			dialog.text = "Aspetta, Mio Signore Capitano. Non era questo che intendevo. Sto parlando di Poincy.";
			link.l1 = "E di lui che ne pensi?";
			link.l1.go = "PZ_TortureRoom_Levasser_25";
		break;
		
		case "PZ_TortureRoom_Levasser_25":
			dialog.text = "Pensa a come ti ricompenserebbe se gli portassi questa bestia viva. Ti riempirebbe di dobloni. E quello stronzo preferirebbe crepare qui che marcire in una segreta a Capsterville.";
			link.l1 = "Potresti aver ragione, Longway. Ma non so cosa sia successo davvero tra questo bastardo e il Cavaliere. Fidati, conosco questa feccia meglio di te. Se si tratta solo di denaro, come dicono, quei due potrebbero trovare un accordo. Poincy potrebbe lasciarlo andare, e un’altra stanza come questa potrebbe spuntare su qualche altra isola o magari in una città del Vecchio Mondo.";
			link.l1.go = "PZ_TortureRoom_Levasser_26";
			link.l2 = "Non è una cattiva idea, Longway. Dubito però che il Cavaliere sarà tanto generoso... Non è proprio nel suo sangue. Ma per me, non si tratta di soldi. Su, sollevalo! E fascia le sue ferite, così non crepa prima del dovuto.";
			link.l2.go = "PZ_TortureRoom_Levasser_28";
		break;
		
		case "PZ_TortureRoom_Levasser_26":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_27", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_27":
			dialog.text = "Ma prima, vengo a prenderti. E il tuo compare. Non ti sfiorerò, uomo dagli occhi stretti – non vali il tempo che sprecherei.";
			link.l1 = "Vedi, Longway? Tutto questo deve finire adesso. Qui e ora.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
		break;
		
		case "PZ_TortureRoom_Levasser_28":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_29", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_29":
			dialog.text = "Aspetta un momento, Capitano, aspetta un momento, kha-kha.";
			link.l1 = "Che succede, Monsieur ex-governatore?";
			link.l1.go = "PZ_TortureRoom_Levasser_30";
		break;
		
		case "PZ_TortureRoom_Levasser_30":
			dialog.text = "La mia chiave è qui da qualche parte in questa stanza. Apre uno scrigno nel mio ufficio. Ci sono duecentomila in argento e una lama pregiata. Se non basta, nella camera di mia moglie, nel comò, c’è una raccolta di gemme preziose.";
			link.l1 = "Hmm, e cosa vuoi in cambio, eh?";
			link.l1.go = "PZ_TortureRoom_Levasser_31";
		break;
		
		case "PZ_TortureRoom_Levasser_31":
			dialog.text = "Una pallottola. Finiscimi. Qui e adesso.";
			link.l1 = "E il Chevalier de Poincy? Ho sentito che siete vecchi amici... Non vuoi incontrarlo?";
			link.l1.go = "PZ_TortureRoom_Levasser_32";
		break;
		
		case "PZ_TortureRoom_Levasser_32":
			dialog.text = "All’inferno Poincy! Allora, sei d’accordo o no?";
			link.l1 = "Non proprio, Monsieur de... Non ho voglia di snocciolare tutto il vostro nome.";
			link.l1.go = "PZ_TortureRoom_Levasser_33";
		break;
		
		case "PZ_TortureRoom_Levasser_33":
			dialog.text = "Non ti basta, eh? Va bene, c’è dell’altro...";
			link.l1 = "Le urla delle tue vittime ti hanno reso sordo, Levasseur. Te l’ho già detto, non si tratta dell’oro. Hai paura di Poincy, e non senza motivo, eh? Non voglio nemmeno sapere cosa ti farà quello. Ma se servirà almeno un po’ come punizione per la tua... arte, che sia così.";
			link.l1.go = "PZ_TortureRoom_Levasser_34";
			pchar.questTemp.PZ_LevasserPlenen = true;
			pchar.questTemp.PZ_LevasserPobezhden = true;
		break;
		
		case "PZ_TortureRoom_Levasser_34":
			dialog.text = "Dunque è questa la tua vera natura, kha-kha... Non vali più di me.";
			link.l1 = "Basta. Longway - alzalo!";
			link.l1.go = "PZ_TortureRoom_Levasser_35";
		break;
		
		case "PZ_TortureRoom_Levasser_35":
			DialogExit();
			
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1 = "locator";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.location = "Tortuga_Torture_room";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator_group = "reload";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator = "reload1";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition = "PZ_TortureRoom_Levasser_ObratnoNaBereg";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) Return_LongwayOfficer();
			sld = CharacterFromID("Levasser");
			sld.location = "None";
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "La nostra nave... non avrei mai pensato di essere così felice di rivederla... giusto? Finalmente, quest’incubo è finito.";
				}
				else
				{
					dialog.text = "È finalmente finita. Dove andiamo ora, Charles?";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "Non riesco a credere che sia davvero finita... E adesso che facciamo, mio Capitano?";
				}
				else
				{
					dialog.text = "Ecco fatto, mio Capitano. E adesso che facciamo?";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l1 = "Ahimè, non è ancora finita. Chang Xing... Questa storia finirà solo quando avrò strappato da lei le risposte che cerco.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Rotta su Capsterville. È giunta l’ora che Monsieur Levasseur diventi solo un ricordo nella storia.";
				}
				else
				{
					link.l1 = "La missione del Cavaliere è compiuta. Devo riferirglielo. Eviterò certi dettagli, però. Spero solo che mantenga la parola e Michel venga liberato...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Anch'io, giusto? Quindi vengo con te. E non provare nemmeno a discutere con me, Charles.";
				link.l1 = "Mary, cara, hai bisogno di riposare. Sei a un soffio dallo svenire, giusto?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Verrò con voi.";
				link.l1 = "Helen, sei quasi finita nelle grinfie di quel demonio. Riesci a malapena a reggerti in piedi...";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Ho bisogno di te, Charles. E tu hai bisogno di me. E se qualcuno sviene stanotte, sarà Chang Xing. Sulla lurida pavimentazione del suo bordello, con una pallottola tra gli occhi!";
				link.l1 = "Già, Levasseur non è riuscito a spegnere il fuoco che hai dentro. Ti rimanderei alla nave, ma so che mi seguiresti comunque...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ma posso ancora impugnare una lama. Charles, devo esserci anch’io. Devo capire cosa l’ha spinta a farlo. Capisci perché è così importante per me?";
				link.l1 = "Capisco che avete bisogno di riposo e di cure. E di un bel po’, per giunta.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Mi conosci troppo bene, Charles, giusto. Quindi basta chiacchiere e finiamola qui.";
				link.l1 = "Come vuoi tu. Ma resta all'erta. Nessuno sa quali sorprese ci attendano là fuori.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Può aspettare. Sei venuto per me, adesso vengo con te. Che tu lo voglia o no.";
				link.l1 = "Vedo che hai ancora fegato, Helen. Bene. Stai dietro di me e, per l'amor di Dio, fa' attenzione.";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SDevushkoyKShin");
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_1":
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "La nostra nave... Non ci credo che la salirò di nuovo, giusto...";
					link.l1 = "Ti sta aspettando, Mary. Un pasto caldo e un letto soffice pure...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ugh... Non credevo di riuscire a salire sulla barca con le mie gambe.";
					link.l1 = "Sei la persona più tenace che abbia mai conosciuto, Helen. Ora entra dentro e poi a letto...";
				}
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "La nostra nave... Non posso credere che ci salirò di nuovo, giusto...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ugh... Non pensavo che sarei riuscito a salire sulla barca con le mie sole gambe.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Rotta su Capsterville. È giunta l’ora che monsieur Levasseur diventi solo un ricordo nella storia.";
				}
				else
				{
					link.l1 = "La missione dello Chevalier è compiuta. Devo riferirglielo. Certi dettagli li terrò per me, però. Spero solo che mantenga la parola e Michel venga liberato...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "E tu, Charles... Che sguardo hai? Stai tramando qualcosa di nuovo, vero?";
				link.l1 = "Chang Xing. Devo raggiungerla anch’io.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "E tu? Dove stai andando?";
				link.l1 = "Per vedere Chang Xing. Ella è l’ultimo capitolo di quest’incubo.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Allora vengo anch’io! Lei mi deve un favore grosso, giusto?";
				link.l1 = "Mary, cara, sei arrivata a malapena alla barca. E adesso non riesci nemmeno a tenere una lama in mano. Farò pagare a quella donna tutto ciò che ti ha fatto, lo giuro su Dio. Ma mi sentirò molto meglio se resti sulla nave, sapendo che sei al sicuro.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mio Capitano, vorrei tanto venire con te... Ti prego, fa' attenzione. Chi può dire cos'altro sia capace di fare? Mi teneva ferma mentre quel cucciolo di Thibaut...";
				link.l1 = "Il peggio è passato, Helen. Presto tutto finirà, te lo prometto.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Beh, almeno Longway veglierà su di te mentre non ci sono. Ma se ti succede qualcosa, giuro che lo sotterro io stessa, insieme a Chang Xing!";
					link.l1 = "Andrà tutto bene. Ora vai a riposare. Tornerò prima che tu possa accorgertene.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "Dove se n'è andato Longway, Charles?";
					link.l1 = "È andato dietro a Chang Xing senza di me. Non sono riuscito a fermarlo, ma che potevo fare?";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Beh, almeno Longway viene con te. È già un piccolo sollievo, giusto?";
					link.l1 = "Vedi? Non c'è motivo di agitarsi. Non ci metterò molto.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "Dov’è Longway? Solo ora mi accorgo che non è qui.";
					link.l1 = "È andato da sua sorella senza di me. Non gliene faccio una colpa. Ha aspettato troppo a lungo questo momento.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
					
				}
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, ho un brutto presentimento su questa faccenda...";
				link.l1 = "Lo so. Questo incubo dura da troppo tempo, e la fine è vicina. Il peggio è passato.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Chi lo sa cosa gli passa per la testa, Charles? Tieni gli occhi aperti, giusto?";
				link.l1 = "Lo farò. Tornerò presto, Helen."link.l1.go ="Mio Signore Capitano, la ragazza... respira ancora, ma il suo spirito è già naufragato. Non resta che pietà per chi è stato spezzato così, giusto?";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_6":
			dialog.text = "Promettimi che sarai pronto a tutto.";
			link.l1 = "Lo sono, e lo resterò. Tornerò presto, Mary.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_7":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) StartInstantDialog("Longway", "PZ_Etap6_NaBeregu_DevaBolnaya_8", "Quest\CompanionQuests\Longway.c");
			else
			{
				DialogExit();
				LAi_SetPlayerType(pchar);
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
				AddQuestRecord("PZ", "51");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", "Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", "Helen");
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_8":
			dialog.text = "Longway   ha aiutato te, Mio Signore Capitano. Ora   è tua parola   da mantenere.";
			link.l1 = "Hai sentito tutto, Longway. Andiamo a vedere tua sorella.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_9";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_9":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Mio Signore Capitano, Longway ha un’ultima richiesta: lascia che Chang Xing si spieghi. Ascoltala prima di giudicare.";
			link.l1 = "Che cosa è successo a "+sStr+" è tutta colpa sua. Ma prima voglio darle una possibilità di spiegare.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_10";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_10":
			dialog.text = "Longway si affida alla vostra parola, al vostro giudizio, e alla vostra clemenza.";
			link.l1 = "Compagno, qui non c’è spazio né per la ragione né per la gentilezza in questo inferno insanguinato. Ed è proprio ora di finirla.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SLongwayKShin");
		break;
		
		case "PZ_LongwayPrishelOdin":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "Mio Signore Capitano...";
				link.l1 = +sStr+" è morto.";
				link.l1.go = "PZ_LongwayPrishelOdin2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Capitano, signora "+sStr+", è un piacere vederti. Questo è... Chang Xing.";
					link.l1 = "L’ho capito, Longway. Fatti da parte. Hai avuto fin troppo tempo per parlare con tua sorella. Ora dovrà rendere conto a "+sStr+" per aver aiutato i sgherri di Levasseur a rapirla.";
					link.l1.go = "PZ_LongwayPrishelOdin7";
				}
				else
				{
					dialog.text = "Sei arrivato... Dov'è la signora "+sStr+"?   È   lei...?";
					link.l1 = "No, Longway. Grazie al cielo, no. L'ho portata sulla nave. Altrimenti, adesso non sarei nemmeno qui a parlare con te. Tuttavia, non sarà comunque né facile né piacevole.";
					link.l1.go = "PZ_LongwayPrishelOdin12";
				}
			}
		break;
		
		case "PZ_LongwayPrishelOdin2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing ed io porgiamo le nostre condoglianze...";
			link.l1 = "Condoglianze da Chang Xing?! Potresti anche portare le condoglianze di Levasseur, Longway! Sai benissimo che ha partecipato al rapimento di "+sStr+" insieme agli altri suoi scagnozzi! E ora lei non c’è più...!";
			link.l1.go = "PZ_LongwayPrishelOdin3";
		break;
		
		case "PZ_LongwayPrishelOdin3":
			dialog.text = "Noi... Capisco bene cosa provate in questo momento, Mio Signore Capitano.";
			link.l1 = "Ah, davvero?";
			link.l1.go = "PZ_LongwayPrishelOdin4";
		break;
		
		case "PZ_LongwayPrishelOdin4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ho perso i miei genitori, come ricorderai. Se davvero te lo ricordi. E poi, non fu Chang Xing a torturare e uccidere "+sStr+"Capisco il vostro dolore, la vostra furia. Ma la colpa di mia sorella non pesa quanto la vostra da giudicare. Ve ne prego, ascoltate le mie parole.";
			link.l1 = "Ricordo. Ascolterò la tua storia. Ma sbrigati, eh! E sappi che una cosa simile non può restare senza castigo!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin5":
			dialog.text = "Allora è meglio che la racconti di nuovo tutta, Monsieur de Maure. Il nostro Tu parla francese così male che per poco non l’hai assalito.";
			link.l1 = "Dovevi tenere la bocca chiusa. Non avevo intenzione di attaccare Longway, ma tu... Sei tu il colpevole della sua morte.";
			link.l1.go = "PZ_LongwayPrishelOdin6";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin6":
			dialog.text = "Vorrei discutere su questo, ma capisco che preferisco di no. Tu hai parlato di te come persona di rispetto e comprensione. Ma è davvero così? Ha senso che io inizi a parlare? O hai già deciso tutto?";
			link.l1 = "Sapete infiltrarvi nella mente altrui, mademoiselle. Ora discutere non serve a nulla. Ma se volete tentare di giustificarvi... Be', fate pure. Per rispetto a Longway, vi ascolterò.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Lei può spiegare tutto, Mio Signore Capitano... Non è come pensate... Non proprio...";
			link.l1 = "Allora spiegalo. Ma non a me. "+sStr+"   Guardala negli occhi. Guarda i suoi lividi e le sue ferite. E dille che non è andata così.";
			link.l1.go = "PZ_LongwayPrishelOdin8";
		break;
		
		case "PZ_LongwayPrishelOdin8":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Le mie scuse a nome di Xing, Mio Signore Capitano...";
			link.l1 = "A giudicare dal suo sorriso beffardo, stai sprecando il fiato. Non merita le tue scuse.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin9":
			dialog.text = "Sei troppo severo con lui, Monsieur de Maure. Anche se probabilmente sei abituato a trattarlo così – come un tipico bracciante dalla pelle gialla.";
			link.l1 = "Stai cercando di mettermi Longway contro? Non funzionerà. L'ho sempre trattato con rispetto, e lui lo sa bene. Questo è tutto ciò che conta. Capisco che ormai non ti resta altro che giocare questi giochetti.";
			link.l1.go = "PZ_LongwayPrishelOdin10";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin10":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Cosa vuoi fare? Portare via il povero Tu dalla sua famiglia? Ora che, dopo dieci anni, li ha finalmente ritrovati?";
			link.l1 = "Il sangue non fa sempre una famiglia. Ma che cosa proponi di fare? Lasciamo che ciò che hai fatto a "+sStr+" andare impunito? E lasciare che Longway vada ogni tanto da una donna che vende altre ragazze senza batter ciglio?";
			link.l1.go = "PZ_LongwayPrishelOdin11";
		break;
		
		case "PZ_LongwayPrishelOdin11":
			dialog.text = "Ecco, per cominciare, ascolta. A differenza di lui, posso raccontare ciò che gli ho appena detto in un francese perfetto. La mia storia. Guardandoti dritto negli occhi, o anche nei suoi. E tutto questo senza quell’accento di cui, immagino, sarai già stufo fino al midollo. Dopotutto, che abbiamo da perdere, noi altri?";
			link.l1 = "I'm used to Longway's accent; it's part of who he is to me. I'll listen to you, but only for the sake of my friend. Go on.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Perché no, Mio Signore Capitano...?";
			link.l1 = "Devi davvero domandarlo? Era coinvolta nel rapimento di "+sStr+", non è vero?";
			link.l1.go = "PZ_LongwayPrishelOdin13";
		break;
		
		case "PZ_LongwayPrishelOdin13":
			dialog.text = "Io... vi porgo le mie più sentite scuse. La colpa è anche mia, per non aver saputo salvare mia sorella dieci anni fa, per non averla protetta da tutto questo.";
			link.l1 = "Non dovresti scusarti per chi non prova neanche il minimo rimorso, Longway. Hai finito qui? Ora tocca a me parlarle.";
			link.l1.go = "PZ_LongwayPrishelOdin14";
		break;
		
		case "PZ_LongwayPrishelOdin14":
			dialog.text = "Mio Signore Capitano, attendete! Chang Xing non è come Levasseur. Non del tutto. Lei mi racconterà la sua vita in questi dieci anni. Lasciate che ve la racconti anch'io.";
			link.l1 = "Va bene, Longway. Ti ascolto. Molto dipende da quello che mi dirai.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin15":
			dialog.text = "Se lo racconti tu, ci verrà il mal di testa tutti quanti. Permetti a me, Tu. Charles de Maure, suppongo?";
			link.l1 = "Giusto. E tu sei Belle Etoile, conosciuta anche come Chang Xing. Hai avuto la tua parte nel rapire il mio amore, insieme a Thibaut e Martene. E sorridi quando lo nomino. Bei ricordi, eh?";
			link.l1.go = "PZ_LongwayPrishelOdin16";
		break;
		
		case "PZ_LongwayPrishelOdin16":
			dialog.text = "È stupido negarlo. Ma che importa ora? Vuoi torturarmi davanti a mio fratello? O magari chiedergli di aiutarti a farmi del male? O mi ucciderai soltanto? Faresti davvero questo a lui?";
			link.l1 = "Come ti ho già detto, nonostante tutto quello che vorrei fare adesso, sto ancora parlando con te. Non tirare troppo la corda. Ripetimi quello che gli hai detto prima. Poi vedremo dove ci porterà tutto questo.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_Longway_91":
			if (!CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Ancora non riesco a credere che Chang Xing sia diventato... questo.";
				link.l1 = "La gente cambia, Longway. Chiunque può essere spezzato, o perdere fino all’ultima stilla di bontà e fede, consumate via dal tempo.";
				link.l1.go = "PZ_Longway_ToGirl1";
			}
			else
			{
				dialog.text = "Longway ancora non riesce a credere che mia sorella sia diventata... questo. Perché... perché? Se solo fossi stato a casa quel giorno...";
				link.l1 = "Non tormentarti con i se e i ma. E poi, non sei rimasto con le mani in mano tutti quegli anni – ci hai provato dannatamente tanto a rimettere insieme i pezzi.";
				link.l1.go = "PZ_Longway_ToShore1";
			}
		break;
		
		case "PZ_Longway_ToGirl1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Eh... Immagino che sia così, Mio Signore Capitano.";
			link.l1 = "Andiamocene da qui. Dobbiamo ancora ripulire il disastro che ha lasciato e salvare la "+sStr+" il prima possibile.";
			link.l1.go = "PZ_Longway_ToGirl2";
		break;
		
		case "PZ_Longway_ToGirl2":
			dialog.text = "Aye. Dobbiamo sbrigarci – ho già fatto perdere fin troppo tempo per colpa mia.";
			link.l1 = "Non è colpa tua, Longway. Sbrighiamoci!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Longway_ToShore1":
			dialog.text = "Giusto. Grazie per il vostro sostegno, Mio Signore Capitano.";
			link.l1 = "Non pensarci. Non meritava la tua dedizione, comunque – non è stata lei a cercarti, neanche quando avrebbe potuto farlo. La tua stella si è spenta da tempo, e lei ha smesso d’essere la tua famiglia molto tempo fa. Noi siamo la tua famiglia, adesso, Longway.";
			link.l1.go = "PZ_Longway_ToShore2";
		break;
		
		case "PZ_Longway_ToShore2":
			dialog.text = "Già... Così è, sei proprio tu. E io, cieco com’ero, non ho mai visto la verità fino ad ora.";
			link.l1 = "Meglio tardi che mai. Ora torniamo a casa – la nostra nave ci aspetta.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Mary_91":
			dialog.text = "Va bene. Non immagini nemmeno quanto lo desiderassi, giusto?";
			link.l1 = "Credo di sì. Come ti senti, Mary? Ho cercato di evitare il sangue perché non ero certo che la tua mano fosse ancora salda come sempre – non volevo che uno di loro prendesse il sopravvento mentre io ero occupato con un altro.";
			link.l1.go = "PZ_Mary_92";
		break;
		
		case "PZ_Mary_92":
			dialog.text = "Mi sottovaluti. Inoltre, la rabbia è una medicina infernale. Non avevo dubbi che saresti corso a salvarmi – proprio come fai sempre, giusto. Sai, Charles... Anche se mi chiami il tuo Talismano Rosso, e se anche tu fossi il mio? Succede sempre qualcosa di incredibile quando siamo insieme.";
			link.l1 = "Sarei il tuo talismano? Ma che bella idea, mi piace.";
			link.l1.go = "PZ_Mary_93";
		break;
		
		case "PZ_Mary_93":
			dialog.text = "Ecco, già sorridi! Adesso usciamo da questo posto schifoso – forza, sbrigati, giusto?";
			link.l1 = "Eh-heh, questa faccenda mi ha colpito più di quanto pensassi. Avrei voluto che finisse in qualsiasi altro modo.";
			link.l1.go = "PZ_Mary_94";
		break;
		
		case "PZ_Mary_94":
			dialog.text = "Non lo credo. Non c’era modo di salvarla, Charles. E si è portata Longway nell’abisso con sé. Lui ha scelto, non ci ha lasciato alternativa. Pensa a tutte le anime che oggi abbiamo aiutato.";
			link.l1 = "Ancora una volta, non ho nulla da obiettare, Mary. E stavolta, nemmeno lo desidero. Vieni, mio Talismano Rosso...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_ElitaShluha_Final1":
			if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva"))
			{
				dialog.text = "Cosa è successo laggiù, monsieur? Abbiamo sentito bestemmie e urla. Ma non abbiamo osato chiamare aiuto finché tutto non è finito.";
				link.l1 = "E giustamente. La vostra padrona è morta. Siete libere di andarvene. Fossi in voi, raccoglierei il tesoro della casa, lo dividerei e fuggirei da quest’isola al più presto. So che siete donne d’onore, non semplici sgualdrine, quindi avrete un futuro oltre questa lurida tana.";
				link.l1.go = "PZ_ElitaShluha_Final2";
			}
			else
			{
				dialog.text = "Oh, siete voi, monsieur. Sapete quando scenderà la padrona di casa?";
				link.l1 = "Non presto. E fossi in te, mi terrei lontano dalla porta. E non parlarle mai di questa sera – non ti dirà nulla, e i gatti impiccioni fanno una brutta fine tutti in una volta. Pare che alla tua signora non piaccia chi ficca il naso nei suoi segreti.";
				link.l1.go = "PZ_ElitaShluha_Final3";
			}
		break;
		
		case "PZ_ElitaShluha_Final2":
			dialog.text = "L'hai uccisa?!";
			link.l1 = "L'ho fatto. E se resti qui o provi a chiamare le guardie, sarebbe il tuo errore più grande. Non è mai stata una santa patrona per voi – per quanta seta e istruzione vi abbia dato, eravate prigioniere qui, costrette a concedervi a qualsiasi feccia lei indicasse. Vi auguro tutta la fortuna possibile per scappare da questo inferno. Addio, signore.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_ElitaShluha_Final3":
			dialog.text = "Sta davvero bene? Possiamo entrare? Dobbiamo chiamare le guardie?";
			link.l1 = "Non starà mai bene. Puoi provare a chiederlo a lei stessa... a tuo rischio e pericolo. Sta ancora parlando con suo fratello. E non credo che gradiranno d’essere disturbati.";
			link.l1.go = "PZ_ElitaShluha_Final4";
		break;
		
		case "PZ_ElitaShluha_Final4":
			dialog.text = "Capisco... Beh, torna a trovarci quando vuoi, monsieur.";
			link.l1 = "Mai. Addio, signore.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_TortugaSoldier1":
			dialog.text = "Alt! Urla e risse sono state segnalate dalla casa di Mademoiselle Etoile. La guardia crede che tu c'entri qualcosa. Consegnaci le armi e seguici, monsieur.";
			if (!CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				link.l1 = "Vero, ma non siamo stati noi a scatenare la rissa, l’abbiamo solo finita. Quei tagliagole assoldati si sono rivoltati per via dei pagamenti in ritardo e hanno assalito Madame Etoile per derubarla. Fidati dei mercenari, eh? La giornata è stata nostra, ma purtroppo lei non ce l’ha fatta.";
				link.l1.go = "PZ_TortugaSoldier2";
			}
			else
			{
				link.l1 = "Oggi ho perso l'amore della mia vita, quindi lasciami passare, ufficiale.";
				link.l1.go = "PZ_TortugaSoldierGirlDied1";
			}
		break;
		
		case "PZ_TortugaSoldier2":
			dialog.text = "Capisci che non possiamo semplicemente crederti sulla parola, vero? Dobbiamo trattenerti. E serviranno testimoni tra le impiegate. Vediamo che cosa hanno da dire.";
			link.l1 = "La persona che amo è gravemente ferita. Anch’io sono sfinita. Non potresti semplicemente lasciarci andare, per favore?";
			link.l1.go = "PZ_TortugaSoldier3";
		break;
		
		case "PZ_TortugaSoldier3":
			dialog.text = "Cercheremo di sistemare questa faccenda al più presto. Ora vieni con noi.";
			link.l1 = "All'inferno...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_TortugaSoldierGirlDied1":
			dialog.text = "Condoglianze, monsieur. E non sono ancora un ufficiale, ma... lasciamo stare. Potreste venire con noi e raccontarci cos'è successo là?";
			link.l1 = "Te lo dirò. Il bordello stava andando in rovina, e non c'era più un soldo per pagare i mercenari che lo sorvegliavano. Hanno deciso di arraffare ciò che restava, proprio mentre io mi trovavo lì. Io e Madame Etoile li abbiamo respinti, ma lei è morta per le ferite. Ora, lasciami passare, finalmente.";
			link.l1.go = "PZ_TortugaSoldierGirlDied2";
		break;
		
		case "PZ_TortugaSoldierGirlDied2":
			dialog.text = "Mi piacerebbe, ma c’è un mucchio di scartoffie da compilare. E devo interrogare le signorine che lavorano lì. Temo che dovrete restare in città almeno per un giorno, anche se dite la verità, monsieur.";
			link.l1 = "Vattene all’inferno...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_Longway_101":
			dialog.text = "Longway ha qualcosa per voi, Mio Signore Capitano.";
			link.l1 = "Che meraviglia, davvero bizzarro. Non ho mai visto nulla di simile. Cos’è, di grazia?";
			link.l1.go = "PZ_Longway_102";
			GiveItem2Character(PChar, "talisman14");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Longway_102":
			dialog.text = "È l’amuletto del Capitano della mia Terra. E poiché Longway non è più Capitano, lo affido a voi.";
			link.l1 = "Grazie, Longway. Con la morte di van der Vink, ti sei vendicato di tutti quelli che volevi. Sono lieto che sia andata così.";
			link.l1.go = "PZ_Longway_103";
		break;
		
		case "PZ_Longway_103":
			dialog.text = "Se solo potessi convincere Xing a tornare una brava persona...";
			link.l1 = "Non avrebbe più voluto ascoltare nessuno, nemmeno suo fratello. Hai fatto tutto quello che potevi. Tutti noi l’abbiamo fatto.";
			link.l1.go = "PZ_Longway_104";
		break;
		
		case "PZ_Longway_104":
			dialog.text = "Sì... Mille grazie, Mio Signore Capitano. Longway sarà libero, e avrà di nuovo casa e compagni.";
			link.l1 = "Di nulla, amico mio. Ora, perché non vieni con me a far visita a mio fratello. Ah, che ironia!";
			link.l1.go = "PZ_Longway_105";
		break;
		
		case "PZ_Longway_105":
			DialogExit();
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			chrDisableReloadToLocation = false;
			Return_LongwayOfficer();
		break;
		
		case "PZ_PuansieDialogWithLevasser_1":
			dialog.text = "Eccoci di nuovo, François. Vedo che la vita ti ha fatto a pezzi, eh eh.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_1_1";
			LAi_SetHuberType(npchar);
		break;
		case "PZ_PuansieDialogWithLevasser_1_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_2":
			dialog.text = "Poincy, bastardo avido... Ti strozzavi quasi con l’oro che ti trabocca dalle casseforti, eppure non ti basta mai?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_2_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_2_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_3":
			//LAi_SetActorType(npchar);
			//LAi_ActorSetHuberMode(npchar);
			dialog.text = "Te ne darò un po', François. Ti basterà, fidati di me.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_3_1";
			//LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		case "PZ_PuansieDialogWithLevasser_3_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_4", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_4":
			dialog.text = "Cosa... cosa intendi dire?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_4_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_4_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_5":
			dialog.text = "";
			link.l1 = "Governatore Generale, avete intenzione di...";
			link.l1.go = "PZ_PuansieDialogWithLevasser_6";
		break;
		
		case "PZ_PuansieDialogWithLevasser_6":
			dialog.text = "Charles, amico mio, hai compiuto il tuo dovere e l’hai fatto con maestria! Quel che accadrà a quest’uomo non dovrebbe turbarti... Tuttavia, potrebbe tornarti utile sapere, Capitano, nel caso la tua testa brillante covasse un giorno pensieri sciocchi. Al nostro amico comune attende una brutta indigestione, per così dire. Dicono che l’oro non sia digeribile... Spero di non dover essere più chiaro di così.";
			link.l1 = "No, Governatore Generale.";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7";
		break;
		
		case "PZ_PuansieDialogWithLevasser_7":
			dialog.text = "A differenza di Monsieur François, tu hai un grande futuro davanti a te, Charles. Ragazzi, portate quel maiale in cella!";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7_1";
		break;
		case "PZ_PuansieDialogWithLevasser_7_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_8", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_8":
			dialog.text = "Giù le mani, bastardi! Contento ora, de Maure?! Che vi possano pigliare i diavoli! Brucerete all’Inferno con me, tutti nello stesso paiolo!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie3");
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
			sld = characterFromID("PZ_SoldFra_1");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
			sld = characterFromID("PZ_SoldFra_2");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_Baker_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Kasper";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Sharp";
			dialog.text = "Ebbene, signore. Ho esaminato la signorina "+sStr+"...";
			link.l1 = "Quanto è grave, Raymond?";
			link.l1.go = "PZ_Baker_2";
		break;
		
		case "PZ_Baker_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Niente di cui preoccuparsi, Capitano. Mary ha preso un brutto colpo, certo, ma, tutto sommato, andrà tutto bene. Dovrà restare a letto qualche giorno, e mi aspetto che in un paio di settimane sarà di nuovo in piedi.";
					link.l1 = "Capisco. Grazie, Raymond. Puoi andare.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Mary ha preso una bella sventola, Capitano. Lividi, tagli... e lo spavento, ovviamente – anche se cerca di non darlo a vedere.";
					link.l1 = "Fa la dura, come sempre. Ma credo che abbia capito che ora le conviene restare a letto. Ma per quanto tempo, però?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Anche un soldato esperto faticherebbe a sopravvivere a ciò che ha passato lei, Capitano. Distorsioni, stiramenti, lividi – siamo stati fortunati che quei maledetti non le abbiano spezzato le ossa. Però i suoi tendini sono danneggiati, quindi non potrà brandire una lama per almeno un mese.";
					link.l1 = "Al diavolo la lama. Quando potrà rimettersi in piedi?";
					link.l1.go = "PZ_Baker_3";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Non ti preoccupare, Capitano. Hellen è ferita, ma non gravemente. Dovrà restare a letto per ora, ma credo che tra un paio di settimane sarà di nuovo in piedi.";
					link.l1 = "Capisco. Grazie, Raymond. Puoi andare.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Ha subito una bella batosta, capitano. E le ferite del corpo sono solo una parte del male... Stare in quel luogo d'orrore le ha risvegliato l’incubo vissuto sull’Arbutus.";
					link.l1 = "Certo... dannazione! Quando riuscirà a rimettersi in piedi?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Helen ha camminato su un filo di lama, Mio Signore Capitano. Mi stupisce sia sopravvissuta a tutto quello che ha passato. Nessuna lacerazione interna né fratture, ma un bel po’ di slogature e stiramenti.";
					link.l1 = "Poverina.   Quanto ci vorrà perché si riprenda?";
					link.l1.go = "PZ_Baker_3";
				}
			}
		break;
		
		case "PZ_Baker_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Almeno una settimana, signore. Se segue i miei consigli, dovrebbe tornare in azione tra circa un mese.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Non prima di quindici giorni, signore. Dopo, le concederò brevi passeggiate sul cassero. Ma per guarire del tutto, ci vorranno almeno due mesi.";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Non disturbarla per almeno una settimana, te lo dico io, signore. Per guarire del tutto ci vorrà almeno un mese.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "She should stay in bed for a fortnight; after that, she may be able to walk around the deck. But don't expect to see her back in action for at least two months.";
				}
			}
			link.l1 = "Capisco. Grazie, Raymond. Puoi andare.";
			link.l1.go = "PZ_Baker_4";
		break;
		
		case "PZ_Baker_4":
			DialogExit();
			sld = CharacterFromID("Baker");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_RazgovorSVrachom_4", -1);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "È più difficile di quanto pensassi stare in piedi da sola dopo essere rimasta sdraiata così a lungo, giusto!";
				link.l1 = "Forse non dovresti smettere di stare a letto così di colpo, amore.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ohh, la mia testa...";
				link.l1 = "Elen! Non ti sei svegliata un po' troppo presto? Riesci a malapena a stare in piedi!";
			}
			link.l1.go = "PZ_DevushkaVstalaSKrovati_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Preferirei incendiare questo maledetto letto piuttosto che sdraiarmici di nuovo – almeno finché non avrò camminato da prua a poppa e ritorno!";
				link.l1 = "È un letto comodo, niente da dire. E anche la nave non è male. Quindi non ti fermerò, ma ci sarò io a controllare che tu non faccia sciocchezze.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Sto bene, Capitano, anche se non del tutto. Non sono ancora pronta a brandire la spada, ma odio questo letto con tutta l'anima mia.";
				link.l1 = "Ebbene, una breve passeggiata sul ponte non ti farà male, credo. Ma non ti azzardare nemmeno ad avvicinarti alle gomene!";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaStoitVosstanovlenie");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, non starai mica dimenticando completamente di me? Ricordami un po’ quando è stata l’ultima volta che abbiamo diviso il letto, giusto!";
				link.l1 = "Prima... Meglio non parlarne, giusto Mary?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mio Capitano, ho forse smesso d’incuriosirti come donna?";
				link.l1 = "Questo sì che mi sorprende, Helen. Di solito sono io a tirare fuori certi discorsi... ma non ero sicuro che fossi pronta, dopo...";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Sex2";
			DelLandQuestMark(npchar);
			pchar.questTemp.PZ_DevushkaSnovaOfficer = true;
			DeleteQuestCondition("PZ_DevushkaSnovaOfficer2");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Allora parla almeno di me, giusto. O sono diventata sgradita dopo che quei due bastardi mi hanno pestata?";
				link.l1 = "Questa è la cosa più stupida che abbia mai sentito. Non volevo solo disturbarti finché non fossi pronto. E visto che ora lo sei...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Sex3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Va tutto bene, Charles, davvero. Cerco solo di non pensarci troppo. E poi, mi hai salvata dal peggio, giusto? Quindi smettiamola di parlarne e... pensiamo ad altro.";
				link.l1 = "Questa sì che è un’ottima idea, Helen.";
				link.l1.go = "exit";
				AddDialogExitQuest("cabin_sex_go");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex3":
				dialog.text = "Charles, non lo voglio, lo pretendo, giusto!";
				link.l1 = "Non oserei mai rifiutare, Mio Signore Capitano...";
				link.l1.go = "exit";
				AddDialogExitQuest("cabin_sex_go");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, dobbiamo parlare, giusto.";
				link.l1 = "C'è qualcosa che non va, Mary? Sembri piuttosto agitata, e di solito non è mai un buon segno.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mio Capitano, c'è qualcosa che devo confidarti.";
				link.l1 = "Ah davvero, Helen? Ti ascolto.";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Proprio così! Non è forse una buona cosa che io sia pronta a riprendere i miei doveri da ufficiale?";
				link.l1 = "Allora è così. Beh, se ti senti abbastanza forte, non è solo buono, è magnifico.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Sono stanca che l’equipaggio mi fissi come se fossi una vecchia decrepita. Voglio tornare al timone e sgranchirmi le braccia facendo pratica con la lama...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Se te la senti, io non mi oppongo, caro. Vado a prendere la tua roba. E sarò felice di lasciarti il timone. Ma stai attento in battaglia, giusto?";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2_1";
				}
				else
				{
					link.l1 = "Sei mancata sul ponte, Helen. Quanto alla lama, credo sia giunto il momento che tu la riprenda.";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
				}
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2_1":
			dialog.text = "Certo, Mio Capitano, come desideri.";
			link.l1 = "Bene.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Meraviglioso, giusto! Non vedo l’ora di fare pratica con la spada...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Felice di sentirlo, Mary. Ma non buttarti subito nella mischia... Ma a chi lo sto dicendo, eh?";
					link.l1.go = "exit";
					AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
				}
				else
				{
					link.l1 = "Suppongo che sarai felice di vedere quella sciabola tornare nel suo fodero...";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Io... Io non so che dire, Charles. Solo ora capisco quanto significhi per me questa sciabola...";
				link.l1 = "L'ho capito molto tempo fa, per questo ti ha aspettato qui, sano e salvo.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				notification("Gave Cutlass of Blaze", "None");
				PlaySound("interface\important_item.wav");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Il mio narvalo, giusto!!! Charles, l’hai salvato! Non sono solo felice, sono al settimo cielo! Grazie, grazie! Avevo tanta paura che fosse rimasto sulla nave di Martin...";
				link.l1 = "Questa lama ti appartiene, mio Talismano Rosso. Confido che non la perderai di nuovo... Ebbene, non mi metterò tra te e il tuo ricongiungimento, ah-ah!";
				notification("Gave Narwhal", "None");
				PlaySound("interface\important_item.wav");
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Grazie, Charles. Sai, forse è proprio per questo che ti amo...";
				link.l1 = "Per riportare indietro ciò che fu perduto? Ah ah ah ah...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog5";
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog5":
			dialog.text = "Stai ridendo, ma io parlo sul serio.";
			link.l1 = "Lo so, Helen. Ti amo anch'io, anche se ancora non capisco bene il perché.";
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog6";
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog6":
			dialog.text = "Forse perché non ti ho ancora assaggiato con questo machete.";
			link.l1 = "Mi salvo andando alle barche. Ti aspetto lì, Helen.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
	}
} 