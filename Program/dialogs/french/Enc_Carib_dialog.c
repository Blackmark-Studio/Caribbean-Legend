void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, iMush, qty;
	string sGroup, sLink, sText;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "First time":
			dialog.text = "Félicitations! C'est un bug. Contactez Jason et dites-lui comment et où vous avez eu celui-ci. Paix!";
			link.l1 = "Je vais le faire immédiatement!";
			link.l1.go = "exit";
			Diag.TempNode = "First time";
		break;

		case "exit_fight":
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
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
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_peace":
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}	
			ChangeIndianRelation(1.00);
		break;
		
		// военные индеи - карибы
		case "war_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				dialog.text = LinkRandPhrase("Salut à toi, fils de la mer! J'ai entendu parler de toi. Tu peux marcher tranquillement sur notre terre.",""+npchar.name+" vous salue, frère au visage pâle. Nous sommes heureux de vous voir en tant que notre invité.","Je vous salue, vaillant guerrier au visage pâle! "+npchar.name+" est heureux de rencontrer un ami des Indiens. Va en paix!");
				link.l1 = RandPhraseSimple("Et salut à toi, frère à la peau rouge! Bonne chasse à toi!","Salutations, vaillant guerrier ! Que les dieux te bénissent, toi et ta famille !");
				link.l1.go = "exit_peace";
				if (CheckCaribGuns())
				{
					npchar.quest.count = 0;
					link.l2 = RandPhraseSimple("J'ai quelque chose qui pourrait t'intéresser, frère à la peau rouge. Veux-tu faire du commerce?","Je peux vous proposer d'acheter quelque chose d'intéressant, brave guerrier. Vous voulez faire du commerce?");
					link.l2.go = "war_indian_trade";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Arrête, visage pâle ! Par quel droit tu marches sur ma terre ?","Arrête, homme blanc ! Tu es sur la terre de mes ancêtres et ma terre !","Arrête, visage pâle ! Tu n'appartiens pas à ma terre");
				link.l1 = RandPhraseSimple("Votre terre ? Perds-toi, espèce de racaille au visage rouge !","Regardez-le - un singe qui parle ! Va-t'en, maintenant !");
				link.l1.go = "war_indian_1";
				link.l2 = RandPhraseSimple("Je suis venu en paix, guerrier à la peau rouge. Nous ne devrions pas nous battre pour rien.","Je ne suis pas un ennemi pour toi et ta terre, guerrier. Je suis venu en paix.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/3)) > hrand(80)) link.l2.go = "war_indian_2_1";
				else link.l2.go = "war_indian_2_2";
				link.l3 = RandPhraseSimple("Je suis venu commercer avec vous, pas pour me battre.","Je ne me bats pas avec les Indiens. Je fais du commerce avec eux.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/6)+makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE)/6)) > hrand(90)) link.l3.go = "war_indian_3_1";
				else link.l3.go = "war_indian_3_2";
			}
		break;
		
		case "war_indian_1":
			dialog.text = RandPhraseSimple("Tu regrettes d'être né, chien à la face pâle... Je découpe ton cœur et le fais frire sur le feu!","Je te fais manger des pierres, chien à la face pâle ! Nous rions quand tu supplie la mort à genoux, chien blanc !");
			link.l1 = RandPhraseSimple("Tu ne peux toujours pas fermer ta gueule puante, épouvantail peint? Je vais te ramener à la jungle d'où tu viens!","Tu oses me menacer, racaille?! Eh bien, maintenant tu vas remonter à l'arbre d'où tu viens!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_2_1":
			dialog.text = RandPhraseSimple("J'entends que ta voix parle vrai. Nous ne levons pas nos haches contre toi aujourd'hui. Va en paix, visage pâle.","Les visages pâles apportent rarement la paix, mais je vois dans vos yeux que vous parlez vrai. Allez maintenant.");
			link.l1 = RandPhraseSimple("Une décision sage, guerrier. Bonne chance à toi.","Je suis content que nous soyons parvenus à une entente, guerrier.");
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_2_2":
			dialog.text = RandPhraseSimple("Tu mens, chien pâle! Tu es venu ici pour tuer des Indiens! Prêt pour la bataille, visage pâle?!","Tu tues des Indiens. La langue blanche est une langue menteuse. Je vais la couper et la faire frire sur le feu !");
			link.l1 = RandPhraseSimple("Eh bien, camarade, ne me blâme pas alors. Dieu sait, j'ai essayé de l'éviter...","Eh bien, tu l'as demandé, guerrier.");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_3_1":
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				dialog.text = "Commerce? Nous avons besoin de l'arme de l'homme blanc. Une arme à feu à une main de l'homme pâle! Pour cela, nous échangeons nos marchandises! Avez-vous une arme à feu à échanger?";
				link.l1 = "Hmm. Je le fais. Et qu'est-ce que tu me donneras en échange?";
				link.l1.go = "war_indian_trade";
				link.l2 = "Espèce de vaurien! Et ensuite tu tireras sur les colons avec mes pistolets? Non, ça n'arrivera pas! Quant à vous, chacals, je vais vous abattre tous maintenant...";
				link.l2.go = "exit_fight";
			}
			else
			{
				dialog.text = "Tu n'as pas ce que nous voulons, visage pâle... Tu seras notre trophée de guerre!";
				link.l1 = "Essaie si tu l'oses, épouvantail...";
				link.l1.go = "exit_fight";
			}
		break;
		
		case "war_indian_3_2":
			dialog.text = RandPhraseSimple("Nous ne faisons pas de commerce avec les chiens au visage pâle. Nous tuons et prenons!","Nous ne sommes pas de sales miskito ou arawaks, nous ne faisons pas commerce avec les visages pâles ! Nous les tuons et obtenons des trophées de guerre !");
			link.l1 = RandPhraseSimple("Eh bien, alors essaye de me voler, vaurien!","D'abord, tu devras prendre mon sabre de moi, toi, ordure !");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_trade":
			iGun = 1;
			dialog.text = "Vous montrez ce que vous avez, et nous disons ce que nous donnons pour cela.";
			for (i=6; i>=1; i--)
			{
				if (GetCharacterFreeItem(pchar, "pistol"+i) > 0)
				{
					sLink = "l"+iGun;
					link.(sLink) = "Offer "+XI_ConvertString("pistol"+i)+".";
					link.(sLink).go = "gun_"+i;
					iGun++;				
				}
			}
		break;
		
		case "gun_1":
			npchar.quest.gun = "pistol1";
			if (hrand(1) == 0)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(1)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(9)+14);
				iTotalTemp = hrand(2)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "Hey-ho ! Nous vous donnons pour cela "+sText+".";
			link.l1 = "Marché conclu !";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Non. Pas question.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_2":
			npchar.quest.gun = "pistol2";
			if (hrand(3) < 2)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(3)+1);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "Hey-ho! Arme ruse... Nous vous la donnons pour cela "+sText+".";
			link.l1 = "Marché conclu !";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Non. Pas du tout.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_3":
			npchar.quest.gun = "pistol3";
			if (hrand(5) < 3)
			{
				qty = rand(1)+2;
				npchar.quest.item = "jewelry5"+qty;
				iTotalTemp = hrand(6)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful pearl";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(2)+2);
				iTotalTemp = hrand(2)+5;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  this beautiful stone";
			}
			dialog.text = "Hé-ho ! Puissante arme ! Tuer beaucoup-beaucoup d'ennemis ! Nous vous la donnons en échange "+sText+".";
			link.l1 = "Marché conclu !";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Non. En aucun cas.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_4":
			npchar.quest.gun = "pistol4";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(10)+qty*30;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "obereg_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hé-ho! Arme terrifiante... Nous vous la donnons en échange"+sText+".";
			link.l1 = "Marché conclu !";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Non. Pas question.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_5":
			npchar.quest.gun = "pistol5";
			if (hrand(7) < 7)
			{
				if (hrand(10) < 8)
				{
					npchar.quest.item = "jewelry7";
					iTotalTemp = 2+hrand(1);
				}
				else
				{
					npchar.quest.item = "jewelry8";
					iTotalTemp = hrand(4)+10;
				}
				qty = hrand(1)+1;
				npchar.quest.item = "jewelry"+(qty+6);
				if (qty == 1) iTotalTemp = 2;
				else iTotalTemp = hrand(5)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful and precious petrified tar";
			}
			else
			{
				npchar.quest.item = "indian_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hé-ho! Belle et puissante arme! Tuer beaucoup-beaucoup d'ennemis! Nous te la donnons pour ça "+sText+".";
			link.l1 = "Marché conclu !";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Non. Pas question.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_6":
			npchar.quest.gun = "pistol6";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(8)+qty*20;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "amulet_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hey-ho! Arme pratique ... Nous vous le donnons en échange "+sText+".";
			link.l1 = "Marché conclu !";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Non. Pas question.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "war_indian_trade_agree":
			ChangeIndianRelation(1.00);
			npchar.quest.count = sti(npchar.quest.count)+1;
			TakeNItems(pchar, npchar.quest.item, iTotalTemp);
			RemoveItems(pchar, npchar.quest.gun, 1);
			Log_Info("You have given "+XI_ConvertString(npchar.quest.gun)+"");
			Log_Info("You have received "+XI_ConvertString(npchar.quest.item)+" in amount of "+FindRussianQtyString(iTotalTemp)+"");
			PlaySound("interface\important_item.wav");
			if (sti(npchar.quest.count) > 3+hrand(2));
			{
				dialog.text = "Bien. Voici tes marchandises. Nous ne faisons plus de commerce. Reviens plus tard. Mieux vaut une arme enflammée, nous en donnerons plus pour ça. Maintenant pars!";
				link.l1 = "Adieu, guerrier à la peau rouge.";
				link.l1.go = "exit_peace";
			}
			else
			{
				dialog.text = "D'accord. Voici vos marchandises. Avez-vous d'autres armes de feu à échanger?";
				if (CheckCaribGuns())
				{
					link.l1 = "J'en ai. Allez-vous acheter?";
					link.l1.go = "war_indian_trade";
				}
				link.l2 = "Non. La prochaine fois j'apporterai plus.";
				link.l2.go = "war_indian_trade_exit";
			}
		break;
		
		case "war_indian_trade_exit":
			dialog.text = "Apporte. Meilleure arme enflammée plus nous donnons pour ça. Maintenant vas-y!";
			link.l1 = "Au revoir, guerrier...";
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_trade_bad":
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				DialogExit();
				sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
				for(i = 0; i < iTemp; i++)
				{
					sld = CharacterFromID(sTemp + i);
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sGroup);
					LAi_SetImmortal(sld, false);
					LAi_CharacterDisableDialog(sld);
				}	
			}
			else
			{
				dialog.text = "Alors nous prenons tout gratuitement, visage pâle!";
				link.l1 = "Vous pouvez essayer...";
				link.l1.go = "exit_fight";
			}
		break;
		
		// мирные индеи - мискито
		case "peace_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase("Salut, homme blanc. De quoi as-tu besoin dans notre jungle?","Notre jungle est très dangereuse. Que faites-vous ici?","Qu'est-ce qui vous amène ici, courageux visage pâle ?");
			link.l1 = RandPhraseSimple("Je passais simplement par là, mon ami à la peau rouge. Je crois qu'il y a assez de place sur ce chemin pour nous deux, non ?","Salutations, fils de la jungle! Je suis ici pour affaires, et je ne me bats pas contre les Indiens.");
			link.l1.go = "peace_indian_1";
			link.l2 = RandPhraseSimple("Et pourquoi avez-vous besoin de savoir? Suivez votre propre chemin et évitez les ennuis!","Va ton propre chemin, peau-rouge. Je n'ai pas de temps à te parler.");
			link.l2.go = "peace_indian_2";
		break;
		
		case "peace_indian_1":
			dialog.text = RandPhraseSimple("Nous sommes un peuple paisible. Nous ne sommes pas ennemis avec les hommes blancs. Allez, mais soyez prudent sur notre terre!","Je suis heureux de rencontrer l'ami au visage pâle des Indiens. Va en paix, fils de la mer !");
			link.l1 = RandPhraseSimple("Bonne chance à toi aussi, fils de la selva...","Adieu, ami à la peau rouge.");
			link.l1.go = "exit_peace";
		break;
		
		case "peace_indian_2":
			dialog.text = RandPhraseSimple("Nous sommes des chasseurs pacifiques. Mais nous ne tolérerons pas que le visage pâle parle ainsi sur notre terre!","Nous ne combattons pas avec les hommes blancs, mais si les hommes blancs nous offensent, nous répondons comme nos ancêtres nous ont appris !");
			link.l1 = RandPhraseSimple("Tu ne peux toujours pas fermer ta gueule puante, épouvantail peint? Je te reconduirai dans la jungle d'où tu viens!","Tu oses me menacer, canaille ?! Maintenant, tu vas remonter dans l'arbre d'où tu viens de descendre !");
			link.l1.go = "exit_fight";
		break;
	}
}
