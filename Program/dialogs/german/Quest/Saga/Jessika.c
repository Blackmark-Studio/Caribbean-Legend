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
			dialog.text = "Willst du etwas?";
			link.l1 = "Nein, nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// бой на рифе
		case "reef":
			PlaySound("Voice\English\saga\Jessica Rose-06.wav");
			dialog.text = "Du! Du hast sie hierher gebracht! Sie ist sein Fleisch und Blut! Sie ist ihr Fleisch und Blut! Die Tochter der Hure ist zum Grab ihrer Mutter gekommen! Sie wird sterben! Und du wirst es nicht verhindern können! Steh Jessica nicht im Weg! Lass die Rache mein sein!";
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
			dialog.text = "Ha! Du kannst mir nichts anhaben!\n Die Luft, das Wasser, die Erde, das Feuer - ich befehle euch, mir zu helfen!\n Lasst die Toten auferstehen, lasst das Feuer brennen, lasst das Wasser die Brücke bewachen und lasst den Wind euch auf seine Flügel nehmen und auf den Boden werfen!\nGenieß es!!!";
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
			dialog.text = "Ha! Du kannst mir nichts anhaben!\nLass mehr Tote aufstehen und angreifen, lass das Feuer den Stein verbrennen, lass den Wind dich aufnehmen und hinunterwerfen und lass die Erde deine Stärken absorbieren!\nViel Vergnügen!!!";
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
			dialog.text = "Ha! Du kannst mir nichts anhaben!\nLass das Gift meine Flammenklinge bedecken, lass den Wind dich in seine Arme schließen, lass das Wasser deine Beweglichkeit wegtrinken!\nStirb! Ha-ha-ha!";
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
			dialog.text = "Genug... Ich bin müde. Ich bin besiegt... Habt Mitleid mit dem Schicksal der unglücklichen Jessica!";
			link.l1 = "Sicher... Ich werde deine arme Seele von der Last dieses toten Körpers befreien!";
			link.l1.go = "exit_battle";
			if (CheckAttribute(sld, "quest.jessika_peace")) // выслушал историю Джессики
			{
				link.l2 = "Ich kenne deine Geschichte, Jessica. Und es tut mir leid, dass dein Leben so traurig war und auf diese Weise endete. Du willst mit mir reden, nicht wahr? Nun, ich werde versuchen zu vergessen, dass du kürzlich versucht hast, mich zu töten und ich werde dir zuhören, obwohl es mir nicht leicht fallen wird...";
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
			dialog.text = "Danke... Du weißt bereits über Beatrice Sharp und Lawrence... mein Lawrence. Ich habe sie ohne zu zögern getötet, aber ich konnte ihn nicht töten. Ich konnte es nicht tun, aber er konnte. Jessica ist gestorben...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef");
			NextDiag.TempNode = "exit_talk_0";
		break;
		
		case "exit_talk_0":
			dialog.text = "... aber der Blutschwur, besiegelt durch einen schrecklichen Eid, ist immer noch nicht erfüllt. Die Macht dieses Schwurs kommt von der indischen Magie. Sie erweckte den Leichnam aus seinem Grab.\nHass verwandelte meine Seele in eine Wüste. Jeder, der zu diesem Riff kam, wurde von meiner Hand erschlagen und ihre toten Körper wurden meine Marionetten. Ich kann um Hilfe niemand anderes bitten als den, der mich besiegt hat...";
			link.l1 = "Und was kann ich für dich tun? Das Einzige, was ich tun kann, ist dir Leiden zu ersparen...";
			link.l1.go = "exit_talk_1";
		break;
		
		case "exit_talk_1":
			PlaySound("Voice\English\saga\Jessica Rose-03.wav");
			dialog.text = "Hilf mir... Bring mich zu ihm.";
			link.l1 = "Zu Lawrence Beltrope? Und wie soll ich das anstellen? Meine Mannschaft wird entweder weglaufen, sobald sie dich sehen, oder sie werden dich ohne Bedauern verbrennen. Übrigens, du bist immer noch in der Lage, meine Männer zu schlachten und sie zu 'kontrollieren'...";
			link.l1.go = "exit_talk_2";
		break;
		
		case "exit_talk_2":
			dialog.text = "Sie werden mich nicht sehen. Aber du wirst es tun. Du musst bereits verstanden haben, dass ich über Kräfte verfüge, die den Lebenden nicht zur Verfügung stehen. Aber ich kann dein Schiff nicht ohne deine Erlaubnis betreten. Bring mich zu ihm.\nIch werde nicht lange bei dir bleiben. Und ich werde deinen Leuten keinen Schaden zufügen. Lande mich um Mitternacht in der Portland Bucht auf Jamaika, die folgende Nacht treffen wir uns wieder und du wirst erhalten, was du hier finden wolltest.";
			link.l1 = "Wie weißt du, warum ich hier bin?";
			link.l1.go = "exit_talk_3";
		break;
		
		case "exit_talk_3":
			PlaySound("Voice\English\saga\Jessica Rose-01.wav");
			dialog.text = "Ich weiß viel. Mehr als die Lebenden. Ich habe sie gesehen... Du brauchst ein Dokument für sie und du wirst es bekommen. Du wirst sogar mehr bekommen, ich werde dir etwas zusätzlich geben. Bring mich zu ihm...";
			link.l1 = "Hm. Mir gefallen deine blutrünstigen Absichten gegenüber Helen nicht. Wage es nicht, sie anzurühren. Schließlich ist sie nicht verantwortlich für die Handlungen ihrer Mutter.";
			link.l1.go = "exit_talk_4";
		break;
		
		case "exit_talk_4":
			dialog.text = "Du hast mich besiegt. Ich werde ihr keinen Schaden zufügen... Ich verspreche es.";
			link.l1 = "Es ist noch nicht vorbei. Werdet Ihr mich von Euren zahlreichen Flüchen befreien? Ich gebe zu, mir gefällt der Gedanke nicht, für immer mit ihnen zu leben...";
			link.l1.go = "exit_talk_5";
		break;
		
		case "exit_talk_5":
			dialog.text = "Es ist nicht so einfach... Wenn wir uns in der Portland Bucht treffen nachdem ich... werde ich Ihnen sagen, wie Sie sich selbst heilen können.";
			link.l1 = "Nachdem du was?.. Was meinst du?";
			link.l1.go = "exit_talk_6";
		break;
		
		case "exit_talk_6":
			dialog.text = "Nach meinem Treffen mit ihm.";
			link.l1 = "Oh, er wird nicht glücklich sein. Ich kann es mir vorstellen. Gut, fassen wir zusammen: erstens, du versprichst, dass dich niemand sehen wird, zweitens, du wirst meiner Mannschaft keinen Schaden zufügen, drittens, du wirst nicht einmal an Helen denken, viertens, du wirst mir geben, wonach ich suche, und fünftens, du wirst mich von deinen Flüchen heilen. Habe ich recht?";
			link.l1.go = "exit_talk_7";
		break;
		
		case "exit_talk_7":
			dialog.text = "Fast. Ich werde dich nicht heilen, aber ich werde dir sagen, wie du es tun kannst. Du wirst es selbst machen müssen.";
			link.l1 = "Gut. Abgemacht. Ich erlaube dir, mein Schiff zu betreten.";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef2");
			NextDiag.TempNode = "exit_talk_8";
		break;
		
		case "exit_talk_8":
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			dialog.text = "";
			link.l1 = "Hey! Wo bist du? Einfach verschwunden...";
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
			dialog.text = "Du hast dein Wort gehalten - wir sind auf Jamaika. Komm morgen Nacht hierher und ich werde mein Versprechen erfüllen. Lebewohl.";
			link.l1 = "Lebewohl...";
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
			dialog.text = "Es ist vorbei, "+pchar.name+"...";
			link.l1 = "Was meinst du?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "Es ist vorbei... Hier, nimm es, das ist was du gesucht hast. Das ist der Brief meiner Rivalin, er wurde mit ihr begraben. Er ist gut erhalten. Ich habe ihr vergeben und in meiner Seele gibt es keinen Hass mehr.";
			link.l1 = "Hast du... dich mit ihm getroffen? Mit Lawrence?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			GiveItem2Character(pchar, "letter_beatriss"); // дать письмо
			AddQuestRecordInfo("Letter_beatriss", "1");
			dialog.text = "Ja. Das letzte, was er in seinem Leben fühlte, war Horror. Ich fühle kein Mitleid für ihn.";
			link.l1 = "Möge Gott seiner sündigen Seele vergeben... Es scheint, dass ich ihn nie treffen werde.";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Du hast nichts von Wert verloren. Er war ein sehr schlechter Mann. Nun sollten wir uns verabschieden, es gibt nichts mehr für mich zu tun hier. Mein Schwur wurde erfüllt und die Magie hat ihre Macht verloren. Ich habe dir ein Geschenk versprochen. Hier. Das ist meine Flamberge. Ich brauche sie nicht mehr. Diese Klinge ist einzigartig, du wirst nirgendwo auf der Welt eine bessere finden.";
			link.l1 = "Danke...";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			RemoveAllCharacterItems(npchar, true);
			GiveItem2Character(pchar, "blade_25");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nun, zu dir. Geh nach Bridgetown, zur örtlichen Kirche, um meine Flüche aufzuheben. Dort findest du einen Priester. Er kannte mich persönlich. Sprich mit ihm und er wird dir sagen, was zu tun ist. Bereite zwanzig Kerzen vor, du wirst sie brauchen.";
			link.l1 = "Bist du sicher, dass er mich heilen wird?";
			link.l1.go = "shore_7";
		break;
		
		case "shore_7":
			dialog.text = "Du wirst es selbst tun. Gott wird dich führen. Sei sicher. Alles wird gut sein.";
			link.l1 = "Gut, ich werde sofort nach Barbados segeln. Und was jetzt?";
			link.l1.go = "shore_8";
		break;
		
		case "shore_8":
			PlaySound("Voice\English\saga\Jessica Rose-04.wav");
			dialog.text = "Und jetzt wünsche ich mir noch eine letzte Sache. Begrabe meinen Körper hier in dieser Bucht nahe dem Meer. Das möchte ich. Vielleicht wirst du eines Tages das Grab der armen Jessica besuchen. Leb wohl, "+pchar.name+", und bete für mich...";
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
			dialog.text = "Erkennen Sie mich, Kapitän?";
			link.l1 = "Ist es... bist du es? Aber wie?";
			link.l1.go = "soul_1";
		break;
		
		case "soul_1":
			dialog.text = "Ja, "+pchar.name+", das bin ich, Jessica! Zumindest sah ich so aus, vor zwanzig Jahren.";
			link.l1 = "Also... bin ich gestorben? Aber wann? Wie?";
			link.l1.go = "soul_2";
		break;
		
		case "soul_2":
			dialog.text = "Du bist nicht tot, "+pchar.name+". Sie sind jetzt in der Kirche von Bridgetown. Sie schlafen nur...";
			link.l1 = "Ist das nur ein Traum? Die Dinge sehen zu real aus...";
			link.l1.go = "soul_3";
		break;
		
		case "soul_3":
			dialog.text = "Es passiert manchmal, "+pchar.name+". Gott hat dich gehört. Deine Gebete haben dich nicht nur geheilt, sondern auch meine Seele gereinigt. Vielen Dank, "+pchar.name+"! Und ich möchte dich bitten, mir zu vergeben, was am Riff passiert ist. Es ist... nun, vergib mir einfach. Ich konnte nicht gehen, ohne um deine Vergebung zu bitten.";
			link.l1 = "Ich vergebe dir, Jessica. Bin ich wirklich am Leben?";
			link.l1.go = "soul_4";
		break;
		
		case "soul_4":
			dialog.text = "Du bist es... Mach dir keine Sorgen. Bald wirst du aufwachen. Ich wollte nur Auf Wiedersehen sagen.";
			link.l1 = "Du bist so... wunderschön!";
			link.l1.go = "soul_5";
		break;
		
		case "soul_5":
			dialog.text = "Gefalle ich dir? Ja, es gab eine Zeit, als die besten Freier aus den Kleinen Antillen um mich warben und jeder dritte Pirat von Isla Tesoro bereit war, für mich zu duellieren.";
			link.l1 = "Aber du hast immer nur einen gebraucht... Eh, Ingwer-Talisman! Sag mir nur, warum ist es so weit gekommen?";
			link.l1.go = "soul_6";
		break;
		
		case "soul_6":
			dialog.text = "Wegen meiner Wut. Wegen meines Hasses. Wegen der Unfähigkeit zu verstehen, zu vergeben und zu vergessen. Ich hätte ein neues Leben beginnen können, aber ich zog es vor, mich einer dummen und sinnlosen Rache zu widmen. Du hast mich befreit. Danke, "+pchar.name+"...";
			link.l1 = "Ich bedauere dein Leben wirklich...";
			link.l1.go = "soul_7";
		break;
		
		// здесь проверяем Мэри
		case "soul_7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{ // Мэри-офицер
				dialog.text = "Nicht... Du hast immer noch deinen Ingwer-Talisman...";
				link.l1 = "Mein was?";
				link.l1.go = "mary_1";
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CheckAttribute(pchar, "questTemp.LSC.marywait"))
			{ // Мэри осталась на острове
				dialog.text = "Nicht... Du hast immer noch deinen Ingwer-Talisman...";
				link.l1 = "Mein was?";
				link.l1.go = "mary_3";
				break;
			}
			dialog.text = "Tue es nicht... Bedenke meine traurige Erfahrung und wiederhole meine Fehler nicht. Und lass auch die Menschen, die du liebst, sie nicht machen.";
			link.l1 = "Ich werde darüber nachdenken und werde sicherlich nicht dieselben Fehler machen...";
			link.l1.go = "soul_8";
		break;
		
		case "mary_1":
			dialog.text = "Denk mal nach. Sie ist auf deinem Schiff.";
			link.l1 = "Mary?!";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Ja. Sie ist das Beste, was dir jemals im Leben passieren wird. Vergiss das nicht. Ihre Liebe ist klar, ihre Hingabe ist unendlich. Sie ist mutig, jung, aber verzweifelt und unerfahren. Sie versteht nicht viel. Kümmere dich um sie, beschütze sie und lass niemanden zwischen euch beide kommen. Sie ist dein Talisman...";
			link.l1 = "Ich... Ich werde sie niemals verlassen und sie vor jeder Gefahr schützen.";
			link.l1.go = "soul_8";
		break;
		
		case "mary_3":
			dialog.text = "Sie ist auf der merkwürdigen Insel, die aus toten Schiffen besteht... Sie ist dort nicht allein, aber sie ist einsam. Jeder ihrer Morgen beginnt mit einem Gedanken an dich, jeden Tag betet sie für dich, jede Nacht brennt ein Licht in ihrer Kabine und ihr Kissen ist nass von ihren Tränen...";
			link.l1 = "Mary...";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "Es gibt eine Tochter zwischen euch beiden. Die Tochter der Frau, die einst zwischen mir und Lawrence stand. Das Schicksal eures Talismans liegt in euren Händen. Sie können nicht zusammen existieren, genauso wie ich und Beatrice es nicht konnten.";
			link.l1 = "Wie weißt du das?";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Die andere Seite... Sie zeigt viel... Es ist deine Wahl, aber denke daran: Mary ist das Beste, was du jemals in deinem Leben haben wirst. Ihre Liebe ist klar, ihre Hingabe ist unendlich. Sie ist tapfer, jung, aber verzweifelt und unerfahren. Sie versteht nicht viel. Sie braucht deinen Schutz, deine Fürsorge und deine Liebe. Sie ist dein Talisman.";
			link.l1 = "Ich werde darüber nachdenken. Das werde ich auf jeden Fall tun...";
			link.l1.go = "soul_8";
		break;
		
		case "soul_8":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) sTemp = "";
			else sTemp = "Und was die Tochter von Beatrice angeht, so solltest du wissen, dass deine edlen Taten für sie nicht gewürdigt werden. Bald wirst du das selbst sehen. Sei vorsichtig mit ihr. Nun...\n";
			dialog.text = ""+sTemp+"Ich muss gehen. Es ist Zeit, Auf Wiedersehen zu sagen... Dieses Mal wirklich. Vergiss Jessica nicht und versuche manchmal, ihr Grab zu besuchen... Nur du weißt, wo es ist.";
			link.l1 = "Sicher, Jess. Ich werde es besuchen und für dich beten.";
			link.l1.go = "soul_9";
		break;
		
		case "soul_9":
			dialog.text = "Danke dir. Auf Wiedersehen, "+pchar.name+"! Auf Wiedersehen!";
			link.l1 = "Auf Wiedersehen, Jessica...";
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
