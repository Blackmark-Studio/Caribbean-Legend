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
			dialog.text = "De quoi avez-vous besoin ?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "AlonsoNaPalube":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube"))
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube2 = true;
				dialog.text = "Votre décision, capitaine ? Peut-être que ce n'est pas la peine ?";
				link.l1 = "Tu as réussi à rassembler plus de volontaires pour l'affaire ?";
				link.l1.go = "AlonsoNaPalube_StrongGroup";
			}
			else
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube = true;
				dialog.text = "Capitaine, un mot si vous permettez.";
				link.l1 = "Je vous écoute, Alonso.";
				link.l1.go = "AlonsoNaPalube_2";
			}
			locCameraFromToPos(-10.33, 9.69, -22.16, true, -5.22, 7.19, -21.06);
		break;
		
		case "AlonsoNaPalube_2":
			dialog.text = "L'équipage se demande quels sont vos plans pour les Caïmans. Les hommes s'inquiètent.";
			link.l1 = "Je n'ai pas encore décidé. Et pourquoi les hommes sont-ils inquiets, Alonso ?";
			link.l1.go = "AlonsoNaPalube_3";
		break;

		case "AlonsoNaPalube_3":
			dialog.text = "Cette île est le domaine du capitaine Blackwood. Les marins disent qu'il la fouille de fond en comble comme un possédé. Qu'il a causé la mort de dizaines d'hommes dans ses fouilles... Et ceux qui le quittent racontent des choses étranges.";
			link.l1 = "Quelles choses ?";
			link.l1.go = "AlonsoNaPalube_4";
		break;

		case "AlonsoNaPalube_4":
			dialog.text = "Que Blackwood n'est plus l'homme qu'il était. Qu'il est obsédé par la recherche d'un trésor de conquistadors. Qu'il est prêt à tout sacrifier pour cela. Nous savons à quel point vous aimez vous mêler à de belles histoires, débarquer seul et tomber dans des pièges... Eh bien : de celle-ci, vous ne sortirez pas.";
			link.l1 = "Merci pour votre rapport et votre avertissement. Si je décide tout de même de débarquer, j'emmènerai avec moi l'avant-garde et un détachement de nos meilleurs hommes.";
			link.l1.go = "AlonsoNaPalube_5";
		break;

		case "AlonsoNaPalube_5":
			dialog.text = "Cela risque d'être compliqué, capitaine. L'abordage, c'est une chose, mais se jeter sous les balles des marines et les sabres de toute la racaille que Blackwood aurait recrutée dans chaque recoin des Petites Antilles, c'en est une autre. Et puis, les rumeurs sur les Caïmans ne sont pas rassurantes... Non, vous ne trouverez pas beaucoup de volontaires pour une telle tâche.";
			link.l1 = "Il faudra donc faire avec ceux que nous avons. Ta présence est indispensable, Alonso.";
			link.l1.go = "AlonsoNaPalube_LiteGroup";
			link.l2 = "À mon avis, j’ai déjà prouvé tout ce qu’il y avait à prouver. Tous les bons combattants et tireurs viennent avec moi. C’est un ordre.";
			link.l2.go = "AlonsoNaPalube_StrongGroup";
			link.l3 = "Hmm... Je dois y réfléchir. Il est possible que nous revenions sur cette question plus tard.";
			link.l3.go = "AlonsoNaPalube_Exit";
		break;
		
		case "AlonsoNaPalube_Exit":
			SetFunctionLocationCondition("LadyBeth_CaimanSea", "Caiman", false);
			EndQuestMovie();
			bQuestDisableMapEnter = false;
			chrDisableReloadToLocation = false;
			if(UnloadLocation(loadedLocation) == true)
			{
				pchar.Ship.Pos.x = 0;
				pchar.Ship.Pos.z = 0;
				pchar.Ship.Ang.y = 0;
				Land_MapLoad();
				pchar.location = "";
			}
		break;
		
		case "AlonsoNaPalube_LiteGroup":
			dialog.text = "Ce sera fait, cap.";
			link.l1 = "Et qu'en est-il du navire de Blackwood ? Ne risque-t-il pas de poser problème ?";
			link.l1.go = "AlonsoNaPalube_Vpered";
			pchar.questTemp.LadyBeth_LiteGroup = true;
		break;
		
		case "AlonsoNaPalube_StrongGroup":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50 || sti(pchar.rank) >= 17)
			{
				dialog.text = "Ce sera fait, cap.";
				link.l1 = "Et qu'en est-il du navire de Blackwood ? Ne risque-t-il pas de poser problème ?";
				link.l1.go = "AlonsoNaPalube_Vpered";
				pchar.questTemp.LadyBeth_StrongGroup = true;
				if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50) notification("Contrôle réussi", SKILL_Leadership);
				if (sti(pchar.rank) >= 17) notification("Vérification de niveau réussie", "None");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube2"))
				{
					dialog.text = "J'ai peur que non, capitaine.";
				}
				else
				{
					dialog.text = "Vous n'avez rien à prouver ni à moi ni à vos officiers, et nous suivrons l'ordre là où vous le direz, mais un marin ordinaire pense autrement. J'ai peur qu'il y ait des problèmes, capitaine.";
				}
				link.l1 = "Il faudra donc faire avec ceux que nous avons. Ta présence est indispensable, Alonso.";
				link.l1.go = "AlonsoNaPalube_LiteGroup";
				link.l2 = "Hmm... Je dois y réfléchir. Il est possible que nous revenions sur cette question plus tard.";
				link.l2.go = "AlonsoNaPalube_Exit";
				if (GetSummonSkillFromName(pchar, SKILL_Leadership) < 50) notification("Compétence insuffisamment développée (50)", SKILL_Leadership);
				if (sti(pchar.rank) < 17) notification("Niveau 17 requis", "None");
			}
		break;
		
		case "AlonsoNaPalube_Vpered":
			dialog.text = "Une Senau. On dit que c'est une vraie beauté au caractère redoutable. Je ne m'inquiéterais pas pour elle. Toute l'équipe doit probablement trimer comme des damnés à terre, tandis que le navire est bien caché dans les replis du littoral. Quand, et si nous gagnons, nous pourrons la prendre comme prix.";
			link.l1 = "Rassemble les hommes. Aujourd'hui est un bon jour - la fortune sera de notre côté.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_AlonsoNaPalube_Vpered");
		break;
		
		// Диалог в таверне с Блеквудом
		case "LadyBeth_DialogInCity": // главное меню
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Fourth"))
			{
				dialog.text = "Heureux de vous voir, capitaine. Il me semble que nous avons déjà tout discuté.";
				link.l1 = "En effet. Adieu.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LadyBeth_DialogInCity_again";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Third"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", Albert.";
				link.l1.go = "LadyBeth_DialogInCity_Third_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", capitaine Blackwood.";
				link.l1.go = "LadyBeth_DialogInCity_Second_1";
				break;
			}
			if (startHeroType == 4)
			{
				dialog.text = "...";
				link.l1 = "Bonjour. Êtes-vous le capitaine Blackwood ?";
				link.l1.go = "LadyBeth_DialogInCity_First_Helena_1";
			}
			else
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+". Vous êtes le capitaine Albert Blackwood, n'est-ce pas ?";
				link.l1.go = "LadyBeth_DialogInCity_First_1";
			}
		break;
		
		case "LadyBeth_DialogInCity_again": // повтор
			dialog.text = "Heureux de vous voir, capitaine. Il me semble que nous avons déjà tout discuté.";
			link.l1 = "En effet. Adieu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "LadyBeth_DialogInCity_again";
		break;
		
		case "LadyBeth_DialogInCity_First_1": // первый диалог
			dialog.text = "Oui, c'est bien moi. Et vous ?";
			link.l1 = "Capitaine "+GetFullName(pchar)+". Je commande le navire '" + PChar.Ship.Name + "'.";
			link.l1.go = "LadyBeth_DialogInCity_First_2";
		break;
		
		case "LadyBeth_DialogInCity_First_2":
			dialog.text = "Capitaine... Êtes-vous déjà allé aux Caïmans ?";
			link.l1 = "Je n'ai fait que passer.";
			link.l1.go = "LadyBeth_DialogInCity_First_3";
		break;
		
		case "LadyBeth_DialogInCity_First_3":
			dialog.text = "Avez-vous entendu parler de trésors là-bas ?";
			link.l1 = "Non, rien de concret.";
			link.l1.go = "LadyBeth_DialogInCity_First_4";
		break;
		
		case "LadyBeth_DialogInCity_First_4":
			dialog.text = "Traces espagnoles ? Vieilles armes ? Pièces des temps des conquistadors ?";
			link.l1 = "Je n'ai rien trouvé de tout cela.";
			link.l1.go = "LadyBeth_DialogInCity_First_5";
		break;
		
		case "LadyBeth_DialogInCity_First_5":
			dialog.text = "Légendes locales ? Histoires sur Cortés ? Quelque chose sur des sépultures ?";
			link.l1 = "Désolé, capitaine, mais je ne dispose pas de telles informations. Et tout cela commence à ressembler à un interrogatoire.";
			link.l1.go = "LadyBeth_DialogInCity_First_6";
		break;
		
		case "LadyBeth_DialogInCity_First_6":
			dialog.text = "Je vous prie de m'excuser... Mauvaise habitude d'un ancien officier. C'est juste que... c'est extrêmement important pour moi.";
			link.l1 = "Pourquoi vous intéressez-vous autant aux Caïmans ?";
			link.l1.go = "LadyBeth_DialogInCity_First_7";
		break;
		
		case "LadyBeth_DialogInCity_First_7":
			dialog.text = "Peu importe. Encore une fois, je vous prie de m'excuser.";
			link.l1 = "Je comprends. Bonne chance dans vos recherches.";
			link.l1.go = "LadyBeth_DialogInCity_First_8";
		break;
		
		case "LadyBeth_DialogInCity_First_8":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Bonne nuit";
			else sStr = "Une bonne journée à vous";
			dialog.text = "Passez me voir si quelque chose d'intéressant se présente. Ce serait un plaisir de parler avec un autre capitaine... une personne qui comprend la mer. Bonne journée à vous. " + sStr + ".";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_First_9";
		break;
		
		case "LadyBeth_DialogInCity_First_9":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_1": // первый диалог с Элен
			dialog.text = "En personne. Et vous... Capitaine Helen MacArthur ? La protégée de Jan Swenson, n'est-ce pas ? J'ai entendu parler de vous.";
			link.l1 = "Vous êtes bien informé, capitaine Blackwood. Mais je ne suis pas surprise qu'un officier anglais sache qui je suis.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_2":
			dialog.text = "Ancien officier. Et tous les habits rouges connaissent vos... privilèges uniques accordés par la Couronne. Comme on dit, l'argent n'a pas d'odeur. Et l'histoire de votre père, Sean MacArthur, vous emmenant en mer depuis l'enfance et faisant de vous un capitaine, est devenue une sorte de légende dans la flotte.";
			link.l1 = "Et qu'éprouvez-vous en rencontrant cette légende ?";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_3";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_3":
			dialog.text = "Personnellement, je suis impressionné. Bien que cela irrite fortement, je l'avoue, bon nombre de mes anciens collègues. Mais pour devenir capitaine, il faut plus que de nobles origines ou une patente royale, n'est-ce pas ?";
			link.l1 = "Exactement. Il faut des connaissances, de l'expérience et une volonté constante de prouver ses compétences. Surtout dans mon cas.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_4";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_4":
			dialog.text = "Exactement ! En mer, comme dans la vie, ce ne sont pas les titres qui comptent, mais les résultats. Ravi de faire votre connaissance, capitaine MacArthur. J'espère que nous nous reverrons. Peut-être passerez-vous pour un verre de vin à mon retour d'expédition ?";
			link.l1 = "Peut-être. Bonne chance dans vos recherches, capitaine.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_5_harizma";
			link.l2 = "Cela ne m'intéresse pas. Mais bonne chance dans vos recherches, capitaine.";
			link.l2.go = "LadyBeth_DialogInCity_First_Helena_5_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_harizma":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_oruzhie":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_1": // второй диалог
			dialog.text = "Ah, capitaine "+pchar.lastname+" ! Ravi de vous voir. Vous vous asseyez ?";
			link.l1 = "Avec plaisir.";
			link.l1.go = "LadyBeth_DialogInCity_Second_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_2":
			dialog.text = "Capitaine... dites-moi, que signifient pour vous les vrais trésors ?";
			link.l1 = "Le vrai trésor, c'est l'amour. La bonne personne est à proximité. Il n'y a rien de pire que d'être seul.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love";
			link.l2 = "L'argent, bien sûr. Qu'est-ce qui pourrait être un trésor sinon ?";
			link.l2.go = "LadyBeth_DialogInCity_Second_3_sokrovisha";
			link.l3 = "Un équipement précieux et unique. Une bonne épée ou un pistolet valent plus que de l'or.";
			link.l3.go = "LadyBeth_DialogInCity_Second_3_oruzhie";
			link.l4 = "Le savoir. Le trésor le plus précieux, c'est ce qu'on a dans la tête.";
			link.l4.go = "LadyBeth_DialogInCity_Second_3_znania";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love":
			if (startHeroType == 4)
			{
				dialog.text = "L'amour ? Hm... Je ne m'attendais pas à une telle réponse de la fille d’un pirate. J'étais... j'étais fiancé à Elizabeth. La fille d’un planteur de la Barbade. Mais son père... il pensait que je n'avais pas assez d'argent. Que pouvais-je offrir à sa fille, à part mon amour ? Vous avez eu de la chance, capitaine MacArthur. Vous aviez un père qui estimait vos compétences plus que votre dot.";
				link.l1 = "Peut-être que ce n'est pas une question de chance, mais que le véritable amour ne se mesure pas en or. Mon père le comprenait. Et votre fiancée ? Partage-t-elle l'avis de son père ?";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_1";
			}
			else
			{
				dialog.text = "L'amour ? Oui... Peut-être avez-vous raison. J'étais... j'étais fiancé. À la Barbade. Nous nous aimions, mais... son père me considérait comme un mauvais parti. Ha ! Pas assez riche. C'est pourquoi je suis ici - je cherche des trésors pour leur prouver à tous. Peut-être en vain ?";
				link.l1 = "Peut-être que vous devriez simplement lui parler ? Au diable ce planteur.";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_2";
			}
			AddComplexLandExpToScill(100, 100, 0);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_2":
			dialog.text = "Parler... Oui, peut-être. Mais que lui dirais-je ? 'Désolé, je n'ai pas pu t'offrir une vie digne ?' Non. Je dois revenir en vainqueur. Ou ne pas revenir du tout.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_1":
			dialog.text = "Elizabeth ? Non... elle m'aime. Mais je... je ne pouvais pas lui faire vivre la pauvreté. Elle mérite mieux. Et je dois prouver que je suis digne d'elle.";
			link.l1 = "Parfois, la fierté fait plus obstacle au bonheur que la pauvreté, capitaine.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_2":
			dialog.text = "Je ne peux pas revenir les mains vides. Je ne peux tout simplement pas. Excusez-moi, j'ai beaucoup de travail. Ce fut un plaisir de discuter avec vous, capitaine MacArthur.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha":
			dialog.text = "Quelle réponse banale. Mais difficile à contester. C'est vrai, quand on a grandi dans les taudis de Bristol, quand on devait se battre pour des restes... on commence à comprendre la vraie valeur de l'argent. Ce n'est pas un luxe. C'est la liberté. La possibilité de ne pas retourner dans cette crasse d'où l'on s'est extrait avec tant de peine.";
			link.l1 = "Je suis d'accord. L'argent résout la plupart des problèmes. Et s'il ne les résout pas, c'est qu'il n'y en a pas assez.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_sokrovisha_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha_2":
			dialog.text = "Exactement ! Vous comprenez. L'argent ne rend pas heureux, mais son absence rend certainement malheureux. Je le sais bien...";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie":
			dialog.text = "Intéressant. Pratique. J'ai une arquebuse... authentique, datant des temps des conquistadors. Un cadeau d’un prêtre. Parfois, je me dis qu'elle vaut plus que tout l'or que j'ai trouvé. Mais... cela ne résoudra pas mes problèmes.";
			link.l1 = "Une bonne arme peut résoudre bien des problèmes. Et elle ne vous trahira jamais.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie_2":
			dialog.text = "C'est pas faux. Mais certaines batailles ne peuvent être gagnées par la force des armes.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_znania":
			dialog.text = "Le savoir... Oui, je comprends. J'ai étudié tout ce que je pouvais sur les conquistadors, sur les trésors. J'ai rédigé un véritable règlement de recherche. J'ai conçu un système d'exercices réguliers et de récompenses matérielles pour la compagnie de tir du navireTout capitaine serait ravi d'avoir mon règlement. Mais tout ce savoir... il est inutile s'il ne mène pas à un résultat. À un vrai résultat.";
			link.l1 = "Mais c'est justement le savoir qui permet d'atteindre un résultat. Sans lui, toute recherche n'est qu'une errance dans l'obscurité.";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "LadyBeth_DialogInCity_Second_4":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Eh bien, il se fait tard, et j'ai beaucoup de travail";
			else sStr = "Eh bien, j'ai beaucoup de travail";
			dialog.text = "" + sStr + ". Merci pour cette conversation, capitaine. C'était vraiment intéressant.";
			link.l1 = "Merci à vous aussi. "+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_5":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Third = true;
		break;
		
		case "LadyBeth_DialogInCity_Third_2": // третий диалог
			dialog.text = "Ah, "+pchar.name+" ! Ravi de vous voir. J'ai d'excellentes nouvelles - j'ai enfin trouvé la solution à mes problèmes. Bientôt une expédition, et cette fois je reviendrai avec un vrai trésor ! Un conseil d'ami - tenez-vous à l'écart de Cayman. C'est mon territoire maintenant.";
			link.l1 = "Cayman ne vous appartient pas, Albert. Vous n'avez aucun droit de la Couronne dessus. C'est de la piraterie.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma";
			link.l2 = "Vous me menacez, Blackwood ?";
			link.l2.go = "LadyBeth_DialogInCity_Third_3_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma":
			dialog.text = "Des droits de la Couronne ? Vous auriez dû vivre dans les taudis de Bristol, "+pchar.name+", alors vous comprendriez ce que valent ces papiers. Quand on a faim, la loi ne veut rien dire. Mais... vous avez raison. Formellement, je n'ai aucun droit sur l'île\nMais j'y ai trouvé ce que je cherchais depuis des années. Et je ne laisserai personne me l'enlever.";
			link.l1 = "J'espère que vous comprenez que vous empruntez une voie dangereuse.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma_2":
			dialog.text = "J'ai toujours su que ma route ne serait pas facile. Adieu, "+pchar.name+". Peut-être que nous nous reverrons.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie":
			dialog.text = "Suis-je menaçant ? Non, voyons. Juste un conseil amical d’un capitaine à un autre. Cayman est dangereux... surtout pour ceux qui se mêlent de mes affaires.";
			link.l1 = "Je me souviendrai de votre 'conseil'. Bonne chance à Cayman.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie_2":
			dialog.text = "J'ai toujours su que ma route ne serait pas facile. Adieu, "+pchar.name+". Peut-être que nous nous reverrons.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_4":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Fourth = true;
		break;
		
		// Ловушка, абордаж в каюте
		case "LadyBeth_abordage":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Vous ?!! Vous croyez que je vais me rendre ? Vous croyez que je retournerai à la misère ? Je préfère mourir plutôt que de crever de faim à nouveau dans les taudis ! Pas de pitié, pas de récompense, pas de victoire ! Il y a un baril de poudre sous la couchette... Nous coulerons tous ensemble !";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
			else
			{
				dialog.text = "Qui êtes-vous pour m'attaquer ?! Vous croyez que je vais me rendre ? Non ! Je préfère mourir plutôt que de crever de faim à nouveau dans les taudis ! Pas de pitié, pas de récompense, pas de victoire ! Il y a un baril de poudre sous la couchette... Nous coulerons tous ensemble !";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
		break;
		
		// Блеквуд разговаривает с ГГ перед битвой на Каймане
		case "LadyBeth_BlackWood_Boss":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Capitaine ! Je vous avais pourtant prévenu. Maintenant vous allez payer pour votre curiosité.";
			}
			else
			{
				dialog.text = "Qui êtes-vous et comment osez-vous envahir mon territoire ? Cette île est à moi !";
			}
			link.l1 = "Nous verrons, Blackwood. Aujourd'hui, il y aura un possédé de moins dans ce monde.";
			link.l1.go = "LadyBeth_BlackWood_Boss_oruzhie_1";
			link.l2 = "Résolvons cela pacifiquement, Blackwood. Je peux partir.";
			link.l2.go = "LadyBeth_BlackWood_Boss_torgovlya_1";
			link.l3 = "Blackwood, vous êtes un homme raisonnable ! Vous êtes un officier ! Le drapeau royal flotte sur votre camp, bon sang ! Ne pouvons-nous vraiment pas trouver un accord ?";
			link.l3.go = "LadyBeth_BlackWood_Boss_harizma_1";
		break;
		
		case "LadyBeth_BlackWood_Boss_oruzhie_1":
			dialog.text = "Un possédé ? Ha ! Je suis simplement un homme qui sait ce qu'il veut !";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_1":
			dialog.text = "Partir ? Après ce que vous avez vu ? Non, non, non ! Personne ne doit savoir ce que j'ai trouvé ici. Personne !";
			link.l1 = "Je vous donne ma parole que je ne dirai rien à personne. Je le jure sur l'honneur d'un capitaine.";
			link.l1.go = "LadyBeth_BlackWood_Boss_torgovlya_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_2":
			dialog.text = "Il n'y a pas d'honneur dans ce monde, capitaine. Il n'y a que la crasse, la misère et le mépris. Je suis désolé, mais vous devez mourir ici.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
		break;
		
		case "LadyBeth_BlackWood_Boss_harizma_1":
			dialog.text = "J'ai réfléchi. Beaucoup réfléchi. Et j'ai compris - c'est ma seule chance. Soit je trouve l'or de Cortés, soit... rien. Vous comprenez ? RIEN ! Je ne retournerai pas à ma vie d'avant ! Je ne retournerai pas à la crasse et à la misère ! Mieux vaut mourir ici !";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_2":
			dialog.text = "Au combat ! Bullock, Fraser - tirez à la mitraille s'ils approchent ! Hopkins, à l'attaque !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_CaimanKino_11");
		break;
		
		// Диалоги с офицерами
		case "LadyBeth_Helena_1": // Элен
			dialog.text = "Ça va ?";
			link.l1 = "Oui, tout va bien. Et toi ?";
			link.l1.go = "LadyBeth_Helena_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Helena_2":
			dialog.text = "Vivante. Mais ces batailles terrestres, ce n'est pas pour moi. Donnez-moi un pont sous les pieds et je pulvériserai n'importe quel navire, mais ici... cet endroit est étrange\nFaire débarquer une centaine de loups de mer, les faire manier des pioches et construire des fortifications... Je n'aurais pas pu.";
			link.l1 = "Blackwood savait comment inspirer son équipage.";
			link.l1.go = "LadyBeth_Helena_3";
		break;
		
		case "LadyBeth_Helena_3":
			dialog.text = "J'ai entendu parler de lui à Blueveldt. Beaucoup de marins anglais parlaient de lui avec respect. Le meilleur officier de la flotte, une carrière brillante... et soudain, il a tout quitté pour chercher des trésors.";
			link.l1 = "Qu'est-ce que tu penses de lui ?";
			link.l1.go = "LadyBeth_Helena_4";
		break;
		
		case "LadyBeth_Helena_4":
			dialog.text = "Je pense que l'exemple de Blackwood montre bien le poids de la responsabilité que nous... enfin, que tu portes envers ton équipage. Je t'en prie, ne deviens pas le même capitaine que lui.";
			link.l1 = "Je ferai de mon mieux, Helen.";
			link.l1.go = "LadyBeth_Helena_5";
		break;
		
		case "LadyBeth_Helena_5":
			dialog.text = "Merci, mon capitaine. Je sais que tu réussiras.";
			link.l1 = "Nous.";
			link.l1.go = "LadyBeth_Helena_6";
		break;
		
		case "LadyBeth_Helena_6":
			dialog.text = "Nous.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Helena_7";
		break;
		
		case "LadyBeth_Helena_7":
			DialogExit();
			Return_HelenaOfficer();
		break;
		
		case "LadyBeth_Mary_1": // Мэри
			dialog.text = "Charles... cet endroit fait vraiment peur.";
			link.l1 = "Ça va, Mary ? Tu t'es comportée comme un vrai soldat.";
			link.l1.go = "LadyBeth_Mary_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Mary_2":
			dialog.text = "Non, je ne vais pas bien, ouais, hein. Regardez ces gens ! Ils travaillaient jusqu'à épuisement, vivaient dans la faim, mouraient de maladie... Et pour quoi ? Pour de l’or, cela n’existe peut-être même pas.";
			link.l1 = "Blackwood croyait qu'il était ici.";
			link.l1.go = "LadyBeth_Mary_3";
		break;
		
		case "LadyBeth_Mary_3":
			dialog.text = "Cet uniforme rouge... exactement comme le mien. Officier anglais... Tu sais, j'ai soudain pensé à mes parents, ouais, hein ?. À mes origines... à ce que je n'ai jamais connu. Peut-être que je suis comme eux ?";
			link.l1 = "Comme qui ?";
			link.l1.go = "LadyBeth_Mary_4";
		break;
		
		case "LadyBeth_Mary_4":
			dialog.text = "De ceux qui cherchent quelque chose qui n'existe peut-être pas. Et qui se perdent dans cette quête. Je... j'aimerais en parler plus tard, ouais, hein. Quand nous aurons quitté cet endroit horrible.";
			link.l1 = "Bien sûr, Mary.";
			link.l1.go = "LadyBeth_Mary_5";
		break;
		
		case "LadyBeth_Mary_5":
			dialog.text = "S'il vous plaît, enterrons-le d'abord ? Même s'il ne le mérite pas. Pour l’homme qu’il était autrefois.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Mary_6";
		break;
		
		case "LadyBeth_Mary_6":
			DialogExit();
			Return_MaryOfficer();
		break;
		
		case "LadyBeth_Tichingitu_1": // Тичингиту
			dialog.text = "Capitaine, Tichingitu voir ici mauvais endroit. Très mauvais.";
			link.l1 = "Que veux-tu dire ?";
			link.l1.go = "LadyBeth_Tichingitu_2";
			DelLandQuestMark(npchar);
		break;

		case "LadyBeth_Tichingitu_2":
			dialog.text = "Cette île maintenant être maudite. Terre boire trop sang et larmes. Qui creuse ici, respire malédiction.";
			link.l1 = "Tu penses que Blackwood était possédé ?";
			link.l1.go = "LadyBeth_Tichingitu_3";
		break;

		case "LadyBeth_Tichingitu_3":
			dialog.text = "Pas juste possédé. Il être... comment dire... récipient vide. Quelque chose entrer, chasser son âme. Moi voir ça avant. Quand chaman de tribu donner sacrifice humain aux esprits. Ce chaman avoir même regard.";
			link.l1 = "Mais qu'est-ce qui a pu provoquer une telle possession ?";
			link.l1.go = "LadyBeth_Tichingitu_4";
		break;

		case "LadyBeth_Tichingitu_4":
			dialog.text = "Homme avec vide dedans facile à remplir avec pensées d'autre. Quelqu’un trouver faiblesse, utiliser. Tichingitu presque avoir pitié pour lui.";
			link.l1 = "Presque ?";
			link.l1.go = "LadyBeth_Tichingitu_5";
		break;

		case "LadyBeth_Tichingitu_5":
			dialog.text = "Oui, presque. Guerrier doit répondre pour ses choix. Même si démons parlent dans oreille.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Tichingitu_6";
		break;
		
		case "LadyBeth_Tichingitu_6":
			DialogExit();
			Return_TichingituOfficer();
		break;
		
		case "LadyBeth_Irons_1": // Томми
			dialog.text = "Nom d’un chien, capitaine ! Regardez-moi ça ! On se croirait dans le bon vieux temps !";
			link.l1 = "Toi, tu sais bien ce que c’est la guerre sur terre.";
			link.l1.go = "LadyBeth_Irons_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Irons_2":
			dialog.text = "Ça m’a rappelé la bataille de Naseby. Notre aile de cavalerie a affronté les cavaliers de Rupert. Ils se battaient avec la même rage pour leur roi.";
			link.l1 = "Que penses-tu de Blackwood ?";
			link.l1.go = "LadyBeth_Irons_3";
		break;
		
		case "LadyBeth_Irons_3":
			dialog.text = "Ce Blackwood était soit un génie, soit un fou furieux. Je pense un peu des deux. Tu sais ce qui m’étonne ? Ses hommes. Beaucoup étaient d’anciens militaires. Pas des vauriens, mais de vrais pros\nEt ils l’ont tous suivi dans cette folie. Même les marines de Fox. Ha ! Lui, il sera ravi du carnage d’aujourd’hui ! Il ne leur a jamais pardonné leur désertion.";
			link.l1 = "Tu crois que c’était pour l’argent ?";
			link.l1.go = "LadyBeth_Irons_4";
		break;
		
		case "LadyBeth_Irons_4":
			dialog.text = "Non, il y avait autre chose. Ce gars avait du pouvoir sur eux. Du vrai pouvoir. Et j’ai entendu dire qu’il était fiancé à une riche demoiselle de la Barbade. Bizarre qu’il ne l’ait pas épousée après avoir trouvé tous ces trésors\nUn soldat typique - il ne savait pas quand s’arrêter de faire la guerre.";
			link.l1 = "Merci, Tommy. T’es un vrai penseur.";
			link.l1.go = "LadyBeth_Irons_5";
		break;
		
		case "LadyBeth_Irons_5":
			dialog.text = "Hein ?";
			link.l1 = "Rien.";
			link.l1.go = "LadyBeth_Irons_6";
		break;
		
		case "LadyBeth_Irons_6":
			DialogExit();
			Return_IronsOfficer();
		break;
		
		case "LadyBeth_Knippel_1": // Книппель
			dialog.text = "Quelle amertume de voir ça, capitaine. Jusqu'où sommes-nous tombés ?";
			link.l1 = "Nous ?";
			link.l1.go = "LadyBeth_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Knippel_2":
			dialog.text = "La flotte anglaise ! Regardez-moi ça : des petites taches d’uniformes rouges allongées au milieu de cette racaille morte !";
			link.l1 = "Certains de ces 'vauriens' sont des nôtres, Charlie. Je comprends ce que tu ressens, mais...";
			link.l1.go = "LadyBeth_Knippel_3";
		break;
		
		case "LadyBeth_Knippel_3":
			dialog.text = "Au diable tout ça, sir.";
			link.l1 = "Je comprends ce que tu ressens, mais tu ferais mieux de diriger ta colère et ta déception contre Blackwood. C’est lui qui a déserté ta chère flotte anglaise et les a amenés ici.";
			link.l1.go = "LadyBeth_Knippel_4";
			link.l2 = "En effet. Allons-y, la journée n’est pas finie.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_4":
			dialog.text = "Ils ne faisaient que suivre leur commandant !";
			link.l1 = "Comme tu as suivi Fleetwood ?";
			link.l1.go = "LadyBeth_Knippel_5";
			link.l2 = "En effet. Allons-y, la journée n’est pas finie.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_5":
			dialog.text = "Comme je vous suis !";
			link.l1 = "J’espère être un meilleur capitaine que Blackwood et Fleetwood. Allons-y, la journée n’est pas finie.";
			link.l1.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_6":
			dialog.text = "Oui, cap’tain. Et quand il sera fini, je boirai jusqu'à ce que le suivant se termine.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Knippel_7";
		break;
		
		case "LadyBeth_Knippel_7":
			DialogExit();
			Return_KnippelOfficer();
		break;
		
		case "LadyBeth_Alonso_1": // Алонсо
			dialog.text = "Madre de Dios, capitaine ! Vous allez bien ?";
			link.l1 = "Ça reste à voir. Combien d’hommes avons-nous perdus ?";
			link.l1.go = "LadyBeth_Alonso_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Alonso_2":
			dialog.text = "Tués ? Dans cette aventure, nous avons perdu "+sti(pchar.SailorDiedInBattleInfo)+" hommes. Je ne veux pas paraître insistant, capitaine, mais... je vous avais prévenu !";
			link.l1 = "Je vais ignorer cette remarque, car aujourd’hui tu t’es bien illustré, Alonso. D’où te viennent tous ces talents ?";
			link.l1.go = "LadyBeth_Alonso_3";
		break;
		
		case "LadyBeth_Alonso_3":
			dialog.text = "Un jour, je vous raconterai cette histoire, capitaine - si on survit, bien sûr.";
			link.l1 = "As-tu d'autres conseils pour moi ?";
			link.l1.go = "LadyBeth_Alonso_4";
		break;
		
		case "LadyBeth_Alonso_4":
			dialog.text = "S’il y avait eu un trésor ici, ils l’auraient déjà trouvé depuis longtemps. Mais on devrait quand même fouiller l’île et chercher des survivants, puis décider quoi faire d’eux. Et il ne faut pas oublier le navire de Blackwood : j’ai entendu dire que cette belle senau était remarquable\nCe serait dommage de rater un tel butin, capitaine. Bien sûr, je ne fais que rapporter l’opinion de l’équipage à ce sujet.";
			link.l1 = "Bien sûr. Allons-y. Les trophées nous attendent !";
			link.l1.go = "LadyBeth_Alonso_5";
		break;
		
		case "LadyBeth_Alonso_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		// Диалог с матросом в гроте Каймана
		case "LadyBeth_MatrosyInGrot":
			dialog.text = "Ne tirez pas ! On se rend !";
			link.l1 = "Qui êtes-vous ?";
			link.l1.go = "LadyBeth_MatrosyInGrot_2";
		break;
		
		case "LadyBeth_MatrosyInGrot_2":
			dialog.text = "Nous... nous venons du 'Lady Beth'. L’équipage du capitaine Blackwood. Est-ce qu’il... est-ce qu’il est vivant ?";
			link.l1 = "Non. Votre capitaine est mort.";
			link.l1.go = "LadyBeth_MatrosyInGrot_3";
		break;
		
		case "LadyBeth_MatrosyInGrot_3":
			dialog.text = "Alors c’est fini... Dieu merci.";
			link.l1 = "Vous ne semblez pas pleurer votre capitaine.";
			link.l1.go = "LadyBeth_MatrosyInGrot_4";
		break;
		
		case "LadyBeth_MatrosyInGrot_4":
			dialog.text = "Vous ne comprenez pas. Blackwood était un grand homme. Le meilleur capitaine que j’aie jamais connu. Mais ces derniers mois... il avait changé. Il était devenu obsédé, cruel. Il nous forçait à travailler jour et nuit, à chercher quelque chose qui n’existe peut-être même pas.";
			link.l1 = "Je vous prends dans mon équipage. Nous avons besoin de marins expérimentés.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda";
			link.l2 = "Malheur aux vaincus, les gars. Vous êtes maintenant sous mon pouvoir. Vous avez de la chance. Si vous tenez le coup, vous finirez dans une plantation à la Barbade.";
			link.l2.go = "LadyBeth_MatrosyInGrot_PlusRaby";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda":
			dialog.text = "Vraiment ? Vous... vous n’avez pas peur que nous... que quelque chose ne tourne pas rond chez nous après tout ça ?";
			link.l1 = "Tout le monde mérite une seconde chance.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda_1";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda_1":
			dialog.text = "Merci, capitaine. Je vous jure que vous ne le regretterez pas. Nous sommes de bons marins. Et... peut-être que les cauchemars s’arrêteront maintenant.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 30;
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusRaby":
			dialog.text = "Merci, merci ! Au moins, nous serons en vie. Emmenez-nous d’ici, je vous en prie. Cette île... elle semble maudite.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+30);
		break;
		
		case "LadyBeth_MatrosyInGrot_exit":
			DialogExit();
			for (i=1; i<=8; i++)
			{
				sld = CharacterFromID("LadyBeth_MatrosyPryachutsya_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		break;
		
		// Диалог с матросом на Леди Бет
		case "LadyBeth_EnemyMatros_1":
			dialog.text = "C’est quoi ce bordel ?! Comment avez-vous osé attaquer la 'Lady' et tuer Jeremy ? Vous ne sortirez pas vivants d’ici, sales chiens, le capitaine va revenir et...";
			link.l1 = "Votre capitaine est mort. Jeremy a tiré le premier, et je prends votre 'Lady' comme un prix légitime, payé dans le sang.";
			link.l1.go = "LadyBeth_EnemyMatros_2";
		break;
		
		case "LadyBeth_EnemyMatros_2":
			dialog.text = "Le capitaine... mort ? Tu mens, sale chien ! Tu ne vaux même pas un bouton de son uniforme !";
			link.l1 = "Si cet uniforme avait une signification, c’était pour le Blackwood d’autrefois. À vous de choisir - combattre pour un mort ou sauver vos vies.";
			link.l1.go = "LadyBeth_EnemyMatros_3";
		break;
		
		case "LadyBeth_EnemyMatros_3":
			if (CharacterIsHere("Helena"))
			{
				StartInstantDialog("Helena", "LadyBeth_EnemyMatros_Helena_1", "Quest\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Knippel"))
			{
				StartInstantDialog("Knippel", "LadyBeth_EnemyMatros_Knippel_1", "Quest\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Irons"))
			{
				StartInstantDialog("Irons", "LadyBeth_EnemyMatros_Irons_1", "Quest\LadyBeth_dialog.c");
				break;
			}
			dialog.text = "On ne vous laissera pas prendre le navire sans se battre !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		case "LadyBeth_EnemyMatros_Helena_1":
			dialog.text = "Écoutez, les gars. Je sais que vous êtes loyaux envers votre capitaine. C’est respectable. Mais il est mort, et vous êtes en vie. Et vous devez décider comment vivre désormais. Nous vous offrons une chance de recommencer.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_Knippel_1":
			dialog.text = "Capitaine, ces hommes ne sont pas des ennemis. Ils obéissaient simplement aux ordres. Beaucoup sont d’anciens marins de la Royal Navy, bien formés et disciplinés. Ce serait du gâchis de ne pas utiliser leurs compétences\nLes gars, j’ai été à votre place plus d’une fois pendant ma longue carrière dans la marine. Et j’ai fait le bon choix. Faites-le aussi.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
		break;
		
		case "LadyBeth_EnemyMatros_Irons_1":
			dialog.text = "Alors, les gars de mer ! Le choix est simple - soit vous vivez, même comme prisonniers dans la cale ou dans notre équipage avec bonne ration et solde régulière, soit... (fait un geste de la main sur la gorge) Moi, à votre place, je n’hésiterais pas une seconde !";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_10";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_5":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_6", "Quest\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_6":
			dialog.text = "...";
			link.l1 = "Vous allez faire partie de mon équipage.";
			link.l1.go = "LadyBeth_EnemyMatros_7";
			link.l2 = "Malheur aux vaincus, les gars. Vous êtes maintenant sous mon pouvoir. Vous avez de la chance. Si vous tenez le coup - vous finirez sur quelque plantation à la Barbade.";
			link.l2.go = "LadyBeth_EnemyMatros_9";
		break;
		
		case "LadyBeth_EnemyMatros_7":
			dialog.text = "Vous nous prenez dans votre équipage ? Après tout ça ?";
			link.l1 = "Les bons marins sont toujours précieux. Et le capitaine Blackwood savait choisir ses hommes.";
			link.l1.go = "LadyBeth_EnemyMatros_8";
		break;
		
		case "LadyBeth_EnemyMatros_8":
			dialog.text = "Merci, capitaine. Nous ne vous décevrons pas.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 12;
		break;
		
		case "LadyBeth_EnemyMatros_9":
			dialog.text = "Eh bien... cette aventure ne pouvait sans doute finir autrement. Pardonne-nous, capitaine Blackwood. Nous n’avons pas su te protéger.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+12);
		break;
		
		case "LadyBeth_EnemyMatros_10":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_11", "Quest\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_11":
			dialog.text = "On ne vous laissera pas prendre le navire sans se battre !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		// Диалог с Элизабет Бишоп
		case "LadyBeth_Elizabeth_1":
			dialog.text = "...";
			link.l1 = "Excusez-moi. Êtes-vous Elizabeth ?";
			if (pchar.sex == "man") link.l1.go = "LadyBeth_Elizabeth_2";
			if (pchar.sex == "woman") link.l1.go = "LadyBeth_Elizabeth_Woman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Elizabeth_2":
			dialog.text = "Oui, c’est moi. Et vous êtes ?";
			link.l1 = "Capitaine "+GetFullName(pchar)+". J’ai... connu Albert Blackwood.";
			link.l1.go = "LadyBeth_Elizabeth_3";
		break;
		
		case "LadyBeth_Elizabeth_3":
			dialog.text = "Mon Albert ? Mon Dieu... Il... il va bien ?";
			link.l1 = "Malheureusement non. Il est mort au combat. Il s’est battu jusqu’au bout.";
			link.l1.go = "LadyBeth_Elizabeth_4";
		break;
		
		case "LadyBeth_Elizabeth_4":
			dialog.text = "Je... je m’en doutais. Tant d’années sans nouvelles... Vous savez, je l’ai attendu. Longtemps. Mon père disait qu’Albert n’avait qu’à attendre sa promotion. Le gouverneur avait tout décidé, ce n’était qu’une question de mois\nMais Albert... il a vu les choses autrement. Il a dit qu’il reviendrait riche, digne de ma main. Et il est parti. Juste... parti.";
			link.l1 = "Il a pensé à vous jusqu’à son dernier jour.";
			link.l1.go = "LadyBeth_Elizabeth_5";
		break;
		
		case "LadyBeth_Elizabeth_5":
			dialog.text = "Comme c’est idiot. Je n’avais pas besoin de ses trésors. Je l’aimais, lui, pas son argent. J’étais prête à m’enfuir avec lui... mais il était si fier. J’attendais une lettre, un signe... Et puis il n’est venu qu’un étrange contrat\nUn document froid, calculé... qui ne ressemblait pas du tout à l’Albert que j’avais connu. C’est là que j’ai compris que je l’avais perdu.";
			link.l1 = "J’ai trouvé ceci parmi ses affaires.";
			link.l1.go = "LadyBeth_Elizabeth_6";
		break;
		
		case "LadyBeth_Elizabeth_6":
			dialog.text = "Une carte menant à ma maison ? J’étais donc son plus grand trésor ? Quelle ironie. Il a cherché des richesses dans tout les Caraïbes, alors que la seule chose qui comptait vraiment pour lui était ici... Attendez\nJ’ai quelque chose pour vous. C’est la charte d’Albert. Il me l’a envoyée il y a un an. Il disait que cela l’aiderait à trouver un trésor et à revenir vers moi. Maintenant, elle vous sera plus utile.";
			link.l1 = "Merci, Elizabeth. Je suis désolé que les choses se soient passées ainsi.";
			link.l1.go = "LadyBeth_Elizabeth_7";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_7":
			dialog.text = "Et moi, je me suis mariée, capitaine. Avec Monsieur Bishop. Mon père a insisté. Vous ne connaissez pas cet homme... et vous ne voudriez pas le connaître. Chaque jour je pense à ce qu’aurait pu être ma vie, si Albert était juste... revenu.";
			link.l1 = "Maintenant, je vais y penser aussi.";
			link.l1.go = "LadyBeth_Elizabeth_8";
		break;
		
		case "LadyBeth_Elizabeth_8":
			dialog.text = "Adieu, capitaine. Et... prenez soin de vous. Ne courez pas après des fantômes.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
		
		case "LadyBeth_Elizabeth_Woman_2":
			dialog.text = "Oui, c’est moi.";
			link.l1 = "Capitaine Helen MacArthur. J’ai... connu Albert Blackwood.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_3";
		break;
		
		case "LadyBeth_Elizabeth_Woman_3":
			dialog.text = "Mon Albert ? Mon Dieu... Il... Et vous êtes ?";
			link.l1 = "Capitaine Helen MacArthur, je vous l’ai dit. Je commande mon propre navire.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_4";
		break;
		
		case "LadyBeth_Elizabeth_Woman_4":
			dialog.text = "Capitaine ? Une femme capitaine ? Vous... Vous étiez avec Albert ? Dans quel sens... vous le connaissiez ?";
			link.l1 = "Seulement comme capitaine. Je suis désolée, mais Albert est mort. J’ai assisté à son dernier combat.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_5";
		break;
		
		case "LadyBeth_Elizabeth_Woman_5":
			dialog.text = "Je comprends. Pardonnez mes soupçons. C’est que... le capitaine Blackwood a toujours attiré l’attention des femmes. Même ici, à la Barbade. Surtout ici.";
			link.l1 = "Vous l’aimiez.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_6";
		break;
		
		case "LadyBeth_Elizabeth_Woman_6":
			dialog.text = "De tout mon cœur. Mon père disait qu’Albert n’avait qu’à attendre sa promotion. Ce n’était qu’une question de mois. Mais Albert a compris ses mots comme un refus à cause de sa pauvreté. Il a dit qu’il reviendrait avec un trésor. Et il est parti.";
			link.l1 = "Les hommes et leur fierté !";
			link.l1.go = "LadyBeth_Elizabeth_Woman_7";
		break;
		
		case "LadyBeth_Elizabeth_Woman_7":
			dialog.text = "Vous avez de la chance, capitaine MacArthur. Vous êtes libre. Vous allez où vous voulez. Pas de planteurs, pas de pères décidant de votre sort. Pas de maris vous considérant comme leur propriété.";
			link.l1 = "La liberté a un prix. Et il faut la défendre chaque jour.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_8";
		break;
		
		case "LadyBeth_Elizabeth_Woman_8":
			dialog.text = "J’ai peut-être quelque chose qui pourra vous aider. Tenez. C’est sa charte de recherche de trésor. Albert me l’a envoyée il y a environ un an. Il disait que c’était la meilleure chose qu’il ait jamais écrite\nQue cela l’aiderait à devenir riche et à revenir vers moi. Mais à chaque page, il ressemblait de moins en moins à l’Albert que j’ai connu.";
			link.l1 = "Merci. Je le garderai.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_9";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_Woman_9":
			dialog.text = "Je vous en prie, capitaine... chérissez votre liberté. J’ai épousé le colonel Bishop. Un homme que même mon père craint. Si j’avais été libre comme vous... Tout aurait été différent.";
			link.l1 = "Je sais.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_10";
		break;
		
		case "LadyBeth_Elizabeth_Woman_10":
			dialog.text = "Adieu, capitaine. Et que le vent vous soit favorable.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
		
		// диалог с Диего де Ланда
		case "LadyBeth_DiegoDeLanda_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Vous avez vu Madame Bishop ? Une histoire bien triste, n’est-ce pas ?";
				link.l1 = "Qui êtes-vous ?";
				link.l1.go = "LadyBeth_DiegoDeLanda_First_1";
			}
			else
			{
				dialog.text = "Bonjour, capitaine.";
				link.l1 = "Attendez ! On s’est déjà rencontrés ! Que faites-vous à la Barbade ?";
				link.l1.go = "LadyBeth_DiegoDeLanda_Second_1";
			}
		break;
		
		case "LadyBeth_DiegoDeLanda_First_1":
			dialog.text = "\nJe sers la paroisse de Sainte-Marie. Peu de catholiques trouvent du réconfort dans notre église, ici à la Barbade.";
			link.l1 = "Vous connaissez Elizabeth ?";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_2";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_2":
			dialog.text = "Oh, oui. Pauvre femme. Son mari... n’est pas un homme bon. On dit que ses plantations sont les plus productives de la Barbade. Et les plus cruelles. Savez-vous combien d’esclaves y meurent chaque mois \nIl a récemment battu à mort un vrai médecin venu d’Angleterre - un homme de grand savoir et talent. Et son sort à elle n’est guère meilleur, croyez-moi.";
			link.l1 = "Vous semblez bien informé.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_3";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_3":
			dialog.text = "Les gens viennent se confesser à moi, capitaine. J’entends ce qu’ils ont peur de dire même à leurs proches. Leurs peurs, leurs péchés... leur douleur.";
			link.l1 = "Et vous n’avez pas peur d’être persécuté ? Ce n’est pas facile d’être prêtre catholique sur les terres anglaises.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_4";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_4":
			dialog.text = "Dites-moi... vous cherchiez Blackwood volontairement ? C’est curieux. Mais pourquoi ? C’était dangereux et insensé. Quelle est votre flamme, capitaine ? Qu’est-ce qui vous pousse ?";
			link.l1 = "Cela ne vous regarde pas.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_5";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_5":
			dialog.text = "Je ne comprends pas. Les autres, oui. Mais vous... pas encore.";
			link.l1 = "Les autres ?";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_6";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_6":
			dialog.text = "L’un cherche la justice. Et un autre... était obsédé par les eaux sombres de la mort. Les gens se perdent si facilement dans leurs désirs. N’est-ce pas ?";
			link.l1 = "Vous êtes un drôle de prêtre, mon père.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_7";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_7":
			dialog.text = "...";
			link.l1 = "Je vais y aller, je crois.";
			link.l1.go = "LadyBeth_DiegoDeLanda_First_8";
		break;
		
		case "LadyBeth_DiegoDeLanda_First_8":
			dialog.text = "Bien sûr. Votre travail ne fait que commencer, capitaine.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Diego_2");
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_1":
			dialog.text = "Je sers à la paroisse de Sainte-Marie. Vous avez vu Madame Bishop ? Un destin bien triste. Mais, je le crains, mérité.";
			link.l1 = "La dernière fois, vous parliez par énigmes. Allez-vous faire de même cette fois ?";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_2";
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_2":
			dialog.text = "\nLa véritable énigme se tient devant moi. Vous avez rassemblé de nombreuses... reliques intéressantes. Une Bible. Une charte. Vous aimez collectionner ce genre de choses ? Êtes-vous collectionneur ?";
			link.l1 = "Comment savez-vous pour la charte ?";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_3";
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_3":
			dialog.text = "Chasseur de trophées ?";
			link.l1 = "Je répète ma question : comment savez-vous pour la charte ?";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_4";
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_4":
			dialog.text = "Amateur de sensations fortes ?";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_5";
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_5":
			dialog.text = "\nAh. Bien sûr. Évidemment. Eh bien, capitaine, je ne vais pas vous retenir davantage.";
			link.l1 = "Un instant, mon père. Vous n’avez toujours pas répondu à ma question.";
			link.l1.go = "LadyBeth_DiegoDeLanda_Second_6";
		break;
		
		case "LadyBeth_DiegoDeLanda_Second_6":
			dialog.text = "Oh, capitaine. Je ne peux pas. Parfois, les réponses font plus de mal que l’ignorance. Allez en paix. Et prenez soin de votre collection... de trophées. Ils pourraient vous être utiles pour le voyage qui vous attend.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Diego_2");
		break;
	}
} 