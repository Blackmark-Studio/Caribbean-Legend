// НПС по квесту Суп из черепахи
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Que désires-tu ?";
			link.l1 = "Non, rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// денщик Фокса - Бенджамин Джонс
		case "BenjaminJons":
			if (CheckAttribute(PChar, "questTemp.Terrapin.Benjamin") && pchar.questTemp.Terrapin == "baster")
			{
				dialog.text = "Le seigneur colonel est actuellement sur le terrain pour un exercice militaire. Que voulez-vous de lui, capitaine ?";
				link.l1 = "Cette fois, Ben, c'est toi dont j'ai besoin. J'ai de mauvaises nouvelles concernant ta sœur Molly. Cette belle fille est apparemment dans de beaux draps. Elle a été capturée par des pirates de Tortuga. Elle a besoin d'aide et elle a demandé qu'on te prévienne. L'homme qui s'est chargé de transmettre le message a été tué, mais avant sa mort, il a réussi à me parler de ta sœur.";
				link.l1.go = "sister";
				break;
			}
			sld = characterFromId("Fox");
			if (sld.location == pchar.location)
			{
				dialog.text = "Si vous vous dirigez vers le colonel Fox, alors faites demi-tour à 360 degrés et éloignez-vous. Il ne reçoit pas d'invités.";
				link.l1 = "Très bien alors.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Le colonel n'est pas ici. Revenez plus tard.";
				link.l1 = "D'accord...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "BenjaminJons";
		break;
		
		case "sister":
			dialog.text = "Ha ! Vous êtes le tout premier homme à avoir jamais qualifié ma sœur de 'belle'. Dieu lui a donné le corps d'un grenadier et la trompette de Jéricho au lieu de voix. Notre Molly sait se battre toute seule. Mais la créativité de Notre Seigneur ne s'est pas arrêtée à tout ce qui est en dessous de son menton. Non non, la meilleure chose qu'Il ait faite a été de coller le visage poilu et marqué de cicatrices de notre défunt père au-dessus de sa poitrine. Et je dois dire, monsieur, que le visage de mon père faisait s'évanouir les chevaux.";
			link.l1 = "Je vois que tu n'es pas particulièrement contrarié...";
			link.l1.go = "sister_1";
		break;
		
		case "sister_1":
			dialog.text = "Et pourquoi se montrerait-elle à Tortuga ? Molly est une servante de Catherine Fox, la fille de notre vaillant colonel. Catherine venait d'Europe pour rendre visite à son père pour son anniversaire. Mais l'escadre avec laquelle son navire naviguait a été retardée\nSi tu veux voir la véritable Molly Jones et sa maîtresse, qui est très belle au passage, viens ici dans un mois. Pas un jour plus tôt.";
			link.l1 = "Il s'avère que votre sœur Molly Jones a été au service de Mme Fox et réside actuellement de l'autre côté de l'Atlantique ?";
			link.l1.go = "sister_2";
		break;
		
		case "sister_2":
			dialog.text = "Exactement ainsi ! Le dernier courrier nous a informés qu'une escadre de la marine envoyée par le Lord Protecteur Cromwell lui-même devait quitter Londres il y a seulement un mois. Le brigantin 'Albatross' avec Catherine à bord devait les accompagner. Nous apprendrons si c'est vraiment le cas avec le prochain bateau courrier. Bien que les navires ne soient pas encore arrivés et que le colonel ait strictement interdit à l''Albatross' de naviguer seul\nSaviez-vous que sa femme bien-aimée est morte lors d'une attaque de corsaires français ? Ce ne fut pas facile pour le colonel et il redoute encore les dangers des hautes mers... Alors je ne peux pas vous aider avec Molly Jones, capitaine ! Il y a beaucoup de filles coloniales nommées Molly ! De plus, avoir le nom de famille Jones en Grande-Bretagne équivaut à ne pas avoir de nom du tout !\nTous les chiens de mer à Antigua me connaissent, ainsi que mon commandant. Pas étonnant qu'une pauvre fille en difficulté veuille mon aide. J'aimerais bien, mais je n'ai pas la pièce pour une rançon. Le colonel me doit trois mois de salaire, mon salaire avec celui de tous les autres arrive avec l''Albatross'.";
			link.l1 = "Apparemment, je me suis donc trompé. Mais merci quand même pour la clarification.";
			link.l1.go = "sister_3";
		break;
		
		case "sister_3":
			dialog.text = "Pas du tout, capitaine.";
			link.l1 = "...";
			link.l1.go = "sister_4";
		break;
		
		case "sister_4":
			DialogExit();
			AddQuestRecord("Terrapin", "3");
			pchar.questTemp.Terrapin.Catherina = "take"; // возможен вариант с Кати
			DeleteAttribute(pchar, "questTemp.Terrapin.Benjamin");
		break;
		
		// Робер Мартэн
		case "Rober":
			PlaySound("Voice\English\sharlie\Rober Marten-01.wav");
			dialog.text = "Que veux-tu ?! Je n'ai pas envie de parler.";
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "rober")
			{
				link.l1 = "J'ai une affaire pour vous, capitaine. Je vois que vous n'êtes pas d'humeur joyeuse et peut-être que ma proposition vous égayera un peu.";
				link.l1.go = "rober_1";
			}
			else
			{
				link.l1 = "Tais-toi, bois du rhum. Ma faute, compagnon. Je suis désolé.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rober";
		break;
		
		case "rober_1":
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Terrapin_LateBaster.over = "yes"; //снять таймер
			dialog.text = "Le son en est fort attrayant ! Et ton visage me semble familier... Je ne me souviens plus où je t'ai vu. Vas-y, raconte !";
			link.l1 = "Je suis au courant de ton affaire avec Thibaut... Détends-toi, mon gars ! Tu n'as pas à me craindre. J'ai une proposition à te faire.";
			link.l1.go = "rober_2";
		break;
		
		case "rober_2":
			dialog.text = "Que le diable m'emporte ! Foutue truie ivre !... Je n'ai pas réussi à...";
			link.l1 = "Tu as bien raison. Ton marin avait une grande gueule, mais ses rumeurs ne sont allées nulle part au-delà de moi. Et ces rumeurs n'iront pas plus loin puisque c'est toi qui t'en es occupé, n'est-ce pas ?";
			link.l1.go = "rober_3";
		break;
		
		case "rober_3":
			dialog.text = "Caramba ! Je te reconnais maintenant ! Tu es l'homme qui a mis en déroute le colonel Doiley et a pris toute son île ! Tu étais impliqué dans de gros affaires avec la Compagnie néerlandaise des Indes occidentales, tu fréquentes un baron de la mer des Caraïbes... Ton nom est... "+GetFullName(pchar)+", n'est-ce pas ?";
			link.l1 = "Vous possédez des informations précises. Oui, c'est moi. Mais pouvez-vous vous calmer un instant, Robert ?";
			link.l1.go = "rober_4";
		break;
		
		case "rober_4":
			PlaySound("Voice\English\sharlie\Rober Marten-02.wav");
			dialog.text = "Argh ! Eh bien, comment puis-je me calmer, quand l'un des plus célèbres loups de mer de l'archipel s'intéresse à moi et, en plus, il a découvert mes affaires ! Qu'est-ce qui m'a pris d'attaquer cette brigantine ! Que voulez-vous de moi ?";
			link.l1 = "Ferme ta bouche et écoute-moi. Il me semble que nous voulons tous deux la tête de Levasseur sur un plateau. Ce fanfaron pompeux a pris la grosse tête et a fâché des gens sérieux. J'ai l'intention de modifier l'équilibre des pouvoirs sur l'île et de remettre de Poincy à sa place, mais je ne veux pas verser le sang superflu de mes compatriotes, surtout à cause d'un sale voleur. Tu peux m'aider. Et je peux t'aider, toi et Thibaut, à conserver vos privilèges.";
			link.l1.go = "rober_5";
		break;
		
		case "rober_5":
			dialog.text = "Attends, attends ! Je ne peux pas en croire mes oreilles ! Fortuna me sourit aujourd'hui. Tu as raison, nous partageons des objectifs. Avec toi, cela peut devenir beaucoup plus intéressant... Thibaut est un bon escrimeur, mais il n'a pas les tripes pour trancher la gorge de son oncle... Mais un requin rusé comme toi pourrait le faire. Ta renommée est bien connue\nJe n'ai pas besoin de tes garanties, mais je t'aiderai en échange de la fille. J'ai besoin d'elle comme otage jusqu'à ce que je termine mes affaires aux Caraïbes. Bientôt, les frégates anglaises commenceront à me pourchasser. Quel diable m'a pris d'attaquer ce brick ! Il semblait être une proie si facile, séparée de l'escadron...";
			link.l1 = "Qu'avait-elle de si spécial ? La fille que tu cachais à Levasseur ?";
			link.l1.go = "rober_6";
		break;
		
		case "rober_6":
			dialog.text = "Oui. Vous devez convaincre Thibaut de se séparer de la fille. Je lui ai demandé de s'occuper d'elle pendant que je découvrais qui diable elle était, mais cette 'Miss Jones', ou quel que soit son nom, lui a complètement tourné la tête et maintenant Henri la cache même de moi ! Amenez-moi cette envoûtante sirène et je vous organiserai une rencontre avec Levasseur à l'extérieur de la ville. À ce moment-là, vous aurez l'opportunité de lui tendre une embuscade. Je vous attendrai à la plage de Fisheye.";
			link.l1 = "D'accord. Maintenant, dis-moi comment attraper Thibaut.";
			link.l1.go = "rober_7";
		break;
		
		case "rober_7":
			dialog.text = "Les gens à la taverne peuvent te montrer le chemin de sa maison. Henri est assez remarquable. Menace-le de l'exposer et fais-le amener la fille à moi. Ce même jour, je ferai savoir à Levasseur que son neveu cache une rare beauté dans le cachot de la ville.\nMon courrier te trouvera à la taverne. Après qu'il échoue à trouver Henri, le gouverneur ira au cachot avec une petite escouade et tu auras une belle opportunité de discuter avec lui.";
			link.l1 = "Où dois-je livrer la fille ?";
			link.l1.go = "rober_8";
		break;
		
		case "rober_8":
			dialog.text = "Dites-lui de la livrer lui-même à la plage. Je lui dirai deux mots pendant que j'y suis...";
			link.l1 = "D'accord. Considère cela comme un accord. À bientôt à Tortuga !";
			link.l1.go = "rober_9";
		break;
		
		case "rober_9":
			dialog.text = "Si tout se passe comme prévu, nous ne nous reverrons jamais. Du moins, je l'espère. Adieu !";
			link.l1 = "...";
			link.l1.go = "rober_10";
		break;
		
		case "rober_10":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Baster_tavern", "goto", "goto2");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina")) AddQuestRecord("Terrapin", "6");
			else AddQuestRecord("Terrapin", "5");
			pchar.questTemp.Terrapin = "tortuga";
			// создаем Тибо
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Tibo", "Tibo", "man", "man", 35, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_18", "pistol4", "bullet", 250);
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.name = "Henry";
			sld.lastname = "Thibaut";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "tibo";
			sld.greeting = "Tibo";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			TakeNItems(sld, "potion2", 8);
			TakeNItems(sld, "potion3", 5);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
		
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 40, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 20, false); // таймер
			SetFunctionLocationCondition("Tonzag_AtTortuga", "Tortuga_town", false);
		break;
		
		case "rober_abordage":
			dialog.text = "Argh ! Je ne l'ai pas vu venir... Tu es venu pour mon âme, n'est-ce pas, camarade ? J'ai tout fait comme convenu ! Nom d'un chien ?!";
			link.l1 = "Tu as une condamnation sur toi, Robert. La sentence m'a été confiée à exécuter. Alors j'accomplis ma mission.";
			link.l1.go = "rober_abordage_1";
		break;
		
		case "rober_abordage_1":
			dialog.text = "Toi, démon ! C'est impossible ! Il n'a pas pu tout découvrir si rapidement ! Et comment l'a-t-il même découvert ?!";
			link.l1 = "Tu parles de Fox ? Non. Ce n'est pas lui qui m'envoie. Le colonel ne sait même pas encore que tu as abattu sa fille. C'est ton vieux camarade Henry Thibaut qui veut ta mort. C'est lui qui m'a engagé.";
			link.l1.go = "rober_abordage_2";
		break;
		
		case "rober_abordage_2":
			dialog.text = "Ce foutu catamite ! J'aurais dû le donner en pâture aux crabes quand il était sur le 'Voltigeur'... Combien ce salaud t'a-t-il promis ?";
			link.l1 = "Ce n'est pas tous les jours qu'un homme apprend le prix de sa tête, n'est-ce pas Robert ? Thibaut t'a évalué à un quart de million, mais je l'ai convaincu que tu vaux plus. Tu vaux trois cent mille pesos d'argent, mon ami. N'es-tu pas content ?";
			link.l1.go = "rober_abordage_3";
		break;
		
		case "rober_abordage_3":
			dialog.text = "Attendez une seconde... Faisons un marché ! Je vous paierai plus !";
			link.l1 = "Avec quel argent, Robert ? Je suis absolument sûr que tu mens. Tu n'as pas autant d'argent que ce qu'Henri m'a promis. Et ce n'est pas le plus important de toute façon. Si ce n'était pas pour un fait, j'aurais refusé sa proposition de te traquer et de mettre fin à tes sales affaires avec Thibaut.";
			link.l1.go = "rober_abordage_4";
		break;
		
		case "rober_abordage_4":
			dialog.text = "Quel fait est-ce là ?";
			link.l1 = "Tu as tué Catherine Fox. La seule faute de cette pauvre fille était d'être née fille du Colonel Fox. Je hais les lâches méprisables comme toi qui mettent à mort des femmes sans défense ! Je ne ferai aucun marché avec toi. Je n'y penserai même pas. Ne gaspille pas ton souffle.";
			link.l1.go = "rober_abordage_5";
		break;
		
		case "rober_abordage_5":
			PlaySound("Voice\English\sharlie\Rober Marten-03.wav");
			dialog.text = "Putain ! Que pouvais-je faire d'autre ?! Je ne pouvais pas la laisser vivre et la cacher sans fin sur le bateau ! Et qui es-tu... vaurien, salaud, assassin, pour me faire la leçon sur la morale ! Regarde-toi ! Tes 'méthodes' ! Tu ne vaux pas mieux que moi !";
			link.l1 = "Assez. Martene, tire ta lame ! Il est temps d'en finir.";
			link.l1.go = "rober_abordage_6";
		break;
		
		case "rober_abordage_6":
			dialog.text = "Je te verrai en enfer !";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "rober_abordage_7";
		break;
		
		case "rober_abordage_7":
			DialogExit();
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Тибо, вариант без Кати
		case "tibo":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "Que faites-vous chez moi, monsieur ?";
			link.l1 = TimeGreeting()+", Monsieur Thibaut. Je suis ici de la part d'un homme que vous connaissez, le Capitaine Robert Martene.";
			link.l1.go = "tibo_1";
		break;
		
		case "tibo_1":
			dialog.text = "Hm. Et? Alors?";
			link.l1 = "Le capitaine Martene demande le plaisir de votre compagnie sur la plage de Fisheye dès maintenant. Mais pas tout seul. Il apprécierait également de voir Molly Jones en votre compagnie. Comprenez-vous ce que je veux dire?";
			link.l1.go = "tibo_2";
		break;
		
		case "tibo_2":
			PlaySound("Voice\English\sharlie\Henry Thibault-01.wav");
			dialog.text = "Hélas, monsieur, je ne le sais pas. Je n'ai jamais entendu parler de Molly Jones et Robert n'a jamais eu besoin de m'envoyer un... plénipotentiaire que je n'ai jamais vu auparavant. Pour votre information, monsieur, je suis le deuxième homme de cette île après mon oncle le gouverneur, donc...";
			link.l1 = "La vie est une bête imprévisible, Henry... En ce moment, vous êtes le second homme de l'île et dans quelques heures, vous pourriez être enchaîné dans les casemates... Tout ça pour la vie de quelqu'un qui ne vous donnerait pas un seul peso. Vous avez désobéi à l'ordre de votre oncle, n'est-ce pas, monsieur Thibaut ? Qu'est-ce qui est plus important pour vous : une fille dévergondée ou votre vie ?";
			link.l1.go = "tibo_3";
		break;
		
		case "tibo_3":
			dialog.text = "Pourquoi toi... Tu mens ! Tu racontes des salades !";
			link.l1 = "Vous, comme tout le monde, devez savoir à quel point le tempérament de votre oncle peut être fougueux. Levasseur découvrira que vous cachez la fille avant le coucher du soleil. Ne me demandez pas comment Robert l'a su, mais écoutez mes mots : il est mort de peur et prêt à lever l'ancre sur-le-champ. Il n'a même pas osé entrer dans la ville et m'a payé une somme coquette pour vous livrer ce message à la place.";
			link.l1.go = "tibo_4";
		break;
		
		case "tibo_4":
			dialog.text = "Merde... Ça ne peut pas être !";
			link.l1 = "C'est à vous de décider, monsieur. Martene ne vous attendra pas plus de deux heures. Il tient à la tête sur ses épaules. C'est uniquement par amitié qu'il traîne encore sur les côtes de la Tortue et ne se cache pas quelque part avec les Hollandais.";
			link.l1.go = "tibo_5";
		break;
		
		case "tibo_5":
			dialog.text = "Caramba ! Comment mon oncle a-t-il pu découvrir cela ?";
			link.l1 = "Langues, Henry. Langues bien pendues. Même moi je sais que toi et Robert avez attrapé la beauté qui est descendue de la brigantine anglaise saisie par ton compagnon. Vous l'avez cachée de Levasseur... tsk tsk. Doutes-tu vraiment que je sois le seul informé de cette histoire ?";
			link.l1.go = "tibo_6";
		break;
		
		case "tibo_6":
			dialog.text = "On dirait que vous dites la vérité, monsieur. Dites à Martene...";
			link.l1 = "Je ne pense pas que tu comprennes, Henry. Martene ne va pas t'attendre. Ton seul espoir est de sortir cette fille d'ici, la raison pour laquelle toi et Robert avez des cordes autour du cou. Cours là-bas où tu la caches, prends-la par ses jolies petites mains, et amène-la au Voltigeur. Trouve-la vite, et amène-la encore plus vite. Ton oncle n'entendra pas un mot de cela de ma part.";
			link.l1.go = "tibo_7";
		break;
		
		case "tibo_7":
			dialog.text = "D'accord. Nous ferons cela alors. Merci pour votre bienveillance, monsieur !";
			link.l1 = "Pas besoin de me remercier, monsieur. Mon travail est payé... Je veux juste que vous sortiez de la mouise avant d'être cuit.";
			link.l1.go = "tibo_8";
		break;
		
		case "tibo_8":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Terrapin_wait.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_wait.win_condition.l1.date.hour  = sti(GetTime()+3);
			pchar.quest.Terrapin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l2 = "location";
			pchar.quest.Terrapin_wait.win_condition.l2.location = "Tortuga_tavern";
			pchar.quest.Terrapin_wait.function = "Terrapin_SetEnvoy";
			pchar.questTemp.Terrapin = "cave";
			AddQuestRecord("Terrapin", "8");
			SetFunctionTimerCondition("Terrapin_ReturnTibo", 0, 0, 10, false);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 4, false);
			} 
			else SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 2, false);
		break;
		
		// вариант с Кати
		case "tibo_9":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "Que faites-vous ici, monsieur ? Je ne vous ai pas invité ici.";
			link.l1 = TimeGreeting()+", Monsieur Thibaut. Je viens de la part d'un homme que vous connaissez. Il s'appelle le Capitaine Robert Martene.";
			link.l1.go = "tibo_10";
		break;
		
		case "tibo_10":
			dialog.text = "Hm. Et? Alors?";
			link.l1 = "Le capitaine Martene demande le plaisir de votre compagnie dès maintenant sur la plage de Fisheye. Mais pas seul. Il apprécierait également voir Molly Jones en votre compagnie. Comprenez-vous ce que je veux dire ?";
			link.l1.go = "tibo_11";
		break;
		
		case "tibo_11":
			dialog.text = "Hélas, monsieur, je ne le fais pas.";
			link.l1 = "Ça, c'est ce que je m'attendais à ce que tu dises. Bien sûr, je doute que tu aies pu être présenté auparavant à la fille du Colonel Fox, tu connais bien sûr le Colonel Fox, commandant des redoutables Renards de Mer... la terreur des ennemis de l'Angleterre dans les Caraïbes ? Toi et Robert avez remué un tel nid de frelons, c'est un miracle que vous n'ayez pas encore été piqués ! La fille Molly Jones que tu as capturée du brigantin anglais, que tu as cachée à Levasseur, est la fille du Colonel Fox, Catherine Fox !";
			link.l1.go = "tibo_12";
		break;
		
		case "tibo_12":
			dialog.text = "Q-quoi?";
			link.l1 = "Vous êtes devenu tout pâle, monsieur. Maintenant écoutez-moi bien, Henry, et prêtez attention : vous et votre compagnon Robert êtes dans la merde jusqu'au cou. D'un jour à l'autre, l'escadron naval de Cromwell arrivera aux Caraïbes. Ils seront à votre recherche. Son vaisseau amiral, à lui seul, est capable de réduire en éclats et en bouillie votre vanté La Roche et son équipage en quelques heures. Qu'en pensez-vous ? L'attaque de ce brick anglais et la captivité de la fille de Fox en valaient-elles la peine ?";
			link.l1.go = "tibo_13";
		break;
		
		case "tibo_13":
			dialog.text = "";
			link.l1 = "Mais ce n'est pas tout. Tes machinations ne sont pas seulement connues de moi. Ton cher oncle le gouverneur découvrira que tu enfreins ses ordres stricts et que tu lui as caché une fille que le vieux débauché aurait certainement voulu prendre pour lui-même. Qu'en penses-tu, Henry ? Que te fera ton oncle ? Tu dois savoir mieux que quiconque à quel point son tempérament est fougueux...";
			link.l1.go = "tibo_14";
		break;
		
		case "tibo_14":
			dialog.text = "Que des mensonges !";
			link.l1 = "Est-ce ? Mon cher Henry, tu peux demander à ton ami Martene. C'est lui qui m'a envoyé. Levasseur découvrira que tu caches la fille avant le coucher du soleil. Ne me demande pas comment Robert l'a su, écoute seulement mes paroles : il est terrifié à en perdre ses tripes et prêt à lever l'ancre et appareiller sur-le-champ. Il n'a même pas osé entrer en ville. C'est pourquoi il m'a demandé de te livrer ce message.";
			link.l1.go = "tibo_15";
		break;
		
		case "tibo_15":
			dialog.text = "";
			link.l1 = "Martene ne vous attendra pas plus de deux heures. Il tient à sa tête sur ses épaules. C'est uniquement par amitié qu'il reste encore sur le rivage de la Tortue et ne se cache pas quelque part avec les Hollandais. Cependant, ce pauvre Robert ne se doute même pas de qui est vraiment Molly Jones. Vous savez, vous deux m'étonnez vraiment avec votre ignorance incroyable de la mode et de l'apparence des femmes ! Vous ne pourriez même pas distinguer une noble de sa servante !";
			link.l1.go = "tibo_16";
		break;
		
		case "tibo_16":
			dialog.text = "Que veux-tu ?";
			link.l1 = "Enfin quelques paroles sages de la part du jeune freluquet ! Très bien, Thibaut : rends-toi là où tu la caches en ce moment, prends-la doucement par ses mains blanches comme le lys, et promène-toi rapidement avec elle jusqu'à la plage Fisheye où se trouve le Voltigeur de Martene. Dis-lui que tes plans ont changé...";
			link.l1.go = "tibo_17";
		break;
		
		case "tibo_17":
			dialog.text = "";
			link.l1 = "Martene doit tenir sa promesse envers moi, il ne devrait même pas essayer d'embarquer la fille sur son propre navire. Elle restera sur la plage et m'attendra. Dis à Robert que s'il ne remplit pas ses obligations, ou s'il emmène Catherine, ou si un cheveu tombe de sa jolie petite tête, je passerai le reste de ma vie à la retrouver. Et quand je la retrouverai, je la livrerai au Colonel Fox... vivante. Mais pour vous deux... je vous ramènerai en morceaux. Oui, d'ailleurs, cela te concerne aussi, Thibaut.";
			link.l1.go = "tibo_18";
		break;
		
		case "tibo_18":
			dialog.text = " ";
			link.l1 = "Qui je suis et quelles sont mes opportunités, vous pouvez demander à Robert. Il est bien au courant. Si vous faites tous les deux ce que j'ai dit, alors nous gagnons tous. Robert pourra continuer son commerce de pirate et vous conserverez tous vos privilèges et recevrez l'héritage de votre cher vieux oncle lorsqu'il rendra son dernier souffle. Quant à moi... Je ne serai pas non plus perdant. Tout est clair ?";
			link.l1.go = "tibo_19";
		break;
		
		case "tibo_19":
			PlaySound("Voice\English\sharlie\Henry Thibault-03.wav");
			dialog.text = "Je préférerais brûler dans le feu éternel de l'enfer que de faire vos volontés... "+GetFullName(pchar)+" ! Comment n'ai-je pas reconnu dès le début ? Assassin ! Tu ne comptes pas laisser Robert ou moi en vie ! Tes 'méthodes' sont bien connues ! Il n'est pas question que je te laisse Molly... ou Catherine d'ailleurs à une ordure comme toi ! Tu ne quitteras pas Tortuga vivant, salaud !";
			link.l1 = "...";
			link.l1.go = "tibo_20";
		break;
		
		case "tibo_20":
			dialog.text = "";
			link.l1 = "Arrête, lâche!";
			link.l1.go = "tibo_21"; // patch
		break;
		
		case "tibo_21":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload_window", "none", "", "", "Terrapin_LevasserRoomEnter", 5); // patch
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_window");
			LAi_RemoveLoginTime(npchar);
		break;
		
		case "tibo_22":
			pchar.quest.Terrapin_TiboCallOver.over = "yes"; //снять прерывание
			pchar.quest.Terrapin_tibo_call.over = "yes"; //снять прерывание
			PlaySound("Voice\English\sharlie\Henry Thibault-04.wav");
			dialog.text = "Eh bien, enfin ! Capitaine "+GetFullName(pchar)+", Je suis très heureux que vous soyez venu. Entrez, asseyez-vous. Quelque chose à boire ? J'ai une proposition d'affaires assez lucrative pour vous, mon ami...";
			link.l1 = "Eh bien, vous voilà dans une humeur des plus courtoises aujourd'hui, Monsieur Thibaut... Ne traînons pas. Allons droit au cœur du sujet.";
			link.l1.go = "tibo_23";
		break;
		
		case "tibo_23":
			dialog.text = "La proposition concerne mon ancien ami et compagnon que vous connaissez sous le nom de Robert Martene, ancien capitaine du galion 'Voltigeur'...";
			link.l1 = "Alors, toi et Robert n'êtes plus camarades? Un développement fascinant.";
			link.l1.go = "tibo_24";
		break;
		
		case "tibo_24":
			dialog.text = "Capitaine, je vous prie, écoutez mes raisons de solliciter votre aide et tout deviendra clair. Comme vous le savez, Martene s'est emparé d'un brick anglais et a capturé comme prisonnière une Anglaise, une certaine servante connue sous le nom de Molly Jones, toute la raison pour laquelle tout ce trouble a été déclenché.";
			link.l1 = "Bien sûr, je sais. Si je comprends bien, vous avez suivi mes recommandations et conduit la fille au navire de Martène ?";
			link.l1.go = "tibo_25";
		break;
		
		case "tibo_25":
			dialog.text = "Oui, je l'ai fait. Mais je le regrette chaque jour. Sachez que Molly est une fille très charmante et belle, je n'ai jamais rencontré quelqu'un comme elle auparavant. Je dois admettre que je suis tombé amoureux d'elle. Elle m'aimait aussi, elle l'a dit elle-même ! Je ne pouvais pas laisser mon oncle la prendre\nQuand je l'escortais vers le 'Voltigeur', j'espérais que mon oncle se calmerait dès qu'il découvrirait que personne ne lui cache de filles, le vieux lubrique. Ensuite, Robert la ramènerait à la Tortue, pour que je puisse la déplacer en toute sécurité chez moi. Quoi qu'il en soit, c'était l'accord que j'avais passé avec Martene. Mais cela s'est passé différemment\nQuand j'ai appris que mon oncle avait été tué, il n'y avait plus de raison de cacher Molly, alors j'ai attendu patiemment que le 'Voltigeur' arrive avec Molly à bord.";
			link.l1 = "Est-elle arrivée ?";
			link.l1.go = "tibo_26";
		break;
		
		case "tibo_26":
			dialog.text = "Oui. Malheureusement, Molly n'était pas sur le navire. Robert était ébranlé, comme s'il s'était heurté à Lucifer en personne. Lors de sa brève expédition, il a découvert un détail terrible : la fille, Molly, n'était pas du tout Molly Jones, mais Catherine Fox ! La fille du Colonel Fox lui-même, commandant des Renards de Mer, le régiment d'élite des marines anglais ! Tu sais ce que cela signifie !";
			link.l1 = "Sapristi, comment cela se fait-il! Robert a donc bien de quoi avoir peur. Mais comment cela a-t-il pu se passer ainsi?";
			link.l1.go = "tibo_27";
		break;
		
		case "tibo_27":
			dialog.text = "Quand Catherine a été capturée, elle a intentionnellement caché son identité en prétendant être Molly Jones, une servante qui est morte lors de l'abordage. Elle craignait que Martene découvre qui elle était vraiment. Et elle a réussi à le tromper. Mais lors du dernier voyage, Robert a découvert d'une manière ou d'une autre qui elle est vraiment. Il a dit qu'il avait trouvé certaines de ses lettres, ou des papiers...";
			link.l1 = "Et où est la fille maintenant si elle n'est pas montée à bord du 'Voltigeur' ?";
			link.l1.go = "tibo_28";
		break;
		
		case "tibo_28":
			dialog.text = "Elle est morte. Effrayé par le châtiment imminent de Fox pour avoir attaqué le brigantin anglais, Martene a décidé de cacher la seule preuve restante dans l'eau. Elle était le dernier témoin de son attaque sur l''Albatros'.";
			link.l1 = "Alors il aurait aussi bien pu tuer tous ses marins... Comme Fernand Luc. Sinon, un jour ils se saouleront et ouvriront un peu trop grand leur bouche à la taverne...";
			link.l1.go = "tibo_29";
		break;
		
		case "tibo_29":
			dialog.text = "Il a l'impression que tout son équipage lui est lié par le sang. Peut-être a-t-il partiellement raison. Mais je connais le colonel Fox ! Il continuera à creuser jusqu'à la fin de ses jours pour découvrir qui a enlevé sa fille !";
			link.l1 = "Je n'en doute pas. Surtout après qu'un pirate français ait tué sa femme. Maintenant sa fille aussi... Au fait, êtes-vous absolument sûr, monsieur, que Catherine est vraiment morte ? Peut-être que Robert l'a cachée quelque part de vous.";
			link.l1.go = "tibo_30";
		break;
		
		case "tibo_30":
			dialog.text = "Je suis sûr. J'ai parlé avec un marin du 'Voltigeur'. Je l'ai cru. Il a vu de ses propres yeux comment ils ont tranché la gorge de la fille, puis attaché un boulet de canon à ses pieds et l'ont jetée par-dessus bord.";
			link.l1 = "Dieu au ciel ! Cette pauvre femme... que veux-tu de moi, Henry ?";
			link.l1.go = "tibo_31";
		break;
		
		case "tibo_31":
			dialog.text = "Je ne peux plus dormir la nuit depuis ce jour-là. Je vois Molly tout le temps devant mes yeux... Catherine, plutôt. Je l'ai menée à sa mort, "+GetFullName(pchar)+"Je ne peux pas me le pardonner. En plus, je ne me fais aucune illusion sur Fox. Cet homme n'est pas complaisant et je ne pense même pas qu'il dorme. Tôt ou tard, il va suivre la piste de Martene, faire parler quelqu'un, et quand il découvrira qui a tué sa fille, tout l'enfer va se déchaîner. Ce sera dur pour quiconque était d'une manière ou d'une autre lié à toute l'histoire.";
			link.l1 = " Cela m'inclut.";
			link.l1.go = "tibo_32";
		break;
		
		case "tibo_32":
			dialog.text = "Oui, moi aussi. C'est pourquoi je veux que tu trouves Martene avant que Fox ne le fasse. Trouve ce salaud et tue-le. Et fais-le souffrir d'abord si tu peux. Pour la pauvre Catherine. Quand c'est fait, coupe cette grosse bague qu'il porte à la main avec le doigt dedans et apporte-la moi comme preuve. Je connais bien son doigt tordu et cette bague. Si tu fais cela, je te paierai un quart de million en argent.";
			link.l1 = "On dirait que tu as reçu un grand héritage de ton cher oncle reposant en paix, hein ? Dis-moi, Henry, pourquoi as-tu décidé de me demander de l'aide pour cette affaire ?";
			link.l1.go = "tibo_33";
		break;
		
		case "tibo_33":
			dialog.text = "Parce que j'ai appris quelques choses sur toi aussi, "+GetFullName(pchar)+". C'était facile, vous êtes un homme célèbre. On ne sait pas vraiment pour qui vous travaillez, que ce soit pour de Poincy, ou pour les Hollandais, ou pour les Anglais, ou pour le baron Jan Svenson... Mais une chose est claire : vous prenez des travaux délicats et discrets et vous les réalisez. Ensuite, vous êtes grassement payé pour cela. Et le meilleur de tout, vous n'êtes pas lié aux Espagnols\nAprès tout, vous avez également participé aux événements après lesquels j'ai hérité de la fortune de mon oncle. Ne le niez pas... Un quart de million, c'est une belle somme. Je vais vous dire où trouver Martene. Vous n'avez qu'à intercepter son navire et l'aborder.";
			link.l1 = "Encore cent mille et je m'occuperai de Martene pour toi.";
			link.l1.go = "tibo_34";
			link.l2 = "Hélas, Monsieur Thibaut, il vous faudra régler votre problème avec Martene et le Colonel Fox sans ma participation. De mon côté, je vous promets que je ne transmettrai aucune information au colonel concernant le sort de sa fille et ceux qui sont coupables de sa mort. Tous mes vœux, monsieur.";
			link.l2.go = "tibo_exit";
		break;
		
		case "tibo_exit":
			DialogExit();
			AddQuestRecord("Sharlie", "26");
			NextDiag.CurrentNode = "tibo_over";
		break;
		
		case "tibo_34":
			dialog.text = "Monsieur, craignez Dieu... Je n'ai pas des millions cachés dans des coffres au trésor, croyez-moi ! Je comprends que vos services coûtent cher, c'est pourquoi je vous ai offert deux cent cinquante mille d'emblée... Bien... D'accord, que diriez-vous si j'ajoute cinquante mille pièces d'or de plus. Je ne peux pas vous offrir davantage !";
			link.l1 = "D'accord. Vous avez un accord. Où avez-vous vu Martene pour la dernière fois ?";
			link.l1.go = "tibo_35";
		break;
		
		case "tibo_35":
			dialog.text = "Il a navigué vers le sud jusqu'à la Côte des Caraïbes à Caracas et a réussi à obtenir une audience avec Don Diego Francisco de Kerres, le gouverneur. Il semble qu'il l'ait soudoyé d'une manière ou d'une autre car Don Diego a accordé à Robert la protection de la couronne espagnole. Il a vendu le 'Voltigeur' et maintenant il est le capitaine du lourd galion 'Infanta'. Il devait avoir de très bonnes économies puisqu'il a pu se permettre de soudoyer le gouverneur et d'acheter et équiper un grand navire militaire comme celui-là\nAlors, ensuite il naviguera de Caracas à Saint-Domingue sur son nouveau navire en tant que partie d'une escadre espagnole. C'est tout ce que mon agent a pu découvrir. La seule opportunité de rattraper Martene est de rejoindre cette escadre espagnole\nS'ils atteignent Saint-Domingue, c'est fini. Aucune idée d'où Robert ira ensuite. Il se terrera comme un lapin dans un terrier et nous ne le trouverons jamais.";
			link.l1 = "Compris. Je vais les intercepter.";
			link.l1.go = "tibo_36";
		break;
		
		case "tibo_36":
			dialog.text = "Et n'oublie pas le doigt avec la bague ! C'est une condition obligatoire de notre accord ! Je veux être absolument sûr que Robert est mort !";
			link.l1 = "D'accord. Ne perdons pas de temps, je mettrai les voiles immédiatement !";
			link.l1.go = "tibo_37";
		break;
		
		case "tibo_37":
			DialogExit();
			AddQuestRecord("Sharlie", "27");
			Terrapin_CreateRoberConvoy();
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			NextDiag.CurrentNode = "tibo_time";
		break;
		
		case "tibo_time":
			dialog.text = "Martene empeste-t-il encore les Caraïbes de sa présence, capitaine ?";
			link.l1 = "Il n'en a plus pour longtemps !";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_time";
		break;
		
		case "tibo_38":
			dialog.text = "Est-ce que Martène empeste les Caraïbes de sa présence, capitaine ?";
			link.l1 = "Plus maintenant. Vous n'avez plus à craindre le Colonel Fox et votre Catherine est vengée. Voici votre preuve.";
			link.l1.go = "tibo_39";
		break;
		
		case "tibo_39":
			RemoveItems(pchar, "finger", 1);
			dialog.text = "Oui... C'est bien le doigt de Martene, sans aucun doute. Vous ne cessez de m'impressionner, Capitaine "+GetFullName(pchar)+" ! Vous méritez vraiment la réputation qu'on vous attribue.";
			link.l1 = "Passons au paiement, voulez-vous, Thibaut ?";
			link.l1.go = "tibo_40";
		break;
		
		case "tibo_40":
			AddMoneyToCharacter(pchar, 250000);
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You've received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Tout est prêt. Tiens, prends ta récompense.";
			link.l1 = "Ma gratitude. Je suis heureux que tu aies pu préparer cela à l'avance. Eh bien Henry, j'espère que tu ne tomberas pas dans d'autres pétrins comme celui-ci et que tu choisiras de meilleurs amis à l'avenir. Tout de bon !";
			link.l1.go = "tibo_41";
		break;
		
		case "tibo_41":
			dialog.text = "Merci pour votre aide, capitaine ! Je vous recommanderai à tous mes amis. Bonne chance !";
			link.l1 = "...";
			link.l1.go = "tibo_42";
		break;
		
		case "tibo_42":
			DialogExit();
			AddQuestRecord("Sharlie", "31");
			NextDiag.CurrentNode = "tibo_stop";
		break;
		
		case "tibo_stop":
			dialog.text = "Oui, monsieur "+GetFullName(pchar)+"Avez-vous affaire avec moi ?";
			link.l1 = "Non, monsieur Thibaut. Je me suis juste décidé à passer un moment. Au revoir !";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_stop";
		break;
		
		case "tibo_late":
			dialog.text = "Ah, "+GetFullName(pchar)+"...Allez, qu'est-ce qui te prend autant de temps ! Alors, qui diable sait où est Robert Martene ?! Si le colonel Fox parvient à tout découvrir, je pense que je vais être dans de beaux draps...";
			link.l1 = "Je vois. J'étais trop tard. Mes excuses, Monsieur Thibaut, mais j'ai été retardé par des affaires très urgentes. Je ne vais pas vous faire perdre votre temps. Adieu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		case "tibo_over":
			dialog.text = "Que veux-tu, "+GetFullName(pchar)+" ? Je n'ai pas le temps de bavarder. J'ai d'autres chats à fouetter. Je dois trouver Martene avant que Fox ne le fasse...";
			link.l1 = "Oui, oui. Je suis en route.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		// посланник от Мартэна
		case "envoy":
			dialog.text = "Êtes-vous Capitaine "+GetFullName(pchar)+"?";
			link.l1 = "Tu es tombé sur le bon homme, l'ami. Je suis tout ouïe.";
			link.l1.go = "envoy_1";
		break;
		
		case "envoy_1":
			dialog.text = "Votre créancier m'a demandé de vous dire que l'affaire est faite et que le poisson nagera dans le filet dans moins d'une heure. Alors faites vite.";
			link.l1 = "Je comprends. Merci !";
			link.l1.go = "envoy_2";
		break;
		
		case "envoy_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Terrapin", "9");
			pchar.quest.Terrapin_cave.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_cave.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.Terrapin_cave.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l2 = "location";
			pchar.quest.Terrapin_cave.win_condition.l2.location = "Tortuga_cave";
			pchar.quest.Terrapin_cave.function = "Terrapin_LevasserInCave";
		break;
		
		// Левассер в пещере
		case "levasser_cave":
			pchar.quest.Terrapin_LateDungeon.over = "yes"; //снять таймер
			dialog.text = "Pourquoi diable errez-vous par ici ? Qui êtes-vous ? Répondez-moi maintenant !";
			link.l1 = "Qui diable es-tu et pourquoi me poses-tu des questions aussi stupides ?";
			link.l1.go = "levasser_cave_1";
		break;
		
		case "levasser_cave_1":
			dialog.text = "Quoi?! Espèce de morveux ! Qui suis-je ? Je suis le gouverneur de cette île, Francois Levasseur, Seigneur de Renet de Boidouflet de Lettre ! Et tout sur cette île est sous ma juridiction ! Cela vous inclut pendant que vous êtes sur mon territoire, chiot !";
			link.l1 = "Eh bien, eh bien... Le grand méchant loup en personne, hein ? Vous êtes un peu perdu, Levasseur, Senior de Renet de peu importe ce que c'était. Votre temps est écoulé. Par ordre du gouverneur général François Longvillier de Poincy, vous avez été démis de vos fonctions et condamné à une mort immédiate ! Je suis votre juge et votre bourreau en une seule personne ! Des dernières paroles ?";
			link.l1.go = "levasser_cave_2";
		break;
		
		case "levasser_cave_2":
			dialog.text = " ";
			link.l1 = "Je suppose que tu ne vas pas abandonner et me demander grâce ne te servira à rien, alors tire ton épée !";
			link.l1.go = "levasser_cave_3";
		break;
		
		case "levasser_cave_3":
			dialog.text = "Merde ! C'est un agent de de Poincy ! Dégainons nos épées ! Tuez-le !";
			link.l1 = "Dansons.";
			link.l1.go = "levasser_cave_4";
		break;
		
		case "levasser_cave_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_cave")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=2; i<=4; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+7;
			int iScl = 30 + 2*sti(pchar.rank);
			for (i=5; i<=9; i++)
			{		
				sld = GetCharacter(NPC_GenerateCharacter("TerrapinGuard"+i, "citiz_5"+i, "man", "man", iRank, PIRATE, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2+50);
				ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserCaveDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Левассер в комнате таверны
		case "levasser_room":
			dialog.text = "Que diable fais-tu ici ? Qui es-tu ? Réponds-moi, maintenant !";
			link.l1 = "Ça alors ! Je ne m'y attendais pas... Monsieur Levasseur en personne, je présume ?";
			link.l1.go = "levasser_room_1";
		break;
		
		case "levasser_room_1":
			dialog.text = "Oui, je suis le gouverneur de cette île, Francois Levasseur, Senior de Renet de Boidouflet de Lettre ! Et tout sur cette île est sous ma juridiction ! Y compris toi tant que tu marches sur mon territoire, vaurien ! Réponds aux questions ! Sergent, verrouillez cette porte. Cet homme ne prépare rien de bon !";
			link.l1 = "Vous êtes incroyablement perspicace, monsieur Levasseur, Senior de Renet de peu importe. Ma présence ici ne vous apportera guère de plaisir. Sur ordre du gouverneur-général François Longvillier de Poincy, vous avez été démis de vos fonctions et condamné à mort immédiate ! Je suis à la fois votre juge et votre bourreau !";
			link.l1.go = "levasser_room_2";
		break;
		
		case "levasser_room_2":
			dialog.text = "";
			link.l1 = "Je suppose que tu ne vas pas abandonner et me demander pitié ne te servira à rien, alors vas-y, tire l'acier ! Tu es mon travail, rien de personnel. Juste au service de la Couronne, ha ! Sergent, je ne te conseille pas d'intervenir pendant que j'exécute les ordres du gouverneur général !";
			link.l1.go = "levasser_room_3";
		break;
		
		case "levasser_room_3":
			dialog.text = "N'écoute pas lui, sergent ! C'est un agent espagnol ! Tuez-le ! Gardes, à l'aide ! Il y a des Espagnols ici !";
			link.l1 = "Jamais été en Espagne, en fait, juste à Narbonne.";
			link.l1.go = "levasser_room_4";
		break;
		
		case "levasser_room_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserRoomDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// девушка на балконе
		case "roof_girl":
			dialog.text = "Aïe! Aidez-moi! Soldats!";
			link.l1 = "Calme-toi, imbécile ! Si tu ne cries pas, je ne te ferai rien !";
			link.l1.go = "roof_girl_1";
		break;
		
		case "roof_girl_1":
			dialog.text = "Ne me tue pas !";
			link.l1 = "Ne fais pas l'idiot ! Un homme vient de passer par ici il y a dix minutes. Un noble bien habillé. Où se cache-t-il ? Et n'essaie même pas de me dire que tu ne l'as pas vu !";
			link.l1.go = "roof_girl_2";
		break;
		
		case "roof_girl_2":
			dialog.text = "Monsieur Thibaut ?";
			link.l1 = "Eh bien, alors tu le connais ! Où a-t-il filé ? Vas-tu répondre ou devrais-je te secouer la tête pour la faire fonctionner ?";
			link.l1.go = "roof_girl_3";
		break;
		
		case "roof_girl_3":
			dialog.text = " Oh non, je vous en prie, ne me faites pas de mal ! Monsieur Thibaut s'est enfui par là, vers la mer. Et il a sauté de la grue directement dans l'eau. Il est probablement mort, c'est tellement haut... ";
			link.l1 = "Je ne pense pas. Ce n'est pas le genre à se suicider. Tu devrais rentrer. C'est dangereux d'être ici ce soir..";
			link.l1.go = "roof_girl_4";
		break;
		
		case "roof_girl_4":
			dialog.text = "Aïe! A-aïe! Ne tirez pas!";
			link.l1 = "Quoi?!";
			link.l1.go = "roof_girl_5";
		break;
		
		case "roof_girl_5":
			DialogExit();
			LAi_SetActorType(pchar);
			PlaySound("People Fight\MushketShot.wav");
			DoQuestCheckDelay("Terrapin_GirlShot", 1.0);
		break;
		
		// Кати
		case "kathy":
			PlaySound("Voice\English\Armo02.wav");
			dialog.text = "Qui êtes-vous ? Êtes-vous venu pour me tuer ou... pire ?";
			link.l1 = "Rien de tel, madame. Je vais vous ramener, Catherine Fox, à votre père à St. John's. S'il vous donne une correction après cela pour avoir désobéi à ses ordres, alors ma culpabilité sera répétée. Cependant, j'espère que le colonel sera heureux de voir sa fille en vie malgré toutes les inquiétudes qu'elle lui a causées.";
			link.l1.go = "kathy_1";
		break;
		
		case "kathy_1":
			dialog.text = "Dieu merci ! Je dois rêver ! Ne savez-vous pas qui je suis ? Vous êtes un Français et un Catholique et pourtant vous avez décidé de venir ici pour me sauver des mains de mes propres compatriotes ? Vous avez risqué votre vie juste pour la fille du Colonel Fox ?";
			link.l1 = "Ma raison originale d'être ici à Tortuga était tout autre. Mais je ne pouvais pas non plus laisser une belle dame aux mains d'une bande de voleurs et de brigands.";
			link.l1.go = "kathy_2";
		break;
		
		case "kathy_2":
			dialog.text = "Vous êtes un gentilhomme noble ! Quel est votre nom, monsieur ?";
			link.l1 = "Bonjour, ami."+GetFullName(pchar)+". Capitaine "+GetFullName(pchar)+".";
			link.l1.go = "kathy_3";
		break;
		
		case "kathy_3":
			dialog.text = "Dis-moi capitaine, vas-tu vraiment m'emmener chez mon père à Saint-Jean ?";
			link.l1 = "Oui, bien qu'il n'ait guère de sympathie pour les Français. Eh bien, je lui rappellerai qu'il y a aussi des Anglais qui sont des vauriens, y compris des officiers anglais ! J'ai été témoin d'au moins l'un d'eux... Richard Fleetwood était son nom.";
			link.l1.go = "kathy_4";
		break;
		
		case "kathy_4":
			dialog.text = "Si nous atteignons Antigua, je ferai tout mon possible pour convaincre mon père qu'il y a de vrais chevaliers parmi les Français.";
			link.l1 = "Je l'apprécierais beaucoup... Très bien, j'espère que mes anges gardiens ont suivi ma trace le long des toits de la ville et qu'ils cherchent déjà notre retour.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_OwrInGrot");
		break;
		
		case "kathy_5":
			PlaySound("Voice\English\Armo01.wav");
			dialog.text = "Je ne pouvais pas croire que vous alliez tenir votre promesse jusqu'à maintenant ! Tant de choses horribles et dégoûtantes me sont arrivées dernièrement... Je vous remercie, capitaine, de m'avoir redonné foi en l'humanité et en la chevalerie. Vous devriez rendre visite à mon père quand vous le pourrez !\nIl respecte les hommes comme vous. Et peu importe que vous soyez Français. Je ferai tout pour convaincre mon père de reconsidérer son attitude envers votre nation.";
			link.l1 = "Merci, Catherine. Peut-être profiterai-je de votre offre courtoise.";
			link.l1.go = "kathy_6";
		break;
		
		case "kathy_6":
			dialog.text = "J'espère bien que vous le ferez, capitaine. Un grand merci encore pour ce que vous avez fait pour moi. Je ne l'oublierai jamais.";
			link.l1 = "Allez, dépêche-toi de rejoindre ton père. Il sera ravi de te voir. Peut-être est-il déjà revenu des champs. Bon, de toute façon il est temps pour moi de partir. Adieu !";
			link.l1.go = "kathy_7";
		break;
		
		case "kathy_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.lifeday = 0;
			SetFunctionTimerCondition("Terrapin_ReturnFox", 0, 0, 3, false); // Фокса на место
			pchar.questTemp.Terrapin_KathyReward = "true"; // награда за спасение Кати 160912
		break;
		
		// наш матрос
		case "terrapin_grot":
			dialog.text = "Ah, te voilà, cap'taine ! Tu nous as fait une de ces frayeurs ! Une course comme ça sur les toits carrelés et un saut d'une hauteur à donner le vertige, c'était à couper le souffle ! Dieu nous est témoin, on craignait que tu n'y parviennes pas... Bienvenue à bord, cap'taine, la chaloupe est prête !";
			link.l1 = "Génial. Catherine, suis-moi !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_GotoShip");
		break;
		
		case "tibo_sailor":
			dialog.text = "Bonjour, monsieur. Êtes-vous capitaine "+GetFullName(pchar)+"?";
			link.l1 = "Oui, c'est moi. Que se passe-t-il ?";
			link.l1.go = "tibo_sailor_1";
		break;
		
		case "tibo_sailor_1":
			dialog.text = "Ouf, je t'ai à peine rattrapé... Je viens à toi de la part d'un gentilhomme que tu connais sous le nom de Henry Thibaut.";
			link.l1 = "Henry ? Et que veut-il ? Partager sa joie suite à l'héritage qui lui est tombé dessus à l'improviste après le décès de son cher oncle ?";
			link.l1.go = "tibo_sailor_2";
		break;
		
		case "tibo_sailor_2":
			dialog.text = "Monsieur Thibaut a demandé d'urgence que vous veniez le voir à son manoir sur Tortuga dès que possible. Il a du travail bien payé pour vous. Il m'a également dit de vous mentionner un nom : Robert Martene. Cela devrait éveiller votre intérêt.";
			link.l1 = "Vraiment ? Et qu'est-ce qui a donné cette idée à Henry ?";
			link.l1.go = "tibo_sailor_3";
		break;
		
		case "tibo_sailor_3":
			dialog.text = "Et si cela ne vous a pas déjà convaincu de venir lui rendre visite, il a également demandé que j'ajoute ceci : 'Robert Martene doit mourir'.";
			link.l1 = "D'accord, d'accord... Maintenant, cela devient intéressant. Deux amis jurés viennent de se disputer... Comme tu dis, j'essaierai de rendre visite à Henry quand j'en aurai l'occasion.";
			link.l1.go = "tibo_sailor_4";
		break;
		
		case "tibo_sailor_4":
			dialog.text = "Monsieur Thibaut vous a demandé de ne pas tarder avec votre visite. 'Les poissons s'échapperont du filet dans dix jours' étaient ses mots exacts...";
			link.l1 = "Il parle de la même manière que Robert. Très bien, je rendrai visite à Henry.";
			link.l1.go = "tibo_sailor_5";
		break;
		
		case "tibo_sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Terrapin_TiboCallOver", 0, 0, 10, false);
			AddQuestRecord("Sharlie", "25");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
