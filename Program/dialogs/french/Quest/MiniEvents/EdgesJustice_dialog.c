void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
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
			dialog.text = "Que voulez-vous ?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;

		case "Naemnik":
			dialog.text = "Tu es doué"+GetSexPhrase("","e")+"... sacrément doué"+GetSexPhrase("","e")+". Mais avant que tu ne termines le travail, écoute-moi. Je suis sûr que ce que j'ai à dire t'intéressera.";
			link.l1 = "Très bien, tu peux parler avant de mourir. Mais ne te fais pas d’illusions. Tu ne sortiras pas vivant"+GetSexPhrase("","e")+" de cette grotte.";
			link.l1.go = "Naemnik_2";
		break;

		case "Naemnik_2":
			dialog.text = "Le chef du port, hein ? C'est lui qui t'a envoyé pour ma tête ?";
			link.l1 = "Tu es perspicace.";
			link.l1.go = "Naemnik_3";
		break;

		case "Naemnik_3":
			dialog.text = "Il t’a bien envoyé pour me tuer, pas pour me capturer ou m’arrêter, n’est-ce pas ?";
			link.l1 = "Exactement. Et alors ?";
			link.l1.go = "Naemnik_4";
		break;

		case "Naemnik_4":
			dialog.text = "Oh... tu es vraiment un"+GetSexPhrase(" imbécile","e petite naïve")+". As-tu seulement réfléchi pourquoi il veut ma mort plutôt que de m'enfermer ? Non ? Tu ne te doutes même pas de qui tu essaies de sauver. Cette araignée du port a tissé sa toile de mensonges partout, et toi, "+GetSexPhrase("gars","fillette")+", tu y es pris"+GetSexPhrase("","e")+" au piège.\nTu crois qu’il est un administrateur honnête ? Ha ! L’honnêteté ne lui vient qu’en rêve ! Il vend des informations aux pirates et aux Hollandais. Il trahit ceux qui lui font confiance. Un tel salaud mérite seulement la tombe !";
			link.l1 = "Peu importe qui patauge dans la boue. Tu ne ressembles pas non plus à un moine.";
			link.l1.go = "Naemnik_5";
		break;

		case "Naemnik_5":
			dialog.text = "Je ne ressemble pas à un moine, et je ne prétends pas l’être. Ma lame ne ment jamais. Un seul regard, et l’homme comprend – la mort est venue pour lui. Je ne souris pas à ma cible, je ne lui serre pas la main en sachant qu’elle est déjà condamnée. Non. Mes intentions sont claires. Mais ce bureaucrate...\nIl trahit tout le monde en leur faisant croire qu’il les aide. Il est pire que n’importe quel salaud que j’ai envoyé dans la tombe.";
			link.l1 = "Admettons que tu dises la vérité. Qui t’a engagé ?";
			link.l1.go = "Naemnik_6";
		break;

		case "Naemnik_6":
			dialog.text = "Je ne te donnerai pas de nom – je ne le connais même pas. Mais c’est quelqu’un qui a souffert à cause de ce pourri. Un homme qui veut la justice... ou la vengeance. Appelle ça comme tu veux, cela ne change rien. Cinq cents doublons pour la tête de ce fonctionnaire pourri ! Aide-moi, et on partage.";
			link.l1 = "Assez parlé ! Tu dirais n'importe quoi pour sauver ta peau misérable. Je t’ai laissé parler"+GetSexPhrase("","e")+", il est temps de mourir.";
			link.l1.go = "Naemnik_7";
			link.l2 = "Belle histoire. Mais je ne vais pas te croire sur parole, mon ami. Tu as des preuves ? Des témoins ? Ou c’est juste une ruse de plus pour éviter la mort ?";
			link.l2.go = "Naemnik_8";
		break;
		
		case "Naemnik_7":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_UbivaemNaemnika");
		break;
		
		case "Naemnik_8":
			dialog.text = "Ces papiers ont été trouvés dans la cabine d'un pirate que mon commanditaire a vaincu en combat. Il recevait des tuyaux du chef du port. Les notes indiquent clairement les itinéraires des navires, leurs heures de départ et les cargaisons qu’ils transportaient. Ces itinéraires correspondent à ceux qui ont été pillés, tués ou ont disparu sans laisser de trace.\nEt surtout, l’écriture est exactement la même que celle des documents officiels de cargaison. Ces notes sont la clé pour le démasquer. Mon commanditaire veut qu'elles soient trouvées sur son cadavre. Un simple procès ne suffit pas.\nCe salaud est trop influent et a beaucoup d’amis corrompus. Si l’affaire allait en justice, il s’en tirerait. Des gens comme lui ne méritent pas de vivre. Une mort dans la honte, c’est tout ce qu’il mérite.";
			link.l1 = "Sacré chien ! Les gens lui confient leur vie, et lui les vend aux pirates ! Je suis partant. Un homme comme lui n’a pas sa place en ce monde.";
			link.l1.go = "Naemnik_9";
			GiveItem2Character(PChar, "GS_letters");
			AddQuestRecordInfo("GS_Letters", "1");
		break;

		case "Naemnik_9":
			dialog.text = "J’ai obtenu une clé de sa maison – d’un menuisier qui réparait ses meubles. Tout se passait bien jusqu’à ce que je découvre qu’il ne vit pas seul. Quand je suis venu pour le tuer, sa femme était à l’intérieur.\nSa présence m’a pris au dépourvu. Personne ne m’aurait payé pour elle, et les autorités auraient été bien plus zélées pour me retrouver. J’ai donc changé de plan et je l’ai attendu près de l’administration.";
			link.l1 = "Par le diable ! Toute la ville est en alerte, on ne peut plus le tuer en pleine rue. Que faire maintenant ?";
			link.l1.go = "Naemnik_10";
		break;

		case "Naemnik_10":
			dialog.text = "J’ai observé la ville, attendant que le tumulte retombe. Après ma visite, ce lâche de rat a caché sa chère épouse. Je l’ai vue de mes propres yeux monter à bord d’un navire et quitter le port.\nIl est maintenant seul – le moment parfait pour finir ce que nous avons commencé. Infiltre sa demeure de nuit et règle son compte. Ensuite, laisse les papiers bien en vue, pour que tout le monde voie quel genre de pourriture il était.\nMais moi, je ne peux plus entrer en ville. Toi, en revanche... tu le peux. Personne ne t’attend. Tu passeras sans problème. Sa maison est près de la prison de la ville. Cinq cents doublons ! La moitié est pour toi si tu termines le travail.";
			link.l1 = "Très bien. Je l’enverrai personnellement rejoindre les morts. Ces papiers resteront dans sa maison – que la vérité soit révélée. Attends-moi ici. Je reviendrai quand ce sera fait.";
			link.l1.go = "Naemnik_11";
		break;
		
		case "Naemnik_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			AddQuestRecord("GS", "5");
			AddQuestUserData("GS", "sSex", GetSexPhrase("","а"));
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetWarriorType(sld);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			NextDiag.CurrentNode = "Naemnik_12";
			
			sld = &Locations[FindLocation("Beliz_town")];
			sld.reload.l11.open_for_night = 1;
			sld = &Locations[FindLocation("Beliz_houseS5_room2")];
			sld.locators_radius.item.button01 = 1.0;
			
			pchar.quest.GS_SoldatyDoma.win_condition.l1 = "Hour";
			pchar.quest.GS_SoldatyDoma.win_condition.l1.start.hour = 0.00;
			pchar.quest.GS_SoldatyDoma.win_condition.l1.finish.hour = 5.00;
			PChar.quest.GS_SoldatyDoma.win_condition.l2 = "location";
			PChar.quest.GS_SoldatyDoma.win_condition.l2.location = "Beliz_houseS5";
			PChar.quest.GS_SoldatyDoma.function = "GS_SoldatyDoma";
		break;
		
		case "Naemnik_12":
			dialog.text = "Pourquoi restes-tu planté"+GetSexPhrase("","e")+" là comme si tu étais enraciné"+GetSexPhrase("","e")+" dans le sol ?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Naemnik_12";
		break;

		case "Portman_1":
			dialog.text = "Vous ? Que diable ? Comment êtes-vous entré ici ?";
			link.l1 = "Comment je suis entré"+GetSexPhrase("","e")+" ici n'a aucune importance. Et je pense qu'au fond de vous, vous comprenez pourquoi je suis venu"+GetSexPhrase("","e")+".";
			link.l1.go = "Portman_2";
			DelLandQuestMark(npchar);
		break;

		case "Portman_2":
			dialog.text = "Non, je ne comprends pas ! Si c'est pour la récompense, venez demain à l'administration, je vous donnerai tout.";
			link.l1 = "Assez de vos simagrées ! Je sais tout. Vous vendiez des informations sur les navires de vos clients aux pirates. Un homme aussi vil ne mérite pas d’occuper un tel poste. Et encore moins de vivre parmi des gens honnêtes. Monsieur, votre place est parmi les vôtres – en enfer.";
			link.l1.go = "Portman_3";
		break;

		case "Portman_3":
			dialog.text = "Oh, non-non-non ! Non ! Vous avez tout mal compris ! I-ils m'ont forcé... Ils sont venus et ont menacé de s’en prendre à ma famille si je ne les aidais pas... vous ne comprenez pas...";
			link.l1 = "J’en ai assez de vos pitoyables excuses ! J’ai en main vos notes, où vous exigez votre pourcentage pour les informations ! Votre hypocrisie est répugnante, et je n’ai plus l’intention de la supporter. Sortez votre arme et défendez-vous, si vous en avez le courage !";
			link.l1.go = "Portman_4";
		break;
		
		case "Portman_4":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Beliz_portman_clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_PortmanDead");
		break;
		
		case "Naemnik_21":
			dialog.text = "Alors, quelles nouvelles ? Le travail est-il fait ?";
			link.l1 = "Tu en doutais ? Il a tout tenté pour trouver une excuse, mais cela ne l'a pas aidé. J’ai laissé les notes bien en vue, comme convenu.";
			link.l1.go = "Naemnik_22";
		break;

		case "Naemnik_22":
			dialog.text = "Des larves pitoyables comme lui pensent toujours qu'elles peuvent acheter la justice avec de vulgaires mensonges et de l'argent.";
			link.l1 = "Eh bien, maintenant il ne pense plus à rien. Donne-moi mon argent et je pars.";
			link.l1.go = "Naemnik_23";
		break;

		case "Naemnik_23":
			dialog.text = "Voici tes doublons. Excellent travail, je dois le reconnaître. Mais tu sais, si j'avais eu quelque chose de plus sérieux entre les mains, tout aurait pu se passer autrement... pour toi. Dans les murs étroits de la maison, on ne peut pas vraiment se battre, alors j'ai pris ce cure-dents misérable en pensant finir vite le travail.\nSi j'avais su comment les choses tourneraient, j'aurais pris une arme plus solide.";
			link.l1 = "Ha-ha. Et notre pauvre gars disait que tu étais armé comme Roland lui-même avant le col de Roncevaux !";
			link.l1.go = "Naemnik_24";
			AddItems(pchar, "gold_dublon", 250);
		break;

		case "Naemnik_24":
			dialog.text = "Heh. Eh bien, la peur a de grands yeux. Tu vois toi-même avec quel genre de fourchette j’ai failli toucher ton cœur.";
			link.l1 = "Tu veux dire que si tu avais eu un morceau de fer plus lourd, tu aurais pu rivaliser avec moi ?";
			link.l1.go = "Naemnik_25";
		break;

		case "Naemnik_25":
			dialog.text = "Dans le maniement des armes de poids moyen, je suis un maître, c’est un fait. Tu ne me crois pas ? Alors écoute bien, je vais te confier quelques astuces qui m'ont sauvé plus d'une fois. Ce ne sont pas de simples paroles – cela pourrait te sauver la peau un jour. On ne partage pas ce genre de secrets avec n’importe qui.";
			link.l1 = "...";
			link.l1.go = "Naemnik_26";
		break;
		
		case "Naemnik_26":
			DialogExit();

			SetLaunchFrameFormParam("Une heure s'est écoulée...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("GS_Spravedlivost_2", 0.0);
			LaunchFrameForm();
		break;

		case "Naemnik_27":
			dialog.text = "...";
			link.l1 = "Je vois que tu maîtrises vraiment ton art. Merci pour la leçon. Mais si c’est tout, il est temps que je parte.";
			link.l1.go = "Naemnik_28";
			AddComplexSelfExpToScill(0, 500, 0, 0);
		break;

		case "Naemnik_28":
			dialog.text = "Adieu, "+GetSexPhrase("capitaine","ma jolie")+". J’espère qu’on ne se croisera plus sur le champ de bataille. Ce serait dommage de devoir te tuer. Ha-ha.";
			link.l1 = "Tu n’auras pas la moindre chance, même si je suis ivre et sur une jambe, héh ! Allez, adieu, mercenaire.";
			link.l1.go = "Naemnik_29";
		break;

		case "Naemnik_29":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			LAi_SetPlayerType(pchar);

			LAi_SetWarriorType(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PEACE);

			AddQuestRecord("GS", "7");
			CloseQuestHeader("GS");

			AddSimpleRumourCity("On dit que le chef du port a été retrouvé mort chez lui. On a trouvé sur lui des notes prouvant son implication dans la disparition de navires. Quelle honte pour notre ville...", "Beliz", 30, 1, "");
			AddSimpleRumourCity("Vous avez entendu ? Quelqu'un s'est introduit dans la maison du chef du port, a tué la garde et l'a exécuté. On a trouvé sur le corps des notes avec les itinéraires de navires disparus – écrites de sa main ! Un serviteur de la Couronne, mais un traître en vérité ! Il a eu ce qu’il méritait ! Où donc regardait le gouverneur pendant toutes ces années ?", "Beliz", 30, 1, "");
			AddSimpleRumourCity("Le chef du port a été tué ! Chez lui, en pleine nuit ! La garde est morte, et parmi ses affaires – des notes indiquant les routes des navires disparus. Pas de doute, c’est lui ! Eh bien, la justice l’a rattrapé.", "Beliz", 30, 1, "");
		break;
	}
}