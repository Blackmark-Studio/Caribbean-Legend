// Джессика Роуз - нежить и супербосс
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Che ti serve?";
			link.l1 = "No, non è nulla.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// бой на рифе
		case "reef":
			PlaySound("Voice\English\saga\Jessica Rose-06.wav");
			dialog.text = "Tu! Sei stato tu a portarla qui! È carne della sua carne! È carne della sua carne! La figlia della sgualdrina è venuta fin sulla tomba di sua madre! Morirà! E tu non potrai impedirlo! Non ostacolare Jessica! Lascia che la vendetta sia mia!";
			link.l1 = "...";
			link.l1.go = "reef_1";
		break;
		
		case "reef_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "stage_1":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "Ah! Non potete farmi del male!\n Aria, acqua, terra, fuoco – vi comando, venite in mio aiuto!\n Che i morti si risveglino, che le fiamme ardano, che le acque sorveglino il ponte e che il vento vi sollevi sulle sue ali e vi scagli contro la terra!\nGodetevela, canaglie!!!";
			link.l1 = "...";
			link.l1.go = "stage_1_exit";
		break;
		
		case "stage_1_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "top", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaFirstKick_2", 3.5);
		break;
		
		case "stage_2":
			PlaySound("Voice\English\saga\Jessica Rose-08.wav");
			dialog.text = "Ah! Non puoi ferirmi!\nChe si levino altri morti a colpire, che il fuoco bruci la pietra, che il vento ti sollevi e ti schianti, che la terra si nutra della tua forza!\nGoditela!!!";
			link.l1 = "...";
			link.l1.go = "stage_2_exit";
		break;
		
		case "stage_2_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "rock", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.BladePenalty = 30;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaSecondKick_2", 3.5);
		break;
		
		case "stage_3":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "Ah! Non puoi farmi del male!\nChe il veleno avvolga la mia lama fiammeggiante, che il vento ti stringa fra le sue braccia, che l’acqua ti rubi l’agilità!\nMuori! Ah-ah-ah!";
			link.l1 = "...";
			link.l1.go = "stage_3_exit";
		break;
		
		case "stage_3_exit":
			DialogExit();
			npchar.viper = true;
			TakeNItems(npchar, "potion2", 3);
			LAi_SetActorType(pchar);
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.EnergyPenalty = 2;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "quest", "bridge2");
			LAi_ActorTurnToLocator(pchar, "quest", "bridge1");
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaThirdKick_2", 3.5);
		break;
		
		case "stage_4":
			PlayStereoOGG("music_shore");
			sld = characterFromId("Svenson");
			dialog.text = "Basta... Sono stanco. Sono sconfitto... Abbi pietà del destino della sventurata Jessica!";
			link.l1 = "Certo... Risparmierò alla tua povera anima il fardello di questo cadavere!";
			link.l1.go = "exit_battle";
			if (CheckAttribute(sld, "quest.jessika_peace")) // выслушал историю Джессики
			{
				link.l2 = "So la tua storia, Jessica. E mi dispiace che la tua vita sia stata così triste e sia finita in quel modo. Vuoi parlarmi, vero? D’accordo, cercherò di dimenticare che poco fa hai tentato di farmi la pelle e ti ascolterò, anche se non sarà facile per me...";
				link.l2.go = "exit_talk";
			}
		break;
		
		case "exit_battle":
			DialogExit();
			SetMusic("music_teleport");
			DeleteAttribute(npchar, "viper");
			LAi_SetImmortal(npchar, false);
			npchar.chr_ai.hp = stf(npchar.chr_ai.hp)+100;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_JessikaDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.JessSeekTreatment = 0;
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
		break;
		
		case "exit_talk":
			dialog.text = "Grazie... Sai già di Beatrice Sharp e di Lawrence... il mio Lawrence. L'ho fatta fuori senza pensarci un attimo, ma lui... lui non ci sono riuscita. Non potevo farlo, ma lui sì. Jessica è morta...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef");
			NextDiag.TempNode = "exit_talk_0";
		break;
		
		case "exit_talk_0":
			dialog.text = "... ma il giuramento di sangue, sancito da un terribile voto, non è ancora compiuto. La forza di questo giuramento viene dalla magia degli indiani. Ha risvegliato il cadavere dalla tomba.\nL’odio ha reso la mia anima un deserto. Chiunque abbia messo piede su questa scogliera è caduto per mia mano, e i loro corpi sono divenuti miei burattini. Non posso chiedere aiuto a nessuno, se non a colui che mi ha sconfitto...";
			link.l1 = "E cosa posso fare per te? L’unica cosa che posso offrirti è risparmiarti la sofferenza...";
			link.l1.go = "exit_talk_1";
		break;
		
		case "exit_talk_1":
			PlaySound("Voice\English\saga\Jessica Rose-03.wav");
			dialog.text = "Aiutami... Portami da lui.";
			link.l1 = "Da Lawrence Beltrope? E come dovrei mai riuscirci? La mia ciurma scapperà appena ti vedrà, oppure ti darà fuoco senza pensarci due volte. Tanto più che riesci ancora a massacrare i miei uomini e ‘comandarli’ a tuo piacimento...";
			link.l1.go = "exit_talk_2";
		break;
		
		case "exit_talk_2":
			dialog.text = "Non mi vedranno. Ma tu sì. Dovresti aver già capito che possiedo poteri preclusi ai vivi. Però non posso salire sulla tua nave senza il tuo consenso. Portami da lui.   Non resterò a lungo con te. E non farò del male ai tuoi uomini. Sbarcami alla baia di Portland in Giamaica allo scoccare della mezzanotte, la notte seguente ci rivedremo e riceverai ciò che sei venuto a cercare qui.";
			link.l1 = "Come fai a sapere perché sono qui?";
			link.l1.go = "exit_talk_3";
		break;
		
		case "exit_talk_3":
			PlaySound("Voice\English\saga\Jessica Rose-01.wav");
			dialog.text = "So molte cose. Più dei vivi. L’ho vista… Ti serve un documento per lei e lo avrai. Otterrai anche di più, ti darò qualcosa in aggiunta. Portami da lui…";
			link.l1 = "Hm. Non mi piacciono le tue intenzioni sanguinarie verso Helen. Non osare nemmeno sfiorarla. In fin dei conti, non è colpevole delle azioni di sua madre.";
			link.l1.go = "exit_talk_4";
		break;
		
		case "exit_talk_4":
			dialog.text = "Mi hai sconfitto. Non le farò del male... Lo giuro.";
			link.l1 = "Non è ancora finita. Hai intenzione di liberarmi dalle tue infinite maledizioni? Ammetto che l’idea di conviverci per sempre non mi va proprio a genio...";
			link.l1.go = "exit_talk_5";
		break;
		
		case "exit_talk_5":
			dialog.text = "Non è così semplice... Quando ci rivedremo a Portland Cove dopo che avrò... ti spiegherò come guarire te stesso.";
			link.l1 = "Dopo di te cosa?.. Che vuoi dire?";
			link.l1.go = "exit_talk_6";
		break;
		
		case "exit_talk_6":
			dialog.text = "Dopo il mio incontro con lui.";
			link.l1 = "Oh, non ne sarà felice. Posso immaginare. Va bene, ricapitoliamo: primo, prometti che nessuno ti vedrà, secondo, non farai del male al mio equipaggio, terzo, non oserai nemmeno pensare a Helen, quarto, mi darai ciò che cerco, e quinto, mi libererai dalle tue maledizioni. Ho capito bene?";
			link.l1.go = "exit_talk_7";
		break;
		
		case "exit_talk_7":
			dialog.text = "Quasi. Non ti curerò io, ma ti dirò come farlo. Dovrai arrangiarti da solo.";
			link.l1 = "Va bene. Affare fatto. Ti concedo d’imbarcarti sulla mia nave.";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef2");
			NextDiag.TempNode = "exit_talk_8";
		break;
		
		case "exit_talk_8":
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			dialog.text = "";
			link.l1 = "Ehi! Dove sei finito? Sparito così, puff...";
			link.l1.go = "exit_talk_9";
		break;
		
		case "exit_talk_9":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			pchar.quest.Saga_JessFire.over = "yes"; 
			pchar.quest.Saga_JessFire1.over = "yes"; 
			pchar.quest.Saga_JessFire2.over = "yes";
			ref chr = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(chr, "hell_fire_1");
			DeleteAttribute(chr, "hell_fire_2");
			DeleteAttribute(chr, "hell_fire_3");
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Shadows", "9");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.Saga.JessOnShip = "true"; // атрибут на отрицательные последствия
			pchar.quest.Saga_Jessika_Travel.win_condition.l1 = "Hour";
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.start.hour = 0.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.finish.hour = 2.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l2 = "location";
			pchar.quest.Saga_Jessika_Travel.win_condition.l2.location = "shore36";
			pchar.quest.Saga_Jessika_Travel.function = "Saga_JessikaOnJamaica";
			NextDiag.CurrentNode = "shore";
			npchar.greeting = "jessika_2";
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
			LAi_LocationDisableOfficersGen("shore36", true);//офицеров не пускать в бухту Портленд
		break;
		
		case "shore":
			dialog.text = "Hai mantenuto la parola – siamo in Giamaica. Vieni qui domani notte e io terrò la mia promessa. Addio.";
			link.l1 = "Addio...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Saga.JessOnShip");
			DeleteAttribute(npchar, "SaveItemsForDead");
			DeleteAttribute(npchar, "DontClearDead");
			LAi_SetActorType(npchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Shadows", "10");
			SetFunctionTimerCondition("Saga_JessikaShoreWait", 0, 0, 1, false);
			NextDiag.CurrentNode = "shore_2";
			npchar.greeting = "jessika_3";
		break;
		
		case "shore_2":
			dialog.text = "È finita, "+pchar.name+"...";
			link.l1 = "Che vuoi dire?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "È finita... Tieni, prendi pure, è questo che cercavi. Questa è la lettera della mia rivale, era sepolta con lei. Si è conservata bene. L’ho perdonata, e nel mio cuore più non alberga odio.";
			link.l1 = "L’hai… incontrato? Con Lawrence?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			GiveItem2Character(pchar, "letter_beatriss"); // дать письмо
			AddQuestRecordInfo("Letter_beatriss", "1");
			dialog.text = "Sì. L'ultima cosa che ha provato in vita sua è stato il terrore. Non provo alcuna pietà per lui.";
			link.l1 = "Che Dio abbia pietà della sua anima peccatrice... Pare che non lo rivedrò mai più.";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Non hai perso nulla di prezioso. Era un uomo malvagio, davvero. Ora dobbiamo dirci addio, qui non mi resta più nulla da fare. Il mio giuramento è compiuto e l'incanto ha perso la sua forza. Ti avevo promesso un dono. Eccolo. Questo è il mio Flamberge. Non mi serve più. Una lama così non ne troverai un'altra in tutto il mondo.";
			link.l1 = "Grazie...";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			RemoveAllCharacterItems(npchar, true);
			GiveItem2Character(pchar, "blade_25");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ora, parliamo di te. Vai a Bridgetown, alla chiesa locale, per liberarmi dalle mie maledizioni. Lì troverai un prete che mi conosceva di persona. Parlagli e ti dirà cosa fare. Procurati venti candele, ti serviranno.";
			link.l1 = "Sei sicuro che mi guarirà?";
			link.l1.go = "shore_7";
		break;
		
		case "shore_7":
			dialog.text = "Lo farai tu stesso. Il Signore ti guiderà. Abbi fede. Tutto andrà per il meglio.";
			link.l1 = "D'accordo, salperò subito per Barbados. E adesso che si fa?";
			link.l1.go = "shore_8";
		break;
		
		case "shore_8":
			PlaySound("Voice\English\saga\Jessica Rose-04.wav");
			dialog.text = "E ora ti chiedo solo un'ultima cosa. Seppellisci il mio corpo qui, su questa baia accanto al mare. È questo che desidero. Forse, un giorno, passerai a visitare la tomba della povera Jessica. Addio, "+pchar.name+", e pregate per me...";
			link.l1 = "Jess?..";
			link.l1.go = "shore_9";
		break;
		
		case "shore_9":
			DialogExit();
			LAi_KillCharacter(npchar);
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("shore36", false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("Shadows", "11");
			pchar.questTemp.Saga.JessTreatment = "true";
			// вытираем Белтропа
			sld = characterFromId("Beltrop");
			sld.lifeday = 0;
			pchar.questTemp.Saga.Beltrop_die = "true"; // Белтроп убит
			sld = ItemsFromID("letter_jess");
			sld.price = 1; // страницу можно выкладывать 270912 
		break;
		
		case "soul":
			dialog.text = "Mi riconosci, capitano?";
			link.l1 = "Sei... sei proprio tu? Ma come?";
			link.l1.go = "soul_1";
		break;
		
		case "soul_1":
			dialog.text = "Sì, "+pchar.name+", sono io, sono Jessica! O almeno così apparivo vent’anni fa.";
			link.l1 = "Allora... sono morto? Ma quando? E come, diavolo?";
			link.l1.go = "soul_2";
		break;
		
		case "soul_2":
			dialog.text = "Non sei stecchito, "+pchar.name+" Sei ora nella chiesa di Bridgetown. Stavi solo... dormendo.";
			link.l1 = "È solo un sogno? Tutto sembra fin troppo vero...";
			link.l1.go = "soul_3";
		break;
		
		case "soul_3":
			dialog.text = "A volte capita, "+pchar.name+". Dio ti ha ascoltato. Le tue preghiere non solo ti hanno guarito, ma hanno anche purificato la mia anima. Ti ringrazio di cuore, "+pchar.name+"! E voglio chiederti di perdonarmi per quello che è successo allo scoglio. È... insomma, ti prego, perdonami. Non potevo partire senza chiederti il tuo perdono.";
			link.l1 = "Ti perdono, Jessica. Sono davvero tra i vivi?";
			link.l1.go = "soul_4";
		break;
		
		case "soul_4":
			dialog.text = "Tu sei... Non preoccuparti. Tra poco ti sveglierai. Volevo solo darti l’addio.";
			link.l1 = "Sei così... splendida!";
			link.l1.go = "soul_5";
		break;
		
		case "soul_5":
			dialog.text = "Ti piaccio? Eh, c’è stato un tempo in cui i migliori pretendenti delle Piccole Antille mi facevano la corte e ogni terzo filibustiere di Isla Tesoro era pronto a sfidarsi a duello per me.";
			link.l1 = "Ma tu hai sempre avuto bisogno solo di una cosa... Eh, talismano rosso! Dimmi solo, come diavolo sei finito così?";
			link.l1.go = "soul_6";
		break;
		
		case "soul_6":
			dialog.text = "A causa della mia rabbia. A causa del mio odio. Per la mia incapacità di comprendere, perdonare e dimenticare. Avrei potuto ricominciare da capo, ma invece ho scelto di consumarmi in una vendetta cieca e inutile. Tu mi hai liberato. Grazie, "+pchar.name+"...";
			link.l1 = "Mi fa davvero pena la tua vita...";
			link.l1.go = "soul_7";
		break;
		
		// здесь проверяем Мэри
		case "soul_7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{ // Мэри-офицер
				dialog.text = "Non... Hai ancora il tuo talismano di zenzero...";
				link.l1 = "Il mio che cosa?";
				link.l1.go = "mary_1";
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CheckAttribute(pchar, "questTemp.LSC.marywait"))
			{ // Мэри осталась на острове
				dialog.text = "Non... Hai ancora il tuo talismano di zenzero...";
				link.l1 = "Il mio che cosa?";
				link.l1.go = "mary_3";
				break;
			}
			dialog.text = "Non... Impara dalla mia triste esperienza e non ripetere i miei errori. E non lasciare che chi ami li commetta a sua volta.";
			link.l1 = "Ci rifletterò su e di certo non ripeterò gli stessi errori...";
			link.l1.go = "soul_8";
		break;
		
		case "mary_1":
			dialog.text = "Pensa un po’. È sulla tua nave.";
			link.l1 = "Mary?!";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Sì. È la migliore che tu possa mai avere nella tua vita. Ricordalo. Il suo amore è limpido, la sua dedizione è senza fine. È coraggiosa, giovane, ma disperata e inesperta. Comprende poco di questo mondo. Abbine cura, proteggila e non lasciare che nessuno si metta tra voi due. Lei è il tuo talismano...";
			link.l1 = "Io... non la lascerò mai e la proteggerò da ogni pericolo.";
			link.l1.go = "soul_8";
		break;
		
		case "mary_3":
			dialog.text = "Si trova sull’isola strana fatta di navi morte... Non è sola laggiù, ma resta comunque sola. Ogni suo mattino comincia pensando a te, ogni giorno prega per te, ogni notte nella sua cabina arde una luce e il suo guanciale è madido di lacrime...";
			link.l1 = "Mary...";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "C'è una figlia tra voi due. La figlia della donna che un tempo si frappose tra me e Lawrence. Il destino del tuo talismano è nelle tue mani. Non possono stare insieme, così come io e Beatrice non potevamo.";
			link.l1 = "Come fai a saperlo?";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "L'altro lato... Rivela molto... La scelta è tua, ma ricorda: Mary è la migliore che mai avrai nella tua vita. Il suo amore è limpido, la sua devozione infinita. È coraggiosa, giovane, ma disperata e inesperta. Non capisce molte cose. Ha bisogno della tua protezione, delle tue cure e del tuo amore. È il tuo talismano.";
			link.l1 = "Ci penserò... Ma sì, lo farò di sicuro...";
			link.l1.go = "soul_8";
		break;
		
		case "soul_8":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) sTemp = "";
			else sTemp = "And about the daughter of Beatrice, know that your noble actions on her behalf will be left unvalued. Soon you will see that for yourself. Be careful with her. Well...\n";
			dialog.text = ""+sTemp+"Devo andare. È giunta l’ora di dirsi addio... sul serio, stavolta. Non scordarti di Jessica, e cerca di farle visita ogni tanto alla sua tomba... Solo tu sai dove si trova.";
			link.l1 = "Certo, Jess. Andrò a visitarlo e pregherò per te.";
			link.l1.go = "soul_9";
		break;
		
		case "soul_9":
			dialog.text = "Grazie. Addio, "+pchar.name+"Addio!";
			link.l1 = "Addio, Jessica...";
			link.l1.go = "soul_10";
		break;
		
		case "soul_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_JessikaSoul_4", -1);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
