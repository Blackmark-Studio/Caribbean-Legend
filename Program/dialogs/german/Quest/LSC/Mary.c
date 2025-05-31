// Мэри Каспер - взаимная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	int iTime, iAddTime;
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
		case "First time":
			dialog.text = "Was brauchst du?";
			link.l1 = "Nein, es ist nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
	// ---------------------------------покушение на Акулу - вариант R --------------------------------
		// разговор в каюте Адольфа
		case "Cabin":
			dialog.text = "Marcello, ich kenne ihn. Er ist ein Freund von Rivados und den Piraten. Adolf würde niemals mit ihm zusammenarbeiten. Riech die Luft ... riechst du den Geruch von Schießpulver? Und da ist Blut an der Wand ... Er hat Adolf getötet und versucht jetzt, uns zu täuschen! Er muss für den Admiral arbeiten! Töte ihn!";
			link.l1 = "...";
			link.l1.go = "Cabin_fight";
		break;
		
		case "Cabin_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			DialogExit();
			sld = characterFromId("Marchello");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack"))
			{
				for (i=1; i<=3; i++)
				{
					sld = characterFromId("CyclopGuard_"+i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CyclopNMaryDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// на улице
		case "Town":
			dialog.text = "Oh, entschuldige... Könntest du mir bitte helfen, ja, gell?";
			link.l1 = "Hm. Ich bin immer bereit, einer wunderschönen Dame zu helfen. Was ist das Problem?";
			link.l1.go = "Town_1";
		break;
		
		case "Town_1":
			dialog.text = "Siehst du, ich habe eine Truhe voller Metallteile von Sessile Gallard gekauft. Sie lebt auf der 'Eva'. Jurgen versprach mir, etwas Gutes für mich zu schmieden, ja, gell... Ich habe es gekauft, ja, aber ich kann es ihm nicht bringen. So dumm von mir!\nKönntest du mir vielleicht helfen, die Truhe von der 'Eva' zum Narwal-Block auf der 'Esmeralda' zu tragen? Bitte, ich wäre dir sehr dankbar!";
			link.l1 = "Und das ist alles? Sicher, Fräulein, ich werde Ihnen helfen. Nicht viel Mühe.";
			link.l1.go = "Town_2";
		break;
		
		case "Town_2":
			dialog.text = "Danke dir! Ich werde dir zur Truhe führen.";
			link.l1 = "Milady...";
			link.l1.go = "Town_3";
		break;
		
		case "Town_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload41", "LSC_EnterAevaWithMary", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "Town_4":
			dialog.text = "Und hier sind wir... Jetzt sag mir, Schurke, wo ist der Schlüssel?!";
			link.l1 = "Wahnsinn! Ha, es scheint, dass keine Hilfe benötigt wird... Mary.";
			link.l1.go = "Town_5";
		break;
		
		case "Town_5":
			dialog.text = "Schlauer Junge, was? Weniger reden, verdammt! Wo ist der Schlüssel? Gib ihn her oder du wirst es bereuen!";
			link.l1 = "So unhöflich! So eine schlechte Zunge von so einem schönen Mädchen. Welcher Schlüssel?";
			link.l1.go = "Town_6";
		break;
		
		case "Town_6":
			dialog.text = "Der Schlüssel, den du von Adolf Barbier genommen hast. Und leugne es nicht- Du wurdest gesehen, wie du seine Kabine verlässt. Adolf ist tot und es war dein Werk... Jetzt gib mir den Schlüssel!";
			link.l1 = "Also warst du es doch... Das war ein Fehler, Mädchen, ein sehr großer Fehler!";
			link.l1.go = "Town_7";
		break;
		
		case "Town_7":
			PlaySound("Voice\English\LSC\Mary Casper-04.wav");
			dialog.text = "Was hast du gesagt?... Verdammt, du bist kein gewöhnlicher Räuber! Er arbeitet für den Admiral! Nehmt ihn fest, Jungs!";
			link.l1 = "...";
			link.l1.go = "Cabin_fight";
		break;
		
	// ---------------------------------покушение на Акулу - вариант N --------------------------------
		case "caroline":
			dialog.text = "Chad, das ist er! Verdammt, er hat einen Helfer mitgebracht! Jungs, tötet sie alle!";
			link.l1 = "..., Freund.";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			// Акулу к бою
			sld = characterFromId("Dodson");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			// устанавливаем 4 толстых нарвалов
			int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
			int iScl = 65;
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaryGuard_"+i, "citiz_5"+(i+4), "man", "man", iRank, PIRATE, -1, true, "soldier"));
				if(i == 4) 
				{
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_07", "pistol11", "bullet", iScl*2);
					sld.DontClearDead = true;
					sld.SaveItemsForDead = true;
				}
				else FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2);
				if (i < 3) ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
				else ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// Мэри и Чада к бою
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_MarynChadDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
	// ---------------------------------покушение на Акулу - вариант M --------------------------------
		case "mary":
			dialog.text = "Du bist gerade rechtzeitig... Ich hätte sie niemals alleine erledigen können... Puh! Um ehrlich zu sein, dachte ich, ich bin erledigt!";
			link.l1 = "Du hast gekämpft wie eine Walküre! Ich habe noch nie so ein schönes Mädchen so heftig kämpfen sehen...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "Ha, du bist ja ein richtiger Gentleman: Kaum hast du deinen Säbel wieder in die Scheide gesteckt, überschüttest du mich schon mit Komplimenten. Vielen Dank für deine Hilfe. Du hast mich wirklich gerettet, ja, gell? Stell dich bitte vor, Gentleman, ich sehe dich nämlich zum ersten Mal. Bist du schon lange auf der Insel?";
			link.l1 = "Mein Name ist "+GetFullName(pchar)+", aber schöne Damen können mich "+pchar.name+". . Bin ich neu hier? Hm... Das bin ich.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Ich kann es sehen, sicher hätte ich einen so gutaussehenden Mann bemerkt. Mein Name ist Mary, Mary Casper. Aber sie nennen mich die Rote Mary. Das liegt daran, dass ich rothaarig bin, ja, gell?";
			link.l1 = "Es freut mich, dich zu treffen, Mary...";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Oh, ich bin doppelt froh... wenn man bedenkt, dass ich ohne dich tot gewesen wäre! Dieser Bastard Chad hat nicht geblufft. Solch ein Ungeziefer! Und ich war ein Narr, die unteren Türen offen zu lassen. So bist du reingekommen, ja, gell?";
			link.l1 = "Ja, gell? Ich schwamm um die Insel herum und versuchte einen Ort zum Aussteigen zu finden.";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "Ich verstehe. Diese offene Tür hätte mich fast ums Leben gebracht. Jurgen selbst hat die Schlösser für mich geschmiedet, man kann sie ohne den richtigen Schlüssel nicht öffnen und Schlösserknacken hilft nicht. Außerdem bleibe ich nicht still, während jemand versucht, hineinzukommen - vier Fässer meiner Pistole hinterlassen vier Löcher in einer Tür oder einem Körper, ha-ha!\nAber verdammt, Chad lässt mich nicht in Ruhe. Er hat schon Mörder geschickt, um mich 'zu überzeugen', seine Seite zu wählen, er meint es definitiv ernst. Wenn du nicht gewesen wärst, hätte ich ja gesagt. Ich werde hier unter der Belagerung bleiben müssen, "+pchar.name+", ja, gell! Gott sei Dank habe ich das vorausgesehen, ich habe genug Vorräte und Jurgen ist mein Nachbar, mit ihm habe ich keinen Streit.";
			link.l1 = "Mary, warum erzählst du mir nicht mehr über deine Probleme? Ich sehe, dass du meine Hilfe brauchst, aber ich habe kein Wort verstanden, das über deine Lippen gekommen ist.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Aye, ich brauche Hilfe, ja, gell! Ich bin jetzt allein. Ich hatte Streit mit Donald, dann hat sich Chad als Schurke herausgestellt. Oh, entschuldige, ich plappere schon wieder. Also, ich werde dir von der Situation erzählen, in die ich geraten bin...";
			link.l1 = "Denk daran, dass ich neu hier bin, also verstehe ich noch nicht viel. Wer ist dieser Chad, der versucht, dich zu 'überzeugen' oder zu töten? Wer ist Donald?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Chad ist ein Pirat aus der Crew von Admiral Shark Dodson, ein Wärter auf der 'Tartarus'...";
			link.l1 = "Warte! Was hast du gesagt? Shark Dodson? Ist er hier?";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "Du musst heute Abend angekommen sein, da du das noch nicht weißt. Wo sollte Shark sonst sein, als hier? Meine Probleme begannen, als er vor einigen Monaten hier ankam. Obwohl, ich gebe zu, das ist alles Narwhals' und Rivados' Schuld. Als Shark mit seiner Crew hier ankam, wollte er eine Basis errichten, aber unsere Leute und Rivados mochten die Idee wirklich nicht. Sie griffen Sharks Brigg bei Nacht an und setzten sie in Brand\nSie hätten besser nicht! Sharks Crew besteht aus Teufeln, nicht aus Männern, ja, gell. Erst zerstörten sie die feindlichen Boote, dann landeten sie und begannen ein richtiges Gemetzel. Narwhals zogen sich zurück und Rivados rannten so schnell sie konnten davon. Schließlich eroberten die Piraten San Augustine, wo die meisten Vorräte und Ressourcen der Insel gelagert werden, dann nahmen sie Tartarus ein\nShark sperrte unseren Anführer Alan Milrow ein, der auch mein... mein enger Freund war, und den Rivados Zauberer Chimiset. Er schickte sie wie Tiere in die Käfige von Tartarus zum Verrotten. Von hier aus ist es einfach, nach Tartarus zu schwimmen und ich konnte Alan ein paar Mal besuchen. Dort traf ich Chad Kapper, Shark hatte ihn als Wärter eingesetzt. Ich bat Chad, Alan freizulassen, versprach ihm Geld, aber er traute sich nicht, den Admiral zu konfrontieren\nUnd dann wurde Alan im Gefängnis ermordet. Chad erzählte mir, dass Shark das getan hat, ja, gell. Also ging ich zu Donald, der zum Anführer an Alan's Stelle gewählt wurde, und forderte, die Piraten sofort anzugreifen, doch er lehnte ab, sagte, dass diese Seeteufel zu hart für uns sind. Das war, als ich ihm gesagt habe, er soll sich zum Teufel scheren\nMeine Leute waren in dieser Angelegenheit wertlos, also machte ich einen Deal mit Kapper, der Abschaum wollte Sharks Platz einnehmen. Wir hatten einen Plan - den Admiral von seiner Festung in einen zwielichtigen Ort zu locken und ihn dort zu töten. Wir fanden auch einen Scharfschützen mit einem guten Gewehr. Er konnte den Admiral vom Mast der Fury aus erschießen\nJetzt kommt der interessante Teil, vorgestern Nacht besuchte ich Tartarus, wollte Chad etwas Wichtiges bezüglich unseres Plans sagen. Schwamm zum Boot und hörte zufällig Chad mit zwei Narwhals reden. Es stellte sich heraus, dass Shark Alan nicht getötet hat. Chad hat es getan. Er verbreitete dann heimlich Gerüchte über die Beteiligung des Admirals\nEr hat ihn wegen mir ermordet. Erstens, er wollte mich als Spielzeug in seinem Bett haben. Zweitens, er wollte mich benutzen, um Shark loszuwerden - er wusste, dass ich immer Rache suchen würde. Kannst du dir das vorstellen? Was für ein Feigling!";
			link.l1 = "Ja, gell? Ich habe schon solche wie ihn getroffen...";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "Dieser Mistkerl ist noch schlimmer! Er... Mir fehlen einfach die Worte, um dieses Monster zu beschreiben! Damals bin ich gegangen, habe ihn am nächsten Morgen gefunden und ihm alles gesagt, was ich von ihm halte. Ja, ich habe ihm gesagt, dass ich nichts mit seiner Verschwörung gegen den Admiral zu tun haben will, ja, gell?";
			link.l1 = "Und es hat ihm offensichtlich nicht gefallen... Das wurde im Zorn getan, Mary. Du solltest vorsichtiger sein.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			dialog.text = "Ich kann nicht, ich konnte meinen Mund nicht halten. Der Bastard hat Alan getötet und versucht, mich zu benutzen, um seine schmutzigen Ziele zu erreichen! Abschaum! Ja, sicher, er wurde wütend und versprach, dass ich das bereuen würde. Ich sagte, ich würde ihm die Eier abschneiden und sie den Krabben zum Fressen geben!\nEr drohte, seine Narwal-Kumpels auf mich zu hetzen, wenn ich meine Meinung nicht ändern würde. Ich lachte, dachte nicht, dass ein Narwal es wagen würde, Hand an mich zu legen.";
			link.l1 = "Es scheint, du hast dich geirrt.";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "Ja, gell?"+pchar.name+", Ich habe Chad unterschätzt und mich selbst überschätzt. Er hat die Bastarde gefunden, die es wagen würden, ein einsames Mädchen in ihrer eigenen Kabine anzugreifen. Und was soll ich jetzt machen? Ich kann niemandem vertrauen. Ich kann nicht einmal meinen eigenen Leuten vertrauen. Diese beiden sind Narwale, ich kannte beide, ja, gell. Solange Chad lebt - bin ich in Gefahr, er wird zweifellos mehr schicken.\nIch habe Angst rauszugehen, der Scharfschütze, den wir gefunden haben, um Shark zu ermorden, könnte mich vom Gebiet der Rivados aus erschießen und leicht entkommen. Ich werde nicht zu Donald gehen, er wird nicht zuhören.\nAdmiral? Ich kann meine Rolle bei den Vorbereitungen seiner Ermordung nicht erklären! Er wird mich in die Zellen der 'Tartarus' schicken, da bin ich mir sicher! Verdammt, ich bin gefangen. Ich werde hier sitzen mit geladenen Waffen, bis die Vorräte ausgehen und dann... Ich habe keine Ahnung, was aus mir werden wird!";
			link.l1 = "Nun, in diesem Fall habe ich keine andere Wahl, als dir zu helfen, ja, gell? Deine Situation passt sowieso zu meinen Plänen hier...";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			dialog.text = "Du willst mir helfen? Aber wie? Willst du Chad töten?";
			link.l1 = "Dieser Teil des Plans, sicher.";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Hör zu, "+pchar.name+", , Ich schätze deine Absichten, aber Chad ist außerhalb deiner Zone. Er ist einer der vertrauenswürdigsten Freunde des Admirals und selbst wenn du zu ihm kommst - die Piraten der Shark werden dich töten, sie kennen die Wahrheit nicht, ja, gell?";
			link.l1 = "Beruhige dich. Ich muss sowieso mit Shark sprechen.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Also bist du auch ein Pirat?! Erzähl mir von dir, schau dich an: hast in meinen Platz eingebrochen, hast mein Leben gerettet, versprachst zu helfen, siehst dabei gut aus und doch weiß ich nichts über dich!";
			link.l1 = "Gut... Ich bin kein Pirat, aber momentan arbeite ich mit einem gewissen Piratenbaron Jan Svenson. Ich bin hierher gekommen, um Nathaniel Hawk zu finden. Hast du von ihm gehört?";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			dialog.text = "Nein, wer ist er?";
			link.l1 = "Er ist ein weiterer berühmter Pirat. Es ist schade, dass du ihn noch nicht getroffen hast, er muss hier irgendwo sein. Ich habe auch nach Shark gesucht, aber ich habe nicht erwartet, ihn hier zu finden.";
			link.l1.go = "mary_15";
		break;
		
		case "mary_15":
			dialog.text = "Aber wie bist du hierher gekommen? Du siehst zu gut aus für einen Schiffbruchüberlebenden.";
			link.l1 = "Und warum denkst du, dass ich Schiffbruch erlitten habe?";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "Das ist der einzige Weg hierher zu kommen. Nur Shark hat es irgendwie geschafft, hierher zu segeln.";
			link.l1 = "Nun, wie du siehst, war Shark nicht der Einzige.";
			link.l1.go = "mary_17";
		break;
		
		case "mary_17":
			dialog.text = "Also, hast du ein Schiff? Wunderbar!";
			link.l1 = "Beruhige dich nicht so schnell, Mary. Ich bin hier durch... auf einer Bark gelandet, aber sie ist auf den Grund gesunken.";
			link.l1.go = "mary_18";
		break;
		
		case "mary_18":
			dialog.text = "A-ah... Nun, wie ich sagte - ein Schiffbruch. Du bist jetzt hier mit uns gefangen, ja, gell?";
			link.l1 = "Mary, lass mich dir meinen Plan erzählen. Du hast erwähnt, dass Chad vorhat, Shark zu töten. Ich brauche Shark lebend, Jan und ich werden ihn zum Anführer der Piraten machen. Deshalb muss ich ihn warnen, denn aus deiner Geschichte bin ich sicher, dass Chad es mit oder ohne deine Hilfe versuchen wird, ja, gell?";
			link.l1.go = "mary_19";
		break;
		
		case "mary_19":
			dialog.text = "Aye, wahrscheinlich. Er hat die Männer, um es geschehen zu lassen...";
			link.l1 = "Das bedeutet, dass mein Hauptziel darin besteht, das Vertrauen des Hais zu gewinnen und ihn zu retten. Dann werde ich offiziell zu Chad gelangen. Hast du irgendwelche Beweise für seine Absichten?";
			link.l1.go = "mary_20";
		break;
		
		case "mary_20":
			dialog.text = "Ich habe seinen Brief bekommen, der von einem dieser... Idioten auf dem Boden hierher gebracht wurde. Es gibt Drohungen und Details, die der Admiral interessant finden könnte. Warte! Und was ist mit mir? Shark wird herausfinden, dass ich mit Chad gearbeitet habe!";
			link.l1 = "Mary, wirst du für immer hier sitzen, bewaffnet mit Pistolen und dein süßes Gesicht vor allen verstecken? Hältst du mich wirklich für einen der Idioten, die eine schöne Dame tot sehen wollen? Zeig mir zuerst den Brief, mal sehen, was ich tun kann...";
			link.l1.go = "mary_21";
		break;
		
		case "mary_21":
			GiveItem2Character(pchar, "letter_chad_1");
			RemoveItems(npchar, "letter_chad_1", 1);
			dialog.text = "Hier. Was denkst du?";
			link.l1 = "Halte durch... (liest). Ja, es scheint, dass Chad eine besondere Art von Bastarden ist, die diese Erde heimsuchen. Dieser Brief wird ausreichen, um Shark darauf brennen zu lassen, Chad selbst den Strick um den Hals zu legen. Mach dir keine Sorgen, Milady, ich werde dafür sorgen, dass Shark nichts von dir ahnt. Er wird sowieso zu beschäftigt mit Chad sein.";
			link.l1.go = "mary_22";
		break;
		
		case "mary_22":
			dialog.text = "Wirst du das tun? Versprich es mir, ja, gell? Schwöre, dass du mich nicht verrätst!";
			link.l1 = "Mary, ich schwöre dir, ich werde dich nicht verraten. Mach dir keine Sorgen, ich habe dich nicht gerettet, nur um das geschehen zu sehen\nChad wird dich sicher nicht in Ruhe lassen, du weißt zu viel. Bleib hier, bis er tot ist.";
			link.l1.go = "mary_23";
		break;
		
		case "mary_23":
			dialog.text = "Ja, ich bleibe hier. Ich will nicht von einem Scharfschützen erschossen oder von hinten erstochen werden.";
			link.l1 = "Gutes Mädchen. Schließe alle Türen, auch die unteren. Hast du nur einen Schlüssel?";
			link.l1.go = "mary_24";
		break;
		
		case "mary_24":
			dialog.text = "Nein. Es gibt noch einen. Willst du ihn?";
			link.l1 = "Ja, gell? Vertraust du mir?";
			link.l1.go = "mary_25";
		break;
		
		case "mary_25":
			dialog.text = "Nun, wenn der Gentleman, der gerade mein Leben gerettet hat, mich verrät, gibt es keinen Grund mehr zu leben... Nimm es.";
			link.l1 = "Hab keine Angst, Schönheit! Ich werde dich nicht im Stich lassen. Ich werde dich sehen, sobald ich dieses Durcheinander gelöst habe. Ich hoffe, es dauert nicht zu lange.";
			link.l1.go = "mary_26";
		break;
		
		case "mary_26":
			GiveItem2Character(pchar, "key_mary");
			dialog.text = "Alles ist in Ordnung, ich kann diesen Ort für ein paar Wochen halten, ja, gell?";
			link.l1 = "Großartig. Dann werde ich keine Zeit verschwenden. Ich werde die Leichen rausholen und mit Shark sprechen. Er ist auf der 'San Augustine', richtig?";
			link.l1.go = "mary_27";
		break;
		
		case "mary_27":
			dialog.text = "Ja, er ist immer da. Und geh raus, so wie du hierher gekommen bist - Ich lasse dich nicht auf das Oberdeck der 'Ceres Schmiede' treten, ja, gell?";
			link.l1 = "Interessant, und warum ist das so?";
			link.l1.go = "mary_28";
		break;
		
		case "mary_28":
			dialog.text = "Weil du mir nicht helfen kannst, wenn du stirbst. Dies ist das Territorium der Narwale und sie werden dich als Außenseiter töten.";
			link.l1 = "Hm... Verstanden. Nun, Mary, wir sehen uns. Ich komme zurück, sobald es sicher ist.";
			link.l1.go = "mary_29";
		break;
		
		case "mary_29":
			dialog.text = "Du kannst mich sehen, wann immer du willst, ich habe damit kein Problem. (kichert)";
			link.l1 = "Auf Wiedersehen, schöne Dame!";
			link.l1.go = "mary_30";
		break;
		
		case "mary_30":
			DialogExit();
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "mary_wait";
			npchar.greeting = "mary_3";
			AddQuestRecord("SharkHunt", "31");
			AddQuestRecordInfo("Chad_Mary_letter", "2");
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем выходы
		break;
		
		case "mary_wait":
			dialog.text = "Hallo, "+pchar.name+", gibt es gute Neuigkeiten für mich? Geht es dir gut?";
			if (pchar.questTemp.Saga.SharkHunt == "mary_whiskey")
			{
				link.l1 = "Das Problem mit dem Admiral ist gelöst. Er hat kein Interesse daran, dich zu jagen, Chad's Verrat ist das einzige, was ihn beunruhigt.";
				link.l1.go = "letters";
			}
			else
			{
				link.l1 = "Noch nicht, Mary. Aber ich werde alles in meiner Macht Stehende tun.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "mary_wait";
		break;
		
		case "letters":
			dialog.text = "Oh, Gott sei Dank! Danke, ich werde es nicht vergessen, ja, gell! Zumindest droht keine Gefahr vom Admiral. Und was ist mit Chad? Was hat Shark getan?";
			link.l1 = "Wir haben die Rivados überzeugt, ihn anzugreifen. Layton Dexter hat Wachen aus der 'Tartarus' genommen und den Schlüssel an Black Eddie gegeben. Die schwarzen Kerle haben ihren Zauberer Chimiset befreit, aber sie haben es nicht geschafft, Chad zu töten. Sie haben zwei seiner Narwal-Freunde getötet, aber er ist davongelaufen und versteckt sich irgendwo.";
			link.l1.go = "letters_1";
		break;
		
		case "letters_1":
			dialog.text = "Verdammt! Das bedeutet, dass ich jetzt noch vorsichtiger sein muss...";
			link.l1 = "Beruhige dich, Mary. Ich bin sicher, er hat bedrohlichere Leute, um die er sich sorgen muss. Er weiß wahrscheinlich, wer die Rivados auf ihn gehetzt hat. Er wird alles tun, um Shark zu töten, nicht dich, ja, gell?";
			link.l1.go = "letters_2";
		break;
		
		case "letters_2":
			dialog.text = "Glaubst du das wirklich? Chad ist nicht der Typ, der Dinge so leicht auf sich beruhen lässt. Ah, ich bin zu müde, um noch länger Angst zu haben...";
			link.l1 = "Hm. Ich dachte nicht, dass Sie die Art von Dame sind, die sich leicht erschrecken lässt.";
			link.l1.go = "letters_3";
		break;
		
		case "letters_3":
			dialog.text = "Ha! Bin ich das nicht? Ich habe keine Angst vor einem Kampf von Angesicht zu Angesicht, aber auf meinem Arsch zu sitzen und darauf zu warten, getötet zu werden? Das macht mir sehr Angst "+pchar.name+", ja, gell!...";
			link.l1 = "Vertraue mir, Mary: Kapper hat momentan genug mit dem Admiral zu tun... Ich brauche deinen Rat.";
			link.l1.go = "letters_4";
		break;
		
		case "letters_4":
			dialog.text = "Mein Rat? Welche Art von Rat?";
			link.l1 = "Eddie hat zwei Briefe von Chad gefunden. Lies sie, vielleicht weißt du, was er vorhat. Du warst schließlich mit Chad in dem Plan verwickelt...";
			link.l1.go = "letters_5";
		break;
		
		case "letters_5":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Gib sie mir... (liest). Axel ist unser Händler auf der 'Esmeralda', ja, gell. Aus irgendeinem Grund wollte Chad Whisky von ihm kaufen. Seltsam! Chad trinkt nur Rum, er sagt, Whisky sei 'der Fusel der Bauern'...";
			link.l1 = "Und was ist mit dem zweiten Brief?";
			link.l1.go = "letters_6";
		break;
		
		case "letters_6":
			dialog.text = "Marcello? Marcello Cyclops, ein ehemaliger königlicher Jäger. Er ist der Hauptgrund, warum ich mich weigere, diese Kabine zu verlassen.";
			link.l1 = "Ist er der Scharfschütze, den du angeheuert hast?";
			link.l1.go = "letters_7";
		break;
		
		case "letters_7":
			dialog.text = "Ja, gell? Marcello kann trotz seines fehlenden Auges eine Fliege aus vierzig Fuß Entfernung abschießen. Seine Mission war es, Shark mit einem Fernstutzen vom Bugspriet der Santa Florentina oder von Furys Plattform aus zu erledigen...";
			link.l1 = "Also scheint es, dass Chad sich entschieden hat, Shark auszuschalten. Aber was ist dann der Sinn von Eva? Cecille? Getränke?";
			link.l1.go = "letters_8";
		break;
		
		case "letters_8":
			dialog.text = "Eva ist ein neutrales Schiff und Cecille ist Cecille Halard, eine lustige alte Frau, die dort lebt. Sie zog vor nicht allzu langer Zeit von der Santa Florentina dort ein. Orelie Bertine ist eine Freundin von ihr. Sie haben hier zusammen gelebt, bevor ich überhaupt geboren wurde, ja, gell?";
			link.l1 = "Hm. Unsinn. Zwei große Kerle verstecken sich vor einer alten Frau, um zusammen einen ganzen Fass Whisky zu trinken. Quatsch... Nicht gerade die beste Zeit zum Trinken, Chad!";
			link.l1.go = "letters_9";
		break;
		
		case "letters_9":
			dialog.text = "Ich habe dir bereits gesagt, dass er keinen Whisky trinkt. Nur Rum, irgendwas stimmt hier nicht.";
			link.l1 = "Gut, was auch immer. Weißt du, wo man den Zyklopen findet?";
			link.l1.go = "letters_10";
		break;
		
		case "letters_10":
			dialog.text = "Nein. Er ist sehr zurückhaltend. Er schießt jeden Tag Vögel am äußeren Ring und niemand weiß, wo er schläft. Er hat oft Rivados besucht, ja, gell?";
			link.l1 = "So ein Pech... Nun, ich werde dann mit Axel reden. Vielleicht wird er mehr Sinn daraus ziehen. Wir sehen uns, Mary! Mach die Tür zu!";
			link.l1.go = "letters_11";
		break;
		
		case "letters_11":
			dialog.text = ""+pchar.name+"! Bitte finde Chad. Beeile dich, seit dem letzten Angriff habe ich nicht geschlafen.";
			link.l1 = "Halte durch, Liebling. Ich werde mein Bestes geben.";
			link.l1.go = "letters_12";
		break;
		
		case "letters_12":
			DialogExit();
			NextDiag.CurrentNode = "mary_wait";
			pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			AddQuestRecord("SharkHunt", "35");
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! Wie ist er hierher gekommen? Ist er gekommen um...";
			link.l1 = "Ja, um dich zu töten, Mary. Er kam hier durch Jurgens Kabine und benutzte ein Seil, um hier runter zu klettern.";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			dialog.text = "Ach! Ich bin so eine Dummkopf, dass ich diesen Weg vergessen habe! Chad hat es ihm sicher beigebracht, ja, gell?";
			link.l1 = "Höchstwahrscheinlich. Ich habe es gerade noch geschafft. Er war hinter dir her.";
			link.l1.go = "happy_2";
		break;
		
		case "happy_2":
			dialog.text = "Und ich habe geschlafen. Er hätte mich in einer Sekunde getötet... Aber wie wusstest du, dass er auf dem Weg hierher war?";
			link.l1 = "Ich habe... Ich habe es gerade getan, Mary.";
			link.l1.go = "happy_3";
		break;
		
		case "happy_3":
			dialog.text = "Du hast mich wieder gerettet, Schönling. Du kommst immer zum perfekten Zeitpunkt, ja, gell? Wie machst du das?";
			link.l1 = "Nun, ich weiß nicht. Eines meiner vielen Talente. Deine Belagerung ist vorbei - Chad Kapper ist tot und all seine Freunde auch. Cyclops war der Letzte seiner verdammten Mannschaft.";
			link.l1.go = "happy_4";
		break;
		
		case "happy_4":
			dialog.text = "Wirklich? Ist es wahr, "+pchar.name+"Du versuchst nicht, mich zu täuschen, oder?";
			link.l1 = "Ganz und gar nicht. Eh, ich brauche nach den Ereignissen der letzten Tage etwas Ruhe...";
			link.l1.go = "happy_5";
		break;
		
		case "happy_5":
			dialog.text = "Ich kann endlich wieder frei atmen! Danke... Vielen Dank! Du bist mein Held, ja, gell?";
			link.l1 = "Ich liebe den Klang davon, dein Held zu sein, ja, gell? Bin einfach nur froh, dass du endlich in Sicherheit bist.";
			link.l1.go = "happy_6";
		break;
		
		case "happy_6":
			dialog.text = "Na und?";
			link.l1 = "Was ist los, Hübsche?";
			link.l1.go = "happy_7";
		break;
		
		case "happy_7":
			dialog.text = "Warum stehst du da? Komm schon, Gentleman.";
			link.l1 = "Und was tun?";
			link.l1.go = "happy_8";
		break;
		
		case "happy_8":
			dialog.text = "Du bist wirklich ein Gentleman... Komm her und umarme mich, küsse mich endlich, du willst das, ich sehe das, ja, gell!";
			link.l1 = "Mary...";
			link.l1.go = "happy_9";
		break;
		
		case "happy_9":
			DialogExit();
			LAi_Fade("LSC_MaryRomantic_1", "");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, false, true);
			PlayStereoOGG("music_romantic");
			pchar.questTemp.LSC.MaryBye = "true"; // атрибут обязательного прощания перед телепортацией
			LocatorReloadEnterDisable("LostShipsCity_town", "reload62", false);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload63", false); // открываем Церес снаружи
		break;
		
		case "happy_10":
			dialog.text = "Lass mich nicht allein...";
			link.l1 = "Ich bin hier, Mary, Liebling...";
			link.l1.go = "happy_11";
		break;
		
		case "happy_11":
			dialog.text = "Alles kann warten. Der Admiral wird warten, deine Piraten werden warten. Diese Nacht gehört nur uns beiden, ja, gell?!";
			link.l1 = "Natürlich...";
			link.l1.go = "happy_12";
		break;
		
		case "happy_12":
			dialog.text = "Und auch alle nächsten Nächte danach...";
			link.l1 = "Ja, Mary.";
			link.l1.go = "happy_13";
		break;
		
		case "happy_13":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("LSC_MaryRomantic_5", 4.0);
		break;
		
	// ----------------------------------вместе с Мэри на Церес Смити------------------------------------------
		case "LSC_love":
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! Du bist zurück... ohne sie. Also konnte sie dich nicht von mir wegnehmen!";
				link.l1 = "Mary, deine Vermutungen waren unbegründet. Du bist die Einzige für mich. In meinen Gedanken und Träumen war ich immer bei dir.";
				link.l1.go = "adversary_hire_return";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", , warum kämpfst du mit den Narwalen? Ich lebe tatsächlich auf ihrem Territorium, falls du es vergessen hast. Bitte, geh zu Fazio und schließe Frieden, ich flehe dich an.";
				link.l1 = "Ja, gell, Mary, ich werde tun, was du verlangst.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.FindDolly")) // нашёл статую - прощается
			{
				dialog.text = ""+pchar.name+", etwas bedrückt dich. Was ist los?";
				link.l1 = "Mary, ich muss mit dir reden.";
				link.l1.go = "dolly";
				break;
			}
			if (CheckAttribute(npchar, "quest.donald"))
			{
				dialog.text = ""+pchar.name+"! Alle Narwale sprechen über dich!";
				link.l1 = "Wirklich, mein Liebling?";
				link.l1.go = "donald";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! Dieses Breitschwert ist unglaublich! Danke nochmal!.. Ich möchte dir auch ein Geschenk machen. Natürlich kann es nicht mit deinem verglichen werden, aber ich möchte, dass du es nimmst, ja, gell?";
				link.l1 = "Mary, der Wert eines Geschenks ist unwichtig... Danke, meine Liebe";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Habe einen anstrengenden Tag vor mir, "+pchar.name+"? Viel Glück!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, wir müssen heute Jurgen sehen.";
					link.l3.go = "narval";
				}
				link.l1 = "Danke, Mary! Daran habe ich keinen Zweifel.";
				link.l1.go = "exit";
				link.l2 = "Nein, Mary. Ich möchte hier ein wenig Ruhe finden. Ist das für dich in Ordnung?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Nun, "+pchar.name+", wie geht es dir? Läufst du wie gewöhnlich auf der Insel herum?";
				link.l1 = "Ja, Mary. Es gibt viel zu tun...";
				link.l1.go = "LSC_love_1";
			}
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_1":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "Es ist bereits Abend, "+pchar.name+", wovon redest du? Bleib hier, lass uns etwas trinken und entspannen, ja, gell! Es kann bis zum Morgen warten!";
				link.l1 = "(lachend) Natürlich, Liebe, sag weniger...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, lass uns heute zur Taverne gehen!";
					link.l2.go = "LSC_tavern";
				}
				link.l3 = "Mary, Liebling, ich bin jetzt sehr beschäftigt. Ich komme später zurück.";
				link.l3.go = "LSC_love_2";
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Vergiss nicht, mich am Abend zu besuchen. Und wage es nicht, mir aus dem Weg zu gehen, ja, gell!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, wir müssen heute Jurgen sehen.";
					link.l3.go = "narval";
				}
				link.l1 = "Sicher, Mary, wie könnte ich nicht? Natürlich werde ich dich besuchen.";
				link.l1.go = "exit";
				link.l2 = "Nein, Mary. Ich möchte heute Nacht hier ausruhen. Ist das für dich in Ordnung?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love";
				break;
			}
			dialog.text = "Wovon redest du? Es ist bereits Nacht! Nein, du gehst nirgendwohin, du bleibst hier, bei mir, ja, gell?";
			link.l1 = "(lachend) wie du willst, Liebling...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_2":
			dialog.text = "Mach nicht mal...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
		break;
		
		// сходить в таверну
		case "LSC_tavern":
			dialog.text = LinkRandPhrase("Eine großartige Idee, "+pchar.name+", ja, gell! Ich bin einverstanden!","Ja, los geht's, "+pchar.name+"! Sancho hat eine feine Auswahl an Weinen, es gibt viel zur Auswahl!","Oh, das wäre mir recht, ja, gell! In der Taverne von Sancho ist es immer lustig und er hat eine großartige Auswahl an Weinen!");
			link.l1 = "Lass uns gehen!";
			link.l1.go = "LSC_love_tavern";
		break;
		
		// --> отдых
		case "rest_morning":
			dialog.text = "Natürlich, "+pchar.name+"Sicher, ruh dich aus, ja, gell!";
			link.l1 = "Ich werde bis zum Mittag bleiben...";
			link.l1.go = "rest_day";
			link.l2 = "Ich werde bis zum Abend bleiben...";
			link.l2.go = "rest_evening";
		break;
		
		case "rest_afternoon":
			dialog.text = "Natürlich, "+pchar.name+"Sicher, ruh dich aus, ja, gell!";
			link.l1 = "Ich werde bis zum Abend bleiben...";
			link.l1.go = "rest_evening";
		break;
		
		case "rest_day":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 13 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		
		case "rest_evening":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 18 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- отдых
		
	//--> если скоро уходит через портал
		case "LSC_love_3": 
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! Du bist zurück... ohne sie. Also konnte er dich nicht von mir wegnehmen!";
				link.l1 = "Mary, deine Verdächtigungen waren unbegründet. Du bist die Einzige für mich. In meinen Gedanken und in meinen Träumen war ich immer bei dir.";
				link.l1.go = "adversary_hire_return";
				break;
			} // 291112
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", warum kämpfst du gegen die Narwale? Ich lebe auf ihrem Territorium, eigentlich bin ich einer von ihnen, falls du es vergessen hast. Bitte, geh zu Fazio und schließe Frieden, ich flehe dich an.";
				link.l1 = "In Ordnung, Mary, ich werde tun, wie du fragst, ja, gell?";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! Dieses Breitschwert ist unglaublich! Danke nochmals!.. Ich möchte dir auch ein Geschenk machen. Natürlich kann es nicht mit deinem mithalten, aber ich möchte, dass du es nimmst, ja, gell.";
				link.l1 = "Mary, der Wert eines Geschenks spielt keine Rolle... Danke, meine Liebe";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Schon gehst du, "+pchar.name+"? Viel Glück und vergiss mich nicht...";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, wir sollten heute Jurgen besuchen gehen.";
					link.l3.go = "narval";
				}
				link.l1 = "Natürlich, Mary.";
				link.l1.go = "exit";
				link.l2 = "Nein, Mary. Ich möchte hier etwas Ruhe finden. Ist das für dich in Ordnung?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Gehst du nicht zu deinem Kukulcan Ding, "+pchar.name+"?";
				link.l1 = "Noch nicht, immer noch vorbereiten.";
				link.l1.go = "LSC_love_4";
			}
			NextDiag.TempNode = "LSC_love_3";
		break;
		
		case "LSC_love_4":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "Es ist schon Abend, "+pchar.name+". Warum bleibst du nicht hier? Ich möchte bei dir sein.";
				link.l1 = "Ja, gell, Liebling, ich bleibe...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, lass uns heute in die Taverne gehen!";
					link.l2.go = "LSC_tavern";
				}
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Viel Glück und vergiss mich nicht... Besuch mich am Abend, wenn du kannst, ja, gell!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, wir sollten heute Jurgen sehen.";
					link.l3.go = "narval";
				}
				link.l1 = "Sehr gut, Liebling.";
				link.l1.go = "exit";
				link.l2 = "Mary, ich möchte mich hier etwas ausruhen. Hast du etwas dagegen, ja, gell?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love_3";
				break;
			}
			dialog.text = "Wovon redest du? Es ist Nacht! Nein, du gehst nirgendwohin, du wirst hier bleiben, ja, gell!";
			link.l1 = "(lachend) Ja, gell, ich bleibe...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love_3";
		break;
		// <-- скоро уходит через портал
		
	// --> взаимоотношения - секс и прочее
		case "LSC_love_tavern":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_MaryTavern");
		break;
		
		case "LSC_love_evening":
			DialogExit();
			//if(CheckAttribute(PChar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LSC_MaryEveneng();
		break;
		
		case "LSC_love_night":
			DialogExit();
			LSC_MaryLove();
		break;
		
		case "LSC_love_morning":
			if (CheckAttribute(npchar, "quest.hire"))
			{
				dialog.text = "Kapitän "+pchar.name+"! Offizierin Mary Casper ist bereit, unter Ihrem Kommando zu dienen!";
				link.l1 = "Gut gemacht, Offizier! Ich befehle Ihnen, sofort an Bord des Schiffes zu gehen. Aber zuerst: Küssen Sie Ihren Kapitän!";
				link.l1.go = "LSC_mary_hire";
			}
			else
			{
				dialog.text = "Das war fantastisch, Liebling... Guten Morgen!";
				link.l1 = "Guten Morgen, Liebling! Du bist wunderbar!";
				link.l1.go = "LSC_love_morning_1";
			}
		break;
		
		case "LSC_love_morning_1":
			DialogExit();
			LAi_SetOwnerType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- взаимоотношения
		
		// стал другом нарвалам
		case "donald":
			dialog.text = "Hast du mit Donald gesprochen? Ist es wahr, dass der Admiral eine Allianz mit den Rivados eingehen und gegen die Narwale kämpfen wollte? Ist es wahr, dass du ihn davon abgebracht hast? Es wird Frieden zwischen den Piraten und Narwalen geben, ja, gell?";
			link.l1 = "Ja, Mary. Das ist so.";
			link.l1.go = "donald_1";
		break;
		
		case "donald_1":
			dialog.text = ""+pchar.name+", Ich finde einfach keine Worte... Man sagt auch, dass Donald dich als Freund ansieht. Du könntest einer von Narwhals werden, ja, gell!";
			link.l1 = "Besuche Donald, wenn du kannst - er möchte auch mit dir Frieden schließen. Er bittet dich, ihm seine Worte und seine Unfähigkeit, dich vor diesen zwei Bastarden zu schützen, zu verzeihen.";
			link.l1.go = "donald_2";
		break;
		
		case "donald_2":
			dialog.text = "Zum Teufel mit Donald! Obwohl ich das natürlich gerne höre. Ich werde ihn sehen. Aber du! Ich... nein, nicht so... Ich bin stolz auf dich, ja, gell!";
			link.l1 = "Herrgott, Mary... du bist... ah, du bringst mein Herz zum Rasen!";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
			DeleteAttribute(npchar, "quest.donald");
		break;
		
		// ноды прощания
		case "dolly":
			dialog.text = "Lass uns reden! Bist du in Schwierigkeiten?";
			link.l1 = "Nein. Mary, erinnerst du dich an die Nacht, als wir uns zum ersten Mal trafen? Nachdem wir mit diesen zwei Bastarden fertig waren, habe ich dir erzählt, dass ich mit einem Schiff hier angekommen bin.";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Ich erinnere mich, ja. Deine Barke ist gesunken und du musstest hierher schwimmen... ja, gell!";
			link.l1 = "Ich habe gelogen. Du hättest mich für verrückt gehalten, wenn ich dir damals die Wahrheit gesagt hätte. Es gab keine Barke. Ich habe eine unerklärliche Kraft des indischen Gottes 'Kukulcan' benutzt, um an diesen Ort zu gelangen.";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = ""+pchar.name+"... Wovon redest du? Kukulcan?";
			link.l1 = "Mary, Liebling, du musst mir glauben, denn es ist nichts Rationales dabei, und ich kann das mit niemandem teilen, außer dir. Nathaniel Hawk verschwand, indem er das indische Idol berührte, er wurde gejagt und es rettete ihn...";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "";
			link.l1 = "Ich suchte Nathaniel. Ich hatte ein Gespräch mit einem indischen Schamanen und musste das Gleiche tun wie Hawk. Ich wurde in den Laderaum der 'San Augustine' teleportiert, kam durch ein Loch in ihrem Rumpf heraus und das Schicksal brachte mich zu dir.";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Ist das etwa eine lustige Geschichte über unsere erste Begegnung, die wir eines Tages unseren Kindern erzählen werden? Oder bist du verrückt geworden?";
			link.l1 = "Ich meine es ernst, Mary. Ich verstehe, dass es schwer zu glauben ist und für dich verrückt erscheinen muss, aber bitte, vertraue mir.";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "Es scheint, dass Erics Geschichten wahr waren...";
			link.l1 = "Wer ist Eric? Und was hat er dir erzählt?";
			link.l1.go = "dolly_6";
		break;
		
		case "dolly_6":
			dialog.text = "Eric war einer der Einheimischen, ein alter Seemann. Er ist bereits tot. Als ich ein Kind war, erzählte er mir Geschichten über einen goldenen Götzen, einen Schrein, an dem Rivados Menschen opferten. Hier, auf der Insel\nDiejenigen, die es berührten, verschwanden und wurden nie wieder gesehen. Ich dachte, es wären nur Geschichten, um die Kinder zu erschrecken.";
			link.l1 = "Es ist wahr, Mary. Eric hat nicht gelogen.";
			link.l1.go = "dolly_7";
		break;
		
		case "dolly_7":
			dialog.text = "Glücklicherweise ist das Schiff mit diesem schrecklichen Idol gesunken. Ich habe es nie mit meinen eigenen Augen gesehen.";
			link.l1 = "Ich habe es gefunden, es liegt am Grund.";
			link.l1.go = "dolly_8";
		break;
		
		case "dolly_8":
			dialog.text = "Hast du dort getaucht?! Hat dir dieser verfluchte Erfinder Vedecker seinen Anzug gegeben? Dort unten krabbeln Krabben herum, ja, gell! Bastard! Dich so in Gefahr zu bringen!";
			link.l1 = "Mary, mach dir keine Sorgen um mich. Ich kann mit den Monstern umgehen. Sie sind nicht so bedrohlich, wie die Leute sagen. Seit meinem ersten Tag auf dieser Insel suche ich nach der Statue und endlich habe ich sie gefunden.";
			link.l1.go = "dolly_9";
		break;
		
		case "dolly_9":
			dialog.text = "Und was wird jetzt passieren?";
			link.l1 = "Dies ist der einzige Ausweg hier. Ich bin durch ein Idol genau wie dieses hier zu diesem Ort gekommen, und ich werde es wieder benutzen, um zurückzukommen... Mary! Weinst du? Mary! Hör auf damit!";
			link.l1.go = "dolly_10";
		break;
		
		case "dolly_10":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark, ";
			else sTemp = "";
			dialog.text = "Warum sollte ich? Ich werde weinen, ich will weinen, ja, gell... (schluchzt) Solche Dinge passieren immer meinen Männern! Ich werde wieder allein sein!";
			link.l1 = "Was glaubst du, was mit mir passieren wird? Glaubst du wirklich, ich würde dich hier lassen?! Ich komme zurück für dich, auf einem Schiff. Ich muss sowohl dich als auch "+sTemp+"Nathaniel zurück mit mir. Wirst du mir in die äußere Welt folgen?";
			link.l1.go = "dolly_11";
		break;
		
		case "dolly_11":
			dialog.text = "(unter Tränen) Natürlich.... Klar, ich werde... Du wirst für mich zurückkommen, ja, gell? Wie zum Teufel planst du zurück zur Insel zu kommen? Nur Shark weiß, wie man hierher segelt. Und wage es nicht, mich zu vergessen, oder ich werde dich schlagen, wenn ich dich finde!";
			link.l1 = "Mary, genug mit deinen wilden Gedanken! Natürlich komme ich für dich zurück, wer sonst soll mein Herz so schlagen lassen, wie es seit dem Tag tut, an dem ich dich getroffen habe? Mach dir keine Sorgen, meine Liebe, Shark hat mir die Koordinaten und Richtungen mitgeteilt. Ich werde meinen Weg zu dir finden.";
			link.l1.go = "dolly_12";
		break;
		
		case "dolly_12":
			dialog.text = "Du hast gesagt, dass eine Statue dich direkt vom Main hierher gebracht hat, aber was ist, wenn diese Statue dich woanders hinbringt, vielleicht nach Afrika? Was soll ich dann ohne dich machen?!";
			link.l1 = "Kukulcan ist ein indischer Gott, er wird mich irgendwo in die Karibik oder nach Main bringen. Ich muss nur eine Siedlung finden, dann wird es für mich leicht sein, mein Schiff und meine Besatzung zu finden.";
			link.l1.go = "dolly_13";
		break;
		
		case "dolly_13":
			dialog.text = "(weint) Versprich mir ... nein, schwöre mir, dass du zurückkommen wirst, ja, gell!";
			link.l1 = "Mary, Liebling, ich schwöre dir, dass ich zurückkommen werde. Und ich werde dich von diesem elenden Ort wegbringen. Du brauchst mich nicht zu lange zu vermissen. Genug mit den Tränen.";
			link.l1.go = "dolly_14";
		break;
		
		case "dolly_14":
			dialog.text = "Gut, "+pchar.name+"... ... Komm zurück zu mir, ich werde warten, ja, gell! Wann wirst du gehen?";
			link.l1 = "Ich weiß es noch nicht. Ich muss mich zuerst vorbereiten, dann werde ich tauchen und die Statue berühren. Sie werden dir sagen, dass ich ertrunken bin - glaube ihnen nicht. Alles wird gut, ja, gell?";
			link.l1.go = "dolly_15";
		break;
		
		case "dolly_15":
			dialog.text = "Ich habe es verstanden. "+pchar.name+", Liebling, umarme mich... Küss mich...";
			link.l1 = "Mary... Meine liebe Mary...";
			link.l1.go = "dolly_16";
		break;
		
		case "dolly_16":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.MaryBye"); // можно телепортироваться
			DeleteAttribute(pchar, "questTemp.LSC.FindDolly");
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love_3";
			npchar.greeting = "mary_5"; 
		break;
		
		// дарим Мэри палаш Нарвал
		case "narval":
			dialog.text = "Jurgen? Warum?";
			link.l1 = "Du wirst sehen. Das wird eine angenehme Überraschung sein.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "Oh, wie interessant! Angenehm? Das ist toll, ja, gell! Los geht's, bevor ich vor Neugier sterbe!";
			link.l1 = "Du wirst es mögen, da bin ich sicher. Los geht's!";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			DialogExit();
			NextDiag.CurrentNode = "narval_wait";
			LocatorReloadEnterDisable("CeresSmithy", "reload6", true);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", true);
			pchar.quest.LSC_PresentMary.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_PresentMary.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_PresentMary.function = "LSC_GotoPresentMary";
		break;
		
		case "narval_wait":
			dialog.text = "Lass uns gehen, "+pchar.name+"!";
			link.l1 = "Sicher...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "narval_3":
			dialog.text = "Nun, "+pchar.name+", , welche Überraschung hast du für mich?";
			link.l1 = "Mary! Jurgen und ich haben beschlossen, dir ein Geschenk von uns beiden zu machen. Dies ist eine einzigartige Klinge, ein Breitschwert mit dem Namen Narwal. Es gibt nur zwei solche Schwerter auf der Welt: das erste gehörte Alan Milrow, dieses wird deins sein. Es besteht aus speziellem Stahl, geschmiedet von Jurgens meisterhafter Berührung, der niemals stumpf wird oder rostet.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Schmidt"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_5":
			dialog.text = "";
			link.l1 = "Unser liebes Mädchen... Alle Narwale wissen, wie sehr du gelitten hast. Ich vermute, dass du es verdienst, dieses Breitschwert zu tragen, ein Symbol des Narwal-Clans. Trage es mit Stolz. Diese Klinge wird eine Bedrohung für deine Feinde sein und dich im Kampf schützen.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			PlaySound("interface\important_item.wav");
			sld = characterFromId("Mary");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveItems(sld, "blade_17", 1);
			sTemp = GetBestGeneratedItem("blade_31");
			GiveItem2Character(sld, sTemp);
			EquipCharacterbyItem(sld, sTemp);
			sld = characterFromId("Blaze");
			dialog.text = "Jurgen? Das... ist für mich?...";
			link.l1 = "Ja, Mary. "+sld.name+"  bat mich, es für dich zu machen, und brachte einzigartiges Eisen vom Meeresgrund mit, kein Stahl wird mit dem Gewicht und der Stärke dieses Materials mithalten können. Ich habe meine Seele in dieses Schwert gesteckt, genau wie ich es einst bei Alan's getan habe.";
			link.l1.go = "narval_7";
		break;
		
		case "narval_7":
			dialog.text = "Ich weiß nicht, was ich sagen soll... Danke, Jurgen! Danke, ja, gell! Ich werde es mit Stolz tragen und dem Wert des Schwertes gerecht werden, das schwöre ich, ja, gell! Ich habe nicht genug mit Breitschwertern trainiert, aber jetzt werde ich hart trainieren!";
			link.l1 = "In dem habe ich keinen Zweifel, Mädel.";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_9":
			dialog.text = ""+pchar.name+"... warte, nein ... Du bist der beste Mann, den ich jemals getroffen habe! Du bist unglaublich, ja, gell! Weißt du, was das für mich bedeutet? Dieses Schwert ist das beste Geschenk, das ich jemals hätte bekommen können! Du hast schon so viel für mich getan, zweimal mein Leben gerettet, und doch hörst du nie auf, mich zu überraschen! Danke, meine Liebe!";
			link.l1 = "Hätte nicht anders sein können, Mary. Ich werde dich jeden Tag überraschen, bis zu meinem letzten Atemzug! Dein Lächeln bereitet mir Freude und ich bin froh, dass dir das Geschenk gefällt.";
			link.l1.go = "narval_10";
		break;
		
		case "narval_10":
			dialog.text = "(kichert) Danke! So eine wunderbare Klinge, ja, gell! Sie braucht eine starke Hand, um sie zu führen... Ich kann es kaum erwarten, mit ihr zu trainieren!";
			link.l1 = "Ich sehe kein Problem. Beeilen Sie sich zu Ihrer Kabine und probieren Sie Ihr neues Breitschwert aus!";
			link.l1.go = "narval_11";
		break;
		
		case "narval_11":
			dialog.text = "Das werde ich tun. Nochmals vielen Dank, Gentleman! "+pchar.name+"...Komm und besuche mich heute Abend, wenn du bereit bist... (kichert)";
			link.l1 = "Natürlich, gnädige Frau. Ich werde Sie am Abend sehen.";
			link.l1.go = "narval_12";
		break;
		
		case "narval_12":
			DialogExit();
			EndQuestMovie();
			sld = characterFromId("Schmidt");
			sld.dialog.currentnode = "Jurgen";
			DeleteAttribute(sld, "quest.narval_blade");
			DeleteAttribute(npchar, "quest.narval_blade");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "CeresSmithy", "goto", "goto10", "LSC_MaryReturnNormal", -1);
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем проход через трюм
			// владение Нарвалом повышает скилл ТО у Мэри и открывает перк тяжелой руки
			SetSelfSkill(npchar, 95, 50, 90, 90, 50);
			SetCharacterPerk(npchar, "HardHitter");
			npchar.quest.talisman = "true";
			npchar.quest.blade31 = "true";
		break;
		
		// Мэри дарит талисман
		case "talisman":
			dialog.text = "Hier, schau mal. Ich habe es in einer der Schiffe im äußeren Ring in einer Kapitänskiste gefunden. Jeder erfahrene Seemann sagt, dass dieser Gegenstand äußerst wertvoll für einen Navigator ist, er kann ein Schiff vor den schlimmsten Stürmen schützen. Einige von ihnen waren sogar bereit, es zu kaufen, aber ich habe es nicht verkauft... Ich möchte, dass du dieses Amulett hast, Liebling. Benutze es, um dich auf dem Meer sicher zu halten, ja, gell?";
			link.l1 = "Danke dir, Mary! Sehr aufmerksam von dir, ich liebe dich!";
			link.l1.go = "talisman_1";
		break;
		
		case "talisman_1":
			GiveItem2Character(pchar, "talisman2"); 
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a talisman of 'Jonah'");
			dialog.text = "Wirklich? Gefällt es dir? Oh, das ist großartig! Ich bin so froh, ja, gell!";
			link.l1 = "Das ist ein sehr seltener und wertvoller Talisman. Natürlich gefällt er mir! Danke, Liebling!";
			link.l1.go = "talisman_2";
		break;
		
		case "talisman_2":
			DialogExit();
			DeleteAttribute(npchar, "quest.talisman");
		break;
		
	// --------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = ""+pchar.name+"... Du bist zurück. Ich habe auf dich gewartet, ich habe jeden Tag zum Horizont geschaut, ja, gell! Du bist zu mir zurückgekommen...";
			link.l1 = "Ja, Mary. Ich bin hier, wie ich versprochen habe. Lass mich dich umarmen, Liebling!";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Ach, "+pchar.name+"... Du kannst dir nicht vorstellen, wie ich mich gefühlt habe! Die Narwale sprachen von deinem Tod, sie sagten, du seist ertrunken. Sie waren sich alle sicher, dass du tot bist. Ich habe ihnen immer wieder gesagt, dass du lebst... Natürlich glaubte mir niemand, sie dachten, ich wäre nach allem, was passiert ist, verrückt geworden.";
			link.l1 = "Mary... Meine Liebe! Was ist los mit dir? Du zitterst... Hast du Kälte?";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Nein, mir ist nicht kalt. Ich will nur... Ich möchte nicht hier darüber sprechen. Komm in meine Kajüte, wenn du fertig bist. Ich möchte alleine mit dir sein, ja, gell... Gehst du jetzt nicht zum Admiral und Nathaniel?";
			link.l1 = "Ja, ich muss mit Shark sprechen und natürlich Danielle zu Nathaniel bringen. Es wird nicht allzu viel Zeit in Anspruch nehmen. Wir sehen uns bald, Mary.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "Ich freue mich darauf... dich zu sehen. Komm so schnell wie möglich, ja, gell!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload62", "CeresSmithy", "goto", "goto11", "LSC_MaryWaitInCabin", 20.0);
		break;
		
		case "adversary":
			dialog.text = ""+pchar.name+"! Endlich. Wir müssen reden, ja, gell!";
			link.l1 = "Was ist los, Mary? Ich sehe, dass dich etwas beunruhigt! Was ist passiert?";
			link.l1.go = "adversary_1";
		break;
		
		case "adversary_1":
			dialog.text = "Sie geschah..."+pchar.name+", wer ist diese Hure auf deinem Schiff?";
			link.l1 = "Wer? Sprichst du von Danielle? Aber du hast schon kn...";
			link.l1.go = "adversary_2";
		break;
		
		case "adversary_2":
			dialog.text = "Nein, nicht Danielle. Ich meine diese Blondine, kaum bekleidet, die auf dem Deck deines Schiffes herumläuft! Ich habe sie durch das Fernrohr gesehen, ja, gell!";
			link.l1 = "A-ah! Das ist Helen McArthur. Sie ist genau wie Danielle in diese seltsame Geschichte verwickelt. Sie dient mir vorübergehend als Offizierin, natürlich nur vorübergehend.";
			link.l1.go = "adversary_3";
		break;
		
		case "adversary_3":
			dialog.text = "Offizier? Sie ist eine Offizierin?!";
			link.l1 = "Nun, ja. Was ist daran falsch?.. Mary, verdammt noch mal! Du bist eifersüchtig, ja, gell?";
			link.l1.go = "adversary_4";
		break;
		
		case "adversary_4":
			dialog.text = "Was hast du dir dabei gedacht?!... (unter Tränen) Ich habe die ganze Zeit auf dich gewartet, wegen dir konnte ich nicht schlafen, und du wagst es, hier mit irgendeiner Schreckschraube aufzukreuzen...";
			link.l1 = "Mary! Hör auf zu weinen! Was ist los mit dir? Du kannst jeden Mann ohne zu zögern ausnehmen, und doch sind deine Augen immer nass... Mary, Liebes, Helen ist nur ein Offizier, der vorübergehend dient, bis die Gerechtigkeit wiederhergestellt ist und unsere gemeinsamen Ziele erreicht sind, nichts mehr.";
			link.l1.go = "adversary_5";
		break;
		
		case "adversary_5":
			if (CheckAttribute(npchar, "quest.blade31")) 
			{
				sTemp = "I have been training hard with the broadsword you gave me, and in your absense I have mastered it perfectly.";
				notification("Heavy Weapons +", "Mary");
			}
			else sTemp = "I have been training hard with rapiers and I have mastered them perfectly.";
			dialog.text = "(schluchzend) Offizier... Dann möchte ich auch dein Offizier sein, ja, gell! Ich kann kämpfen, das weißt du doch!"+sTemp+" Und ich kann gut schießen! Ich habe vielleicht keine Seefahrtskenntnisse, aber ich lerne schnell, ich bin begabt, ja, gell!";
			// проход первый - ГГ либо соглашается, либо нет, отказ ведет к полному разрыву
			link.l1 = "(zustimmen) Mary... Ich wollte dir selbst den Posten anbieten. Es gibt keine bessere, geschicktere, feurigere Maid als dich! Ich will dich an meiner Seite!";
			link.l1.go = "adversary_hire";
			link.l2 = "(ablehnen) Mary! Ein Enteroffizier zu sein, ist zu gefährlich! Du verstehst nicht, worum du bittest. Ich kann dein Leben nicht aufs Spiel setzen.";
			link.l2.go = "adversary_fail";
		break;
		
		// отказ
		case "adversary_fail":
			dialog.text = "Kannst du nicht? Also kann diese blonde Hure Offizierin werden und ich nicht? Du belügst mich, "+pchar.name+", du willst einfach nicht bei mir sein! (weint) Ist dieses Mädchen besser als ich, ja, gell?";
			link.l1 = "Mary, du verstehst nicht!";
			link.l1.go = "adversary_fail_1";
		break;
		
		case "adversary_fail_1":
			dialog.text = "Ich tue es! Ich sah ihre leuchtenden Augen auf dich gerichtet! Sie ist nicht nur ein Offizier, ja, gell! Ich verstehe das (schluchzend). Natürlich kann ich nicht mit ihr konkurrieren - sie weiß, wie man ein Schiff führt...";
			link.l1 = "Mary, wovon redest du!";
			link.l1.go = "adversary_fail_2";
		break;
		
		case "adversary_fail_2":
			dialog.text = "Es ist vorbei... (weint) Geh weg! Geh zu deiner Hure! Und ich bleibe hier... Ich gehe nirgendwo hin! Gib mir meinen Schlüssel!";
			link.l1 = "Aber Mary...";
			link.l1.go = "adversary_fail_3";
		break;
		
		case "adversary_fail_3":
			RemoveItems(pchar, "key_mary", 1);
			dialog.text = "Verschwinde...";
			link.l1 = "..., Freund.";
			link.l1.go = "adversary_fail_4";
		break;
		
		case "adversary_fail_4": // обидел Мэри - больше от неё ничего не получишь
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=0; i<=3; i++)
			{
				LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, true); // закрываем вход к Мэри
			}
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "");
			pchar.questTemp.LSC.Mary = "fail";
			AddQuestRecord("LSC", "23");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// соглашаемся
		case "adversary_hire":
			// проход второй - смотрим, Элен может стать подругой или нет
			bOk = (CheckAttribute(pchar, "questTemp.HelenDrinking.GaveCutlass")) && (sti(pchar.questTemp.Saga.HelenRelation) >= 6);
			if (bOk || sti(pchar.questTemp.Saga.HelenRelation) >= 5 || CharacterIsAlive("Longway"))
			{
				dialog.text = "Wirklich? Wolltest du mich wirklich als deinen Offizier? "+pchar.name+", verdammt, du kannst dir nicht vorstellen, wie glücklich ich bin! Ich möchte so sehr dein Offizier sein... aber nicht auf demselben Schiff mit dieser Blondine!";
				link.l1 = "Mary, aber warum?!";
				link.l1.go = "adversary_hire_no";
			}
			else
			{
				dialog.text = "Wirklich? Wolltest du mich wirklich als deinen Offizier haben? "+pchar.name+", verdammt, du kannst dir nicht vorstellen, wie glücklich ich bin! Ich schwöre, ich werde dich nicht enttäuschen, das wirst du sehen!";
				link.l1 = "Jesus, Mary, Liebling, du bist kostbar. Vor einer Minute hast du noch geweint und jetzt strahlt dein Gesicht! Und, Mary, du bist für mich nicht nur ein weiterer Offizier. Du bist mehr als das und ich bezweifle, dass du mich in irgendeiner Weise enttäuschen könntest.";
				link.l1.go = "adversary_hire_yes";
			}
		break;
		
		case "adversary_hire_no": // Мэри не пойдёт, пока не ГГ не расстанется с Элен. Выбирай, кто тебе милее...
			dialog.text = "Du magst sie vielleicht nur als deine Offizierin betrachten, obwohl ich bezweifle, dass sie dich nur als ihren Kapitän sieht. Ich habe die Blicke gesehen, die sie dir zugeworfen hat, ich kenne diesen Blick, ja, gell! Nur ich kann dir solche Blicke zuwerfen!";
			link.l1 = "Mary, Liebling, aber ich habe dir schon gesagt, ich habe keine Gefühle für sie, und das ist es! Da ist nichts zwischen uns! Ich schwöre, verdammt noch mal! Ich brauche ihre Hilfe, um mit dem Durcheinander bei den Piraten der Karibik klarzukommen. Jan Svenson wird mir nicht helfen, Tortuga zu erobern, wenn ich ihr nicht helfe, und ich brauche ihn!";
			link.l1.go = "adversary_hire_no_1";
		break;
		
		case "adversary_hire_no_1":
			dialog.text = ""+pchar.name+", Liebling, umarme mich... Es tut mir leid. Ich glaube dir. Aber ich kann nicht in ihrer Nähe bleiben und zusehen, wie sie mit dir flirtet, ja, gell! Irgendwann werde ich mein Schwert nehmen und sie halbieren!";
			link.l1 = "Ja, das kannst du definitiv... Du hast ganz schön Temperament, hm?";
			link.l1.go = "adversary_hire_no_2";
		break;
		
		case "adversary_hire_no_2":
			dialog.text = "Und wenn ich sie töte - du wirst mich verlassen, ja, gell... Ich würde es mir nie verzeihen.";
			link.l1 = "Also, was schlägst du vor, Mary? Was soll ich mit ihr machen?";
			link.l1.go = "adversary_hire_no_3";
		break;
		
		case "adversary_hire_no_3":
			dialog.text = "Du hast gesagt, dass sie eine vorübergehende Offizierin ist. Ich werde mich dir anschließen, sobald du sie an Land lässt. Gestrandet auf irgendeiner unbewohnten Insel, hoffe ich (kichert), ich werde dir bis ans Ende der Welt folgen, ja, gell?"+pchar.name+", Liebling, ist sie wirklich besser als ich?";
			link.l1 = "Unsinn! Hör auf, so zu reden, Mary, Liebes, es gibt keine bessere Frau als dich!...";
			link.l1.go = "adversary_hire_no_4";
		break;
		
		case "adversary_hire_no_4":
			dialog.text = "Beweise es mir dann. Ich möchte dich nicht teilen, "+pchar.name+"! Ich wäre lieber allein, als dich mit einer anderen zu teilen, ja, gell...";
			link.l1 = "Gut, Mary. Lass uns einen Deal machen. Ich kann Helen jetzt nicht loswerden, sie ist wichtig für diese Verfolgung. Ich werde ihr bei ihren Problemen helfen, sie zur Herrin von Isla Tesoro machen, sie gehen lassen, und zwischen uns wird nichts mehr übrig sein. Hoffentlich dauert es nicht länger als ein oder zwei Monate. Wirst du so lange auf mich warten?";
			link.l1.go = "adversary_hire_no_5";
		break;
		
		case "adversary_hire_no_5":
			dialog.text = "Natürlich werde ich das tun, ja, gell! Es ist meine Entscheidung... Wenn du zu mir zurückkehrst, bedeutet das, dass du mich anstelle von ihr gewählt hast. Und wenn du nicht zurückkehrst... dann ist es mein Schicksal. Ich werde hier bleiben und meinen eigenen Clan gründen. Den Casper Clan...";
			link.l1 = "Weinst du schon wieder? Mary, komm schon. Genug mit diesem Unsinn! Wovon redest du? Welcher Clan... Dummes Mädchen, natürlich komme ich zurück, ich würde es nicht wagen, dich unter diesen verrotteten alten Schiffen zu lassen! Du würdest die Insel mit deinen Tränen überschwemmen!";
			link.l1.go = "adversary_hire_no_6";
		break;
		
		case "adversary_hire_no_6":
			dialog.text = "Kehre so schnell wie möglich zurück dann... "+pchar.name+", Schatz, küss mich, bitte...";
			link.l1 = "Ich werde zurückkommen. Ich verspreche es!"; // ага, а мы посмотрим, обманешь или нет
			link.l1.go = "adversary_hire_no_7";
		break;
		
		case "adversary_hire_no_7":
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love"; // оставляем штучки с Мэри на Острове в силе
			pchar.questTemp.LSC.MaryWait = "true";
			AddQuestRecord("LSC", "22");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// повторный разговор после расставания с Элен
		case "adversary_hire_return":
			dialog.text = "Spielst du mit mir einen Streich? "+pchar.name+", hast du mich wirklich nicht vergessen?";
			link.l1 = "Natürlich! Habe ich dich jemals betrogen? Ich habe während unserer Trennung viel durchgemacht und habe nicht vor, mich wieder von dir zu trennen... mein Talisman.";
			link.l1.go = "adversary_hire_yes";
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
		break;
		
		case "adversary_hire_yes": // Элен заведомо не друг - Мэри идёт сразу, либо если выбрал Мэри
			dialog.text = "Wirklich? "+pchar.name+"! Ich werde dir immer folgen! Ich werde dich nie belügen, ich werde dich nie verraten, ich schwöre es!";
			link.l1 = "Ich glaube dir, mein Lieber... Ich auch nicht."; // а куда же ты денешься )
			link.l1.go = "adversary_hire_yes_1";
		break;
		
		case "adversary_hire_yes_1":
			dialog.text = ""+pchar.name+", Liebling, umarme mich... Wir werden zusammen sein, nicht wahr? Sag es mir!";
			link.l1 = "Ja, wir werden zusammen sein, Mary. Für immer.";
			link.l1.go = "adversary_hire_yes_2";
		break;
		
		case "adversary_hire_yes_2":
			dialog.text = "Genau wie Danielle und Nathaniel?";
			link.l1 = "(lachend) Ja, genau wie sie, gell?";
			link.l1.go = "adversary_hire_yes_3";
		break;
		
		case "adversary_hire_yes_3":
			dialog.text = ""+pchar.name+"... Ich liebe dich! Ich werde dich heiraten, wenn du willst, ja, gell...";
			link.l1 = "Liebe Mary... Natürlich - wir werden später darüber sprechen. Dein Leben auf diesem Friedhof von Schiffen ist vorbei, lass uns dich erstmal hier rausbringen - willkommen an Bord meines Schiffes und in der großen Welt, meine Liebe!";
			link.l1.go = "adversary_hire_yes_4";
		break;
		
		case "adversary_hire_yes_4":
			dialog.text = "Lass uns unsere letzte Nacht auf dieser Insel zusammen auf der 'Ceres Schmiede' verbringen. Nur wir zwei. Nur du und ich... Ich werde dich bis zum Morgen nirgendwohin gehen lassen, ja, gell?";
			link.l1 = "Nun, wir sind nicht auf meinem Schiff, also folge ich deinem Befehl... Meine liebe Mary!";
			link.l1.go = "adversary_hire_yes_5";
		break;
		
		case "adversary_hire_yes_5":
			DialogExit();
			npchar.quest.hire = "true";
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			DoQuestCheckDelay("LSC_LastNight_CS", 3.0);
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "LSC_mary_hire":
			dialog.text = "Aye-aye, Kapitän!";
			link.l1 = "...";
			link.l1.go = "LSC_mary_hire_1";
		break;
		
		case "LSC_mary_hire_1":
			DialogExit();
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "LSC_Mary_hire");
			if (pchar.questTemp.LSC.Mary != "return") AddQuestRecord("LSC", "24");
			pchar.questTemp.LSC.Mary = "officer";
			RemoveItems(pchar, "key_mary", 1);
		break;
		
	// --> консультации по морским сражениям
		case "sea_bomb":
			dialog.text = ""+pchar.name+"! Ich habe eine Idee...";
			link.l1 = ""+npchar.name+"? Es ist hier nicht sicher und ich habe dir befohlen, auf dem Schiff zu bleiben...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+", es gibt so viel Schießpulver auf diesem alten Kutter, wenn es explodiert, fliegt die ganze Insel in die Luft. Es macht jetzt keinen Unterschied mehr, wo man bleibt. Hör einfach auf mich!";
			link.l1 = "Ich höre zu, bitte fasse dich kurz.";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "Die Piratenkorvette und die Fregatte. Sie sind getäuscht und denken, dass wir einer von ihnen sind... Messer, ja, gell. Dies könnte eine Gelegenheit für uns sein. Lass uns ein paar Fässer Schießpulver, eine Lunte nehmen und auf sie zusteuern.\nWenn sie uns näher kommen lassen, zünden wir die Lunte an, werfen das Fass auf eines der Schiffe und segeln so schnell wie möglich davon. Muss eine perfekte Gelegenheit sein, um ein paar Feuerwerke zu sehen... Was denkst du?";
			link.l1 = "Gefährlich, allerdings könnte dein Plan funktionieren... Nur wenn sie uns nicht erkennen.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Lass es uns riskieren, "+pchar.name+"?";
			link.l1 = "Gut. Los geht's! Jungs! Nehmt drei Fässer Schießpulver! Wir hauen hier ab! Ich liebe deine Vorstellungskraft, "+npchar.name+"... Ich wäre nie selbst auf diese Idee gekommen.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			dialog.text = "Hab ich dir doch gesagt, ich habe meine Talente, ja, gell?";
			link.l1 = "...";
			link.l1.go = "sea_bomb_5";
		break;
		
		case "sea_bomb_5":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			AddQuestRecord("BarbTemptation", "15");
			AddQuestUserData("BarbTemptation", "sName", "Mary");
			pchar.questTemp.Saga.BarbTemptation.adviser = "Mary";
		break;
		
		case "fugas":
			dialog.text = "Ja, sicher, Liebling. Ich bin immer bereit zu helfen, ja, gell! Was ist los?";
			link.l1 = "Jackmans Schiff befindet sich in der Sabo-Matila-Bucht, die schwere Fregatte 'Centurion'. Dieses Schiff gehörte einst den Hawkes, also müssen wichtige Gegenstände und Dokumente in Jackmans Kabine sein... wir müssen es entern.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Ich verstehe. Wie willst du das auf unserem kleinen Vogel durchführen? Sie haben mehr Männer und Kanonen. Ich habe durch das Fernglas geschaut, ja, gell!";
			link.l1 = "Du hast recht. Jackman hat mindestens doppelt so viele Männer wie wir, und alle sind erfahrene Schlächter und Söldner. Es wäre Wahnsinn, ohne die richtigen Vorbereitungen an Bord zu gehen. Eine langwierige Seeschlacht ist auch keine Option. Also habe ich über andere Möglichkeiten nachgedacht, um die Aufgabe zu erfüllen.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", sie haben uns noch nicht als Feind erkannt, genau wie diese Idioten zurück bei den Türken... Wir können unseren Trick noch einmal versuchen...";
			link.l1 = "Mary, ich habe dir gerade gesagt, dass wir die Fregatte entern müssen, sie zu versenken ist keine Option.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Ich weiß das, "+pchar.name+". wir werden sie nicht versenken. Hör zu, wir nehmen ein paar leere Rumfässer und füllen sie mit Schießpulver, Traubenschrot und kurzen Zündschnüren. Dann segeln wir näher an ihre Fregatte heran und werfen die improvisierten Sprengstoffe auf ihr Deck.";
			link.l1 = "Ha! Glaubst du wirklich, dass es funktionieren wird?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "Und warum nicht? Ihr Freibord ist höher als unseres, aber zwei oder drei Männer könnten mit Hilfe eines Flaschenzugs ein voll beladenes Fass leicht heben und werfen. Wir rufen aus - 'Hier ist etwas freier Rum von Knive! Und die Fässer explodieren, bevor sie überhaupt reagieren können.";
			link.l1 = "Die explodierende Traubenschussladung wird seine besten Männer an Deck in Hackfleisch verwandeln... Verdammt, das klingt verlockend.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Lass uns fünf Fässer benutzen. "+pchar.name+", wir haben das Überraschungsmoment. Sie werden nichts ahnen! Wir müssen jedoch sofort segeln, bevor sie an Bord kommen.";
			link.l1 = "Nun, lass es uns versuchen. Sie dürfen uns nicht erkennen, bevor wir die Fässer werfen... Verdammt, es wird nicht einfach sein, ihnen nahe zu kommen. Jackman ist kein Idiot wie Ghoul es war.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Lass uns das Risiko eingehen, "+pchar.name+"! Es wird sowieso nicht wehtun.";
			link.l1 = "Guter Punkt, wir haben nichts zu verlieren... Bereitet die Fougassen vor!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			dialog.text = "Ich werde, mein Kapitän! Ich werde sie perfekt vorbereiten, ja, gell!";
			link.l1 = "He, sie haben dir nicht erlaubt, diese Krabben auf der Insel zu betäuben, also lasse ich dich hier ein paar Piratenärsche sprengen, ja, gell... Mary, du bist wunderbar!";
			link.l1.go = "fugas_8";
		break;
		
		case "fugas_8":
			dialog.text = "Danke, "+pchar.name+"! Ich werde dich nicht enttäuschen!";
			link.l1 = "Darüber habe ich keinen Zweifel. Ich hoffe, wir sind nicht diejenigen, die dich enttäuschen, indem wir deinen Plan vermasseln... Zu den Waffen!";
			link.l1.go = "fugas_9";
		break;
		
		case "fugas_9":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		// <-- консультации по морским сражениям
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "Da bist du ja! Es war nicht leicht, dich zu finden... Das war fantastisch, Käpt'n! So einen atemberaubenden Sprung habe ich noch nie gesehen! Du bist immer mein Held! Obwohl ich zugeben muss, du hast mir fast einen Herzinfarkt verpasst\nEines Tages bringst du mich noch um mit deinen Tricks, Liebster... Nun, wer zum Teufel könnte sie wohl sein? Oh "+pchar.name+", Ich lasse dich nur einen Moment aus den Augen und schon bist du von Horden von Abschaum umgeben!";
			link.l1 = "Mary, dieser 'Schlacken' ist Catherine Fox, Tochter von Oberst Fox, dem Kommandeur der See-Füchse. Wir müssen sie nach Antigua bringen.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Oh, wirklich? Solche Freude! Gut, du wirst mir von ihr erzählen... heute Nacht, wenn wir die Nacht zusammen, allein verbringen. Jetzt, lass uns gehen, wir müssen uns beeilen!";
			link.l1 = "Du bist die Beste, Mary. Was würde ich ohne dich tun? Catherine, komm schon!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Endlich bist du wach, mein Liebling... Schuft! Erschreck mich nie wieder so!";
			link.l1 = "Mary... Liebling, was ist passiert? Mein Kopf spaltet sich...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Als wir die Kapitänskabine betraten, lagst du still wie eine Leiche auf dem Boden. Mein Herz raste! Die Jungs haben dich aufgehoben und zu unserem Schiff geschleppt - gerade rechtzeitig, denn die toten Männer auf dem Deck begannen wieder aufzustehen\n Was für ein Albtraum! Wir konnten nichts gegen sie ausrichten! Wir haben schnell die Leinen gekappt und versucht wegzusegeln, aber eine Salve von ihrem Schiff hat unser Schiff schwer beschädigt und wir haben die Kontrolle verloren. Sie waren echte Teufel, ja, gell! Und dann haben sie die Segel gehisst und waren im Nu verschwunden\nUnser Schiff lief auf Grund, also mussten wir an dieses Ufer fliehen, bevor der Sturm sie zerstören konnte. Viele gute Leute sind heute gestorben, aber das Schiff hat am Ende überlebt...";
			link.l1 = "Gute Arbeit, Mary... Was würde ich ohne dich tun?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Vielleicht wärst du ertrunken oder du hättest auf diesem Schiff bleiben müssen und die Toten hätten dich in Stücke gerissen... Meine Hände zittern immer noch!";
			link.l1 = "Danke dir, Liebling. Wie lange war ich bewusstlos?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Einen ganzen Tag lang. Ich habe deine Wunden gereinigt, dir Medizin gegeben und dir etwas Rum eingeflößt. Du solltest bald wieder gesund werden. Und wage es nicht, mir zu sterben!";
			link.l1 = "Ich verspreche, dass ich diesmal nicht sterben werde, Liebling. Obwohl ich mich nicht allzu gut fühle...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Das steht fest... War es der 'Fliegende Holländer', Kapitän? Warum haben sie uns angegriffen? Und warum haben sie nicht vor dem Entern geschossen?";
			link.l1 = "Ihr Kapitän brauchte das Amulett, das ich mit Tuttuathapak, dem indischen Schamanen, besprochen hatte. Deshalb mussten sie an Bord kommen, aber sobald ihr Kapitän das Amulett genommen hatte, brauchten sie uns nicht mehr... Was für ein Albtraum! Ein Schiff, bemannt von den Toten! Unglaublich...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Ja, es scheint, dass der 'Fliegende Holländer' früher oder später nach uns kommen würde. Wenn ich die Chance habe, gehe ich zur Kirche, zünde eine Kerze für unsere wunderbare Rettung an und bete zu unserem Herrn...";
			link.l1 = "Ich auch, Mary, denke ich. Ich muss zurück in das Dorf. Lass Tuttuathapak wissen, was passiert ist. Dieses Schiff hat uns wegen des Amuletts angegriffen! Ich hoffe, dieser rothäutige Teufel hat eine Erklärung dafür, warum zum Teufel diese lebenden Toten es überhaupt brauchten.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Ja, gell. Aber sei vorsichtig - deine Wunden sind kaum verheilt.";
			link.l1 = "Du bist all die Medizin, die ich brauche. Und... Mary, ich liebe dich...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "Ich liebe dich auch, mein Liebling...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
	// --> Мэри вне LSC
		// секс - Мэри не отказывает никогда
		case "cabin_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+", es gibt für mich kein größeres Glück, als in deinen Armen zu sein, ja, gell... Lass uns gehen!",""+pchar.name+", Ich würde gerne jeden wachen Moment mit dir verbringen, wenn es möglich wäre. Lass uns gehen!");
			link.l1 = RandPhraseSimple("Du bist der Beste, meine Liebe...","Du bist wunderbar, mein Talisman...");
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuest("cabin_sex_go");
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("Liebling, du warst erstaunlich... das bist du immer!","Es war großartig!");
			link.l1 = RandPhraseSimple("Ich bin froh, dass du glücklich bist, meine Liebe...","Ich liebe dich, Mary...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); // belamour для бесконфликтности квестов							
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", es gibt für mich kein größeres Glück, als in deinen Armen zu sein, ja, gell... Aber jetzt ist nicht der richtige Zeitpunkt - wir müssen diesen Abschaum Thibaut fangen, bevor er wegrennt.";
				link.l1 = "Du hast wie immer Recht, mein Mädchen...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = RandPhraseSimple(""+pchar.name+", es gibt für mich kein größeres Glück als in deinen Armen zu sein, ja, gell... Lass uns gehen!",""+pchar.name+", Ich würde gerne jeden Moment bei dir sein, wenn es möglich wäre. Lass uns gehen!");
			link.l1 = RandPhraseSimple("Du bist die Beste, mein Mädchen...","Du bist wunderbar, mein rothaariges Talisman...");
			link.l1.go = "room_sex_go";
		break;
		
		case "room_sex_go":
			DialogExit();
			pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;//закрыть локацию
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
			{
			//DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			DoFunctionReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "GiveKissInRoom");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			} // patch-8
			//DoQuestCheckDelay("Mary_LoveSex", 2.5);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
		break;
		
		// требует секса, если давно не давал
		case "givemesex":
			dialog.text = RandPhraseSimple(""+pchar.name+", es ist schon zu lange her seit wir zuletzt Sex hatten... Du hast mich total vergessen, ja, gell! Liebling, ich will entspannen, lass uns ein Zimmer für die Nacht nehmen und unsere Sorgen auf einen anderen Tag verschieben!",""+pchar.name+", du warst zu beschäftigt und ich fange an zu denken, dass du mich völlig vergessen hast! Liebling, ich möchte... mit dir alleine sein. Lass uns ein Zimmer für die Nacht nehmen, ja, gell!",""+pchar.name+", hast du den Verstand verloren? Ich möchte die Nacht mit dir verbringen, etwas Wein trinken und entspannen. Du warst zu beschäftigt auf See und hast mich völlig vergessen!");
			link.l1 = "Mary, Liebling, wovon redest du - 'völlig über mich vergessen'? Dummes Mädchen... Aber ich war wirklich zu beschäftigt, die Probleme, die meine Aufmerksamkeit benötigen, sind endlos. Verzeih mir, meine Liebe. Lass uns nach oben gehen, ich gehöre dir für die Nacht, die Welt kann warten!";
			link.l1.go = "room_sex_go";
		// belamour legendary edition -->
			link.l2 = RandPhraseSimple(RandPhraseSimple("Heute nicht, Liebling. Ich habe Kopfschmerzen.","Mary, Liebling, wie könnte ich dich vergessen? Komm schon, später - wir haben noch Arbeit zu tun..."),RandPhraseSimple("Du bist immer in meinen Gedanken, Mary, aber wir können es uns gerade nicht leisten, uns zu entspannen.","Mary "+npchar.lastname+", wir haben heute keine Zeit für Unsinn"));
			link.l2.go = "room_sex_goNS";
		break;
		
		case "room_sex_goNS":
		if(sti(pchar.reputation.fame) > 60)
		{
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); 
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
			pchar.quest.Mary_giveme_sex.over = "yes"; 
			pchar.quest.Mary_giveme_sex1.over = "yes";
			dialog.text = "Nun ... Was kann ich noch sagen ... Ja, Kapitän!";
			link.l1 = "...";
			link.l1.go = "exit";
		}
		else
		{
			if(bImCasual) Log_Info("To refuse Mary become more famous");
			ChangeCharacterComplexReputation(pchar,"authority", -2);
			dialog.text = "Charles...";
			link.l1 = "Mary, Liebling, wovon redest du - 'völlig vergessen'? Dummes Mädchen... Aber ich war wirklich beschäftigt, die Probleme nehmen kein Ende. Verzeih mir, mein Mädchen. Lass uns nach oben gehen, die Welt kann warten!";
			link.l1.go = "room_sex_go";
		}
		break;
		// <-- legendary edition
		// ругается за то, что ходил по борделям, ГГ изворачивается
		case "brothel":
			dialog.text = "Aye, da ist er ja! Magst du mich nicht mehr, oder was? Sag es mir!";
			link.l1 = "Was?! Mary, welchen Unsinn redest du? Warum denkst du das?";
			link.l1.go = "brothel_1";
		break;
		
		case "brothel_1":
			dialog.text = "Dann warum hast du diese Schlampen, diese Bordellhuren besucht? Ich weiß, dass du es getan hast, lüg mich nicht an! Gefällt dir etwas nicht an mir, wenn wir Liebe machen, ja, gell? (weint) Sag es mir...";
			link.l1 = "Mary, Mary... beruhige dich, bitte, mein Mädchen. Ja, ich war ein paar Mal im Bordell, aber nur wegen Geschäftsangelegenheiten. Ich war nicht auf der Suche nach Spaß!";
			link.l1.go = "brothel_2";
		break;
		
		case "brothel_2":
			dialog.text = "Und welche Art von 'Geschäftsangelegenheiten' haben dich nach oben in das verdammte Zimmer gebracht? (schluchzend) Du lügst, "+pchar.name+"!";
			link.l1 = "Mary, Liebes, hör endlich auf damit... Ich hatte wirklich einige Geschäfte mit der Bordellwirtin zu erledigen. Und ich bin ein paar Mal nach oben gegangen. Das letzte Mal wegen einer persönlichen Angelegenheit des Gouverneurs - er bat mich, seinen Ehering zu finden. Wie könnte ich Seiner Exzellenz verweigern?";
			link.l1.go = "brothel_3";
		break;
		
		case "brothel_3":
			dialog.text = "";
			link.l1 = "Und wie könnte ich der Herrin erklären, dass ich unter dem Bett im Obergeschoss nachsehen muss? Ich konnte nicht. Also musste ich für die Nacht eine Hure kaufen, um nach oben zu dürfen... Das zweite Mal wurde mir gesagt, dass ein Händler seine Schiffsunterlagen dort verloren hat. Ich musste wieder für ein Mädchen bezahlen, um das Zimmer durchsuchen zu dürfen, und wurde gut für die Unterlagen bezahlt...";
			link.l1.go = "brothel_4";
		break;
		
		case "brothel_4":
			dialog.text = "";
			link.l1 = "Dreimal habe ich dem örtlichen Kommandanten geholfen: Ich musste die Huren nach einem Offizier aus der Garnison fragen. Dieser Offizier wurde der Spionage und der Verbindungen mit Piraten verdächtigt. Schließlich haben wir ihn gefangen und ich erhielt eine stattliche Belohnung...";
			link.l1.go = "brothel_5";
		break;
		
		case "brothel_5":
			dialog.text = "";
			link.l1 = "Siehst du jetzt? Ich sage dir, es ging nur um Geschäfte. Mary, du bist diejenige, die ich liebe und brauche. Du bist die Beste, ich schwöre es! Glaubst du wirklich, dass ich mit irgendeiner schmutzigen Hafen-Hure herumhure, wenn ich dich habe? Wie könntest du nur so von mir denken!";
			link.l1.go = "brothel_6";
		break;
		
		case "brothel_6":
			dialog.text = ""+pchar.name+"... Ist das alles wahr? Bist du ehrlich zu mir? Warst du nicht bei ihnen?";
			link.l1 = "Mary, Liebling, du bist die einzige Frau, die ich liebe, das ist wahr. Komm näher, Liebling. Lass mich dich umarmen... Wisch deine Tränen ab und, bitte, sei nicht mehr eifersüchtig! Ich werde die Bordelle nie wieder besuchen, wenn das ist, was du willst!";
			link.l1.go = "brothel_7";
		break;
		
		case "brothel_7":
			dialog.text = "Aye, das ist es, was ich will!... "+pchar.name+", Ich bin eifersüchtig, weil ich dich liebe... Und ich will dich nicht verlieren, ja, gell! Hörst du mir zu? Ich werde jede Schlampe töten, die es wagt, dir zu nahe zu kommen!";
			link.l1 = "Beruhige dich... Es ist nicht nötig, jemanden zu töten. Und du wirst mich nicht verlieren, das verspreche ich. Alles ist in Ordnung, beruhige dich. Du bist meine Einzige und das beste Mädchen der Welt... Glaube mir, das bist du, ja, gell?";
			link.l1.go = "brothel_8";
		break;
		
		case "brothel_8":
			DialogExit();
			SetLaunchFrameFormParam("", "", 0, 5);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			pchar.GenQuest.BrothelLock = true; // все, больше не походишь по борделям :)
			DeleteAttribute(pchar, "GenQuest.BrothelCount");
		break;
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", was für eine merkwürdige Frage? Ich liebe dich. Du hast mich gerettet. Ich bin dein rothaariger Talisman - glaubst du wirklich, dass ich dich dort alleine hingehen lasse? Zähl nicht darauf, ja, gell! Ich bin bei dir! Wann sollen wir losgehen?";
			link.l1 = "Du hast recht, Liebling, das war eine seltsame Frage... Ich werde es dir später erzählen, wenn wir gehen. Wir müssen uns erst vorbereiten, ja, gell?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ich bin bereit, mein Kapitän! Ich werde dir bis ans Ende der Welt folgen!";
			link.l1 = "Danke dir, meine Liebe...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "19");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			pchar.quest.Mary_giveme_sex1.over = "yes"; // fix 22-03-20
			pchar.questTemp.GoldenGirl.MaryBlock = "true"; // fix 22-03-20
			dialog.text = "Was ist diesmal los, Kapitän? Spanier, Piraten oder noch schlimmer?";
			link.l1 = "Es ist schlimmer, Mary, viel schlimmer. Der Gouverneur plant, eine äußerst teure Kurtisane zu besuchen und ich soll ihn als Person von Interesse begleiten, wie es der Herrin versprochen wurde. Langweilige Gespräche, überteuerter Wein und stumpfe Adlige.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Ganz im Gegenteil, eine lästige Einladung zu einer gesellschaftlichen Veranstaltung, organisiert von einer Adelsdame. Seine Exzellenz hat mich überrascht, als er mich bat, ihn zu begleiten, aber ehrlich gesagt, ich freue mich darauf, meinen Kopf von Dingen abzulenken.";
			link.l2.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Ist das so?! Eine Kurtisane? Du sagst das, als ob es keine große Sache wäre, was? Nur ein bisschen Spaß mit Seiner Exzellenz? Charles, du ver...";
			link.l1 = "Mary, beruhige dich bitte! Es ist nicht so, als würde ich dort hingehen, um... es ist kein Bordell! Nun, es ist ein Bordell, aber verdammt noch mal, ich bin ein Edelmann und ein Mann meines Wortes. Vertraust du mir wirklich nicht? Der Gouverneur hat mich nur um einen kleinen Gefallen gebeten und ich muss ihm nachkommen, das ist alles!";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "Ja, ich habe von ein paar 'Adligen' wie dir gehört, gell? Ich habe sie auch in deiner Gesellschaft gesehen. Kurtisanen sind für sie ein tägliches Bedürfnis! 'Hohe' Gesellschaft, 'würdevolle' Unterhaltung, mein Arsch! Selbst eine Ehe hält sie nicht davon ab, diese... Damen zu besuchen. Verdammt, ich hatte keine Ahnung, dass du genau wie sie bist. Wir sind nicht einmal... Verdammt seid ihr alle!";
			link.l1 = "Mary, warte! Verdammt...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Wir haben uns wirklich einen Urlaub verdient, ja, gell? Denkst du, sie können es ertragen, eine Dame in einem roten Mantel zu sehen? Stell dir all das Getuschel in den Ecken vor? Jemand wird sicherlich in Ohnmacht fallen, das wäre lustig, oder?";
			link.l1 = "Mary, meine Liebe, das ist nicht die Art von Fest, zu der man eine Dame mitnimmt... zumindest nicht eine Dame wie dich. Nun, es ist ein bisschen kompliziert, aber lass es mich erklären...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Wirklich, mach dir keine Mühe. Sag es einfach gerade heraus: Ich bin nicht gut genug für diese Schnösel in Perücken. Ein einfaches Mädchen, nur zum Spaß, nicht wahr? Du schämst dich also, dich mit mir zu zeigen? Nicht gut genug für schicke Partys, richtig, ehrenwerter Monsieur Charles de Maure, ja, gell?";
			link.l1 = "Nein, überhaupt nicht. Du bist erstaunlich und es ist mir egal, welche Eindrücke wir auf die Menschen um uns herum machen. Der Gouverneur versucht, seine Probleme mit meiner Hilfe zu lösen, wie immer. Ich werde wie eine wertvolle Trophäe im Raum sein. Ein interessanter Gast, um die edlen Taugenichtse zu beeindrucken.";
			link.l1.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "So bin ich also nichts für dich, ja, gell? Ich verstehe, es ist in Ordnung, Adelige sind für Adelige, Bauern sind nur zur einfachen Unterhaltung. Viel Glück mit deinem Hochadel. Ich spreche mit dir, wenn du wieder auf unserem bescheidenen Boden bist, ja, gell?";
			link.l1 = "Mary, warte! Verdammt...";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_7":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Viel Glück mit deinem Adel. Ich spreche mit dir, wenn du wieder auf unserem bescheidenen Boden bist, ja, gell?";
			link.l1 = "Mary ach, komm schon!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Schau dir das an, ja, gell! Unser in der feinen Gesellschaft verlorener Kapitän!";
			link.l1 = "..., Freund.";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "Du bist den ganzen Tag im Bordell verschwunden und jetzt reden die Leute in der Stadt. Charles, gib mir nur einen guten Grund, warum ich jetzt mit dir reden sollte, anstatt sagen wir, den Narwal in deinen... Bauch zu schieben? Du schätzt mich nicht besonders, ja, gell?!";
			link.l1 = "Mary, ich werde alles erklären, aber erst später. Ich sollte mich vorbereiten und zum Duell gehen. Fühle dich frei, mich zu töten, wenn ich das überlebe. Kümmere dich in der Zwischenzeit bitte um unser neues Schiff, ja, gell? Ich habe es letzte Nacht in einem Kartenspiel gewonnen.";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Vergiss das Schiff, du hast etwas von einem Duell gesagt, ja, gell? Die Einheimischen erzählen allerlei Scheißgeschichten, denen ich nicht zuhöre. Sie sagen, du sollst entweder gegen den Sohn des Königs oder gegen den verdammten Papst selbst kämpfen. Sag mir jetzt, was zum Teufel los ist?!";
			link.l1 = "Dieser Mann ist ein Bastard eines sehr einflussreichen Adligen, Graf de Levi Vantadur. Er war es, der mich zuerst herausgefordert hat, und ich muss das Duell gewinnen, ohne ihm Schaden zuzufügen, um den Zorn seines Vaters zu vermeiden.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Während ich auf meinem Hintern auf der Wanne sitze, die du gerade gewonnen hast? Bist du verrückt geworden, Charles?";
			link.l1 = "Ich fürchte, es muss so sein. Der Gouverneur hat mir ein paar edle Offiziere zur Verfügung gestellt, um meine Sekundanten zu sein, um jegliche Verwirrung danach zu vermeiden. Ich kann dich oder einen der Jungs nicht mit mir nehmen, um die offizielle Integrität des Duells zu wahren. Das ist zu ernst, es tut mir leid.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "Weißt du, was ich jetzt tun werde? Ich gehe zu diesem verfluchten Schiff und betrinke mich ordentlich, ja, gell! Mach, was du willst, aber wenn dieser edle Bastard es nicht schafft, dich zu töten, schwöre ich, ich werde es selbst tun!";
			link.l1 = "Mary, alles wird gut, vertrau mir. Jetzt warte ... Verdammt! Es geht schon wieder los!";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "Da ist er ja! Wir haben den ganzen Tag kein einziges Wort von dir gehört! Wir waren besorgt, als wir die Gerüchte auf dem Markt hörten. Sie sagen, du hättest um Schiffe und Frauen gezockt und dich sogar mit irgendeinem gekrönten Prinzen oder sogar dem Papst selbst duelliert! Was zum Teufel geht hier vor, ja, gell?";
			link.l1 = "Es ist kompliziert, Mary. Es wird eine Weile dauern, es zu erklären. Ich habe es allerdings geschafft, eine Fregatte zu gewinnen. Du musst dich um sie kümmern, während ich meine Streitigkeiten mit ihrem vorherigen Besitzer kläre.";
			link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "Also hatten sie recht mit dem Duell, ja, gell? Wer ist dieser hochnäsige Adelskerl? Warum kämpfst du gegen ihn?";
			link.l1 = "Ich muss. Es ist kompliziert, aber kurz gesagt: Ich habe sein Schiff und seine... Dame gewonnen. Er hat mich öffentlich des Betrugs beschuldigt und mich zum Duell herausgefordert. Dieser Mann ist ein Bastard eines sehr einflussreichen Adligen, Graf de Levi Vantadur. Ich werde mein Bestes tun müssen, um ihn nicht zu verletzen.";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Eine Dame? Ich kann verstehen, dass man um ein Schiff spielt, aber... eine Frau, wirklich? Sie haben also die Wahrheit auf den Straßen gesprochen, huh? Du gibst es einfach so zu?! Als ob ich... einer deiner idiotischen Matrosen wäre?";
			link.l1 = "Verdammt noch mal, Mary, das ist überhaupt nicht so! Er hat sie vom Gouverneur gewonnen, ich habe sie von ihm zurückgewonnen, um sie freizulassen, das ist alles. Es gibt nichts mehr dazu, ich schwöre!";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Nun, vielleicht ist das unter euch Adligen normal, aber ich bin nicht so, ja, gell! Mach was du willst, sag was du willst... stirb für sie, wenn du willst! Ich werde zu dem verdammten Schiff gehen, das du gewonnen hast und mich betrinken. Ich dachte, das wäre echt und... würde ewig dauern. Ich habe wohl zu viel erwartet!";
			link.l1 = "Mary, mir ist diese Frau scheißegal! Warte bitte... Verdammt! Schon wieder das Gleiche...";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, du bist für mich gekommen, ja, gell! Ich wusste es, habe nie daran gezweifelt! Ich bin so froh, dich zu sehen!";
			link.l1 = "Ich auch, Mary! Es hat mich die ganze Zeit getötet. Gott sei Dank, du bist in Ordnung, ja, gell?";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Apropos, was genau hast du getan, damit sie mich so leicht freilassen? Ohne eine ordentliche Prügelei oder Schießerei, ja, gell! Oh, und ich habe diese schöne Dame an Deck gesehen, als sie mich herauszogen. Was ist passiert, Charles?";
			}
			else
			{
				dialog.text = "Was genau hast du getan, um sie dazu zu bringen, mich einfach so freizulassen? Kein Kampf, kein Schuss abgefeuert, ja, gell! Ich sah einige britische Pfauen auf dem Deck, als sie mich rausbrachten. Was war das alles, Charles?";
			}
			link.l1 = "Alles, was zählt, ist, dass du wieder bei mir bist. Ich habe dich im Stich gelassen, Mary. Es tut mir so leid! Ich hoffe, du kannst es in deinem Herzen finden, mir zu vergeben! Ich hasse es, wie wir uns zuletzt verabschiedet haben, ja, gell?";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Hab ich schon. Es tut mir auch leid, ja, gell! Wenn ich nur nicht deine Angelegenheiten mit dieser Dame so persönlich genommen hätte... Ich hätte in dieser Nacht eine ordentliche Wache aufgestellt. Sie hätten uns nie so leicht erledigen können! Das war so dumm von mir!";
			link.l1 = "Die Vergangenheit ist die Vergangenheit. Ich liebe dich und ich werde dich nie wieder so verlassen. Ich verspreche es!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Ich wusste, dass du mich niemals verlassen würdest, ja, gell. Entschuldigung, dass ich je an dir gezweifelt habe, Charles! Es scheint, ich sollte wohl besser nicht genau wissen, was du getan hast, aye? Wir sind wieder zusammen und das ist alles, was zählt.";
			link.l1 = "Ich habe keine Geheimnisse vor dir. Ich werde dir erzählen...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Was für eine Geschichte... bezweifle, dass sonst jemand sie glauben würde, ja, gell! Ich wusste es von Anfang an! Ich wusste, dass deine 'spielerische' Nacht ein merkwürdiges Geschäft war! All diese noblen Pfauen... herzlose Bestien! Zumindest lag ich bei dir nicht falsch, ich wusste, dass du anders bist, ja, gell!";
				link.l1 = "Ich bin mir ziemlich sicher, dass viele Leute dort draußen mich für weitaus schlimmer halten. Ein richtiges Monster aus Märchen, ja, gell?";
			}
			else
			{
				dialog.text = "Welch eine Geschichte... niemand sonst würde es glauben, ja, gell! Ich wusste es von Anfang an! Ich wusste, dass deine 'spielerische' Nacht ein lustiges Geschäft war! Politik, Spione, Ver-schwö-rungen. Und du hast uns einmal mehr gerettet, ja, gell! Mein Held!";
				link.l1 = "Nicht sicher darüber. Es kann sein, dass der Krieg mit Großbritannien in ein paar Wochen beginnt. Aber ich habe getan, was ich musste, Mary. Du bedeutest mir alles, ja, gell?";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Ich kümmere mich nicht darum, was die Leute denken, wenn das der Fall ist, wirst du mein Monster, Charles sein! Die anderen sollten entweder gehen und darüber weinen oder mit mir umgehen! Denk daran, dass ich immer an deiner Seite bleiben werde, ja, gell?";
			}
			else
			{
				dialog.text = "Ich weiß, Charles. Ich habe es immer gewusst, aber es ist so schön, es von dir zu hören. Wisse das - ich werde immer an deiner Seite bleiben, ja, gell!";
			}
			link.l1 = "Habe das nie bezweifelt, Mary. Los geht's, die Jungs machen sich Sorgen. Zeit, die Segel zu setzen und hier raus zu kommen. Du bist wieder an meiner Seite und der Horizont wird von alleine nirgendwo hingehen.";
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			dialog.text = "Aye, aye, Kapitän!";
			link.l1 = "";
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, bist du das wirklich?! Ich habe fast alle Hoffnung verloren, ja, gell! Gott, du hast mir so sehr gefehlt! Bitte, bitte vergib mir, aye!";
			link.l1 = "Nein, verzeih mir, ich habe es nicht kommen sehen... Gott sei Dank, du hast es geschafft, Mary! Ich bin so glücklich!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Wenn wir schon von Vergebung sprechen - um ganz ehrlich zu sein, überlege ich, ob ich dich erschießen oder umarmen soll. Du solltest mir besser sagen, was zum Teufel hier vor sich geht, ja, gell?";
			link.l1 = "Ich liebe dich, Mary. Das ist alles, was ich dir sagen wollte.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Ja, als ob das hilfreich war, aber... Verdammt, ich auch, Charles. Ich liebe dich auch, ja, gell? Gott, endlich sind wir zusammen!";
			link.l1 = "Und ich möchte die Zeit, die wir haben, nicht damit verbringen, über Dinge zu sprechen, die keine Rolle spielen. Komm mit mir und ich werde dich heute Nacht nicht wagen zu verlassen. Selbst wenn der Himmel auf diese elende Stadt zu fallen beginnt. Ich werde dich nie wieder verlassen. Niemals.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Es scheint, ich sollte wohl besser nicht wissen, was genau du getan hast, ja, gell? Wir sind wieder zusammen und das ist alles, was zählt.";
			link.l1 = "Ich habe keine Geheimnisse vor dir. Ich werde dir erzählen...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Sagst du, diese... Marquise hat dir geholfen, mich zurückzubringen? Und du hast fast einen Krieg zwischen England und Frankreich angefangen, ja, gell? Versteh mich nicht falsch - das ist so romantisch und alles, aber was wird jetzt passieren? ";
			link.l1 = "Ich habe keine Ahnung, Mary. Wir sind wieder zusammen, der Rest ist irrelevant. Wenn die Machthaber es nicht unter den Teppich kehren können ... nun, ich bin bereit, meine Pflicht vor der Krone zu erfüllen.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "Und diese Marquise von dir? Hast du sie auch zurückgebracht? Der Portugiese hat viel von ihr gehalten. Er versicherte mir, dass du ihren Avancen standgehalten hast wie die Bastille. Ich möchte ihm glauben, ja, gell? Aber ich muss es von dir hören!";
			link.l1 = "Zwischen Frau Botot und mir läuft nichts, Mary. Ich habe ihr geholfen, sie hat mir geholfen, das ist alles. Wo wir gerade von Bartholomäus sprechen, wo ist er?";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Er ist weg, ja, gell. Hat sofort die Segel gesetzt, nachdem er mich hierher gebracht hat. Ich würde niemals in dieses verdammte Bordell gehen, also hat er ein Zimmer für mich gemietet, für ein paar Wochen im Voraus bezahlt und ist einfach abgehauen. Oh, ich habe fast vergessen, ja, gell! Ich habe einen Brief für dich!";
			link.l1 = "Ein Brief? Von Bartholomäus dem Portugiesen? Das ist etwas Neues. Mir gefällt nicht, wohin das führt...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Mach weiter, lies es. Ich werde zu den Jungs gehen. Sie haben sich wahrscheinlich Sorgen gemacht. Hat es jeder geschafft? Hoffentlich stört es dich nicht, wenn wir unten ein oder zwei Gläser trinken. Bring dich nicht wieder in ein Durcheinander, ja, gell!";
			link.l1 = "Sicher, aber bitte sei vorsichtig mit ihnen, Mary. Ich würde lieber heute Abend Zeit mit dir verbringen, anstatt betrunkene Körper zurück zum Schiff tragen zu müssen. Gott, ich kann immer noch nicht glauben, dass ich dich zurückbekommen habe!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "Der Strand, du, ich und guter Wein - Charles, das ist so romantisch! Wir sollten das öfter machen, ja, gell!";
			link.l1 = "Freut mich, dass es dir gefällt. Ich denke, wir werden von nun an mehr Zeit füreinander haben für Anlässe wie diesen.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "Wovon redest du? Ist etwas mit dem Schiff passiert, huh? Warum bist du auf den Knien, meine Liebe?";
			link.l1 = "Weil ich dich liebe, Mary. Das weißt du, das weiß ich, das weiß jeder. Also hier und jetzt, vor dem Meer und dem Himmel, frage ich dich, Mary Casper - gib mir die Ehre, mit mir vor den Menschen und Gott zu stehen, so viele Tage, wie uns von oben gegeben sind. Ich, Charles de Maure, Chevalier de Monper, frage dich - willst du meine Frau werden?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore36")
			{
				dialog.text = "Ich habe davon geträumt, es zu hören, ja, gell! Ich... du kennst meine Antwort Charles... oh, entschuldigung!";
				link.l1 = "Macht nichts, das ist nur Wein und ich habe dieses Hemd nie geliebt...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, natürlich ja! Ja, ja, tausendmal ja!!! Du... dieser Ort... nichts könnte mich glücklicher machen!!! Oh Gott, ich bin so glücklich, ja, gell!";
				link.l1 = "Du hast mich glücklich gemacht, Mary. Und ich möchte auf dich anstoßen, meine brennende Karibiksonne!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Mary_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Trink auf dich, mein Kapitän und zukünftiger Ehemann, ja, gell! Du bist das Beste, was mir je passiert ist!";
			link.l1 = "Aber das ist erst der Anfang - für uns! Und für unsere gemeinsame Zukunft! Es liegt so viel vor uns!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Trink auf dich, mein Kapitän und zukünftiger Ehemann, ja, gell! Du bist das Beste, was mir je passiert ist!";
			link.l1 = "Aber das ist erst der Anfang - für uns! Und für unsere gemeinsame Zukunft! So viel liegt noch vor uns!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Mary_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Charles, Abt Benoit in Martinique wieder, damit wir fortfahren können, ja, gell? Aber ich werde kein Kleid tragen, auch nicht um der Kirche willen, ich hoffe, du nimmst es mir nicht übel?";
			link.l1 = "Mary, ich liebe dich in jedem Outfit und ... na ja, du weißt schon. Du kannst tragen, was du willst, ich werde mich um jeden kümmern, der damit ein Problem hat! Aber ich wollte nur mit dir über die Gäste und die Zeremonie sprechen.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			if (LongHappy_CheckSaga())
			{
				dialog.text = "Weißt du, die meisten von denen, die sich aufrichtig über unser Glück freuen können, dürfen diese Stadt nicht einmal betreten, geschweige denn die Kirche, ja, gell? Deshalb - lass uns hier mit all den wichtigen Leuten heiraten, wie erwartet, und dann segeln wir nach Isla Tessoro und feiern richtig mit echten Freunden! Was meinst du, ja, gell?";
				link.l1 = "Tolle Option! Also los. Ich werde mit Abt Benoit sprechen, aber wir müssen Einladungen versenden und mehr...";
				link.l1.go = "LongHappy_9";
			}
			else // Сага провалена по времени или утоплен Центурион
			{
				dialog.text = "Weißt du, ich habe nicht viele Freunde außer unserer Crew. Also lade die ein, die du für notwendig hältst, und ich werde einfach glücklich sein mit dem, was ist, ja, gell!";
				link.l1 = "Wie du wünschst, Liebling. Ich werde mit Abt Benoit sprechen und alles organisieren, du bist einer prächtigsten Zeremonie würdig.";
				link.l1.go = "LongHappy_9a";
			}
		break;
		
		case "LongHappy_9":
			dialog.text = "Mach dir keine Sorgen, als gute Ehefrau werde ich einen Teil der Vorbereitungen übernehmen, ja, gell. Ich werde unseren Freunden schreiben und alles arrangieren, aber erzähl mir zuerst: Wie stellst du dir diese Hochzeit vor?";
			link.l1 = "Mein Ideal ist du, ich und unsere engsten Freunde. Nach all den offiziellen Gesichtern hier in Martinique werden wir etwas Aufrichtigkeit wollen.";
			link.l1.go = "LongHappy_10";
			link.l2 = "Wir müssen uns an diesen Tag erinnern. Rufen Sie alle! Niemand wird ausgelassen!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_9a":
			dialog.text = "Mit dir wäre eine Zeremonie mit einem Schiffskaplan auf dem Achterdeck, unter dem Sonnenuntergang im Meer, ausreichend, ja, gell. Aber wenn das ist, was du willst - wir werden feiern! Charles ... Ich werde jetzt weinen, umarme mich, ja, gell ...";
			link.l1 = "Mary...";
			link.l1.go = "LongHappy_9b";
		break;
		
		case "LongHappy_9b":
			dialog.text = "Das ist es, ich bin ruhig, ja, gell. Entschuldigung, das ist alles so ungewöhnlich. Aber Charles, als gute Frau, werde ich die Organisation übernehmen. Wir müssen auch eine Party für die Jungs organisieren, ja, gell, aber es ist unwahrscheinlich, dass die ganze Crew in die Kirche passt. Ich werde Absprachen mit der Taverne treffen, aber wir werden Schnaps und Geld brauchen - du weißt, wie gern Matrosen feiern.";
			link.l1 = "Also gut, das werden wir tun. Was muss ich vorbereiten?";
			link.l1.go = "LongHappy_9c";
		break;
		
		case "LongHappy_9c":
			pchar.questTemp.LongHappy.MarryMoney = 100000;
			pchar.questTemp.LongHappy.MarryRum = 100;
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				pchar.questTemp.LongHappy.MarryMoney = 200000;
				pchar.questTemp.LongHappy.MarryRum = 150;
			}
			if (GetCompanionQuantity(pchar) > 1)
			{
				pchar.questTemp.LongHappy.MarryMoney = 300000;
				pchar.questTemp.LongHappy.MarryRum = 200;
			}
			dialog.text = "Ich denke, "+sti(pchar.questTemp.LongHappy.MarryMoney)+" Pesos werden genug sein, ja, gell. "+sti(pchar.questTemp.LongHappy.MarryRum)+" Fässer Rum, es gibt nichts Schlimmeres als ohne Getränke dazustehen. Sobald du alles gesammelt hast, was wir brauchen, komm in die Taverne, ich kümmere mich um den Rest.";
			link.l1 = "Gut, Schatz, ich mache es.";
			link.l1.go = "LongHappy_9d";
		break;
		
		case "LongHappy_9d":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10_1");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Verstanden, lass uns das tun. Aber wir müssen Sharptown besuchen und alles vorbereiten. Ich denke, fünfzig Fässer Rum und ein paar Dutzend Fässer Wein werden ausreichen, ja, gell? Aber für den Fall der Fälle brauche ich dreihunderttausend Pesos.";
			link.l1 = "Das ist viel, aber der Anlass ist es wert. Ich werde es zusammenkratzen, mach dir keine Sorgen. Jetzt werde ich beim Abt vorbeischauen und nach Sharptown gehen.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Großartig, wir werden alle zusammenbringen, ja, gell! Aber wir müssen Sharptown besuchen und alles vorbereiten - wir werden eine Galeone voller Alkohol brauchen! Ich denke, hundert Fässer Rum und fünfzig Fässer Wein werden es tun. Aber, nur für den Fall, werde ich fünfhunderttausend Pesos hinzufügen. Wenn die Feier schnell endet, was für eine Feier ist das dann, habe ich recht?";
			link.l1 = "Ja, unsere Freunde dürfen nicht vor Durst sterben - ich werde alles besorgen, mach dir keine Sorgen! Jetzt werde ich beim Abt vorbeischauen und nach Scharftown gehen.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Alles ist bereit, Charles, ja, gell? Ich werde dafür sorgen, dass das Getränk entladen wird, gehe in die örtliche Taverne, treffe den Baron und übergebe die Einladungen. Warte hier, ja, gell?";
			link.l1 = "Du bist am Steuer, Lieber! Dann werde ich einfach irgendwo herumwuseln. Ich hätte wirklich nicht gedacht, dass Expeditionen in den Maine-Dschungel einfacher vorzubereiten wären als eine Hochzeit.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Wir sind hier fertig, Charles, ja, gell! Ich habe alles arrangiert, glaub mir - es wird wunderbar! Eine Sache ist peinlich: die örtliche Taverne ist vor einer Woche bei irgendeinem Fest abgebrannt. Aber sie ist fast wieder aufgebaut, größer und besser als die alte, ja, gell! Wir sollten alle hineinpassen.";
			link.l1 = "Ich hoffe wirklich, dass wir dieses nicht verbrennen. Mir hat die 'Alte Specht' wirklich gefallen! Wie auch immer, wir haben noch viel zu tun. Es ist Zeit, die Segel zu setzen. Und ja, Mary - du bist die Beste, das weißt du, ja, gell?";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Also los geht's, ja, gell? Die Gäste sind angekommen, die Kirche ist bereit. Ich weiß, dass wir uns näher stehen als viele Ehepartner, und das sind nur ein paar wichtige Worte in einem schönen Saal, aber verdammt mich - in dieser antiken, ursprünglichen Stadt war ich weniger besorgt, ja, gell!";
			link.l1 = "Es ist absolut normal, meine Liebe, absolut normal. Ich bin auch nervös. Ich denke, Vater Benoit wartet bereits, ich werde zu ihm gehen und herausfinden, wann der Gottesdienst beginnt.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Gut, ich werde eine Weile in der Stadt herumlaufen, mich fertig machen wollen, ja, gell! Charles, du verstehst, dass es kein Zurück gibt?";
			link.l1 = "Mary, Liebling, für mich gab es kein Zurück, seit wir uns getroffen haben. Ich habe mit ganzem Herzen auf diesen Tag gewartet. Mach dir keine Sorgen, alles wird gut.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Mary");
		break;
		
		case "LongHappy_20":
			dialog.text = "Ja, gell?";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Ja, gell?";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Ja, gell?";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "Ich, Charles Henry de Maure, Ritter von Monper, nehme dich, Mary Casper, zu meiner Frau, um dich zu haben und zu halten, von diesem Tag an, zum Besseren und zum Schlechteren, in Reichtum und in Armut, in Krankheit und Gesundheit, bis der Tod uns scheidet. Gemäß Gottes Heiligem Gesetz, in Gottes Gegenwart, lege ich dieses Gelübde ab.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Ich, Mary Casper, nehme dich, Charles de Maure, zu meinem Ehemann, zum Haben und zum Halten, von diesem Tag an, zum Besseren und zum Schlechteren, in Reichtum und in Armut, in Krankheit und in Gesundheit, bis der Tod uns scheidet. Nach Gottes heiligem Gesetz, vor Gott, gebe ich dieses Gelübde ab.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amen.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "Das ist unglaublich, ja, gell! Ich... ich weine, es tut mir leid Charles, ich werde... meine Nase ist rot geworden, oder?";
			link.l1 = "Mary de Maure, meine Frau, du bist an diesem Tag ebenso schön wie an jedem anderen Tag!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) dialog.text = "Danke dir, Charles, danke dir... Alles ist so feierlich und wunderbar! Dies ist der beste Tag meines Lebens, ja, gell!!! Schau, wie glücklich alle sind! Aber es ist Zeit für dich, die Gäste zu begrüßen und Glückwünsche entgegenzunehmen! Wenn du fertig bist - komm zurück - lass uns nach den Jungs in der Taverne sehen.";
			else dialog.text = "Danke dir, Charles, danke... Alles ist so feierlich und wunderbar! Dies ist der beste Tag meines Lebens, ja, gell!!! Schau, wie glücklich alle sind! Aber jetzt ist es Zeit für dich, die Gäste zu begrüßen und Glückwünsche entgegenzunehmen! Wenn du fertig bist, komm zurück, wir werden in Sharptown erwartet.";
			link.l1 = "Ich werde das sofort tun, Schatz. Ein Kuss und ich gehe!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Charles, meine Liebe, hast du schon mit den Gästen gesprochen?";
			link.l1 = "Noch nicht, hab Geduld, Schätzchen, ich komme bald zurück.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Ja, ich habe noch nie so viele Glückwünsche auf einmal gehört. Und weißt du was - die meisten von ihnen sprachen aufrichtig, ja, gell?";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) 
			{
				dialog.text = "Ja, ja! Sie haben mir auch so viele angenehme Dinge gesagt! Nicht alle natürlich, einige Leute sind klar überrascht von meinem Outfit, ja, gell! Aber ich bin so glücklich, dass die Hälfte der Dinge, die die Leute sagen, einfach an mir vorbeigehen. Und generell sind alle so süß. Charles, die Jungs in der Taverne erwarten uns bereits - wir sollten zu ihnen gehen. Sie werden sich freuen, ihren Kapitän zu beglückwünschen, ja, gell!";
				link.l1 = "Wir gehen jetzt sofort. Aber ich möchte diesen Tag an einem romantischeren Ort als dem Zimmer in der Hafentaverne beenden. Ich hoffe, meine Frau, es macht dir nichts aus, diese Nacht in unserer Kabine zu verbringen? Außerdem gibt es jetzt keine Wache auf dem Schiff...";
			}
			else
			{
				dialog.text = "Ja, ja! Sie haben mir auch so viele angenehme Dinge gesagt! Nicht jeder, natürlich, einige Leute sind offensichtlich überrascht von meinem Outfit, ja, gell! Aber ich bin so glücklich, dass die Hälfte der Dinge, die die Leute sagen, einfach an mir vorbeigehen. Und im Allgemeinen sind alle so niedlich. Charles! Aber wir werden in Sharptown erwartet, wann setzen wir die Segel?";
				link.l1 = "Genau jetzt. Wir können unseren Gästen nicht erlauben, alle Vorräte zu trinken! Ich hoffe, meine Frau, dass es dir nichts ausmacht, diese Nacht in unserer Kabine zu verbringen?";
			}
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Sogar in einer Hütte auf einer einsamen Insel, aber natürlich nur mit dir!";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Ich weiß. Ich liebe dich auch. Los, bevor die Jungs unseren Rum trinken und die Taverne in Brand setzen.";
			else link.l1 = "Ich tue es. Ich liebe dich auch. Dann - lass uns in See stechen!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Oh, mein Lieber, ich bin so glücklich! Heute ist ein wunderbarer Tag...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Reiß ihm seinen ungereinigten Kopf ab, Charles!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "Mir geht's gut, ja, gell! Wie geht es Nathan, lebt er noch?";
			link.l1 = "So viel Blut... Dannie, atmet er? Ich sehe ihn atmen!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Schneller, Liebling, verschwende keine Zeit!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Wir haben gewonnen, ja, gell! Verzeih mir, ich bin spät dran. Wir waren oben festgeklebt, da waren ein Dutzend dieser Bastarde, also war ich ein bisschen beschäftigt!";
			link.l1 = "Es ist gut, ich habe es geregelt. Ich bin froh, dass ich diese Geschichte mit Jacques endlich beenden konnte... endlich. Er hat bekommen, was er verdient hat.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Dann beende hier und geh zurück nach Sharptown! Wir sollten nach Nathan sehen, ja, gell? Er hat sein Leben für uns riskiert!";
			link.l1 = "Du hast recht, meine Liebe. Geh, ich bin direkt hinter dir.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "Übrigens, Liebling, wir haben Marcus gefunden, ja, gell! Er war im Laderaum, gefesselt und bewusstlos.";
			link.l1 = "Er lebt noch?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Er ist verletzt, aber er wird in Ordnung sein. Unseren Baron kann man nicht brechen, ja, gell! Er ist gerade aufgewacht und schon bereit für den Kampf.";
			link.l1 = "Das ist unser guter alter Marcus! Also, beende hier und ab an den Strand.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Es tut mir so leid, Charles, ja, gell, ich... Ich bin spazieren gegangen. Ich habe gesehen, dass du zurück bist, ich habe gehört, dass alle vor Sieg lebendig waren, aber ich... Aber was stimmt nicht mit mir, ja, gell!";
				link.l1 = "Alles wird gut, Liebling, alles wird gut. Ich bin auch traurig. Aber wir haben gewonnen, und Jacques Barbazon hat für alles bezahlt, was er getan hat.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Es tut mir so leid wegen Gino, Charles, ja, gell! Als ich es herausgefunden habe, konnte ich es nicht glauben! Wie geht es dir?";
					link.l1 = "Ich kann es auch nicht glauben... es hat sich so dumm entwickelt, ich habe mir diesen Tag nicht so vorgestellt.";
				}
				else
				{
					dialog.text = "Wir haben wieder gewonnen, ja, gell! Mein Ehemann ist ein Sturm für rebellische Barone der Bruderschaft der Küste! Freunde sind am Leben und Feinde sind tot - ein glorreiches Geschenk, ja, gell!";
					link.l1 = "Ja, so eine Feier, aber wir haben es geschafft, meine Liebe. Wir haben es geschafft.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Du stehst kaum auf deinen Füßen, ja, gell! Komm schon, Dannie hat uns hier am Stadtrand ein Haus gefunden, ich will jetzt nicht zum Schiff zurückkehren. Wir werden sitzen und auf unsere gefallenen Freunde trinken. Das alles ist zu viel für einen nüchternen Kopf, ja, gell.";
			link.l1 = "Ja, Mary, lass uns gehen.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Ich fühle mich so schlecht wegen Gino, Charles, ja, gell! Als ich es herausfand, konnte ich es nicht glauben! Wie geht es dir?";
				link.l1 = "Ich kann es auch nicht glauben ... es ist so dumm gelaufen, ich habe mir diesen Tag nicht so vorgestellt.";
			}
			else
			{
				dialog.text = "Entschuldigung, dass ich zu spät komme, mein Lieber, ja, gell! Ich ging spazieren, dann sah ich, wie du dich nähertest und rannte so schnell ich konnte! Dannielle hat mich rausgeworfen, als Gino sagte 'die Gefahr ist vorbei', ja, gell! Ich bin so froh, dass jetzt alles in Ordnung ist!";
				link.l1 = "Auch ich, Liebling. Und wir haben gewonnen. Barbazon ist tot, die Barone sammeln, was von ihren Besatzungen übrig ist. Der Kampf ist vorbei.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, ich sehe, du kannst kaum auf deinen Füßen stehen, aber niemand kann Tichingitu finden.";
			link.l1 = "Jan hat mir einen Tipp gegeben... Es scheint mir, dass unser rauer Maskogue auf die Piste gegangen ist. Lass uns zur Sabo-Matila Bucht gehen, einige Leute haben ihn in diese Richtung gehen sehen.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Nun, das ist unser strenger Ureinwohner, ja, gell! Komm schon, Dannie hat uns ein Haus hier am Rand gefunden - du bist zu diesem Zeitpunkt praktisch Schlafwandler, Charles, ja, gell!";
			link.l1 = "Da ist es ... entführe mich, meine schöne Squaw. Und lass es morgen alles wie einen schlechten Traum erscheinen.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_57":
			dialog.text = "Mach mich nicht falsch, mein Ehemann, in der Kirche war alles nur luxuriös, aber hier ist die Atmosphäre deutlich seelenvoller, ja, gell! Nun, das ist alles, Charles, jetzt wo all die Ärger hinter uns liegen, können wir uns entspannen.";
			link.l1 = "Nun, es ist nicht ganz 'alles', meine Frau - unser Leben geht weiter! Man kann im Allgemeinen sagen, dass es heute gerade erst begonnen hat. Also, lass uns gehen, mit unseren Leuten trinken, und dann - na ja, du erinnerst dich: die Kabine, der Wein, und wir...";
			link.l1.go = "LongHappy_58";
		break;
		
		case "LongHappy_58":
			DialogExit(); // телепорт в каюту
			DoQuestReloadToLocation("My_Cabin", "rld", "loc1", "LongHappy_InSPcabin");
		break;
		
		case "LongHappy_59":
			dialog.text = "Mein Ehemann... Es klingt so süß, ja, gell! Jetzt bist du für immer mein!";
			link.l1 = "Ich gehöre dir schon lange und werde es für immer tun, meine Liebe...";
			link.l1.go = "LongHappy_60";
		break;
		
		case "LongHappy_60":
			DialogExit();
			DoQuestCheckDelay("Mary_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_61";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_61":
			dialog.text = "Ich bin so glücklich, Charles! Und jetzt müssen wir wieder weiterziehen, ja, gell?";
			link.l1 = "Sicher, Liebling! Seite an Seite, zusammen und für immer!";
			link.l1.go = "LongHappy_62";
		break;
		
		case "LongHappy_62":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload1", "LongHappy_InSPComplete");
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "Ich fürchte, diese Pandemie setzt deinen Mädchen zu, Rodrigo. Beschäftige sie mit Stricken oder so etwas!";
			link.l1 = "Dieses Gespräch führt offensichtlich zu nichts. Wir haben vereinbart, dass wir morgen in die Kirche gehen. Zum Beten... natürlich.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "Ich bin stolz auf dich, meine Liebe!";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Nun, Charles...";
			link.l1 = "Was geht dir schon wieder durch den Kopf, Mary?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "(lacht) Die Tatsache, dass ich und Alan dasselbe auf der Insel tun wollten, wie du es hier getan hast";
			link.l1 = "Dein... Alan?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "Ja, er war wirklich ein verdammter Träumer, ihr beide könntet gute Freunde sein, wenn er noch am Leben wäre, gell?";
			link.l1 = "Nun, unsere Vorlieben haben sich bei einer Sache sicher gekreuzt!";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "Was? Ha-ha-ha! Hör auf Charles!\nSo oder so, das ist erstaunlich, wir haben diesen Leuten so viel Freude bereitet!";
			link.l1 = "Wir haben ihnen eine Chance auf Glück gegeben, aber den Rest haben sie selbst gemacht. Also, was denkst du, ja, gell?";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			dialog.text = "Komm später zu mir und du wirst es herausfinden...";
			link.l1 = "Verdammt ja, das werde ich!";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestCheckDelay("Mary_LoveSex", 2.0);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Ich mag Dunkelheit und enge Räume. Sie beruhigen mich. Endlich kann ich meine Gedanken sammeln\nEs ist, als ob alle Sorgen und Probleme... verschwunden sind, ja, gell! Ich vermisse dieses Gefühl wirklich...";
			link.l1 = "Du musst einen Arzt aufsuchen.";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "Richtig. Es ist, als wärst du zurück auf der 'Ceres Schmiede'.";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;

		case "tonzag_jailed_1":
			dialog.text = "...Schade, dass ich nicht alleine bin. In Stille, in Dunkelheit und in Einsamkeit, ja, gell? Das wäre perfekt.";
			link.l1 = "Mach weiter so, Mary Casper.";
			link.l1.go = "exit";
		break;

		case "tonzag_jailed_2":
			dialog.text = "Eines Tages kroch eine Krabbe in mein Bett - Ich schnitt sie auf und aß sie. Ja, gell.";
			link.l1 = "Mach weiter so, Mary Casper.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Maskierter Arsch! Autsch! Hilf mir, mein Lieber - wir müssen die Gitterstäbe durchbrechen!";
			link.l1 = "Ruhe! Ich versuche herauszufinden, was zu tun ist!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Liebling, diese maskierten Teufel sind überall! Sie haben ein riesiges Loch in den Rumpf geschlagen und kriechen hindurch wie diese Krabben! Wir müssen sie alle niederschlagen, ja, gell?";
			link.l1 = "Mary, stay here, find the senior officer, and take command! Take the ship out of the battle; we won't withstand another boarding!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Und wo willst du hin? Ich werde dich nicht gehen lassen!";
			link.l1 = "Ich muss Hercule und unserer Crew helfen! Vertraue mir, Mary!";
			link.l1.go = "tonzag_after_boarding_2";
		break;

		case "tonzag_after_boarding_2":
			dialog.text = "Aye aye, Liebling!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Sieg, ja, gell? Komm zu mir, Liebling! Ich will dich für ein oder zwei Stunden!";
			link.l1 = "Äh...";
			link.l1.go = "tonzag_after_victory_1";
			link.l2 = "Lass uns gehen!";
			link.l2.go = "tonzag_after_victory_1";
		break;

		case "tonzag_after_victory_1":
			dialog.text = "Hallo, Hercule! Ich bin so froh, dich zu sehen, grauer Bart!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog");
		break;

		case "tonzag_after_victory_2":
			dialog.text = "";
			link.l1 = "Mary, Mary, warte! Ich brauche deinen Bericht!";
			link.l1.go = "tonzag_after_victory_3";
		break;

		case "tonzag_after_victory_3":
			dialog.text = "Huh? Nun, wir haben gewonnen, ja, gell! Dieses verdammte Schiff ist geflohen. Ich habe einem Bastard den Schädel gespalten!\nPhew, verdammte Knöpfe!";
			link.l1 = "Oh, Mary...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Oh Gott, schau mich nicht an, Liebchen! Ich werde... puuh!";
			link.l1 = "Halte durch, Mädchen. Ich bin hier!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
		break;

		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Mary_officer":
			// если шлялся по борделям - устроит небольшой скандал 
			if (sti(pchar.GenQuest.BrothelCount) >= 3 && LAi_grp_playeralarm == 0)
			{
				dialog.Text = ""+pchar.name+"! Ich muss mit dir reden, ja, gell! Ernsthaft!";
				Link.l1 = "Was ist passiert, Mary? Gibt es ein Problem?";
				Link.l1.go = "brothel";
				break;
			}
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Ich höre zu, mein lieber Kapitän!","Ja, gell?"+pchar.name+", Ich bin ganz Ohr!","Haben Sie eine Aufgabe für mich, "+pchar.name+"?");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Mary, ich werde die alte indische Stadt Tayasal besuchen. Ich will dir nichts vormachen: Diese Reise ist sehr gefährlich und mehr noch - sie beinhaltet eine Teleportation durch das Idol, von dem ich dir erzählt habe. Wirst du... mir folgen?";
				Link.l4.go = "tieyasal";
			}
			////////////////////////казначей///////////////////////////////////////////////////////////
			// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Mary, gib mir einen vollständigen Schiffsbericht.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Ich möchte, dass du bestimmte Waren kaufst, jedes Mal wenn wir im Hafen sind.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Mary, ich brauche deinen Rat.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Mary, ich habe einen Auftrag für dich...";
            Link.l1.go = "stay_follow";
			if (pchar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex"))
			{
				Link.l2 = RandPhraseSimple("Liebling, ich will dich jetzt gerade. Ist das in Ordnung für dich?","Mary, wie wäre es, wenn wir... eine Weile zusammenbleiben? Nur wir zwei.");
				Link.l2.go = "cabin_sex";
			}
			if (rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple("Mary, sollen wir ein Zimmer mieten und zusammen bleiben?","Liebe, ich möchte mit dir alleine sein... wie wäre es, wenn wir uns ein Zimmer mieten und für ein paar Stunden alles vergessen?");
				Link.l2.go = "room_sex";
			}
			link.l9 = "Es ist bisher nichts, Mary.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Mary_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, sie ist eine Schönheit, ja, gell! Wir haben dieses winzige Loch unterhalb der Wasserlinie geflickt und die Segel getrocknet. Was- Was hast du erwartet? Schau mich nicht so an, ich habe nie gelernt, ein Schiffsverwalter zu sein.";
			Link.l1 = "Es tut mir leid, Mary, ich habe wirklich nicht nachgedacht.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Charles, aber mir geht's gut! Ich habe bereits meine Garderobe und mein Schwert. Aber danke für die Nachfrage, das ist sehr nett von dir, ja, gell!";
			link.l1 = "Aber ich habe nicht einmal... Was auch immer, vergiss es, Liebling, wir sind gut, ja, gell?";
			link.l1.go = "exit";
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
					Link.l3 = "Mary, wechsle die Munition für Feuerwaffen.";
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
            dialog.Text = "Sofort, mein Kapitän!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Sofort, mein Kapitän!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
