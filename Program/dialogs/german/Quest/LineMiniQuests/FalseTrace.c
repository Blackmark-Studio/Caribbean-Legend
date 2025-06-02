void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Fehler. Lassen Sie uns wissen.";
			link.l1 = "Sicher!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "FalseTrace":
			DelMapQuestMarkCity(pchar.questTemp.FalseTrace.StartCity);
			dialog.text = "Guten Nachmittag, Kapitän... ähm... kha-hahrm! Verdammt noch mal, Minen... Lassen Sie mich mich vorstellen. Adam Rayner. Ich bin ein einfacher Mann und mag keine langen Vorreden, also spucke ich es gleich aus. Wollen Sie gutes Geld verdienen? Ich biete Ihnen ein kleines Geschäft an, das wir beide alleine nicht bewältigen können.";
			link.l1 = "Heh! Gutes Geld? Interessant. Ich höre dir zu, Adam.";
			link.l1.go = "FalseTrace_1";
			link.l2 = "Weißt du, es tut mir leid, aber du scheinst mir nicht vertrauenswürdig zu sein. Also werde ich keine Geschäfte mit dir machen.";
			link.l2.go = "FalseTrace_exit";
		break;
		
		case "FalseTrace_exit":
			dialog.text = "Vertrauenswürdig? Ha-ha! Man sollte einen Mann nicht nach seinem Gesicht beurteilen. Nun, egal. Du hast gerade eine gute Gelegenheit verpasst, leicht und schnell gutes Geld zu verdienen. Ich werde jemanden finden, der kooperativer ist...";
			link.l1 = "Unser Gespräch ist vorbei, Herr. Auf Wiedersehen!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_exit_1":
			DialogExit();
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "questTemp.FalseTrace");
		break;
		
		case "FalseTrace_1":
			//выбираем целевой пункт
			switch (hrand(2))
			{
				case 0: 
					pchar.questTemp.FalseTrace.DayQty = 18;
					pchar.questTemp.FalseTrace.TargetCity = "Beliz";
					pchar.questTemp.FalseTrace.TargetShore = "Shore8";
				break;
				case 1: 
					pchar.questTemp.FalseTrace.DayQty = 22;
					pchar.questTemp.FalseTrace.TargetCity = "Marigo";
					pchar.questTemp.FalseTrace.TargetShore = "Shore41";
				break;
				case 2: 
					pchar.questTemp.FalseTrace.DayQty = 20;
					pchar.questTemp.FalseTrace.TargetCity = "Santodomingo";
					pchar.questTemp.FalseTrace.TargetShore = "Mayak8";
				break;
			}
			pchar.questTemp.FalseTrace.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.FalseTrace.Mation = sti(npchar.nation);
			dialog.text = "Kha! Es ist ein Vergnügen, Geschäfte mit einem so schnellen Denker wie Ihnen, Kapitän, zu machen. Also, der Job ist einfach: es gibt eine Fleute voll mit einer anständigen Menge Silber und sie wird bald von einem der örtlichen Häfen auslaufen. Ein einzelnes Schiff, ohne Eskorte. Dumm, nicht wahr? K-kha\n So einfach wie Kuchen. Ich sage Ihnen wo und wann, Sie nehmen den Preis und ich bekomme meinen Anteil.";
			link.l1 = "Und natürlich möchten Sie es sofort in bar erhalten?";
			link.l1.go = "FalseTrace_2";
		break;
		
		case "FalseTrace_2":
			dialog.text = "Sehe ich aus wie ein erbärmlicher Gauner, Kapitän? Auf keinen Fall. Ich werde mich Ihnen bei diesem Überfall anschließen und wir werden es gemeinsam machen. Ich werde während des Kampfes nicht im Laderaum bleiben, ganz im Gegenteil - ich bitte Sie, mich als Ihren Offizier in eine Entermannschaft zu setzen, natürlich nur vorübergehend.\nIch kenne meinen Job, ich weiß, wie man Leute ersticht und erschießt. Also werde ich meinen Arsch genauso riskieren wie du... khe... kha! Sie werden mir meinen Anteil zahlen, nachdem wir die Fleute erobert haben.";
			link.l1 = "Welchen Anteil an der Beute beanspruchst du für dich selbst?";
			link.l1.go = "FalseTrace_3";
		break;
		
		case "FalseTrace_3":
			dialog.text = "Ich bin kein gieriger Mann, Kapitän. Mein Anteil ist so viel, wie in den Laderaum meines alten Langbootes geladen werden kann und das sind etwa 200 Packungen Silber. Nach meinen Informationen wird es auf der Fleute nicht weniger als 2000 Packungen Silber geben, also bekomme ich den zehnten Teil. Das ist fair, finden Sie nicht auch?";
			link.l1 = "Ein Zehntel der Beute nur für Informationen? Solche Informationen kaufe ich von den Betrunkenen für ein Glas Rum in der örtlichen Taverne. Nein, wir gehen nicht den gleichen Weg, Freund!";
			link.l1.go = "FalseTrace_4";
			link.l2 = "Hm. Ich denke, ich stimme zu. Ich nehme dein Angebot an, Adam. Willkommen an Bord. Jetzt zu deinen Informationen: woher, wohin, Zeit, Name des Schiffes?";
			link.l2.go = "FalseTrace_5";
		break;
		
		case "FalseTrace_4":
			dialog.text = "Was für ein Geizhals du bist, Kapitän! In diesem Fall bekommst du Scheiße! Bis dann!";
			link.l1 = "Viel Glück! Finden Sie einen anderen Tölpel für Ihr zwielichtiges Unterfangen!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_5":
			dialog.text = "Der Name der Fleute ist der "+pchar.questTemp.FalseTrace.ShipName+", sie verlässt Cartagena und segelt "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". Wir haben jedoch nicht viel Zeit. Zwei Wochen, höchstens drei. Wenn wir sie nicht innerhalb von drei Wochen finden, ist es vorbei.";
			link.l1 = "Lass uns keine Zeit verschwenden, dann! Das Abenteuer ruft!";
			link.l1.go = "FalseTrace_6";
		break;
		
		case "FalseTrace_6":
			DialogExit();
			NextDiag.CurrentNode = "FalseTrace_officer";
			DelLandQuestMark(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			AddQuestRecord("FalseTrace", "1");
			AddQuestUserData("FalseTrace", "sCity1", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen"));
			AddQuestUserData("FalseTrace", "sCity2", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity));
			AddQuestUserData("FalseTrace", "sShip", pchar.questTemp.FalseTrace.ShipName);
			//установим таймер на генерацию энкаунтера
			pchar.quest.False_Trace_2.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.False_Trace_2.function = "CreateFalseTraceGaleonOnMap";
			SetFunctionTimerCondition("FalseTraceGaleonOver", 0, 0, sti(pchar.questTemp.FalseTrace.DayQty)+2, false);//таймер
		break;
		
		case "FalseTrace_officer":
			dialog.text = "Wollten Sie etwas, Kapitän?";
			link.l1 = "Nichts, vergiss es.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FalseTrace_officer";
		break;
		
		case "FalseTrace_7":
			chrDisableReloadToLocation = true;
			dialog.text = "Wollten Sie mich sehen, Kapitän?";
			link.l1 = "Ich denke, du hast das kommen sehen... Wo ist das Silber, verdammt? Wo ist es? Ich rede mit dir! Der Kapitän der Fleute hat mir gesagt, dass es ein Versorgungsschiff war! Du hast mich belogen!";
			link.l1.go = "FalseTrace_8";
		break;
		
		case "FalseTrace_8":
			dialog.text = "Beruhigen Sie sich, Kapitän. Ich werde versuchen, alles zu erklären.";
			link.l1 = "Natürlich wirst du das! Ich habe mich bereits beruhigt! Du hängst im Moment nur deshalb nicht am Ausleger, weil ich deine Beweggründe immer noch nicht verstehe. Du hast mit mir diese Fleute verfolgt, wissend, dass es kein Silber gab. Also bitte erklären Sie sich.";
			link.l1.go = "FalseTrace_9";
		break;
		
		case "FalseTrace_9":
			dialog.text = "Ja, ich habe Sie wirklich getäuscht, Kapitän. Aber das war der einzige Weg, Sie dazu zu bringen, zu tun, was ich brauche, zu erobern... khe kha! Dieses verdammte Galeon zu erobern\nAber ich verspreche Ihnen, meine Schuld bei Ihnen zu begleichen. Lassen Sie mich Ihnen nun erzählen, warum ich es getan habe. Haben Sie eine Frau auf dem Galeon gefunden? Ich sah, wie die Besatzung sie auf Ihr Schiff brachte...";
			link.l1 = "Hm... Also, du brauchtest das Mädchen? Und deswegen hast du mich gezwungen, eine Seeschlacht zu beginnen und viele Menschen zu töten!?";
			link.l1.go = "FalseTrace_10";
		break;
		
		case "FalseTrace_10":
			dialog.text = "Es ist meine Frau. Katerine Rayner. Sie ist vor drei Monaten mit diesem erbärmlichen Kapitän von mir weggelaufen. Ich habe alle Anstrengungen unternommen, um sie zu finden, und ich habe es geschafft. Sie beide wollten "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". Ich könnte mir keinen besseren Weg vorstellen, Katerine zurückzubringen und sogar mit diesem Ehebrecher fertig zu werden\nWenn ich dir die Wahrheit erzählen würde, würdest du weggehen. Also musste ich dir eine saftige Geschichte über eine Fleute voller Silber erzählen.";
			link.l1 = "Hmpf... Deine Frau hat dich verlassen, nicht wahr? Sehr interessant!";
			link.l1.go = "FalseTrace_11";
		break;
		
		case "FalseTrace_11":
			dialog.text = "Das ist meine rechtmäßige Frau, ich liebe sie und niemand sonst hat das Recht, bei ihr zu sein! Dieser Schurke erzählte ihr schöne Lügen über Romantik und all diesen Unsinn, als ich... weg war. Kennen Sie keine Frauen? Sie glaubte diesen Schrott, dummes Mädchen, und rannte mit ihm davon.";
			link.l1 = "Also hör zu, ich interessiere mich wirklich nicht für dein Familienleben, also klär das mit deiner Frau. Aber du hast mir von der Kostenerstattung erzählt, nicht wahr? Habe ich dich richtig gehört?";
			link.l1.go = "FalseTrace_12";
		break;
		
		case "FalseTrace_12":
			if (pchar.basenation == SPAIN || pchar.basenation == HOLLAND)
			{
				pchar.questTemp.FalseTrace.QuestCity = "Portobello";
				pchar.questTemp.FalseTrace.QuestShore = "Shore48";
			}
			else
			{
				pchar.questTemp.FalseTrace.QuestCity = "SantaCatalina";
				pchar.questTemp.FalseTrace.QuestShore = "Shore54";
			}
			dialog.text = "Ja, du hast mich richtig verstanden, Kapitän. Eine Gefälligkeit für eine Gefälligkeit. Ich habe im Moment kein Geld, aber wenn du Katerine und mich zu "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", Ich werde dir völlig zuverlässige Informationen geben, wo du ohne jede Anstrengung Gold holen kannst.";
			link.l1 = "Sehr interessant. Und warum kannst du mir diese absolut zuverlässige Information jetzt nicht sagen?";
			link.l1.go = "FalseTrace_13";
		break;
		
		case "FalseTrace_13":
			dialog.text = "Denn, ich habe diese Informationen noch nicht. Lassen Sie mich im Detail erklären. Ein Glücksritter namens Schielaugen-Solly - haben Sie schon mal von ihm gehört? - er plant, einige Goldminen nicht weit von Blueweld zu plündern\nAufgrund einiger Ereignisse wird er gezwungen sein, all sein Gold an einem verborgenen Ort zu lassen und ein paar Wächter zum Schutz abzustellen. Der Mann selbst wird zu Fuß nach Belize oder nach Blueweld gehen, um ein Schiff zu holen\nIch habe einen Agenten in Solly's Besatzung, er wird auf mich warten in "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+". Sobald wir dort den Anker werfen, wird er mir sagen, wo Solly seine Schätze versteckt\nDu gehst dort hin, eliminierst die Wachen und nimmst das ganze Gold für dich. Ich wollte es selbst machen, aber angesichts der aktuellen Lage überlasse ich alles dir. Kostenlos.";
			link.l1 = "Deine Geschichte klingt sehr nach deinem vorherigen Märchen über eine Fleute voller Silber. Du hast mich schon einmal getäuscht. Wie kannst du garantieren, dass du diesmal nicht lügst?";
			link.l1.go = "FalseTrace_14";
		break;
		
		case "FalseTrace_14":
			dialog.text = "Ich gebe dir mein Wort. Ich habe keine anderen Garantien. Aber es ist wahr, ich schwöre khe... kha... verdammte Minen!";
			link.l1 = "In Ordnung. Nun geh, und ich werde über das nachdenken, was du gesagt hast.";
			link.l1.go = "FalseTrace_15";
		break;
		
		case "FalseTrace_15":
			dialog.text = "Denk nicht zu lange nach. Schieläugiger Solly wird für seine Schätze zurückkehren, wie du dir denken solltest. Meiner Berechnung nach, hast du nur zwei Wochen Zeit, um zu "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+".";
			link.l1 = "Ich werde das im Hinterkopf behalten. Und nun geh in die Mannschaftsunterkünfte und schließe dich den Seeleuten an. Ich denke, es wäre besser, wenn du bis zu unserer Ankunft von deiner Frau getrennt wärst. Du kannst jetzt gehen.";
			link.l1.go = "FalseTrace_16";
		break;
		
		case "FalseTrace_16":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.FalseTrace = "TalkCabinWoman";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "TalkSelf_Quest", 3.0);
			SetFunctionTimerCondition("FalseTraceSollyOver", 0, 0, 15, false);//таймер
			AddQuestRecord("FalseTrace", "5");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_17":
			dialog.text = "Haben Sie nach mir gerufen, Kapitän?";
			link.l1 = "Ja. Adam Rayner, ich werde dich verhaften und einsperren. Du hast mich betrogen, und ich habe keine andere Wahl, als dich zu isolieren und dich den Behörden zu übergeben.";
			link.l1.go = "FalseTrace_18";
		break;
		
		case "FalseTrace_18":
			dialog.text = "Wirklich? Das habe ich von Ihnen erwartet, Kapitän. Besonders nachdem Sie in den Laderaum gekommen sind und mit diesem schmutzigen Entführer von fremden Frauen gesprochen haben. Sie haben sich entschieden, auf seiner Seite zu stehen, oder nicht, Kapitän?";
			link.l1 = "Das geht dich nichts an. Du hast mich benutzt, du hast mich hintergangen und jetzt versuchst du mich erneut mit lächerlichen Schatzgeschichten zu täuschen! Bootsmann, bring ihn weg!";
			link.l1.go = "FalseTrace_19";
		break;
		
		case "FalseTrace_19":
			dialog.text = "Kha, nicht so schnell, Kapitän... Der Bootsmann und der Rest deiner Leute werden nicht so bald hier rein können. Hast du nicht bemerkt, dass ich die Tür abgeschlossen habe? Jetzt sind wir hier alleine - nur du und ich. Also zeig mir, Kapitän, aus welchem Holz du geschnitzt bist!";
			link.l1 = "Wirklich? Glaubst du wirklich, dass du eine Chance hast?! Du wirst das bereuen, du Arschloch!";
			link.l1.go = "FalseTrace_20";
		break;
		
		case "FalseTrace_20":
			DialogExit();
			NextDiag.currentnode = "FalseTrace_21";
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetHP(npchar, 100+MOD_SKILL_ENEMY_RATE*35, 100+MOD_SKILL_ENEMY_RATE*35); // belamour с 40 хп боец из него никудышный
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "FalseTrace_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_21":
			dialog.text = "";
			link.l1 = "Das ist besser... Leg deine Waffen nieder, Schurke! Bootsmann! Leg diesem Schelm Eisen an und werf ihn in den Laderaum!";
			link.l1.go = "FalseTrace_22";
		break;
		
		case "FalseTrace_22":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			bQuestDisableMapEnter = false;
			RemovePassenger(Pchar, npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.questTemp.FalseTrace.PrisonerAdamIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			LAi_SetPlayerType(pchar);
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, CIRASS_ITEM_TYPE);
			sld = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerIDX)];
			ReleasePrisoner(sld); //освободили пленника
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			DeleteAttribute(sld, "LifeDay") //постоянный персонаж
			GiveItem2Character(sld, "blade_10");
			EquipCharacterbyItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");//патроны не даю - все одно для антуражу
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			AddComplexSelfExpToScill(40, 40, 40, 40);
			AddQuestRecord("FalseTrace", "11");
			AddQuestUserData("FalseTrace", "sShore", XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen"));
			pchar.questTemp.FalseTrace = "AdamPrisoner";
		break;
		
		case "FalseTrace_23":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Danke, Kapitän, dass Sie dazu beigetragen haben, meine Frau zurückzubringen! Adam Rayner ist Ihnen zu Dank verpflichtet, er wird es nicht vergessen, ha-ha, ich schwöre es ... kha! Verfluchte Minen! Jetzt zu Schieläugigen Solly. Mein Mann hat mir bereits alle Einzelheiten gegeben. Solly hat all seine Güter in einer Grotte in der Bucht von San Juan del Norte gelassen. Der Mann selbst ist jetzt in Blueweld\nSie sollten sich beeilen, laut meinem Kumpel haben Sie nur fünf Tage Zeit. Nehmen Sie Ihre Männer mit, Sollys Banditen sind hart, sie werden Ihnen ordentlich einheizen\nEs ist Zeit, Abschied zu nehmen. Nochmals vielen Dank, Kapitän, Gottes Geschwindigkeit!";
			link.l1 = "Viel Glück für dich, Adam. Beleidige deine Frau nicht!";
			link.l1.go = "FalseTrace_Remove_exit";
			SetFunctionTimerCondition("FalseTraceBonanzaOver", 0, 0, 5, false);//таймер
			pchar.quest.False_Trace_4.win_condition.l1 = "location";
			pchar.quest.False_Trace_4.win_condition.l1.location = "Shore55";
			pchar.quest.False_Trace_4.function = "FalseTrace_SollyBonanza";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddQuestRecord("FalseTrace", "14");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_24":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Ha! Warum zum Teufel, Kapitän, sind wir in dieser Bucht an Land gegangen? Ich habe Ihnen gesagt, dass mein Mann im Hafen auf mich wartet von "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Geschlecht")+"! Planst du, zu Fuß durch die Dschungel dorthin zu gehen?";
			link.l1 = "Schlechte Vermutung, Adam. Hast du wirklich gedacht, dass ich deinen Mist noch einmal glauben würde? Denkst du, ich bin ein kompletter Narr? Dieses Mal habe ich einen Handel mit deiner Frau abgeschlossen.";
			link.l1.go = "FalseTrace_25";
		break;
		
		case "FalseTrace_25":
			dialog.text = "Was?! Kha! Was für ein Geschäft mit meiner Frau? Wovon redest du, du verdorbener Fisch?!";
			link.l1 = "Wegen deiner falschen Informationen habe ich eine leere Fleute erobert und ihren Kapitän getötet. Ich bedauere, dass ich das getan habe, obwohl es jetzt zu spät für Reue ist. Deine Frau war in diesen Seemann verliebt, wie ich verstanden habe. Deshalb bat sie mich, dich zu töten. Deshalb sind wir jetzt hier in dieser Bucht.";
			link.l1.go = "FalseTrace_26";
		break;
		
		case "FalseTrace_26":
			dialog.text = "Ich kann es nicht glauben! Katerine ... was für eine Schlampe! Nun, du wirst noch bekommen, was du verdienst... Also, wie hat sie dir versprochen zu bezahlen, du Narr? Sie hat keinen Pfennig, sie hat sogar all ihren Schmuck verkauft, um mit diesem Kapitän durchzubrennen!";
			link.l1 = "Das geht dich nichts an, Schurke. Aber es ist Zeit, unser Gespräch zu beenden. Ich werde dich zur Hölle schicken, wo du schon seit geraumer Zeit hättest sein sollen!";
			link.l1.go = "FalseTrace_27";
		break;
		
		case "FalseTrace_27":
			dialog.text = "Lass uns mal sehen, was du kannst, du verdorbener Hering!";
			link.l1 = "...";
			link.l1.go = "FalseTrace_28";
		break;
		
		case "FalseTrace_28":
			DialogExit();
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_AdamDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_abordage":
			dialog.text = "Ach! Warum zum Teufel hast du mein Schiff angegriffen, du Abschaum? Ich kann es nicht verstehen...";
			link.l1 = "Tun Sie nicht so unschuldig, Kapitän. Ich weiß, welche Art von Ladung Sie transportieren. Ich brauche es.";
			link.l1.go = "FalseTrace_abordage_1";
		break;
		
		case "FalseTrace_abordage_1":
			dialog.text = "Fracht? Ha-ha! Was für eine Fracht erwartest du hier zu sehen? Meine Laderäume sind leer!";
			link.l1 = "Was hast du gesagt, Schurke! Noch einmal!";
			link.l1.go = "FalseTrace_abordage_2";
		break;
		
		case "FalseTrace_abordage_2":
			dialog.text = "Ich wiederhole - Ich habe keine Ladung an Bord. Diese Fleute ist ein Versorgungsschiff auf dem Weg zu "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+" um eine Ladung Kanonenkugeln und Proviant für die Truppen zu übernehmen.";
			link.l1 = "Du ziehst mir die Wolle über die Augen. Deine Laderäume müssen voller Silber sein. Und ich werde es überprüfen, nachdem wir dieses Gespräch beendet haben...";
			link.l1.go = "FalseTrace_abordage_3";
		break;
		
		case "FalseTrace_abordage_3":
			dialog.text = "Ich weiß nicht, wer Ihnen von Silber erzählt hat. Aber das ist absoluter Unsinn... Ich habe gegen Sie verloren, also gebe ich auf. Hier ist mein Schwert. Jetzt können Sie gehen und die Laderäume überprüfen. Sie sind leer.";
			link.l1 = "Aufgeben? Nein! Ich brauche keine Zeugen. Zieh dein Schwert und kämpfe, oder ich werde dich wie ein Schaf ausweiden.";
			link.l1.go = "FalseTrace_abordage_4";
			link.l2 = "Gut für dich, dass du Vernunft gezeigt hast. Ich denke, ich werde ein Lösegeld für dich bekommen können... Hey, Leute - werft den Kapitän in den Laderaum!";
			link.l2.go = "FalseTrace_abordage_5";
		break;
		
		case "FalseTrace_abordage_4":
			DialogExit();
			pchar.questTemp.FalseTrace.KillCaptain = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "FalseTrace_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "FalseTrace_abordage_5":
			DialogExit();
			pchar.questTemp.FalseTrace.CapPrisoner = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FalseTrace_AfterFight", 3.0);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "FalseTrace_wife":
			dialog.text = "Du hast ihn getötet, du Schurke! Schuft! Armer "+pchar.questTemp.FalseTrace.CapName+"!";
			link.l1 = "Was ist das? Woher kommst du, Liebchen?";
			link.l1.go = "FalseTrace_wife_1";
		break;
		
		case "FalseTrace_wife_1":
			dialog.text = "Du wirst in der Hölle brennen für alles, was du getan hast. Zum Teufel mit dir!";
			link.l1 = "Beruhige dich, junge Dame! Fordere dein Glück nicht heraus, indem du mich verfluchst - oder ich schicke dich direkt nach deinem Kapitän!";
			link.l1.go = "FalseTrace_wife_2";
		break;
		
		case "FalseTrace_wife_2":
			dialog.text = "Du ... du wirst es nicht wagen, deine Hand gegen eine Frau zu erheben!";
			link.l1 = "Ich muss es nicht einmal. Ich kann dich erschießen. Oder ich werfe dich einfach über Bord, und die Haie erledigen den Rest... Nun, worauf wartest du? Geh zu meinem Schiff. Hab keine Angst - ich werde niemandem erlauben, dir wehzutun, und werde dich selbst nicht anfassen, wenn du ruhig bist...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_3":
			DialogExit();
			pchar.quest.False_Trace_AfterBattle.over = "yes";
			pchar.quest.FalseTraceGaleonOver.over = "yes";
			if (CheckAttribute(pchar, "questTemp.FalseTrace.CapPrisoner")) AddQuestRecord("FalseTrace", "");
			else AddQuestRecord("FalseTrace", "");
			sld = characterFromId("Mugger");
			DeleteAttribute(sld, "HalfImmortal");
			RemovePassenger(Pchar, sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DoQuestCheckDelay("LAi_EnableReload", 4.0);
			bQuestDisableMapEnter = true;
			pchar.questTemp.FalseTrace = "TalkCabin";
			AddQuestRecord("FalseTrace", "4");
		break;
		
		case "FalseTrace_wife_4":
			dialog.text = "Was... was werdet ihr mit ihm machen?";
			link.l1 = "Was ist das? Woher kommst du, Liebling?";
			link.l1.go = "FalseTrace_wife_5";
		break;
		
		case "FalseTrace_wife_5":
			dialog.text = "Armer "+pchar.questTemp.FalseTrace.CapName+"! Sag mir - wirst du ihn töten? Tu das nicht...";
			link.l1 = "Hör jetzt zu, Frau - wenn ich ihn töten wollte, hätte ich das schon längst getan. Er wird im Laderaum bleiben, und dann werde ich ihn entweder gehen lassen oder wahrscheinlich ein Lösegeld für ihn verlangen... letzteres ist wahrscheinlicher. Und jetzt sei bitte ein braves Mädchen und geh an Bord meines Schiffes. Hab keine Angst - ich werde niemandem erlauben, dir wehzutun, und werde dich selbst in Ruhe lassen, wenn du still bist...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_6":
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "Was wollt ihr von mir? Werft mich zu den Haien, wie ihr gesagt habt? Ihr habt mein Leben ruiniert und ich...";
				link.l1 = "Komm schon, Liebling. Niemand wird dich irgendwohin werfen. Ich möchte nur die Situation klären, da ich diesen Fleuten wegen dir und aus keinem anderen Grund angegriffen habe.";
				link.l1.go = "FalseTrace_wife_7";
			}
			else
			{
				dialog.text = "Was wollen Sie von mir? Wo ist "+pchar.questTemp.FalseTrace.CapName+"? Lösegeld? Brauchst du ein Lösegeld?";
				link.l1 = "Gut, Dame, lass uns diesen Fluss von sinnlosen Fragen stoppen. Ich rief dich nicht dafür hierher. Eine Tatsache wurde geklärt, und es wird interessant für dich sein, sie zu hören.";
				link.l1.go = "FalseTrace_wife_20";
			}
		break;
		
		case "FalseTrace_wife_7":
			dialog.text = "Wegen mir? Du sagst, es ist meine Schuld, dass du unser Schiff angegriffen und meine geliebte Person getötet hast? Armer "+pchar.questTemp.FalseTrace.CapName+", was hat er dir angetan? Du wirst dem Herrn für alles, was du getan hast, Antwort stehen müssen...";
			link.l1 = "Immer der gleiche Eintopf! Sollen wir wieder über Haie sprechen?";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_8"://ноды пересечения - старт
			dialog.text = "";
			link.l1 = "Ruhig jetzt? Gut. Jetzt hört mir zu! Ich habe das Schiff angegriffen, weil ich Informationen hatte, dass sie eine anständige Ladung Silber transportierte. Und diese Informationen habe ich von Adam Rayner.";
			link.l1.go = "FalseTrace_wife_9";
		break;
		
		case "FalseTrace_wife_9":
			dialog.text = "Ach! Was?! Adam? Wo ist er? Ist er hier?";
			link.l1 = "Ich sehe, du kennst den Namen... Katerine. Und wie du siehst, weiß ich bereits alles über dich. Ich nehme an, Adam Rayner ist dein Ehemann, nicht wahr?";
			link.l1.go = "FalseTrace_wife_10";
		break;
		
		case "FalseTrace_wife_10":
			dialog.text = "Ja. Ich bin die Frau dieses Monsters. Ich war unter dem Trugschluss, dass dieser Alptraum endlich vorbei war... Hat er dich angeheuert, um mich zu fangen?";
			link.l1 = "Allgemein stellte sich heraus, dass es so war. Adam hat mich über das Splitterholz belogen, damit ich die Fleute einfange '"+pchar.questTemp.FalseTrace.ShipName+"'. Auf jeden Fall war er entschlossen, dich zurückzubringen. Vor einer Viertelstunde erklärte er mir alle seine Aktionen.";
			link.l1.go = "FalseTrace_wife_11";
		break;
		
		case "FalseTrace_wife_11":
			dialog.text = "Und... was will er? Was hat er dir gesagt?";
			link.l1 = "Er will, dass seine rechtmäßige Frau zu ihm zurückkehrt. Er wird mir Informationen über das Gold des Schieläugigen Solly als Entschädigung für die Täuschung geben. Und ich werde euch beide zu "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+".";
			link.l1.go = "FalseTrace_wife_12";
		break;
		
		case "FalseTrace_wife_12":
			dialog.text = "Nein... (weint) Ich will nicht zu diesem Schurken zurück! Ich habe große Anstrengungen unternommen, um vor ihm wegzulaufen und meine Spuren zu verwischen, aber er hat mich trotzdem gefunden... Schurke! Bandit! Verfluchter Dieb!";
			link.l1 = "Beruhige dich, Katerine... Achte auf deine Sprache. Er ist immerhin dein Ehemann. Und er sagte, er liebte dich.";
			link.l1.go = "FalseTrace_wife_13";
		break;
		
		case "FalseTrace_wife_13":
			dialog.text = "(weinend) Mein Mann? Wissen Sie, wer mein Mann ist? Er ist ein Ex-Gefangener, ein Sträfling und jetzt der grausamste Bandit von "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Geschlecht")+"! Er ist ein niedriges und schmutziges Biest, und ich bin für ihn nur ein Loch zwischen den Beinen zum Ficken!";
			link.l1 = "Hattest du das alles nicht gesehen, bevor du ihn geheiratet hast?";
			link.l1.go = "FalseTrace_wife_14";
		break;
		
		case "FalseTrace_wife_14":
			dialog.text = "Zuerst war er anders... Und seine Vergangenheit schien mir so romantisch... Aber letztendlich hat sich alles verändert. Und ich möchte ihn nicht einmal sehen, geschweige denn mit ihm leben, kannst du das nicht verstehen? Ich will nicht! Besonders nach diesem Angriff auf die Fleute, den er arrangiert hat!";
			link.l1 = "Hm... Was soll ich dann mit dir anfangen, süße Dame?";
			link.l1.go = "FalseTrace_wife_15";
		break;
		
		case "FalseTrace_wife_15"://ноды пересечения - конец
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "Was zu tun? Ich weiß, was zu tun ist. Du bist das Werkzeug der Sünde, dank den Taten meines Mannes. Du hast einen unschuldigen Mann getötet, den einzigen Mann, der mich gut behandelt hat. Sühne deine Sünden, Kapitän. Töte Adam. Direkt vor meinen Augen. Ich möchte diesen Abschaum sterben sehen, ich möchte auf seine Leiche spucken\nWenn er tot ist, werde ich dir sagen, wo er seine Schätze versteckt. Der betrunkene Idiot hat mir einmal von seinem Versteck erzählt, ha-ha, er erinnert sich nicht einmal daran!";
				link.l1 = "Heh! Du bist eine grausame Frau, Katerine, wie ich sehe!";
				link.l1.go = "FalseTrace_wife_16";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.FalseTrace.CapName+"... Der Kapitän der Fleute. Ihr habt ihn eingesperrt. Sprecht mit ihm, ich flehe euch an! Er wird euch etwas für unser Leben und unsere Freiheit anbieten! Er wird eine Idee haben! Ich... Ich möchte nicht zu Adam zurückkehren, von nun an "+pchar.questTemp.FalseTrace.CapName+" ist mein Ehemann! Ich flehe dich an - bring mich nicht zurück zu Adam, zu diesem Ungeheuer!";
				link.l1 = "Hm. Interessant. Und was kann mein Gefangener mir möglicherweise anbieten? Ich kann ein Lösegeld für ihn von den Behörden bekommen, und ich werde auch das Gold des Schieläugigen Solly bekommen...";
				link.l1.go = "FalseTrace_wife_21";
			}
		break;
		
		case "FalseTrace_wife_16":
			dialog.text = "Schau mal, wer über Grausamkeit spricht. Segle zu "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", tun Sie, was Adam Ihnen gesagt hat, landen Sie nicht im Hafen, sondern in der nächsten Bucht. Drei von uns werden dorthin gehen und Sie werden den Bastard töten\n Sobald es erledigt ist, werde ich Ihnen von dem Versteck erzählen. Ich schwöre, ich lüge nicht. Ich glaube, dass Sie meinen Worten mehr vertrauen als Adam's, er hat Sie einmal reingelegt, richtig? Was sagen Sie dazu, Kapitän?";
			link.l1 = "Ja... Es gibt einen Grund, warum Mann und Frau tatsächlich von der gleichen Sorte sind. Ich schaue dich an, Katerine, und ich sehe, dass du die beste Partie für Adam bist... Wenn du ihn so sehr tot sehen willst, könntest du ihn genauso gut in seinem betrunkenen Schlaf erstechen... Bootsmann! Bring sie weg!";
			link.l1.go = "FalseTrace_wife_17";
			link.l2 = "Ich hasse Schurken, die versuchen, mich zu betrügen und für ihre eigenen Zwecke zu benutzen. Also gut, Katherine, ich stimme deinem Angebot zu, da mir klar ist, dass Adam nicht vertrauenswürdig ist. Aber wenn du mich auch täuscht, finde ich dich sogar in Europa, das schwöre ich, und ich werde dir eine Kugel durch den Kopf jagen. Jetzt verschwinde. Bootsmann! Bring sie weg!";
			link.l2.go = "FalseTrace_wife_19";
		break;
		
		case "FalseTrace_wife_17":
			dialog.text = "Du wirst das bereuen... Ich schwöre, ich ...";
			link.l1 = "Bootsmann! Bewache sie und behalte sie ständig im Auge, bis wir ankommen "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
		break;
		
		case "FalseTrace_wife_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "6");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_19":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "7");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForKillAdam");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_20":
			dialog.text = "Welche Tatsache? Was werdet ihr mit uns machen? Warum habt ihr unser Schiff gekapert?";
			link.l1 = "Wirst du mich ein Wort sprechen lassen oder soll ich meinen Bootsmann befehlen, dich mit einem Knebel zum Schweigen zu bringen?!";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_21":
			dialog.text = "Sollys Gold? Vertraust du diesem Schurken wirklich? Er wird dich wieder täuschen, das ist einfach seine Art! Rede mit deinem Gefangenen!\n"+pchar.questTemp.FalseTrace.CapName+" ist ein wahrer Gentleman, er wird sein Wort nicht brechen und er wird dich nicht belügen!";
			link.l1 = "Sie haben mich nicht überzeugt, Dame. Ich habe nichts mit Ihrem Kapitän zu besprechen. Ich werde ein Lösegeld für ihn bekommen und ich werde Solly's Gold von Adam holen. Wenn Adam mich wieder betrügt, werde ich ihn selbst am Ende der Welt finden, und er wird den Tag verfluchen, an dem er geboren wurde... Bootsmann! Bring sie weg!";
			link.l1.go = "FalseTrace_wife_23";
			link.l2 = "Um Ihnen die Wahrheit zu sagen, ich vertraue Adam nicht... Ich hasse es, manipuliert zu werden. Also gut, ich werde mit Ihrem Kapitän sprechen und sehen, was er mir sagen kann. Sie können jetzt gehen... Bootsmann! Bring sie weg!";
			link.l2.go = "FalseTrace_wife_24";
		break;
		
		case "FalseTrace_wife_23":
			dialog.text = "Du bist ein grausamer und herzloser Mann! Ich schwöre, ich...";
			link.l1 = "Bootsmann! Bewache sie und behalte sie die ganze Zeit im Auge, bis wir ankommen "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "8");
			chrDisableReloadToLocation = false;
			pchar.questTemp.FalseTrace.Prisoner = "true";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_25":
			dialog.text = "Es ist jetzt vorbei... Arm "+pchar.questTemp.FalseTrace.CapName+" ist gerächt, und ich kann nun frei atmen und mich eine Witwe nennen...";
			link.l1 = "Ich habe meinen Teil des Deals erfüllt, Katerine. Jetzt bist du dran.";
			link.l1.go = "FalseTrace_wife_26";
		break;
		
		case "FalseTrace_wife_26":
			dialog.text = "Natürlich, Kapitän. Mein Ehemann - Gott sei Dank, nun Ex-Ehemann - war ein Bandit, wie Sie bereits wissen. Aus Angst vor möglichen Durchsuchungen behielt er die geplünderte Beute nicht zu Hause. Er organisierte ein Versteck - aber er plauderte einmal darüber. Dennoch hat er es sehr clever versteckt - es gibt keinen Zugang zu diesem Ort vom Ufer aus.";
			link.l1 = "Sehr interessant... Und wo ist es?";
			link.l1.go = "FalseTrace_wife_27";
		break;
		
		case "FalseTrace_wife_27":
			dialog.text = "Auf einer kleinen Insel in der Nähe von Hispaniola. Im Leuchtturm.";
			link.l1 = "Port-au-Prince Leuchtturm! Er befindet sich auf der Insel!";
			link.l1.go = "FalseTrace_wife_28";
		break;
		
		case "FalseTrace_wife_28":
			dialog.text = "Wahrscheinlich ja. Dort wirst du die Beute finden. Du wirst sehen. Das ist alles. Tschüss, Kapitän.";
			link.l1 = "Warte... Vergib mir, Katerine, wenn du kannst. Ich hoffe, dass der Tod desjenigen, der für all dein Unglück verantwortlich ist, eine Erleichterung sein wird, so oder so. Es tut mir wirklich leid...";
			link.l1.go = "FalseTrace_wife_29";
		break;
		
		case "FalseTrace_wife_29":
			dialog.text = "Ich brauche deine Bedauern nicht, Kapitän. Du hast getan, was ich dich gebeten habe zu tun - und ich habe dir alles erzählt, was du wissen wolltest. Leb wohl jetzt und lass mich allein mit meiner Trauer...";
			link.l1 = "Tschüss, Katerine.";
			link.l1.go = "FalseTrace_wife_30";
		break;
		
		case "FalseTrace_wife_30":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15);
			LAi_LocationDisableOfficersGen(pchar.questTemp.FalseTrace.QuestShore, false);//офицеров пускать
			//LAi_LocationDisableOfficersGen("Mayak7", true);//офицеров не пускать
			locations[FindLocation("Mayak7")].DisableEncounters = true;//энкаунтеры закрыть
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.False_Trace_7.win_condition.l1 = "location";
			pchar.quest.False_Trace_7.win_condition.l1.location = "Mayak7";
			pchar.quest.False_Trace_7.function = "FalseTrace_AdamTreasure";
			AddQuestRecord("FalseTrace", "23");
		break;
		
		case "FalseTrace_wife_31":
			dialog.text = "Dreckiger Schurke! Er hat es geschafft, alle vier zu töten! Unglaublich!";
			link.l1 = "Hättest du nicht so eine Wendung erwartet, Katerine? Ich bin schwer zu töten. Du spielst Doppelspiele ziemlich gut, muss ich sagen!";
			link.l1.go = "FalseTrace_wife_32";
		break;
		
		case "FalseTrace_wife_32":
			dialog.text = "Du hast meinen Mann ermordet. Glaubst du wirklich, dass ich dich weiter atmen lassen könnte?! Du dachtest, Adams Tod hätte mich befriedigt? Nein! Du wirst diesen Ort nicht verlassen. Nicht weit von dieser Insel gibt es ein Schiff, es wird deine alte Röhre zusammen mit dir versenken!\nJetzt, mach mit mir, was du willst.";
			link.l1 = "Habe ich dir nicht gesagt, Liebling, dass du deinen Kopf verlieren würdest, wenn du mich betrügst? Ein schlauer Teufel! Tot wirst du weitaus weniger gefährlich sein. Dieser hübsche Kopf bekommt gleich eine Kugel...";
			link.l1.go = "FalseTrace_wife_33";
			link.l2 = "Ich habe Mitleid mit dir, Katerine. Deine Rachsucht hat dir am Ende nichts Gutes gebracht. Ich werde dich deinem Schicksal überlassen - du wirst auf dieser Insel bleiben. Ich denke, die örtlichen Fischer werden dich bald finden und nach Hispaniola bringen. Und möge der Herr uns alle für unsere Taten richten...";
			link.l2.go = "FalseTrace_wife_35";
		break;
		
		case "FalseTrace_wife_33":
			dialog.text = "Du bist es, der beten sollte, Ungeheuer! Mörder! Hilfe! Verdammt...";
			link.l1 = "Ich habe genug gehört.";
			link.l1.go = "FalseTrace_wife_34";
		break;
		
		case "FalseTrace_wife_34":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "shot", "FalseTrace_CaterinaKilled", 1.0);
		break;
		
		case "FalseTrace_wife_35":
			dialog.text = "Mögest du ertrinken! Möge dein Schiff gegen die Felsen zerschellen! Mögest du...";
			link.l1 = "Tschüss, Katerine.";
			link.l1.go = "FalseTrace_wife_36";
		break;
		
		case "FalseTrace_wife_36":
			DialogExit();
			sld = characterFromID("FalseTraceWife"); 
			sld.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "goto", "goto33", "none", "", "", "", -1);
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("Mayak7", false);//офицеров пускать
			locations[FindLocation("Mayak7")].DisableEncounters = false;//энкаунтеры открыть
			AddQuestRecord("FalseTrace", "25");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
		break;
		
		case "FalseTrace_Bandits":
			dialog.text = "A-ah, hier ist Adams Mörder! Katerine hatte recht, dieser Bastard kam, um das Versteck auszurauben!";
			link.l1 = "Was? Katerine? Wer bist du?";
			link.l1.go = "FalseTrace_Bandits_1";
		break;
		
		case "FalseTrace_Bandits_1":
			dialog.text = "Wer sind wir? Wir sind Freunde von Adam Rayner, der von Ihnen ermordet wurde. Er war der Anführer unserer Bruderschaft. Jetzt bin ich der Anführer, mein Name ist "+GetFullName(npchar)+", und ich werde dich bestrafen für den Mord an meinem Boss und die Gewalt, die du seiner Frau angetan hast.";
			link.l1 = "Gewalt? Wovon zum Teufel redest du?";
			link.l1.go = "FalseTrace_Bandits_2";
		break;
		
		case "FalseTrace_Bandits_2":
			dialog.text = "Du hast Adam in den Rücken gestochen, du dreckiger Verräter, du hast seine Frau gezwungen, dir zu sagen, wo Adam sein Gold versteckt hat, und dann hast du die arme Frau auf einer verlassenen Küste sterben lassen\nAber sie hat überlebt, sie hat uns um Hilfe gebeten, um ein Unrecht zu beheben. Wir haben mehrere Tage auf dich gewartet. Und hier bist du, du Bastard!";
			link.l1 = "Ha-ha! Definitiv Katerines Stil... Jetzt hör zu, ich habe Adam getötet, das stimmt, aber ich habe das getan, weil seine Frau mich tatsächlich gebeten hat, ihn zu töten. Das war eine Rache für den Tod ihres Liebhabers. Sie hat mir gesagt, wo ich die Beute finden kann, um mich zu bezahlen...";
			link.l1.go = "FalseTrace_Bandits_3";
		break;
		
		case "FalseTrace_Bandits_3":
			dialog.text = "Verleumde nicht die arme Witwe, Abschaum! Warum sollte sie sonst zu uns kommen? Sie bot uns an, uns all das Gold im Austausch für dein Leben zu überlassen. Sie will keine Münzen, sie will deinen Tod! Einen heiligen Tod für den Tod ihres Mannes!\nAber ich schwöre, sie wird nicht in Armut sterben, das ist so wahr wie mein Name ist "+GetFullName(npchar)+", und dies ist die Zeit für dich zu sterben, Feigling!";
			link.l1 = "Heiliger Mist, was für eine glorreiche Rede. Oh, da ist sie ja, begierig darauf, diese Komödie persönlich zu beobachten... Meine Herren?";
			link.l1.go = "FalseTrace_Bandits_4";
		break;
		
		case "FalseTrace_Bandits_4":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Adam_bandit_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_BanditsAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_Remove1":
			dialog.text = "Du bist so ein Chaot, Kapitän! Einen Fleute voller Silber zu verlieren... Ich habe einen Fehler gemacht, indem ich auf dich gezählt habe. Lebewohl!";
			link.l1 = "Auf Wiedersehen, Adam.";
			link.l1.go = "FalseTrace_Remove2";
		break;
		
		case "FalseTrace_Remove2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 15);
		break;
		
		case "FalseTrace_Remove_exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "FalseTraceWife_Remove", 15);
		break;
		
		case "FalseTrace_Remove2":
			dialog.text = "Ich habe Sie gewarnt, Kapitän, wir hatten nur zwei Wochen! Bis jetzt muss Schieläugiger Solly bereits die ganze Beute weggenommen haben. Es ist nicht meine Schuld, dass Sie so ein Kuddelmuddel sind. Lebewohl!";
			link.l1 = "Ja, mein Fehler. Lebewohl, ich hoffe, dass wir uns nicht wieder treffen, du bist nur ein Unglück für mich.";
			link.l1.go = "FalseTrace_Remove_exit";
		break;
		
		case "FalseTrace_Solly":
			dialog.text = "Heh! Endlich! Wir sind es leid zu warten, und diese verdammten Mücken... Warte... Und wo ist Solly? Ich verstehe es nicht...";
			link.l1 = "Solly wird nicht hierher kommen. Ich handle in seinem Namen... Also entweder gibst du mir das Gold oder du bist so gut wie tot.";
			link.l1.go = "FalseTrace_Solly_1";
		break;
		
		case "FalseTrace_Solly_1":
			dialog.text = "Argh! Wir werden sehen! Zu mir, Jungs! Zu den Waffen!";
			link.l1 = "So ein törichter Weg zu sterben, kommt dann Aasfresser!";
			link.l1.go = "FalseTrace_Solly_2";
			AddDialogExitQuestFunction("FalseTrace_SollyBonanzaAdd");
		break;
		
		case "FalseTrace_Solly_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("FTEnemy_crew_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_SollyAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_GoldShip":
			dialog.text = "Sie haben Ihren Teil des Handels erfüllt, Kapitän. Danke, dass Sie mir vertraut haben. Machen Sie sich keine Sorgen um Adam, ich werde ihn an den richtigen Ort bringen. Er wird bekommen, was er verdient.";
			link.l1 = "Es ist mir egal, was mit Adam ist. Was ist mit deinem Versprechen bezüglich eines Schiffes?";
			link.l1.go = "FalseTrace_GoldShip_1";
		break;
		
		case "FalseTrace_GoldShip_1":
			if (sti(pchar.basenation == HOLLAND) || sti(pchar.basenation == SPAIN))
			{
				pchar.questTemp.FalseTrace.ShipNation = ENGLAND;
				pchar.questTemp.FalseTrace.ShipCity = "PortRoyal";
			}
			else
			{
				pchar.questTemp.FalseTrace.ShipNation = SPAIN;
				pchar.questTemp.FalseTrace.ShipCity = "Maracaibo";
			}
			dialog.text = "Ja, ja, sicher. Lassen Sie uns sehen, zählt ab heute... Ja... In 12-14 Tagen ab "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" eine schwere Galeone beladen mit goldenem Erz wird nach Europa segeln. Sie wird von einer einzigen Fregatte oder Korvette geschützt\nAlso bereite dich vor, es ist eine reiche Beute, aber sie hat Zähne. Aber ich bin sicher, dass du Erfolg haben wirst, du hast meinen Widerstand ziemlich leicht gebrochen... Du musst erreichen "+XI_ConvertString("Kolonie"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" in zwei Wochen und bereite einen Hinterhalt vor\nDenke daran, dass dein Ziel eine schwere Galeone mit einem einzigen Konvoischiff ist. Das ist es, schätze ich. Der Rest liegt in deinen Händen.";
			link.l1 = "Ich verstehe... Nun, "+pchar.questTemp.FalseTrace.CapName+", leb wohl. Vielleicht sollte ich dir Glück und ein glückliches Leben mit Katerine wünschen? Ich hoffe, dass es euch beiden gut geht. Es ist schade, dass wir uns unter so traurigen Umständen getroffen haben.";
			link.l1.go = "FalseTrace_GoldShip_2";
		break;
		
		case "FalseTrace_GoldShip_2":
			dialog.text = "Danke, Kapitän. Wie ich schon sagte, haben Sie etwas Adel in sich. Ich hoffe, Sie kommen zu dem richtigen Schluss, dass ehrliche Aktionen mehr Profit bringen als unehrenhafte. Widmen Sie sich dem Dienst an Ihrer Nation, und Sie werden ein großer Seemann werden.";
			link.l1 = "Ich werde über deine Worte nachdenken. Nun, lebe wohl!";
			link.l1.go = "FalseTrace_GoldShip_3";
		break;
		
		case "FalseTrace_GoldShip_3":
			DialogExit();
			locations[FindLocation(pchar.questTemp.FalseTrace.TargetShore)].DisableEncounters = false; //энкаутеры открыть
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "FalseTraceDouble_Remove", -1);
			pchar.quest.False_Trace_6.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_6.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_6.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.False_Trace_6.function = "CreateFalseTraceGoldShipOnMap";
			AddQuestRecord("FalseTrace", "19");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen"));
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
