// Даниэль Хоук - жена Натаниэля Хоука
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	bool bOk1, bOk2;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time": //первая встреча - знакомство
			PlaySound("Voice\English\saga\Denny Hawk-02.wav");
			dialog.text = "Warte, Schönling! Ich denke wir sollten reden.";
			link.l1 = "Kennen wir uns? Wie auch immer, ich habe immer ein paar extra Stunden für eine Dame übrig.";
			link.l1.go = "meeting";			
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			PlaySound("Voice\English\saga\Denny Hawk-01.wav");
			dialog.text = "Macht noch keine Pläne, Kapitän. Such dir ein jüngeres, töricht aussehendes Mädchen für ein paar zusätzliche Stunden. Ich habe Geschäfte für dich. Ich bin tatsächlich verheiratet. Mein Ehemann heißt Nathaniel Hawk.";
			link.l1 = "Das ist doch mal was! Also müssen Sie diese Schla... äh, Dannie Hawk sein, Herr Svenson hat Sie erwähnt.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "In Fleisch und Blut. Ja, mir ist bewusst, dass der Forest Devil nicht viel von mir hält, das Gefühl ist gegenseitig, aber er musste dich warnen, dass ich meinen Säbel nicht nur trage, weil er hübsch ist. Also kommen wir zur Sache, Junge!\nIch habe Svenson und seine Besucher eine Weile beobachtet, weil er es war, der meinen Mann in den Dschungel schickte, um zu sterben. Ich dachte, er arbeitete mit Jackman zusammen, aber jetzt sehe ich, dass er das nicht tut. Ich versteckte mich unter dem Fenster während eures Gesprächs. Konnte nicht alles belauschen, aber habe viele nützliche Informationen gelernt.\nBist du wirklich bereit, meinen Mann zu finden und Jackman in den Arsch zu treten? Oder hast du nur billig geredet?";
			link.l1 = "Lauschen ist schlecht, Madame Hawk. Aber ich werde Ihnen vergeben, wenn Sie respektvoller mit mir sprechen. Ob ich nach Hawk suche oder nicht, das geht nur mich etwas an. Sprechen Sie, wenn Sie etwas Nützliches zu sagen haben, oder lassen Sie mich in Ruhe, wenn Sie es nicht tun. Ich werde nicht zweimal fragen.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "A-ha, was für ein Hitzkopf! Komm schon, Kapitän... Mein Temperament macht es dir sicherlich nicht wirklich bequem. Ich sehe, dass du kein Feigling bist und deinen Wert kennst. Also... lass uns bekannt machen. Ich verspreche dir, dass ich vorsichtig mit dem bin, was ich zu dir sage. Ich brauche dich und du brauchst mich. Wir teilen Ziele. Nimm mich in deine Crew und du wirst es nicht bereuen. Ich werde dir mit gutem Glauben und Treue dienen, bis wir Nathan finden, du hast mein Wort.";
			link.l1 = "Betrachten Sie sich als angenommen... Dannie. Svenson hat mir erzählt, dass Sie bereits nach Ihrem Ehemann gesucht haben. Haben Sie etwas Interessantes herausgefunden?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Nicht viel, aber genug, um Jackman der Lüge zu beschuldigen. Der Bastard sagte, dass die Wächter der Mine, jene, denen mein Nathan gegenüberstand, keine Gefangenen machten. Und während es wahr ist, dass niemand die Leiche meines Mannes in der Bucht gesehen hat, wie könnten sie auch, denn er wurde tatsächlich als Gefangener in die Minen gebracht. Snake Eye, ein Schamane des Miskito-Volkes, fand ihn dort.\nEr arrangierte auch seine Flucht. Aber wo mein Mann jetzt ist, das bleibt unbekannt. Der Schamane murmelte etwas von einem Kukulcan, der ihn gefressen hat, aber ich habe nichts verstanden. Außerdem machte der Rothaut ziemlich deutlich, dass weiße Frauen für ihn nichts als ein Witz sind. Du solltest mit ihm sprechen, vielleicht wird er gesprächiger sein";
			link.l1 = "Das ist doch schon mal etwas! Solche Neuigkeiten machen mich glücklicher. Wo kann ich diesen Indianer finden?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Es gibt ein Dorf tief in den Dschungeln. Wir müssen in der Bucht von Amatique landen und westlich durch die Dschungel gehen. Ich zeige dir den Weg, wenn du ihn selbst nicht findest. Nicht weit vom Dorf entfernt kann man ein Steinidol finden und die Wilden verehren es als ihren Gott. Ich war schon mehrere Male dort. Nichts Besonderes wirklich. Nur ein einfacher Stein, bedeckt mit Moos.";
			link.l1 = "Interessant. Gut, lass uns gehen. Wir werden mit dem Schamanen sprechen und sehen, was wir als nächstes tun. Bereit?";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Sicher! Natürlich bin ich bereit. Ich bin die ganze Zeit gereist, seit ich Maroon Town verlassen habe. Außerdem möchte ich nicht nur ein weiterer Ihrer Passagiere sein.";
			link.l1 = "Gut. Gehen wir zu meinem Schiff.";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Aye-aye, Kapitän!";
			link.l1 = "...";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.OfficerPrice = sti(pchar.rank)*700;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны - чтобы не утонула
			LAi_SetImmortal(npchar, false);
			npchar.HalfImmortal = true; //чтобы не убили в сухопутном бою
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Danielle_officer";
			npchar.HoldEquip = true; // лесник -  не отдавать саблю и пистоль																					 
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("BaronReturn", "2");
			Saga_CreateSnakeEye();
			//выбираем амулеты
			pchar.questTemp.Saga.BaronReturn.Indian = "indian_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Amulet = "amulet_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Obereg = "obereg_"+(rand(10)+1);
			// на локацию с истуканом
			npchar.quest.talk = "dolly";
			pchar.quest.Saga_Dolly.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly.function = "Saga_DannyTalk";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.greeting = "danny_1";
		break;
		
		// у истукана в джунглях
		case "Dolly":
			dialog.text = ""+pchar.name+"! Komm schon! Ich zeige dir den Steinidol, von dem der indianische Schamane gesprochen hat. Nur eine gewöhnliche Steinsäule. Auf geht's!";
			link.l1 = "...";
			link.l1.go = "Dolly_1";
		break;
		
		case "Dolly_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "item", "torch1", "Saga_ShowDolly", -1);
		break;
		
		case "Dolly_2":
			dialog.text = "Hey! Schau mal, es ist nur eine Steinstatue. Nichts Besonderes...";
			link.l1 = "Ich verstehe... Aber die Figur an der Spitze ist ein bisschen unheimlich, findest du nicht? ";
			link.l1.go = "Dolly_3";
		break;
		
		case "Dolly_3":
			dialog.text = "Alle indischen Statuen sind gruselig und böse aussehend. Ich habe schon einmal etwas Ähnliches gesehen. Sie sind alle gleich. Wie auch immer, lass uns gehen, das Dorf ist in der Nähe!";
			link.l1 = "Lass uns gehen!";
			link.l1.go = "Dolly_4";
		break;
		
		case "Dolly_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Danielle_officer";
		break;
		
		// у мискито
		case "SnakeEye":
			dialog.text = "Also, was sagst du, "+pchar.name+"? Was hat dir dieser Rothäutiger Bauchredner erzählt? Hast du etwas aus seinen philosophischen Worten verstanden?";
			link.l1 = "Hast du schon wieder gelauscht, Dannie?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "Nun... ein bisschen. Sie wissen, wir Frauen sind eben so. Aber Sie müssen verstehen - ich mache mir nur Sorgen um meinen Mann. Ich liebe ihn halt. Was macht es schon aus, wenn ich lausche? Haben Sie übrigens etwas Nützliches herausgefunden?";
			link.l1 = "Ich versuche nachzudenken... es war nicht einfach, Snake Eye zu verstehen. Es scheint jedoch, dass das Idol, welches wir auf unserem Weg ins Dorf gesehen haben, eine Art magisches Portal ist, das Menschen teleportieren kann.";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "";
			link.l1 = "Schau mich nicht so an. Es war nicht meine Idee und bis jetzt habe ich keine Probleme mit meinem Kopf. Du hast mich gefragt, was der Schamane mir erzählt hat, also erzähle ich es dir.";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "Bitte, entschuldige mich. Ich werde dich nicht mehr so ansehen. Mach weiter.";
			link.l1 = "Er sagte, dass, als Nathan fast von seinen Verfolgern gefangen wurde, der Indianer ihm die Statue als Rettungsweg zeigte, den sie Kukulcan nannten und sagte, es habe Nathan lebendig gefressen und irgendwo ausgespuckt. Einfach ausgedrückt, scheint es, dass Nathan von der Statue weg teleportiert wurde.";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "Gott, was zum... Nathan und ich waren schon einmal in einer ähnlichen Misere und jetzt passiert es wieder. Wir hatten genug Abenteuer mit diesem indischen Tempel voller Maya-Magie...";
			link.l1 = "Was hast du gerade gesagt?";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "Ach nichts, "+pchar.name+", das spielt keine Rolle. Nur Erinnerungen an meine stürmische Jugend. Aber wie hat Nathan das gemacht? Ich meine sich zu teleportieren? Wir waren gerade in der Nähe dieses Idols, ich bin um es herum gelaufen und habe es berührt... es ist nur ein Stein!";
			link.l1 = "Snake Eye hat mir erzählt, dass das Idol um Mitternacht zum Leben erwacht. Nur dann beginnt es in einer goldenen Farbe zu leuchten, wenn der Geist von Kukulcan hineinkommt. Das ist die Zeit, in der man es nicht berühren sollte. Oder im Gegenteil sollte...";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "Unheimlich... Und jetzt? Warten wir bis Mitternacht und gehen dann in den Dschungel?";
			link.l1 = "Nein. Der Schamane sagte, dass das Idol nicht nur Menschen teleportiert, sondern auch ihr Leben frisst. Soweit ich ihn verstanden habe, meinte er, dass es ihre Gesundheit aussaugt. Snake Eye ist dreimal durch diese Statuen hindurchgegangen und hat sich nach jeder Teleportation mit einem einzigartigen Trank geheilt.";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "Hast du ihn nach diesem Trank gefragt?";
			link.l1 = "Sicher. Aber erstens, es sind nur noch drei Flaschen übrig und zweitens, er verlangte drei Amulette im Austausch dafür.";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "Wie wäre es, dies ohne den Trank zu tun? Lass uns nachts zur Statue gehen und sie berühren...";
			link.l1 = "Zu riskant. Ich gebe zu, dass der Indianer ein bisschen verrückt ist, aber er sieht nicht aus wie ein Psychopath, also glaube ich, dass er die Wahrheit sagt. Ich erinnere mich, dass du mir etwas über indische Magie erzählt hast... Zweifelst du an ihrer Existenz?";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			dialog.text = "Ja, hatte ich. Ich bezweifle es nicht, weil ich es mit meinen eigenen Augen gesehen habe. Also, ich vermute, du hast recht, es hat keinen Sinn, es zu riskieren.";
			link.l1 = "Genau. Deshalb werden wir zuerst die Amulette finden, dann diesen wunderbaren Trank vom Schamanen holen und zur Statue gehen. Ich werde gehen. Alleine.";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Warum denn so? Und was ist mit mir?";
			link.l1 = "Du wirst auf meinem Schiff bleiben und die Führung übernehmen, während ich weg bin. Versuche nicht einmal zu argumentieren, Dannie. Es gibt nur drei Flaschen des Tranks. Es ist unbekannt, wohin das Portal führt, falls der Schamane recht hat und dieses Ding wirklich funktioniert. Vielleicht kann ich Nathan dort nicht einmal finden.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			dialog.text = "Du bist genau wie Nathan. Alle Männer sind gleich... Gut, ich stimme zu.";
			link.l1 = "Es ist gut, dass wir uns verstehen. Lass uns jetzt gehen, wir müssen die Amulette finden.";
			link.l1.go = "Dolly_4";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед походом к истукану
		case "teleport":
			dialog.text = "Also? Hast du die Tränke bekommen?";
			link.l1 = "Ja. Ich habe die Tränke und einige Anweisungen. Das Einzige, was noch zu tun bleibt, ist um Mitternacht zum Idol zu gehen und es zu berühren.";
			link.l1.go = "teleport_1";
		break;
		
		case "teleport_1":
			dialog.text = "Hast du Angst?";
			link.l1 = "Ja. Ich fürchte, dass der Schamane nur verrückt sein könnte und keine Teleportation stattfinden wird.";
			link.l1.go = "teleport_2";
		break;
		
		case "teleport_2":
			dialog.text = "Nun, nun... Hast du wirklich keine Angst? Nicht einmal ein kleines bisschen?";
			link.l1 = "Dannie, dräng mich nicht... Wenn du es wirklich wissen willst, dann ja, ich gestehe, ich fühle mich nicht allzu sicher.";
			link.l1.go = "teleport_3";
		break;
		
		case "teleport_3":
			dialog.text = "Ich werde mit dir gehen.";
			link.l1 = "Willst du schon wieder streiten? Ich dachte, wir hätten eine Abmachung...";
			link.l1.go = "teleport_4";
		break;
		
		case "teleport_4":
			dialog.text = "Du hast mich falsch verstanden. Ich werde nur in deiner Nähe bleiben. Ich muss sicherstellen, dass die Statue funktioniert... oder dass sie es nicht tut.";
			link.l1 = "Dann habe ich habe keine Einwände. Aber denk nicht einmal daran, mir zu folgen, falls die Statue mich 'frisst'. Hörst du mich?";
			link.l1.go = "teleport_5";
		break;
		
		case "teleport_5":
			dialog.text = "Ich verspreche, dass ich dir nicht folgen werde... Kapitän.";
			link.l1 = "Gut. Und, Dannie, es scheint, dass du nicht so eine Schlampe bist, wie sie sagen.";
			link.l1.go = "teleport_6";
		break;
		
		case "teleport_6":
			dialog.text = "Du kennst mich nicht allzu gut, "+pchar.name+". Aber reden wir jetzt nicht darüber.";
			link.l1 = "Ja lassen wir es besser ... Nun, wir sollten uns auf unseren nächtlichen Ausflug vorbereiten!";
			link.l1.go = "Dolly_4";
			npchar.quest.talk = "shadowstar";
			pchar.quest.Saga_Dolly1.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly1.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly1.win_condition.l2 = "Hour";
			pchar.quest.Saga_Dolly1.win_condition.l2.start.hour = 0.00;
			pchar.quest.Saga_Dolly1.win_condition.l2.finish.hour = 1.00;
			pchar.quest.Saga_Dolly1.function = "Saga_DannyTalk";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед телепортацией
		case "shadowstar":
			dialog.text = "Schau, "+pchar.name+"! Ich schwöre bei allem was heilig ist, dort ist tatsächlich ein seltsames Licht über der Statue!";
			link.l1 = "Es scheint, dass der Schamane nicht gelogen hat. Und, wenn die Dunkelheit mich nicht täuscht, sieht die Spitze der Statue nicht mehr so steinig aus.";
			link.l1.go = "shadowstar_1";
			QuestPointerDelLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		case "shadowstar_1":
			dialog.text = "Genau... Es sieht aus, als wäre es aus purem Gold! Unglaublich!";
			link.l1 = "Die Zeit ist gekommen, Dannie. Wünsch mir Glück und drück die Daumen für mich. Geh nicht in die Nähe des Idols! Bleib hier.";
			link.l1.go = "shadowstar_2";
		break;
		
		case "shadowstar_2":
			dialog.text = "Viel Glück, "+pchar.name+". Lass uns hoffen, dass das funktionieren wird... Hast du den Schamanen-Trank vorbereitet?";
			link.l1 = "Ja, ich habe es hier. Alles wird gut, Dannie. Also, los geht's! (Drücke T, um das Idol zu aktivieren)";
			link.l1.go = "shadowstar_3";
		break;
		
		case "shadowstar_3":
			DialogExit();
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
		break;
		
		// прибыл назад 
		case "arrive":
			dialog.text = "A-a-ah?! Verdammt! Was für ein Monster bist du, zum Teufel?! Fick dich! Ich habe in meinem Leben schlimmere Kreaturen gesehen, einschließlich Van der Decken selbst! Jetzt gebe ich dir, was du verlangst!";
			link.l1 = "(leise) Dannie, warte! Hör auf! Jetzt!";
			link.l1.go = "arrive_1";
		// belamour legendary edition -->
			link.l2 = "(schwach) Van der Decken? Uh-ha-ha-ha! Dieser Wurm dient mir bereits! Jetzt bist du dran! Verbeuge dich vor mir, treuer Diener! Du wirst meine Armee der Toten führen!";
			link.l2.go = "arrive_1a";
			SetMusic("music_jungle");
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("Du hast das Gefühl, dass deine Gesundheit wiederhergestellt ist!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "arrive_1a":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "A-A-A-A-A-A-A-A-A-A-A-A-A! Geh weg! Das kann jetzt nicht passieren!";
			link.l1 = "(leise) Dannie, warte! Hör auf! Jetzt!";
			link.l1.go = "arrive_1";
		break;
		// <-- legendary edition
		case "arrive_1":
			dialog.text = "Ach?! Was hast du gesagt?! Dannie?";
			link.l1 = "(schwach) Halt sofort ein! Halt dein Säbel fest! Lass mich dieses Ding abnehmen!";
			link.l1.go = "arrive_2";
		break;
		
		case "arrive_2":
			dialog.text = "Verdammt, du Monster klingst wie... "+pchar.name+"?!";
			link.l1 = "(leise) Oh-oh... Sag bloß!";
			link.l1.go = "arrive_3";
		break;
		
		case "arrive_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			DoQuestCheckDelay("Pearl_TeleportArrive_1", 1.5);
		break;
		
		case "arrive_4":
			dialog.text = "Verdammt, du hast mich fast zu Tode erschreckt! Ich war kurz davor, dich mit meinem Säbel niederzuhauen!";
			link.l1 = "Ich habe das gesehen... und warum bist du so feurig, hm?";
			link.l1.go = "arrive_5";
		break;
		
		case "arrive_5":
			dialog.text = "Das bin ich... Oh, mein Herz schlägt noch immer direkt aus meiner Brust...";
			link.l1 = "Dannie, wo sind wir jetzt? Nicht weit vom Miskito Dorf, oder?";
			link.l1.go = "arrive_6";
		break;
		
		case "arrive_6":
			dialog.text = "Wo könnten wir sonst sein! Dies ist die Statue, die dich verschwinden ließ. Das war spektakulär! Ich werde mich mein ganzes Leben daran erinnern.";
			link.l1 = "Ich sehe, du hast hier die ganze Zeit auf mich gewartet?";
			link.l1.go = "arrive_7";
		break;
		
		case "arrive_7":
			dialog.text = "Sag mir, was hätte ich sonst tun sollen? Nachdem die Statue dich gefressen hatte, konnte ich nur hoffen, dass es dich eines Tages wieder ausspucken würde. Außerdem sagte Snake Eye, dass dies am wahrscheinlichsten passieren würde.\nIch lebte bei den Miskito und beobachtete jeden Tag das Idol. Warum sprechen wir überhaupt über solchen Unsinn? Sag mir! Was ist da draußen passiert? Wo warst du?";
			link.l1 = "Dannie, diese Geschichte ist viel zu lang, ich habe so viel gesehen... Aber um es von deiner Brust zu bekommen, sage ich dir, dass ich Nathaniel gefunden habe!";
			link.l1.go = "arrive_8";
		break;
		
		case "arrive_8":
			dialog.text = "Du hast Nathan gefunden? Wo ist er? Und wie geht es ihm?!";
			link.l1 = "Ich werde nicht lügen - er lebt, aber er fühlt sich wirklich schlecht. Er hatte keinen Trank der Comanche und das Idol hat ihm alle Kraft geraubt. Er liegt in einer Kabine eines alten und kaputten Schiffes auf der seltsamen Insel der Verlassenen Schiffe. Ich wurde auch dorthin teleportiert, also hatte Snake Eye recht!";
			link.l1.go = "arrive_9";
		break;
		
		case "arrive_9":
			dialog.text = "Armer Nathan... Wo ist diese verdammte Insel? Wie kommen wir dorthin?! Nur durch das Idol? Ich werde versuchen, jeden einzelnen Heiltrank von den Miskito zu kaufen und noch heute Nacht dorthin zu gehen! Irgendwie werde ich es schaffen...";
			link.l1 = "Halt! Warte! Nathan ist krank, aber sein Leben ist nicht in Gefahr. Ein Junge kümmert sich um ihn und füttert ihn. Wenn du durch das Idol gehst, wirst du deine Gesundheit ruinieren und die Insel ist wirklich gefährlich. Es ist zu riskant!";
			link.l1.go = "arrive_10";
		break;
		
		case "arrive_10":
			dialog.text = "Also, was schlägst du vor? Nichts zu tun, während Nathan leidet oder vielleicht stirbt?";
			link.l1 = "Hör auf hysterisch zu sein. Erstens habe ich dir gesagt, dass Nathan krank, aber nicht sterbend ist. Ich habe mit ihm gesprochen. Zweitens werde ich zur Insel segeln und du wirst mit mir gehen.";
			link.l1.go = "arrive_11";
		break;
		
		case "arrive_11":
			dialog.text = "Du weißt wo diese Insel ist?";
			link.l1 = "Sicher, das tue ich! Ich habe dort nicht nur Nathan, sondern auch Shark Dodson gefunden. Ich habe die ungefähren Koordinaten der Insel und Segelanweisungen, um die Riffe zu umgehen. Und jetzt gehen wir zurück zu meinem Schiff und segeln nach Blueweld...";
			link.l1.go = "arrive_12";
		break;
		
		case "arrive_12":
			dialog.text = "Wozu? Warum können wir nicht jetzt direkt zur Insel segeln?";
			link.l1 = "Dannie, ich muss eine Expedition organisieren. Es gibt einen großen Mangel an Vorräten auf der Insel, also werde ich so viel Essen kaufen, wie ich kann. Dann muss ich ein Schiff auswählen, um dorthin zu segeln, nicht alle Schiffe werden in der Lage sein, die Riffe der Insel zu umfahren. Und ich möchte zuerst mit Svenson sprechen...";
			link.l1.go = "arrive_13";
		break;
		
		case "arrive_13":
			dialog.text = "";
			link.l1 = "Es wird nicht lange dauern, sich vorzubereiten. Die Insel ist nicht weit von hier, sie liegt nordwestlich von Havanna, östlich des Golfs von Mexiko.";
			link.l1.go = "arrive_14";
		break;
		
		case "arrive_14":
			dialog.text = "Gut... dann machen wir das. Du hast Nathan gefunden und das ist das Wichtigste. Danke dir! Geht es ihm dort schlecht?";
			link.l1 = "Nun... er ist krank. Und dazu ist er auch noch deprimiert und verzweifelt. Er vermisst dich. Und ja, Nathan hat mich gebeten dir zu sagen, dass er dich sehr liebt.";
			link.l1.go = "arrive_15";
		break;
		
		case "arrive_15":
			dialog.text = "(wischt eine Träne weg) Alter Narr! Er hat mir nie zugehört... "+pchar.name+", lass uns zu deinem Schiff gehen! Ich will so schnell wie möglich dorthin segeln!";
			link.l1 = "Sicher, Dannie. Und ich werde dir von meinen Abenteuern erzählen. Gehen wir!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "9");
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", false); // пускать офицеров в локу телепорта
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			setCharacterShipLocation(pchar, "Shore9"); // калеуче
			setWDMPointXZ("Shore9"); // корабль в бухту Аматике
			bNoEatNoRats  = false; // еду и крыс включить
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog");
		break;
		
		// в LSC у причала
		case "nathaniel":
			dialog.text = "Ich habe noch nie einen Ort wie diesen gesehen. Die ganze Insel besteht aus Schiffen!";
			link.l1 = "Ich habe dir davon erzählt, Dannie...";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "Aber jetzt kann ich es mit meinen eigenen Augen sehen. Aber egal, sag mir wo ich Nathaniel finden kann?";
			link.l1 = "Er ist in einem der Schiffe. Aber du musst dorthin schwimmen.";
			link.l1.go = "nathaniel_2";
		break;
		
		case "nathaniel_2":
			dialog.text = "Es ist mir egal. Sag mir, wie ich zu diesem Schiff komme.";
			link.l1 = "Dannie, beruhige dich. Du und Nathan habt schon lange gewartet, also hab noch ein wenig Geduld! Ich werde dich zu ihm führen, du wirst ihn nie selbst finden. Außerdem möchte ich nicht, dass du auf die Narwale oder Rivados triffst, du wirst mit ihnen anfangen zu streiten und das wird nicht gut enden.";
			link.l1.go = "nathaniel_3";
		break;
		
		case "nathaniel_3":
			dialog.text = "Gut, dann lass uns gehen. Ich werde dir folgen.";
			link.l1 = "Vergiss nicht, dass wir viel schwimmen müssen.";
			link.l1.go = "nathaniel_4";
		break;
		
		case "nathaniel_4":
			dialog.text = "Es ist in Ordnung, ich kann damit umgehen.";
			link.l1 = "Freut mich das zu hören... Du wirst deinen Mann bald sehen!";
			link.l1.go = "nathaniel_5";
		break;
		
		case "nathaniel_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Danny_Natan.win_condition.l1 = "location";
			pchar.quest.LSC_Danny_Natan.win_condition.l1.location = "FernandaDiffIndoor";
			pchar.quest.LSC_Danny_Natan.function = "LSC_DannyAndNatan";
			AddQuestRecord("LSC", "15");
			// следующая нода
			if (CheckCharacterItem(pchar, "keys_skel")) // идёт Оле
			{
				sld = characterFromId("Ole");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				if (GetCharacterIndex("Mary") != -1) // иначе Мэри
				{
					sld = characterFromId("Mary");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else // иначе завершение
				{
					chrDisableReloadToLocation = false;
					LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				}
			}
		break;
		
		case "nathaniel_6":
			dialog.text = "Nathaniel... Nathan! Verdammt! Meine Liebe...";
			link.l1 = "...";
			link.l1.go = "nathaniel_7";
		break;
		
		case "nathaniel_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("LSC_DanielleRomantic", 15.0);
		break;
		
		case "nathaniel_8":
			dialog.text = "Jesus, sieh dich doch nur an... Warum hast du dir das angetan?!.. (weint) Du hörst mir nie zu, nie! Ich habe dir gesagt, du sollst nicht in diesen Urwald gehen! Aber du bist trotzdem hingegangen! Warum Nathan?!";
			link.l1 = "Dannie... Es tut mir leid. Ich hatte keine Wahl, das weißt du...";
			link.l1.go = "nathaniel_9";
		break;
		
		case "nathaniel_9":
			sld = characterFromId("Blaze");
			dialog.text = "Ich weiß das! Oh Gott, Liebling... was ist dir passiert! (mit Tränen) Alles ist in Ordnung, Liebling, alles wird gut... Ich bin hier. Wir werden dich zu den Miskito bringen, zu Snake Eye. "+sld.name+"  hat mir erzählt, dass der Schamane dich heilen kann. Wir haben ein Schiff... Alles wird gut!";
			link.l1 = "Dannie, Liebste... meine Liebe! Deine Anwesenheit hat mich schon zur hälfte geheilt. Wir gehen wohin du sagst. Wenn es zu Snake Eye geht, dann zu ihm.";
			link.l1.go = "nathaniel_10";
		break;
		
		case "nathaniel_10":
			dialog.text = "Pack deine Sachen. Ach, ich bin so dumm... Es gibt keine Sachen zum Packen, außer leeren Flaschen. Nathan...";
			link.l1 = "Dannie...";
			link.l1.go = "nathaniel_11";
		break;
		
		case "nathaniel_11": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			DeleteAttribute(pchar, "GenQuest.MusicContinue");
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "nathaniel_12":
			dialog.text = ""+pchar.name+" ... verzeihe mir und Nathan für die Szene.";
			link.l1 = "Dannie! Dir für was vergeben? Es ist in Ordnung. Schämst du dich für deine Gefühle?";
			link.l1.go = "nathaniel_13";
		break;
		
		case "nathaniel_13":
			dialog.text = "Nein, ich bin nicht... Es ist nur...";
			link.l1 = "Niemand wird jemals von dieser Szene erfahren. Ich verspreche es. Und niemand wird wissen, was mit Nathan passiert ist. Die Piraten von Maroon Town werden einen starken und furchteinflößenden Nathaniel Hawk sehen!";
			link.l1.go = "nathaniel_14";
		break;
		
		case "nathaniel_14":
			dialog.text = "Danke, "+pchar.name+"! Ich schulde dir... Ich werde meinen Mann zum Schiff bringen. Mach dir keine Sorgen, ich werde es schaffen, ihn dorthin zu bringen, ich habe mir den Weg gemerkt. Ich werde ihn ins Bett legen und bei ihm bleiben. Wir werden zur Snake Eye segeln, nachdem du hier alles erledigt hast, was du tun musst. Ich glaube an seine Fähigkeit, Nathan zu heilen.";
			link.l1 = "Gut, Dannie. Wir werden sowieso nicht lange hier bleiben. Bist du sicher, dass du keine Hilfe brauchst?";
			link.l1.go = "nathaniel_15";
		break;
		
		case "nathaniel_15":
			dialog.text = "Ich bin sicher. Wir werden das Schiff erreichen. Mach dir keine Sorgen, ich lasse meinen Mann nicht sterben!";
			link.l1 = "Dannie, du bist... wunderbar!";
			link.l1.go = "nathaniel_16";
		break;
		
		case "nathaniel_16":
			dialog.text = "(eine Träne wegwischend) Geh... geh einfach, "+pchar.name+"... und bitte verschwende hier keine Zeit!";
			link.l1 = "...";
			link.l1.go = "nathaniel_17";
		break;
		
		case "nathaniel_17":
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableCharacterMenu = false;//лоченые интерфейсы
			EndQuestMovie();
			DialogExit();
			pchar.quest.LSC_NatanPassenger.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_NatanPassenger.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_NatanPassenger.function = "LSC_SetNatanPassenger";
			pchar.quest.Saga_NatanTreatment.win_condition.l1 = "location";
			pchar.quest.Saga_NatanTreatment.win_condition.l1.location = "Miskito_village";
			pchar.quest.Saga_NatanTreatment.function = "Saga_NatanPrepareTreatment";
			pchar.questTemp.Saga.BaronReturn = "shamane";
			AddQuestRecord("BaronReturn", "11");
			// открываем вход к Мэри
			if (GetCharacterIndex("Mary") != -1)
			{
				for (i=0; i<=3; i++)
				{
					LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, false);
				}
			}
			else
			{
				bQuestDisableMapEnter = false; //открыть карту
				DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			}
		break;
		
		case "treatment":
			dialog.text = "Also? Wird er meinen Mann heilen? Sag mir, dass er ihn heilen wird!";
			link.l1 = "Dannie, Nathan muss hier bleiben. Allein. Der Schamane bat darum, seine Rituale nicht zu stören. Das betrifft auch dich. Er hat versprochen, Nathaniel innerhalb eines Monats zu heilen.";
			link.l1.go = "treatment_1";
		break;
		
		case "treatment_1":
			dialog.text = "Weißt du, "+pchar.name+", jetzt kann ich endlich wieder frei atmen. Ich glaube fest daran, dass der Schamane meinen Ehemann wieder in seinen normalen Zustand bringen wird. Ich werde Nathan hier lassen, denn wenn Snake Eye ihn nicht heilen kann - kann es niemand.";
			link.l1 = "Alles wird gut, Dannie. Snake Eye hat mich noch nie belogen. Ich vertraue ihm.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "So werde ich auch. Ich werde für eine Weile bei dir bleiben, "+pchar.name+", bist du damit einverstanden? Wir müssen immer noch diesen Bastard Jackman finden, schließlich ist er für all unsere Probleme verantwortlich. Er hat den Hinterhalt organisiert! Er hat Nathans Platz in Maroon Town eingenommen! Er hat unsere Fregatte 'Centurion' gestohlen!";
			link.l1 = "Einverstanden. Wir müssen uns mit Jackman befassen. Keiner von uns ist sicher, solange Jackman nicht tot ist. Es wird jedoch nicht leicht sein, ihn zu töten.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark Dodson";
			else sTemp = "Marcus Tyrex";
			dialog.text = "Hast du irgendwelche Pläne, "+pchar.name+"?";
			link.l1 = "Noch nicht. Ich muss zu Jan Svenson gehen und ihn um Rat fragen. Lass uns eins nach dem anderen machen, wir müssen "+sTemp+" zuerst zum Anführer der Bruderschaft der Küste ernennen. Also, wir brauchen die Stimme von jedem Piratenbaron, um das zu tun.";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "Gut, gehen wir zu Svenson. Hören wir, was dieser alte Fossil zu sagen hat...";
			link.l1 = "Weißt du, du solltest nicht so negativ gegenüber Jan sein. Tatsächlich wäre es viel besser, wenn du dich mit ihm vertragen würdest... schließlich verfolgen wir alle das gleiche Ziel!";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "Aber nur weil ich dich respektiere... Gut, "+pchar.name+", Es tut mir leid. Ich wollte Svenson nicht beleidigen, ich bin nur nervös. Es wird nicht wieder vorkommen.";
			link.l1 = "Gut. Dannie, alles wird gut. Das kann ich dir versprechen!";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "Ich vertraue dir absolut, "+pchar.name+". Lass uns zu Svenson gehen?";
			link.l1 = "Auf geht's, Dannie!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "13");
		break;
		
		case "islatesoro":
			dialog.text = "Ja? Ich höre zu. Wie kann ich dir helfen?";
			link.l1 = "Hast du eine Ahnung, wo sich dieser Schurke Jackman verstecken könnte? Du kennst diesen Bastard besser als ich. Vielleicht hat er einen Ort, eine Basis...";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			dialog.text = "Verdammt wenn ich es bloß wüsste! Jakob war immer sehr geheimnisvoll. Ich habe noch nie von einem Versteck von ihm gehört. Es ist wahrscheinlich besser, logisch zu denken... Lass uns den Brief noch einmal lesen, den du von Knive bekommen hast. Vielleicht finden wir einen Hinweis darin.";
			link.l1 = "Lass es uns versuchen...";
			link.l1.go = "islatesoro_2";
		break;
		
		case "islatesoro_2":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Nun... es erwähnt Isla Tesoro und irgendein Testament... Sagt dir das etwas?";
			link.l1 = "Ich und Jan denken, dass Blaze Sharp von Jackman auf Isla Tesoro getötet wurde und Shark dafür verantwortlich gemacht wurde. Und ein Testament... eine Hure... es muss um Helen gehen... Verdammt, wie konnte ich das vorher nicht verstehen! Dieser Bastard muss in der Nähe von Isla Tesoro segeln!";
			link.l1.go = "islatesoro_3";
		break;
		
		case "islatesoro_3":
			dialog.text = "Lassen wir dann keine Zeit verschwenden, "+pchar.name+"";
			link.l1 = "Ja. Lass uns zur Isla Tesoro aufmachen. Der alte 'Marlin' wird uns bei diesem Überfall helfen.";
			link.l1.go = "islatesoro_4";
		break;
		
		case "islatesoro_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "18");
			pchar.questTemp.Saga.BarbTemptation = "islatesoro";
			// ставим прерывание на Исла-Тесоро
			pchar.quest.Saga_AttackJackman.win_condition.l1 = "location";
			pchar.quest.Saga_AttackJackman.win_condition.l1.location = "Bermudes";
			pchar.quest.Saga_AttackJackman.function = "Saga_CheckJackmanBermudes";
		break;
		
		case "after_boarding":
			dialog.text = "Dieser Mistkerl ist endlich tot... Ich kann es nicht glauben - Ich stehe wieder auf dem Deck der 'Centurion'! Ich kenne jeden Nagel hier und es scheint, als hätte das Schiff mich auch erkannt.";
			link.l1 = "Sie gehört wieder dir, Dannie. Dir und Nathaniel.";
			link.l1.go = "after_boarding_1";
		break;
		
		case "after_boarding_1":
			PlaySound("Voice\English\saga\Denny Hawk-03.wav");
			dialog.text = "Du kannst dir nicht vorstellen, wie froh ich bin. Nathaniel sprach oft von unserem Schiff, er wird froh sein zu erfahren, dass sie wieder unser ist.";
			link.l1 = "Was wirst du jetzt tun, Dannie?";
			link.l1.go = "after_boarding_2";
		break;
		
		case "after_boarding_2":
			dialog.text = "Ich? Ich werde das Schiff zur Sharp town nehmen, die Mindestbesatzung anheuern und nach Blueweld segeln. Ich werde Jan Svenson bitten, sich um den 'Centurion' zu kümmern, zu den Miskito-Leuten gehen und dort warten, bis Snake Eye meinen Mann geheilt hat.";
			link.l1 = "Bist du wirklich dabei, Jan Svenson zu besuchen? Ich bin überrascht...";
			link.l1.go = "after_boarding_3";
		break;
		
		case "after_boarding_3":
			dialog.text = ""+pchar.name+", es ist alles dein Verdienst. Ich habe über deine Worte nachgedacht: 'wir verfolgen alle das gleiche Ziel'. Erinnerst du dich? Ich möchte Frieden mit Svenson schließen, er hat mir schließlich Nathan zurückgegeben. Es ist Zeit, aufzuhören zu streiten.";
			link.l1 = "Weise Worte, Dannie! Nathaniel wird in der Lage sein, seine Position in Maroon Town wieder einzunehmen, sobald es ihm besser geht.";
			link.l1.go = "after_boarding_4";
		break;
		
		case "after_boarding_4":
			dialog.text = "Vielleicht... die Sache ist, Piratenbaron ist ein Wahlamt. Was ist, wenn die anderen dagegen entscheiden?";
			link.l1 = "Lass Svenson damit umgehen. Er kann jeden überzeugen. Die Eliminierung von Jackman wird auch seine Rolle spielen.";
			link.l1.go = "after_boarding_5";
		break;
		
		case "after_boarding_5":
			dialog.text = "Gut. Ich muss sowieso Svenson zu meinem Freund machen... "+pchar.name+"! Ich möchte dir danken für alles, was du für mich und Nathan getan hast. Du hast meinen Ehemann gerettet und uns alles zurückgegeben, was wir verloren hatten. Ich schulde dir was.";
			link.l1 = "Komm schon, Dannie. Wir sind Freunde.";
			link.l1.go = "after_boarding_6";
		break;
		
		case "after_boarding_6":
			dialog.text = "Ich möchte, dass du weißt, dass wir immer froh sein werden, dich in Maroon Town zu sehen. Schau bei uns vorbei, wenn du etwas Zeit hast. Nathaniel und ich werden einen Weg finden, dich zu entlohnen für alles was du getan hast.";
			link.l1 = "Ach du meine Güte, Dannie! Ich nehme deine Einladung mit Vergnügen an. Wir werden dann sitzen, trinken und darüber reden wie du und Nathan, Van der Decken versenkt habt...";
			link.l1.go = "after_boarding_7";
		break;
		
		case "after_boarding_7":
			dialog.text = "Hat er es dir verraten? Oh, erinnere mich nicht daran...";
			link.l1 = "Gut, Dannie. Du hast noch viel Arbeit vor dir und ich muss unsere geschworenen Freunde - Marcus und Barbazon - besuchen. Ich hoffe, du lässt mich diese Kajüte auf den Kopf stellen, ich bin sicher, in Jackmans Truhen gibt es viele interessante Dinge.";
			link.l1.go = "after_boarding_8";
		break;
		
		case "after_boarding_8":
			dialog.text = "Sicher, glaubst du wirklich, dass ich etwas dagegen hätte?";
			link.l1 = "Schön. Eigentlich ist es schade, sich von dir zu trennen, Dannie... Wir sehen uns in Maroon Town!";
			link.l1.go = "after_boarding_9";
		break;
		
		case "after_boarding_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			LAi_SetHP(npchar, 280, 280); 
			LAi_SetImmortal(npchar, false); // если сработало
			pchar.GenQuest.CannotTakeShip = true; // нельзя захватить
			DoQuestFunctionDelay("Saga_CheckJackmanCabinItems", 5.0); // первая проверка через 5 сек
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = ""+pchar.name+", ich freue mich sehr, dich zu sehen! Wir sind wieder in Maroon Town und Nathan ist wieder an seinem rechtmäßigen Platz. Eigentlich ist jeder im Dorf darüber glücklich. Jetzt wird alles genauso gut laufen wie früher! Ich bin sehr dankbar für deine selbstlose Hilfe!\nIch möchte dir ein Geschenk machen. Hier, nimm es. Dieser Talisman kann einen Kampf für dich so viel einfacher machen. Und diese Formel ermöglicht es dir, mehr von ihnen für dich selbst zu machen.";
			link.l1 = "Danke, Dannie!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			GiveItem2Character(pchar, "totem_12"); 
			GiveItem2Character(pchar, "recipe_totem_12"); 
			Log_Info("Du hast einen Talisman erhalten");
			Log_Info("Du hast das Rezept für den Talisman erhalten");
			PlaySound("interface\important_item.wav");
			dialog.text = "Das ist nicht alles. Ich habe hier auch zwei Kisten voll Gold gefunden. Sie gehörten zweifellos Jackman. Nimm sie als Zeichen meiner Dankbarkeit. Und wage es nicht abzulehnen! Ich weiß, wie viel Geld du verschwendet hast, um mir und Nathan zu helfen.";
			link.l1 = "Gut, gut, Dannie, ich akzeptiere sie!";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			TakeNItems(pchar, "chest", 2); 
			Log_Info("Du hast zwei Truhen mit Dublonen erhalten");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ausgezeichnet! "+pchar.name+", Ich möchte, dass du weißt, dass du ab jetzt unser bester Freund bist. Nathan und ich werden uns immer freuen, dich in Maroon Town zu sehen! Besuch uns öfter!";
			link.l1 = "Danke! Ich werde mich freuen, dich wiederzusehen, also erwarte mich!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_3";
		break;
		
		case "marun_town_3":
			if (CheckAttribute(pchar, "GenQuest.MaruntownSex"))
			{
				dialog.text = "Was können wir für dich tun, "+pchar.name+"?";
				link.l1 = "Ach, leider muss ich gehen... Auf Wiedersehen, Dannie.";
				link.l1.go = "exit";
				if (CheckAttribute(pchar, "GenQuest.MaruntownSex2"))
				{
					dialog.text = "Und hier ist "+GetFullName(pchar)+". Man kann an deinem Gesicht erkennen, dass du keine Zeit verschwendet hast!";
					link.l1 = "Ich muss zugeben, du weißt, wie man Spaß hat! Vielen Dank, ich hatte eine großartige Zeit.";
					link.l1.go = "marun_town_fuckgirl_3";
				}
				NextDiag.TempNode = "marun_town_3";
				break;
			}
			bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
			bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
			dialog.text = "Ich freue mich, dich zu sehen, "+pchar.name+"! Rum, Wein? Oder ein Mädchen?";
			link.l1 = "Danke, Dannie! Ich wollte dich nur sehen...";
			link.l1.go = "exit";
			if (bOk1 || bOk2)
			{
				link.l2 = "Ein Mädchen? Sei leise, Dannie! Du willst mich nicht in Stücke geschnitten und ordentlich gefaltet vor deiner Haustür finden, oder? Ha-ha. Meine treue Dame, die gerade vor der Tür steht, wird mir solche Späße nicht vergeben.";
				link.l2.go = "marun_town_fuckgirl_Otkaz_1";
			}
			else
			{
				link.l2 = "Ein Mädchen? Das klingt interessant, Dannie. Ich sehne mich nach... dem Herzschlag einer Frau... Ich denke, ich sollte einen Blick darauf werfen - du würdest doch nicht einfach irgendwen vorschlagen, oder?";
				link.l2.go = "marun_town_fuckgirl_1";
			}
			NextDiag.TempNode = "marun_town_3";
		break;
		
		// Данни предлагает девочку
		case "marun_town_fuckgirl_Otkaz_1":
			dialog.text = "Wirklich? Warum bist du so blass? Ha-ha, ich habe nur gescherzt. Pass auf sie auf, hörst du?";
			link.l1 = "Natürlich. Sie ist mir wertvoller als alle Schätze in diesen Gefilden!";
			link.l1.go = "marun_town_fuckgirl_Otkaz_2";
		break;
		
		case "marun_town_fuckgirl_Otkaz_2":
			dialog.text = "Das ist besser, ha-ha. Los, geh schon, deine Liebste wird wahrscheinlich nervös.";
			link.l1 = "Auf Wiedersehen, Dannie. Und danke für deine Sorge, ha-ha.";
			link.l1.go = "exit";
		break;
		
		case "marun_town_fuckgirl_1":
			dialog.text = "Ich versichere dir, diese junge Schönheit weiß definitiv, wie man dir eine unvergessliche Zeit beschert, "+pchar.name+". Viel Spaß! Sie wird auf dich in der Taverne warten.";
			link.l1 = "Danke dir, Dannie. Ich bin auf dem Weg. Ich will keine Minute verschwenden!";
			link.l1.go = "marun_town_fuckgirl_2";
		break;
		
		case "marun_town_fuckgirl_3":
			dialog.text = ""+pchar.name+", Du bist immer willkommen in Maroon Town. Die besten Mädchen sind deine!";
			link.l1 = "Oh, Dannie. Ich schwöre, das ist mein zweites Zuhause.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.MaruntownSex2");
			
		break;
		
		case "marun_town_fuckgirl_2":
			DialogExit();
			pchar.GenQuest.MaruntownSex = "true";
			SetTimerCondition("MarunFuckGirl_4", 0, 0, 2, false);
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", false); //открыть комнату
			sld = GetCharacter(NPC_GenerateCharacter("MarunFuckGirl", "women_2"+(rand(6)), "woman", "woman", 1, PIRATE, 1, false, "quest"));
			sld.Dialog.Filename = "Quest\Saga\Danielle.c";
			sld.dialog.currentnode = "MarunFuckGirl";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_tavern_upstairs", "goto", "goto1");
		break;
		
		// Диалог с проституткой
		case "MarunFuckGirl":
			dialog.text = "Und hier ist mein Kapitän. Heute gehörst du nur mir! Komm zu mir, ich habe so lange auf dich gewartet...";
			link.l1 = "Ach, ist das so? Du kannst nicht länger warten? Nun, verschwenden wir keine Zeit!";
			link.l1.go = "MarunFuckGirl_2";
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", true); //закрыть комнату
			chrDisableReloadToLocation = true;
		break;
		
		case "MarunFuckGirl_2":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("MarunFuckGirl", "");
			pchar.GenQuest.MaruntownSex2 = "true";
		break;
		
		case "MarunFuckGirl_3":
			dialog.text = RandPhraseSimple("Mein Kapitän... Sie wissen wirklich, wie man Damen erobert! So etwas hatte ich noch nie! Vielleicht bleiben Sie noch ein paar Stunden länger?","Gehst du schon, meine Liebe?");
			link.l1 = RandPhraseSimple("Ich wusste, dass du mich nicht so leicht gehen lassen würdest. Auf Wiedersehen, Liebling. Große Dinge erwarten mich...","Ach, die Arbeit kommt dazwischen. Aber vielleicht treffen wir uns wieder...");
			link.l1.go = "MarunFuckGirl_4";
		break;
		
		case "MarunFuckGirl_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
	// ------------------------------------------- провалы Саги ------------------------------------------------
		case "failcenturion":
			dialog.text = "Endlich können Nathan und ich wieder frei atmen! Dieser verdammte Bastard Jackman ist tot! Ich fühle mich schlecht für die 'Centurion', aber ich habe ihren Verlust bereits akzeptiert, als dieser Bastard sie mir gestohlen hat. Also mache ich mir nicht allzu viele Sorgen.";
			link.l1 = "Aber ich bin es. Ich bin ein Idiot! Alle Beweise sind zusammen mit dem Schiff auf den Grund des Meeres gesunken. Sie hätten uns bei der Abstimmung für den neuen Anführer der Bruderschaft der Küste helfen können. Jetzt... ist alles weg.";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = "Mach dir keinen Kopf! Das passiert. Nächstes Mal hast du mehr Glück... Egal. Ich möchte dir danken für das, was du für mich und Nathan getan hast. Du hast das Leben meines Mannes gerettet. Ich schulde dir viel.\nIch möchte, dass du weißt, Maroon Town wird sich immer freuen, dich zu sehen. Besuch mich und Nate dort, wenn du Zeit hast. Wir werden einen Weg finden, dir zu danken.";
			link.l1 = "Na gut, Dannie. Ich werde dich sicherlich besuchen. Gehst du schon?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Ja, ich werde zum Miskito gehen, ich hoffe, dass Snake Eye Nathan bereits geheilt hat. Dann kehren wir nach Maroon Town zurück.";
			link.l1 = "Heh, ich habe mich schon so an dich gewöhnt, es ist schade, dass ich mich von dir trennen muss... Viel Glück, Dannie!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Saga_FailCenturion", 10.0);
			npchar.greeting = "danny_2";
		break;
		
		case "before_kiss":
			dialog.text = "Oh, spiel nicht die Dumme, Liebling. Charles, dieser Liebeskäfer lief Tag und Nacht um das Idol herum und nervte den armen Snake Eye mit Fragen. Und dann rannte sie nach Hause und brachte ihm etwas, nicht wahr?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog2");
		break;
		
		case "after_kiss":
			dialog.text = "Oh, danke für die Vorstellung, Charles. Jeder in Maroon Town wird darüber tratschen, ha-ha!";
			link.l1 = "Ich habe keinen Zweifel daran, dass es deine neue Priorität ist - sicherzustellen, dass es passiert.";
			link.l1.go = "after_kiss_1";
		break;
		
		case "after_kiss_1":
			dialog.text = "Ganz unten auf meiner Liste, tatsächlich. Sei nicht böse auf das Mädchen - es ist ihr erstes Mal. Als Nathan und ich unsere Abenteuer hatten, hat das ganze Archipel auch über uns gelacht.";
			link.l1 = "Lassen wir das Thema, und wechseln die Stimmung. Ich bin fertig mit diesem Idol, lass uns gehen.";
			link.l1.go = "after_kiss_2";
		break;
		
		case "after_kiss_2":
			dialog.text = "Einverstanden, lass uns gehen, Held.";
			link.l1 = "";
			link.l1.go = "Dolly_4";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss3");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Danielle_officer":
			dialog.text = "Was willst du, Kapitän?";
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "danielle")
			{
				Link.l3 = "Dannie, ich möchte dich um einen Rat bitten!";
				Link.l3.go = "islatesoro";
			}
			Link.l1 = "Hör auf meinen Befehl!";
            Link.l1.go = "stay_follow";
			link.l2 = "Es ist nichts. wegtreten!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Danielle_officer";
			sld = characterFromId("Danielle");
		    sld.HoldEquip = true; // лесник -  не отдавать саблю и пистоль для текущей игры. поэтому так . другого способа не нашёл						 
		break;
		
		case "stay_follow":
            dialog.Text = "Befehle?";
            Link.l1 = "Steh hier!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Folge mir und halt Schritt!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Wechsel die Art der Munition für deine Feuerwaffen.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Wähle die Art der Munition:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");;
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Es gibt einen Wechsel der Veranlagung!";
            Link.l1 = "Wegtreten.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Es gibt eine Änderung der Gemütsverfassung!";
            Link.l1 = "Wegtreten.";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
