//Jason общий диалог цыганок
// ugeen <-- добавил продажу мышьяка из под полы
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ah bonjour, ma chérie. Que veux-tu?";
			link.l1 = "Rien, je suppose.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("J'ai une question à te poser.","J'ai besoin d'informations.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Chéri, aurais-tu l'amabilité de partager un peu d'or ? Je te dirai ton avenir.","Hé, matelot, ne te presse pas comme ça ! Veux-tu connaître l'avenir ?","Donne-moi un peu de tabac et quelques pièces d'argent, vaillant jeune homme. Et je jetterai un coup d'œil à ton avenir. (clin d'œil) Veux-tu entendre un peu de magie secrète tzigane ?");
				link.l1 = " Désolé, mais je dois partir.";
				link.l1.go = "exit";
				// --> мангароса
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Ecoutez, dame forgeron, je sais que votre peuple est expert en potions et poisons. On m'a dit que cette plante pourrait vous intéresser. Jetez-y un oeil. Qu'en pensez-vous ?";
					link.l5.go = "mangarosa";
				}
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Eh, yeux noirs, j'ai quelque chose pour toi... C'est de la mangarosa. Tu veux en acheter??";
					link.l5.go = "mangarosa_trade1";
				}
				// <-- мангароса
				link.l2 = "Peux-tu lire mon avenir ?";
				link.l2.go = "guess";
				link.l3 = RandPhraseSimple("J'ai une question pour vous.","J'ai besoin d'informations.");
				link.l3.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_Start") && !CheckAttribute(pchar, "questTemp.DWH_gipsy") && npchar.city == "SentJons")
			{
				link.l6 = "Écoute, sourcils noirs, j'ai entendu dire que tu guéris les gens, même des maladies graves, est-ce vrai ?";
				link.l6.go = "dwh_gypsy_1";
			}
			// <-- Тёмные воды исцеления
			if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
			{
				link.l4 = "Hé, yeux noirs, as-tu des poisons pour les rats ? Ils sont un sacré fléau sur mon navire.";
				link.l4.go = "get_poison_1";
			}
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------------гадание-------------------------------------------------
		case "guess":
			dialog.text = "Bien sûr, beau gosse. Donne-moi quelques pièces et montre-moi ta main droite. Je te parlerai de ton avenir et t'aiderai à éviter les désastres. Je ne triche jamais ! Remboursement garanti !";
			link.l1 = "Je sens que c'est le moment où ton compatriote me fait les poches... J'ai changé d'avis. Je ne suis pas d'humeur.";
			link.l1.go = "exit";
			link.l2 = "Combien d'argent veux-tu ?";
			link.l2.go = "guess_1";
		break;
		
		case "guess_1":
			dialog.text = "Ah mon cher, autant que votre bourse le permet et que votre cœur le désire. Plus vous avez de pièces de huit, plus loin dans l'avenir je peux voir !";
			link.l1 = "100 pesos";
			link.l1.go = "guess_rate_1";
			link.l2 = "500 pesos";
			link.l2.go = "guess_rate_2";
			link.l3 = "1000 pesos";
			link.l3.go = "guess_rate_3";
			link.l4 = "5000 pesos";
			link.l4.go = "guess_rate_4";
		break;
		
		sTemp = GuessText();
		case "guess_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Ah, merci pour ta charité, mon beau jeune faucon ! Maintenant écoute : "+sTemp+"";
				link.l1 = LinkRandPhrase("Ha ! C'est très intéressant. Je vais y réfléchir...","Vraiment ? Je vais y réfléchir...","Ah, vraiment? Es-tu sérieux? Je m'en souviendrai...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Le plus laid et inévitable malheur t'attend. Maudis le moqueur ! Que des nuages sombres se rassemblent sur toi et que le châtiment te trouve !";
				link.l1 = "Ha-ha ! Pensais-tu vraiment que je te donnerais de l'argent, sorcière gitane ? Hors de mon chemin ! J'espère que l'Inquisition t'emportera !";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_2"://немного в везение или скрытность
			if (sti(pchar.money) >= 500)
			{
				AddMoneyToCharacter(pchar, -500);
				dialog.text = "Ah, merci, mon beau jeune faucon ! Maintenant écoute :"+sTemp+"Bonjour, monami.";
				link.l1 = LinkRandPhrase("Hé ! C'est très intéressant. Je vais y réfléchir...","Vraiment ? J'y réfléchirai...","Oh, vraiment ? Es-tu sérieux ? Eh bien, je m'en souviendrai...","Hé, je me sens déjà mieux !");
				link.l1.go = "exit";
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30+rand(10));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 30+rand(10));//скрытность
			}
			else
			{
				dialog.text = "Le plus laid et l'inévitable malheur t'attend. Maudit soit le railleur ! Que les nuages sombres s'amassent sur toi et que le châtiment te trouve !";
				link.l1 = "Ha-ha! Pensais-tu vraiment que je te donnerais de l'argent, sorcière gitane? Hors de mon chemin! J'espère que l'Inquisition te prendra!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_3"://здоровье + везение или скрытность, харизма
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Ah, merci pour ton argent, mon beau jeune faucon ! Écoute maintenant :"+sTemp+"Bonjour, monami.";
				link.l1 = LinkRandPhrase("Heh ! C'est très intéressant. Je vais y réfléchir...","Vraiment? J'y réfléchirai...","Oh, vraiment ? Vous êtes sérieux ? Eh bien, je m'en souviendrai...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50+rand(20));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 50+rand(20));//скрытность
			}
			else
			{
				dialog.text = "Le plus vilain et inévitable malheur t'attend. Maudis le raillard ! Que les sombres nuages se rassemblent sur toi et que le châtiment te trouve !";
				link.l1 = "Ha-ha ! Penses-tu vraiment que je te donnerais de l'argent, sorcière gitane ? Dégage de mon chemin ! J'espère que l'Inquisition te prendra !";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_4"://умения в оружие, везение+скрытность, здоровье, харизма
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Oh là là ! Merci pour votre générosité, mon beau jeune faucon ! Maintenant écoute : "+sTemp+"";
				link.l1 = LinkRandPhrase("Hé ! C'est très intéressant. J'y réfléchirai...","Vraiment ? Je vais y réfléchir...","Oh, vraiment? Es-tu sérieux? Eh bien, je m'en souviendrai...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 2);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCharacterExpToSkill(pchar, "Fortune", 50+rand(100));//везение
				AddCharacterExpToSkill(pchar, "Sneak", 50+rand(50));//скрытность
				AddComplexSelfExpToScill(20, 20, 20, 20);
			}
			else
			{
				dialog.text = "Le plus affreux et inévitable malheur t'attend. Maudis le railleur ! Que des nuages sombres s'amassent sur toi et que le châtiment te trouve !";
				link.l1 = "Ha-ha ! Pensais-tu vraiment que je te donnerais de l'argent, sorcière gitane ? Hors de mon chemin ! J'espère que l'Inquisition t'emportera !";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_exit":
			DialogExit();
			AddCharacterHealth(pchar, -10);
			LAi_CharacterDisableDialog(npchar);
		break;
//<-- гадание

// --> продажа мышьяка
		case "get_poison_1" :
			npchar.quest.poison_price = (hrand(3) + 1) * 10;
			if(hrand(10) == 3 || IsCharacterPerkOn(pchar, "Trustworthy"))
			{				
				dialog.text = LinkRandPhrase("Oh, je ne suis pas sûr, beau gosse! Il y avait un type il n'y a pas longtemps qui demandait de l'aide pour tuer des rats, et puis quelqu'un a empoisonné les soldats dans le fort. Ça a chauffé pour mes gens sur l'île pendant que les gardes nous interrogeaient pendant deux semaines jusqu'à ce qu'ils trouvent le meurtrier. C'était un espion ennemi.","Et comment puis-je être sûr de vos intentions ? Peut-être voulez-vous seulement empoisonner un noble que vous êtes trop lâche pour affronter dans un duel honorable ??","On m'a dit que quelqu'un avait empoisonné un commerçant dans la taverne et avait volé toutes ses affaires. L'homme a souffert pendant longtemps avant de rendre l'âme. De l'écume sortait de sa bouche et il est devenu violet comme une aubergine... Es-tu responsable de cela, mon amour ?");
				link.l1 = "Vous, les gitanes, aimez certainement partager vos opinions ! Ne t'inquiète pas ma fille, je ne vais pas empoisonner les gens. C'est une manière féminine de tuer, pas mon style. Pour les hommes, j'ai mon épée, mais je ne peux pas gérer ces maudits rats.";
				link.l1.go = "get_poison_2";
				if (IsCharacterPerkOn(pchar, "Trustworthy")) notification("Trustworthy", "Trustworthy");
			}
			else
			{
				dialog.text = "Vous essayez de me piéger ! Non monsieur, je n'ai aucun poison. J'ai des plantes et des potions, mais pas de poisons.";
				link.l1 = "Quoi qu'il en soit. Ne me jette pas le mauvais oeil.";
				link.l1.go = "exit";
				notification("Perk Check Failed", "Trustworthy");
			}	
		break;
		
		case "get_poison_2" :
			dialog.text = "Oh beau et si galant homme ! (chuchotant) Payez-moi "+sti(npchar.quest.poison_price)+" doublons.";
			if (PCharDublonsTotal() >= sti(npchar.quest.poison_price))
			{				
				link.l1 = "Cher... Mieux vaut que cette camelote fonctionne.";
				link.l1.go = "get_poison_4";
			}
			else
			{
				link.l1 = "Pas question ! J'ai acheté le même chez moi pour cinq pistoles ! Je pourrais attraper tous les rats moi-même pour autant d'argent !";
				link.l1.go = "get_poison_3";
			}
		break;
		
		case "get_poison_3" :
			dialog.text = "Attrape-les toi-même alors et ne m'embête pas. J'appellerai la garde la prochaine fois.";
			link.l1 = "Pas besoin des gardes, sorcière, je m'en vais.";
			link.l1.go = "exit";
		break;
		
		case "get_poison_4" :
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(sti(npchar.quest.poison_price));
			TakeNItems(pchar, "rat_poison", 1);
			DialogExit();
		break;
// <-- продажа мышьяка

	// --> Мангароса
		case "mangarosa":
			dialog.text = LinkRandPhrase("Montre-moi la plante, cher... Hm... Je suppose que je peux l'acheter de toi. Trois cents pièces de huit, d'accord ?","Montre-le-moi, beau gosse... Heh... Eh bien, je peux payer deux cent cinquante pour ça.","Voyons voir... Oh ! Un exemple intéressant ! Deux cents pesos ! Marché conclu ?")"Bonjour, mon ami.";
			link.l1 = LinkRandPhrase("Oh Seigneur... aux yeux noirs, je ne suis pas un paysan. Je connais cette plante. C'est de la mangarosa...","Oh, vraiment ?! C'est un spécimen parfait de mangarosa. Ne tente pas de m'escroquer, gitan.","Ah, et tu supposes que je vais te donner cette mangarosa pour une somme si dérisoire.");
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			dialog.text = "Bien, bien, beau garçon. Je vois que tu sais quelque chose sur cette plante. Cinquante doublons. Donne-la-moi.";
			link.l1 = "Attends un peu ! Je veux savoir comment cela peut être utilisé et à quoi cela sert. Peux-tu m'en parler ? Tous tes gens sont prêts à payer beaucoup d'or pour ce petit arbuste !";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			// тут работает харизма
			if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10+hrand(25)+hrand(30, "1"))
			{
				dialog.text = "Hm... Je suppose que ce n'est pas trop grave si je vous en parle un peu. Vous ne pourrez rien faire avec cette plante sans compétences particulières.";
				link.l1 = "Je vous écoute.";
				link.l1.go = "mangarosa_3";
			}
			else
			{
				dialog.text = LinkRandPhrase("Mon peuple pourrait payer beaucoup d'or mais ils n'exposeraient jamais leurs secrets.","L'or c'est l'or et les secrets sont des secrets, jeune homme... ","Oui, nous sommes prêts à payer, mais pas à parler.")+"Alors, vas-tu me vendre ta mangarosa ? Cinquante doublons est notre tarif actuel pour ça, personne ne te paiera plus.";
				link.l1 = "Oh, bien... Ça me convient de toute façon. Cinquante doublons. Prends-les";
				link.l1.go = "mangarosa_trade";
				link.l2 = "Comprenez-moi, je ne veux pas le vendre. Je veux savoir pourquoi vous en avez besoin. Partagez votre savoir avec moi et je vous le donnerai gratuitement.";
				link.l2.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_trade":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Prends tes pièces, jeune faucon. Et encore une chose, apporte-nous plus de ces plantes. Mais nous ne pouvons les acheter qu'une par une car nous ne portons pas de grosses sommes avec nous. Les gardes ne font pas confiance à notre espèce et aiment nous embêter...";
			link.l1 = "D'accord. Si j'en trouve plus, je l'apporterai.";
			link.l1.go = "mangarosa_trade_exit";
		break;
		
		case "mangarosa_trade_exit":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "gipsy_trade";
			AddQuestRecord("Mangarosa", "3");
		break;
		
		case "mangarosa_exit":
			dialog.text = LinkRandPhrase("Pas question ! Si tu ne veux pas le vendre - ne le fais pas alors. Je ne te dirai rien.","Je ne vais pas exposer nos secrets à un gadjo étranger ! (crache) Tu ne veux pas le vendre ? Au diable avec toi.","Ami, cela ne te regarde pas. Tu ne veux pas le vendre pour cinquante doublons ? Va le vendre à la fille du commerce pour deux cents pesos.");
			link.l1 = LinkRandPhrase("Quel dommage pour vous alors ! Un autre de vos gens me le dira de toute façon. Et elle recevra cette plante en cadeau. À bientôt !","Pourquoi être si têtu ? Si tu ne me le dis pas, l'autre le fera. Et elle recevra cette mangarosa en cadeau. Adieu.","Ton haleine pue l'ail. J'obtiendrai ce que je veux tôt ou tard. Un autre de ta race sera plus loquace et obtiendra la plante gratuitement. À plus tard.");
			link.l1.go = "exit";
			npchar.quest.mangarosa = "true";
			pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count)+1;
		break;
		
		case "mangarosa_trade1":
			dialog.text = "Et pourquoi demandes-tu, faucon ?! Bien sûr ! Donne-le moi.";
			link.l1 = "Donne-moi cinquante doublons.";
			link.l1.go = "mangarosa_trade1_1";
			link.l2 = "Oups ! Il semble que je l'ai perdu ou oublié sur mon navire. Quel dommage. Adieu...";
			link.l2.go = "exit";
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_trade1_1":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ne t'inquiète pas, je ne te tromperai pas. Prends tes pièces.";
			link.l1 = "Prends ta mangarosa. J'en apporterai plus si j'en trouve.";
			link.l1.go = "exit";
		break;
		
		case "mangarosa_3":
			dialog.text = "Nous broyons les bourgeons d'une manière spéciale, puis nous les séchons, trions les graines et les tiges, puis les mélangeons avec du tabac, tassons nos pipes et fumons le mélange. Et nous obtenons un effet... inoubliable. Comme l'ivresse de l'alcool, mais sans maux de tête après. Une plante suffit pour deux douzaines de pipes.";
			link.l1 = "Je vois maintenant ! Peux-tu m'enseigner cette technique secrète ? Je peux bien te payer...";
			link.l1.go = "mangarosa_4";
		break;
		
		case "mangarosa_4":
			dialog.text = "Jeune faucon, crois-moi, tu n'as pas besoin de ça. Ne t'en mêle pas, la plante te ruinera. Elle émousse l'esprit et te rend gras. Ne me le demande même pas. Mais... je vois un homme brave devant moi, avec une épée, un homme de la mer... peut-être même un capitaine ?";
			link.l1 = "Vous avez raison.";
			link.l1.go = "mangarosa_5";
		break;
		
		case "mangarosa_5":
			dialog.text = "Ecoute donc. Mangarosa peut être utilisée pour des choses bien plus nobles et tu pourrais la trouver utile. Une de nos guérisseuses connaît tous ses secrets. C'est elle dont tu as besoin\nDonne-moi la plante et je te dirai son nom et où la trouver. Mais la convaincre de partager ses secrets avec toi sera ton problème.";
			link.l1 = "Très bien. Prends la plante et dis-moi comment trouver ton magicien gitan.";
			link.l1.go = "mangarosa_6";
		break;
		
		case "mangarosa_6":
			RemoveItems(pchar, "cannabis7", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Elle s'appelle Amelia. Elle vit seule dans une petite maison parmi les dunes, non loin de la mer, quelque part sur la côte sud-ouest de la Main espagnole, comme disent les gens sages.";
			link.l1 = "Oh par le saint nom de Dieu, pouvez-vous être plus précis, je vous prie ?";
			link.l1.go = "mangarosa_7";
		break;
		
		case "mangarosa_7":
			dialog.text = "Tu es un marin, faucon courageux, et moi, je ne le suis pas. Cherche-la là où je l'ai dit. Sa maison est vraiment proche de la côte. Elle est près d'une baie juste au sud-ouest du Main espagnol - les marins doivent le savoir.";
			link.l1 = "D'accord, je vais essayer de le trouver...";
			link.l1.go = "mangarosa_8";
		break;
		
		case "mangarosa_8":
			dialog.text = "Apporte-lui une Mangarosa ou elle ne te parlera même pas. Et n'oublie pas d'apporter des doublons non plus, ne pense même pas qu'elle t'enseignera gratuitement !";
			link.l1 = "Quelle avarice. J'y réfléchirai. Merci pour ton histoire !";
			link.l1.go = "mangarosa_9";
		break;
		
		case "mangarosa_9":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "amelia";
			pchar.questTemp.Mangarosa.Tell = "true"; // калеуче
			AddQuestRecord("Mangarosa", "4");
			// создаем и ставим Амелию
			sld = GetCharacter(NPC_GenerateCharacter("Amelia", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Amelia";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Mangarosa.c";
			sld.dialog.currentnode = "amelia";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Amelia_house", "barmen", "stay");
		break;
		
		// --> Тёмные воды исцеления
		case "dwh_ne_ta":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Non, mon cher, ce n’est pas moi que tu cherches, c’est " + sld.name + ". Elle est en ville en ce moment. Je l’ai vue récemment.";
			link.l1 = "Merci.";
			link.l1.go = "exit";
		break;
		// <-- Тёмные воды исцеления
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Ecoute-moi, vaillant faucon, je suis peut-être un gitan, mais même nous dénonçons la violence ouverte. S'il te plaît, remets ton épée au fourreau.","Ecoute-moi, vaillant faucon, en tant que citoyen de cette ville, je te demande de rengainer ton épée.");
			link.l1 = LinkRandPhrase("D'accord.","Comme vous voulez.","Comme vous dites...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;
	switch (hrand(19))
	{
		case 0: sText = "you will have luck, brave young falcon, tomorrow you'll be lucky with cards!" break;
		case 1: sText = "the fortune will be kind with you in your mercantile business, captain!" break;
		case 2: sText = "there is a misfortune awaiting you in the open sea, it's waiting just for you, wait for three days!" break;
		case 3: sText = "I see that you need to seek help from your closest ones, you won't make it alone in your next fight!" break;
		case 4: sText = "go and light a candle in a church, you have been cursed by your enemy. You won't make it without God's help!" break;
		case 5: sText = "you are going to lose a lot soon, my falcon, but don't despair and hope for yourself, seek help from you friends..." break;
		case 6: sText = "a heavy loss is waiting for you in the sea, but I see, that you, captain, will be able to ride it out even if you don't get what you want." break;
		case 7: sText = "you have entered the aim of misfortune, captain! Visit a brothel and have some rest." break;
		case 8: sText = "you will get what you want, captain, but don't expect anything good from it. All what you've wanted so passionately, captain, will bring only bad things so you'd better change your plans away." break;
		case 9: sText = "I see that there is a sign on that face of yours, the sign of ultimate luck. You will get more than you're expecting to get, young man!" break;
		case 10: sText = "you need to evaluate your wish once again and decide. Do you really need it? Your fate is giving you a chance to rethink." break;
		case 11: sText = "it's rare luck, not everyday we've getting a chance to rethink. Take a rest for a few days, bright-eyed, think about things. Don't hurry to your death!" break;
		case 12: sText = "though all of your efforts won't give you the expected result, don't despair, young falcon, great luck is waiting for you in the most unexpected day, don't lose it!" break;
		case 13: sText = "your problem won't be solved in a positive way but you are a stubborn one and you'll get what you want but, perhaps, not from the place you've expected." break;
		case 14: sText = "you'd better forget about the business you are up to. You will never be lucky in this and if you'll be continuing in it than, perhaps, your closest people will be hurt or killed." break;
		case 15: sText = "there is an event which is waiting for you, captain, and it will completely change your life. Your recent concerns will lose all of their meaning to you after that." break;
		case 16: sText = "there is danger on your way to your dream, captain, and you must be really lucky if you will be able to get what you want without heavy losses. It's better to turn away and forget your unachievable dream. Or perhaps, this fate could be tricked if you lose in cards or dice right now..." break;
		case 17: sText = "I see a strong power in you like a rock and a light as bright as the north star which leads people. Good news is waiting for you!" break;
		case 18: sText = "a bad sign is rising on your way, fear the evil eye and keep loyal men close to you." break;
		case 19: sText = "a lucky event is rising on your way right behind your own back. Look for the good which is coming right to your hands and don't chase the unachievable." break;
	}
	return sText;
}
