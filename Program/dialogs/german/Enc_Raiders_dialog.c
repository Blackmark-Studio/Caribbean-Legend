void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = int(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_Robbed":
			int iMoney = int(int(Pchar.money)/20)*10;
			AddMoneyToCharacter(pchar, -iMoney);
			AddSimpleRumour(LinkRandPhrase("Have you heard? The local robber " + GetFullName(npchar) + " found a new victim. One captain got scared and bought off. They say, he gave him " + FindRussianMoneyString(iMoney) + ", he-he... ", 
				"Yeah, captain " + GetFullName(pchar) + ", I already heard that you had to pay " + FindRussianMoneyString(iMoney) + ", to buy off a local bandit, " + GetFullName(npchar) + ". Now that's what I call bad luck! Ha-ha-ha!", 
				"Have you heard that the local bandits attacked one captain? He was totally robbed, he lost " + FindRussianMoneyString(iMoney) + "!"), int(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();			
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(LinkRandPhrase(RandPhraseSimple("Have you heard? That bandit " + GetFullName(npchar) + " has finally found justice. He and his boys tried to rob "+ GetSexPhrase("some captain, but he turned out to be","some lady captain, but she turned out to be") +" a tough nut. So our dear robber shited his pants, ha-ha! That will be a lesson for him! Robbing the local farmers is one thing, but a brave captain is a different story!", 
				"Thank you, captain " + GetFullName(pchar) + ", for finally dealing with the gang of that bandit " + GetFullName(npchar) + ". Those rascals were really a pain in everyone's ass. We were scared to even send couriers to the farm for milk, they could have intercepted them and rob of all the money."), 
				"Have you heard, "+ GetSexPhrase("finally, some captain","finally, some lady captain") +" stopped that rascal " + GetFullName(npchar) + ", who was in 'charge' of the jungle, terrorizing all the local farmers. I do hope, it will stop them from their dirty deeds for long enough...", 
				"Have you heard that local bandit " + GetFullName(npchar) + " and his boys attempted to rob "+ GetSexPhrase("some captain","some lady captain") +"? Bah! Nothing of the sort! That captain turned out to be a tough nut. They say, he chased on these robbers over all the jungle like a shark chases flock of sardines. Thank God that there are still people who can stand up for us at time when the authorities do nothing, too busy with their dark deeds..."), int(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "GetLost";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}		
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(LinkRandPhrase("Steh da, wo du bist und leg deine Waffe nieder! Dein Geld oder dein Leben!","Bleib stehen, wo du bist, "+GetSexPhrase("Reisender","Lass")+"!) Berühre deine Waffe nicht und keine plötzlichen Bewegungen!","Bleib wo du bist, "+GetSexPhrase("Reisender","lass")+"! Das ist eine Mautstraße. Wenn du passieren willst, musst du die Maut bezahlen."),LinkRandPhrase("Hallo, "+GetSexPhrase("Kumpel","lass")+"! Nicht so schnell! Ich möchte sehen, wie schwer deine Geldbörse ist.","Komm näher, Freund. Ich will das Klimpern von Gold in deiner Geldbörse hören.","Halt ein, "+GetSexPhrase("Kamerad","lass")+". Ich und die Jungs haben darauf gewettet, wie viel Gold in deine Geldbörse passt. Jetzt müssen wir es überprüfen, bevor die Dinge gewalttätig werden."),"Mach keine Hast, "+GetSexPhrase("Reisender","Schatz")+"! Lass uns ein Herz-zu-Herz-Gespräch führen, ja?");				
			Link.l1 = LinkRandPhrase(LinkRandPhrase("Warum redest du diesen Unsinn?","Was ist los?","Wovon redest du?"),"Was meinst du?","Nur was wollen Sie damit andeuten?");
			Link.l1.go = "Node_2";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("Briganten?! Ausgezeichnet, ich sehnte mich nach einem Kampf!","Oh, ihr seid Briganten! Vor der Gerechtigkeit versteckt, nehme ich an? Nun, es scheint, dass die Gerechtigkeit gerade zu euch gekommen ist...","Hast du nicht gelernt, dass es ein Zeichen schlechter Manieren ist, Fremde mit deinem Unsinn zu belästigen? Scheint, dass ich dir diese Lektion beibringen muss..."),LinkRandPhrase("Oh, du bist ein frecher, nicht wahr?! Ich hoffe, dein Schwert ist so scharf wie deine Zunge.","Ich sehe, dass du ein Meister deiner Zunge bist, ich hoffe, du bist auch ein Meister deines Schwertes.","Oh, Banditen! So viele von deiner Sorte wurden gehängt, aber du kannst einfach nicht aufhören, direkt zum Galgen zu laufen."),LinkRandPhrase(RandPhraseSimple("Oh, Schurken! Ihr wisst, ich verschwende normalerweise keine Worte mit eurem Schlage!","Was für ein unverschämter Kerl! Stinkt wie ein dampfender Haufen Scheiße und wagt es immer noch, einen anständigen anzusprechen "+GetSexPhrase("Kerl","Mädchen")+"."),"Ich werde keine Worte mit dir verschwenden, aber du wirst feststellen, dass meine Pistole sehr beredt ist!","Schurken schon wieder! Nun, ich verspreche euch nicht den Galgen, aber ich kann euch sicherlich ein paar Löcher in den Bauch machen!"));
			Link.l2.go = "CheckSkills";	
			Link.l3 = LinkRandPhrase("Und wissen Sie, dass eine Patrouille mir dicht auf den Fersen ist? Ich kann sie nur anpfeifen und Sie sind erledigt.",RandPhraseSimple("Weißt du, ich kann die Patrouille rufen, hast du keine Angst davor? Sie sind in der Nähe. Ich vermute, sie suchen nach dir.","Eine Patrouillenpartei wurde kürzlich ausgeschickt, um dich zu finden, und sie werden jeden Moment hier sein. Du gehst ein großes Risiko ein."),RandPhraseSimple("Ich würde Ihnen raten, so schnell wie möglich zu laufen. Eine Patrouille kommt in diese Richtung, ich habe gerade mit ihrem Offizier gesprochen.","Ich hätte gerne unser Gespräch fortgesetzt, aber ich fürchte, die Patrouille, die ich gerade getroffen habe, wird unsere Bekanntschaft nicht zu einer engen Freundschaft werden lassen."));
			Link.l3.go = "Node_3";
		break;
		
		case "Node_2":
			dialog.text = LinkRandPhrase(LinkRandPhrase("Spiel nicht den Narren! Bargeld auf den Nagel und vielleicht lasse ich dich dann gehen!","Hast du noch nicht von der Reisezahlung gehört? Wenn du dich nicht von deinem Gold trennst, wirst du dich von einem Kopf trennen!","Heh, dieses gewöhnliche Abenteuer wird dich einen Geldbeutel kosten... wenn ich nicht wütend werde."),RandPhraseSimple("Es ist ganz einfach. Du gibst uns all dein Gold und dann bist du frei zu gehen, oder du bleibst hier, und wir nehmen trotzdem all dein Gold. Aber ich denke, das Letztere ist nicht das, was du möchtest, he-he.","Tun Sie nicht so, als ob Sie nicht verstehen! Geben Sie mir Ihre Geldbörse, wenn Sie nicht wollen, dass ich sie von Ihrem toten Körper nehme!"),"Ich erkläre es, wenn du so schwer von Begriff bist. Du gibst mir all dein Geld, wenn dir dein Leben lieb ist.");
			Link.l1 = "Verdammter Schurke! Ich habe nur "+int(int(Pchar.money)/20)*10+" Pesos.";
			Link.l1.go = "CheckMoney";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("Du willst mein Geld? Komm und hol es dir, und ich werde sehen, wie viel du wert bist!","Wie wagst du es, Tölpel! Ich werde dir eine Lektion in gutem Benehmen erteilen!","Welch ein Selbstvertrauen! Nun, lass uns sehen, wie du gegen einen echten "+GetSexPhrase("Seewolf","Seelöwin")+"!"),LinkRandPhrase("Du solltest für solche Empörung ausgepeitscht werden!","Ihr Schurken! Betet zu euren Teufeln um einen warmen Platz in der Hölle!","Du hättest schon lange gehängt werden sollen, Galgenvögel! Nun, es scheint, dass ich meinen Säbel mit eurem Blut beflecken muss!"),RandPhraseSimple("Und was bringt dich dazu zu denken, dass ich dir mein Geld geben werde?","Und hast du nicht bemerkt, dass ich gut bewaffnet bin und nicht nur zum Spazierengehen hierher gekommen bin?"));
			Link.l2.go = "CheckSkills";	
		break;

		case "Node_3":
			bOk = int(pchar.reputation.nobility) < 11 || int(pchar.reputation.nobility) > 90;
			if(bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				dialog.text = RandPhraseSimple("Verdammt! Gut, du darfst gehen. Aber denk nicht einmal daran, hier Lärm zu machen!","Dieses Mal hattest du Glück, aber nächstes Mal schuldest du uns das Doppelte! Vergiss nicht, uns daran zu erinnern, he-he.");
				Link.l1 = RandPhraseSimple("Aber natürlich.","Lauf schon, solange du noch kannst.");
				Link.l1.go = "Exit_NoFight";
			}
			else
			{
				bOk = int(pchar.reputation.nobility) < 51 && int(pchar.reputation.nobility) > 41; // Captain Beltrop, 23.01.21 - жесть!!! Надо было всего лишь убрать единичку!
				if(!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
				{
					dialog.text = RandPhraseSimple("Wir werden dich leise erlegen, du wirst nicht mal einen Mucks von dir geben.","Verdammt! Wir müssen dich schnell töten, bevor du Alarm schlägst.");
					Link.l1 = "Nun, das ist dein Begräbnis. Ich habe dich gewarnt.";
					Link.l1.go = "Exit_Fight";
				}
				else
				{
					dialog.text = RandPhraseSimple("Und warum sollte ich mich um deine Patrouille kümmern? Ich bezahle sie. Also, gib mir deine Geldbörse und hör auf, dein Maul zu zerreißen.","Du denkst, du kannst mir Angst machen? Ich bin selbst 'die Patrouille' für solche wie dich in diesem Dschungel. Noch niemand hat ohne Gebühr verlassen!");
					Link.l1 = "Verdammt, Schurke! Ich habe nur "+int(int(Pchar.money)/20)*10+" Pesos.";
					Link.l1.go = "CheckMoney";	
					Link.l2 = RandPhraseSimple(LinkRandPhrase("He-h, ich werde doch keine Befehle von so einem Schwächling wie dir befolgen.","Ich werde ein paar neue Löcher in deinen Schädel bohren wegen solcher Frechheit! Nur um dein Gehirn ein bisschen zu belüften.","Solche Frechheit wird nicht ungestraft bleiben!"),"Du hättest das nicht tun sollen...");
					Link.l2.go = "CheckSkills";
				}
			}
		break;
		
		case "CheckSkills":
		    bool isStrong = (GetCharacterSkillToOld(Pchar, "FencingL") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingS") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingH") >= 7);
			bool z_ok = (isStrong) && (int(Pchar.Rank) >= 8) && (int(PChar.reputation.nobility) <= 30); // Captain Beltrop & mitrokosta, 23.01.21 проверяем на оружие (новый вариант)
			if (z_ok || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				Diag.TempNode = "GetLost";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Hey, reg dich nicht so auf, "+GetSexPhrase("Kamerad","lass")+"! Ich habe nur gescherzt! Du kannst deinen Weg fortsetzen!","Gut, ich habe meine Meinung geändert. Du darfst gehen, wenn du so furchterregend bist."),"Was, ein "+GetSexPhrase("'tapferer Kapitän'","'kämpferisches Mädel'")+"? wieder? Nun gut, geh in Frieden...","Entspann dich, "+GetSexPhrase("Kumpel","lass es")+". Sie sehen, wir haben uns geirrt, "+GetSexPhrase(" wir dachten, du wärst ein Kaufmann"," wir dachten, du wärst ein Kaufmann")+". Du kannst gehen.");
				Link.l1 = LinkRandPhrase(LinkRandPhrase("In Ordnung, bis wir uns wiedersehen!","Du solltest aufhören, Leute auszurauben, solange du noch kannst.","In Ordnung, aber wenn ich dich jemals wieder sehe..."),RandPhraseSimple("Nächstes Mal pass auf, wen du bedrohst, du Hund.","Dank Gott, dass ich heute gute Laune habe."),RandPhraseSimple("Dieser kriminelle Handel wird dich sicherlich am Ende töten. Lebewohl.","Das ist eine weise Entscheidung. Nun, viel Glück!"));
				Link.l1.go = "Exit_NoFight";
				Link.l99 = LinkRandPhrase("Nein, Kumpel. Jetzt bringe ich dir gute Manieren bei!","Oh, hast du Angst bekommen? Nun, man sollte für seine Taten geradestehen, nicht wahr?","Nein! Jetzt werde ich mich nicht beruhigen, bis ich dich bei lebendigem Leibe häute!");
				Link.l99.go = "GetTheHellOut";
			}
			else 
			{
				dialog.text = LinkRandPhrase("Und du hättest in Frieden gehen können! Jetzt kannst du nur dich selbst beschuldigen!","Du hättest es nicht anfangen sollen, du Schurke! Jetzt wirst du sterben wie ein Hund!","Ach was! Ich reiß dich in Stücke! Schneid die Leber raus und fütter die Hunde damit!");
				Link.l1 = RandPhraseSimple("Ich werde dir deine Worte wieder in den Hals stopfen!","Wen bedrohst du, Abschaum?!");
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if(int(int(Pchar.money)/20)*10 >= int(Pchar.rank)*100)
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = LinkRandPhrase(RandPhraseSimple("In Ordnung! Gib es mir und verschwinde!","Nicht viel, aber immer noch besser als nichts. Es ist gut, mit einer klugen Person zu verhandeln! Du kannst gehen."),"Das ist eine andere Geschichte! Wie mein Freund immer sagt: 'Es ist immer gut, jemandem zuzuhören, der klug ist, aber mit dem Narren zu sprechen ist viel besser'! He-he!","Im Austausch für dein Gold gebe ich dir einen Rat, du solltest nicht im Dschungel spazieren gehen, wenn du bist "+GetSexPhrase("so ein Weichei. Trink deinen Rum in der Taverne, damit du und deine Geldbörse sicher bleiben!","ein Mädchen. Ausgeraubt zu werden ist nicht das Schlimmste, was dir hätte passieren können.")+".");
				Link.l1 = "Verdammt seist du!";
				Link.l1.go = "Exit_Robbed";				
			}
			else
			{
				dialog.text = "Ich nehme an, du versuchst mich zu betrügen! Keine Sorge, ich werde dich mit meinem Messer kitzeln, und vielleicht fällt etwas herunter.";
				Link.l1 = "Verdammt!";
				Link.l1.go = "Exit_Fight";				
			}				
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase("Du schon wieder? Lauf nach Hause zu deiner Mutter, bevor ich wütend auf dich werde!","Was? Du hast mir noch nicht all dein Gold gegeben? Ha-ha!","Schau, "+GetSexPhrase("Kamerad","Lass los")+", Ich habe die Nase voll von dir! Verschwinde aus meinen Augen, solange du noch lebst!");
			Link.l1 = "Ja, ich gehe schon.";
			Link.l1.go = "Exit";
			Link.l2 = "Ich dachte, es wäre nicht fair. Deshalb beschloss ich, die Dinge richtig zu stellen...";
			Link.l2.go = "Exit_Fight";
		break;
				
		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase("Was brauchen Sie noch? Wir haben bereits vereinbart, dass Sie gehen!","Lass mich in Ruhe, "+GetSexPhrase("Gefährte","lass")+". Ich kümmere mich um meine eigenen Angelegenheiten, und du hast deine eigenen, und wir sollten nicht versuchen, miteinander auszukommen!","Verlassen Sie jetzt, "+GetSexPhrase("Kamerad","lass")+"! Verdammt, bist du wirklich bereit, all dein Geld wegzugeben?");
			Link.l1 = "Ja, ich gehe schon.";
			Link.l1.go = "Exit";
			Link.l2 = "Ich erinnere mich, dass du dich nicht verabschiedet hast! Lass uns also richtig Abschied nehmen...";
			Link.l2.go = "Exit_Fight";
		break;

		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase("Lass mich in Ruhe! Hilf mir! Ich will leben!","Hilf mir! "+GetSexPhrase("Er ist ein Wahnsinniger","Sie ist eine Maniak")+"! Töte mich nicht!","Verschone mich! Ich bin nur ein bescheidener Brigant! Ich bin zu jung um zu sterben!");
			Link.l1 = LinkRandPhrase(LinkRandPhrase("Wenn du zu Hause geblieben wärst, würdest du noch leben!","Du hättest vorher darüber nachdenken sollen!","Du hättest wissen sollen, dass es immer Konsequenzen gibt!"),"Früher oder später, das war unvermeidlich.","Zu spät zum Bereuen, jetzt kämpfen Sie Abschaum!");
			Link.l1.go = "exit_Fight";			
		break; 				
	}
}
