// диалоги НПС по квесту Коварный остров Ксочитэм
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "C’è qualcosa che desideri?";
			link.l1 = "No, niente.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// капитан-нежить Санта-Квитерии
		case "SQC_skeletcap":
			PlaySound("Types\skel.wav");
			dialog.text = "Tu... dovrai comunque... morire. Lui verrà... e ti farà fuori... come ha fatto fuori tutti noi... come ha fatto fuori ogni anima qui...";
			link.l1 = "Cosa? Chi sei tu? Di chi stai parlando?";
			link.l1.go = "SQC_skeletcap_1";
		break;
		
		case "SQC_skeletcap_1":
			PlaySound("Types\skel.wav");
			dialog.text = "È enorme... è invulnerabile... uccide... ti ucciderà. Devo ucciderti io... se ti uccido, non diventerai come noi... non capisci... morirai per la sua spada... ti trasformerai in ciò che siamo noi... come tutti sulla Santa Quiteria...";
			link.l1 = "Non se ne parla!";
			link.l1.go = "SQC_skeletcap_2";
		break;
		
		case "SQC_skeletcap_2":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=2; i<=3; i++)
			{
				sld = characterFromId("SQI_skelet_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_SQCskeletcapdie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Страж маски Кукулькана
		case "guardmask":
			PlaySound("Voice\English\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "Ti aspettavo da una vita!..";
			link.l1 = "Ehm!.. Straordinario!... Che spettacolo d'ossa!";
			link.l1.go = "guardmask_1";
		break;
		
		case "guardmask_1":
			dialog.text = "Lo vedo... Lo sento... Mi hai portato... la mia libertà...";
			link.l1 = "Di che diavolo vai cianciando? Che creatura sei tu?!";
			link.l1.go = "guardmask_2";
		break;
		
		case "guardmask_2":
			dialog.text = "Io sono il Guardiano di Ksocheatem, custode della maschera di Kukulcan... e l’artefice della tua imminente rovina!..";
			link.l1 = "...";
			link.l1.go = "guardmask_3";
		break;
		
		case "guardmask_3":
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "KSOCHITAM_MONSTERS");
			LAi_group_FightGroups("KSOCHITAM_MONSTERS", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("Terrapin_SetMusic", 1.2);
			n = Findlocation("Shore_mask");
			locations[n].type = "seashore";
			pchar.questTemp.Ksochitam.GuardMaskFight = "true";
			for (i=1; i<=4; i++)
			{
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 1, 0, 0, "fortfire");
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 2.5, 0, 0, "fortfire");
			}
		break;
		
		case "guardmask_4":
			PlaySound("Voice\English\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "Fermati...";
			link.l1 = "E perché mai dovrei farlo, eh? Sei già senza fiato, vecchio ossuto?";
			link.l1.go = "guardmask_5";
		break;
		
		case "guardmask_5":
			dialog.text = "No. Non riuscirai mai ad ammazzarmi, mai. Nemmeno con quel pugnale magico. Il nostro duello potrebbe durare a lungo, molto a lungo, finché non sarai sfinito e creperai.";
			link.l1 = "Ah sì? E perché mai non puoi colpirmi?";
			link.l1.go = "guardmask_6";
		break;
		
		case "guardmask_6":
			dialog.text = "Sei un valoroso e fiero guerriero, e impugni l’Artiglio del Capo. Non posso che risparmiarti la vita, perché chi possiede questo pugnale e osa sfidarmi in battaglia, ottiene ciò che cerca.";
			link.l1 = "Chi sei tu? Chi sei davvero, Custode?";
			link.l1.go = "guardmask_7";
		break;
		
		case "guardmask_7":
			dialog.text = "Mi chiamavano Alberto Casco un tempo. Ero soldato nella squadra di Alonso de Maldonado. Avevamo scoperto la città antica di Tayasal, ma ci presero e ci sacrificarono. Per la mia stazza e la mia forza, il pagano Kanek mi trasformò nel Guardiano di Ksocheatem, custode della maschera di Kukulcan. Chiunque abbia mai posato piede su Ksocheatem fu scovato da me, fatto a pezzi dalla mia mano, e condannato a vagare come non-morto.\nCol pugnale Artiglio del Capo fu inciso sulla mia carne il disegno di questo luogo. Veglierò sulla maschera in eterno, e non avrò pace finché il pugnale non sarà stretto tra le mie dita.";
			link.l1 = "Hai bisogno dell'Artiglio del Capo?";
			link.l1.go = "guardmask_8";
		break;
		
		case "guardmask_8":
			dialog.text = "Sì. Dal momento che hai bisogno della maschera. Dammi il pugnale. Troverò la pace che attendo da una vita, e tu riceverai la maschera. Ti giuro che potrai prenderla e lasciare Ksocheatem con la pelle intatta.";
			link.l1 = "Accetto la tua offerta, Custode. Ho visto la maschera su quel piedistallo dietro la fonte battesimale. È quella?";
			link.l1.go = "guardmask_9";
		break;
		
		case "guardmask_9":
			dialog.text = "Così è. Questo è il possente artefatto di Kukulcan in persona, il serpente alato. Quando avremo finito di chiacchierare, potrai andare laggiù e prenderlo.";
			link.l1 = "Ebbene, spero che tu mantenga la parola, Guardiano...";
			link.l1.go = "guardmask_10";
		break;
		
		case "guardmask_10":
			dialog.text = "Ho giurato...";
			link.l1 = "Allora prendi l'Artiglio del Capo. Che possa portare quiete alla tua anima.";
			link.l1.go = "guardmask_11";
		break;
		
		case "guardmask_11":
			RemoveItems(pchar, "knife_01", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the Chief's Claw");
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			dialog.text = "Oh, quanto ho atteso questo momento! Ora posso finalmente andarmene... Ma come dono d’addio, vorrei trasmetterti un frammento del mio potere. Questo sarà l’ultimo regalo che Alberto Casco farà mai.";
			link.l1 = "...";
			link.l1.go = "guardmask_12";
		break;
		
		case "guardmask_12":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Ksochitam_GuardMaskGift", 1.5);
		break;
		
		case "guardmask_13":
			dialog.text = "Ora è il momento che io me ne vada. Non perdere tempo: senza il suo Guardiano e la maschera di Kukulcan, l’isola sparirà per sempre.";
			link.l1 = "Non c’è proprio nulla da rimpiangere. Un covo di dannati in meno su questa terra... Ma aspetta, Guardiano! Sei stato a Tayasal! Ti prego, raccontami che razza di posto era.";
			link.l1.go = "guardmask_14";
		break;
		
		case "guardmask_14":
			dialog.text = "È un’antica città Maya. Il suo aspetto è rimasto intatto dai tempi in cui era ancora abitata. Templi maestosi, piramidi svettanti... Ora vi abita la tribù degli Itza, che si dicono discendenti diretti dei Maya. Cercano di imitarli in tutto: nella fede, nei costumi, nel vivere stesso.";
			link.l1 = "Come posso arrivarci?";
			link.l1.go = "guardmask_15";
		break;
		
		case "guardmask_15":
			dialog.text = "Il nostro comandante sapeva dove andare, Alonso de Maldonado. Noi gli siamo solo andati dietro nella giungla. Ricordo soltanto che siamo sbarcati nella baia dei Mosquito, a nord di Capo Perlas, e ci siamo addentrati nella selva verso ponente.";
			link.l1 = "Cosa c'è di degno di nota a Tayasal?";
			link.l1.go = "guardmask_16";
		break;
		
		case "guardmask_16":
			dialog.text = "Tutto laggiù vale la pena d’esser visto. Proprio tutto. Ma a noi non importava altro che i tesori dei Maya. E li abbiamo trovati. E ci sono costati cari, soprattutto a me. Ma adesso, finalmente, sono libero!";
			link.l1 = "Cosa devo sapere prima di metter piede a Tayasal?";
			link.l1.go = "guardmask_17";
		break;
		
		case "guardmask_17":
			dialog.text = "Il popolo Itza è forte e scaltro. Odiano i visi pallidi, a prescindere dalla loro bandiera, e faranno a pezzi chiunque osi mettere piede nelle loro terre. I guerrieri Itza non sprecano fiato con gli stranieri, ma Kanek o suo figlio Urakan... se vedono la maschera, forse parleranno. Se arrivi vivo a Tayasal, vedrai coi tuoi stessi occhi. Ma riuscirai poi a uscirne...";
			link.l1 = "Kanek offre in sacrificio tutti i bianchi che mettono piede a Tayasal?";
			link.l1.go = "guardmask_18";
		break;
		
		case "guardmask_18":
			dialog.text = "Suppongo di sì. Ma forse non vale per colui che porta la maschera di Kukulcan.";
			link.l1 = "Va bene. Conto proprio su questo.";
			link.l1.go = "guardmask_19";
		break;
		
		case "guardmask_19":
			dialog.text = "Addio, soldato. Spero che tu faccia buon uso del potere della maschera.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Ksochitam_GuardMaskGoAway");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
