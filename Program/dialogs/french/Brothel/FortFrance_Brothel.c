// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;   
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quel genre de questions, "+GetSexPhrase("jeune homme","jeune demoiselle")+" ?","Que désirez-vous, "+GetSexPhrase("bel étalon","jolie demoiselle")+" ? Demandez donc."),"Encore des questions ?","Hihi, si ça vous est égal - des questions...",""+GetSexPhrase("Hum, pourquoi vous ne choisissez pas une jolie fille ? Je commence à avoir des soupçons à votre sujet...","Hm, choisissez donc une fille par vous-même. Nous n'avons pas de garçons ici, j'en ai peur, hi-hi...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis, excusez-moi.","En fait, laissez tomber..."),"Je... m'excuse, je n'ai pas de questions, pour l'instant.","Vous avez raison, c'est déjà la troisième fois. Pardonnez-moi.","Peut-être la prochaine fois, Madame.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Ecoute, Aurora, j'ai besoin d'une fille pour la nuit. Et je veux l'emmener chez moi. Peux-tu arranger cela ?";
                link.l1.go = "Gigolo";
			}	
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Gigolo":
			dialog.text = "Bien sûr, mon chou. Avez-vous trouvé une demoiselle à votre goût ?";
			link.l1 = "Tout à fait. J'avais en vue une certaine Lucille.";
			link.l1.go = "Gigolo_1";
		break;
		
		case "Gigolo_1":
			dialog.text = "Vous parlez de Lucille Montaigne ?";
			link.l1 = "Honnêtement, je ne lui ai pas demandé son nom de famille. Tout ce que je sais, c'est qu'elle est jeune et belle, blonde, et s'appelle Lucille.";
			link.l1.go = "Gigolo_2";
		break;
		
		case "Gigolo_2":
			dialog.text = "Oui, ça la décrit bien. D'accord. Mais dites-moi, pourquoi elle ? Les autres filles ne vous plaisent pas ?";
			link.l1 = "Eh bien, voyez-vous... elle vient de commencer ici, donc je pense qu'elle n'a pas encore assez d'expérience dans le 'Métier' pour vider ma bourse.";
			link.l1.go = "Gigolo_2_1";
			link.l2 = "Vous voyez, j'adore les blondes à la peau claire. Lucille fera parfaitement l'affaire.";
			link.l2.go = "Gigolo_2_2";
		break;
		
		case "Gigolo_2_1":
			if (int(pchar.questTemp.Sharlie.Gigolo.Rand1) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 5000;
				dialog.text = "Voyons Monsieur, ce n'est pas vrai ! Elle est jeune, jolie et expérimentée, mes clients ne font que l'admirer. Elle vous coûtera cher. Cinq mille pesos pour une nuit avec elle, pas un de moins.";
				if (int(pchar.money) >= 5000)
				{
					link.l1 = "C'est cher, mais d'accord. Prenez votre argent.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "C'est cher ! Je n'ai pas autant d'argent sur moi. Je reviendrai.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 2500;
				dialog.text = "Hmm, vous avez raison, Monsieur, elle est jeune et jolie mais manque d'expérience. Mes clients ne la remarquent généralement pas, c'est pourquoi j'ai demandé. Mais si vous aimez vraiment les filles modestes, c'est un bon choix. Elle vous coûtera deux mille cinq cents pesos.";
				if (int(pchar.money) >= 2500)
				{
					link.l1 = "Elle fera l'affaire. Voici votre argent.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "C'est cher ! Je n'ai pas autant d'argent sur moi. Je reviendrai.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_2_2":
			if (int(pchar.questTemp.Sharlie.Gigolo.Rand2) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 4500;
				dialog.text = "Vous ne seriez pas le premier, bel étalon. Il arrive que mes clients fassent la queue pour attirer son attention, elle se distingue des filles des îles et leur peau sombre. Elle vous coûtera quatre mille cinq cents pesos.";
				if (int(pchar.money) >= 4500)
				{
					link.l1 = "C'est cher, mais très bien. Voici votre argent.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "C'est cher ! Je n'ai pas autant d'argent sur moi. Je reviendrai.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 3000;
				dialog.text = "Vraiment, Monsieur ? Déjà nostalgique ? Mes créoles, et surtout mes mulâtres sont bien plus ardentes que cette chatte de gouttière parisienne sans manières. Mais hélas, c'est votre choix. Elle vous coûtera trois mille pesos.";
				if (int(pchar.money) >= 3000)
				{
					link.l1 = "C'est cher, mais très bien. Voici votre argent.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "C'est cher ! Je n'ai pas autant d'argent sur moi. Je reviendrai.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_3":
			AddMoneyToCharacter(pchar, -int(pchar.questTemp.Sharlie.Gigolo.Money));
			dialog.text = "Comme vous voulez, mon chou. Lucille vous attendra impatiemment à onze heures du soir. Elle ne doit pas rentrer plus tard que sept heures du matin. Si vous n'arrivez pas avant minuit, elle s'occupera d'un autre client, et vous devrez attendre la nuit suivante pour la prendre.\nEt ne pensez même pas à... lui faire du mal, de quelque manière que ce soit. Vous le regretteriez. Un simple avertissement, mon chou.";
			link.l1 = "Ne vous inquiétez pas, je la traiterai comme un amant, pas comme un rustre. Je la prendrai à onze heures. Que vais-je bien pouvoir faire d'ici là ?";
			link.l1.go = "Gigolo_4a";
		break;
		
		case "Gigolo_4a":
			dialog.text = "Ma foi, je ne sais pas, mon chou. Passez à la taverne, discutez au comptoir...";
			link.l1 = "Bonne idée. J'y vais de ce pas. Passez une bonne journée !";
			link.l1.go = "Gigolo_4";
		break;
		
		case "Gigolo_4":
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			DialogExit();
			AddQuestRecord("SharlieC", "2");
			pchar.questTemp.Sharlie.Gigolo = "girl";
			Sharlie_CreateGigoloGirl();
			QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerDelLoc("fortfrance_brothel", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
			//NewGameTip("Доступна функция перемотки времени! Она доступна через опцию 'мысли вслух' в меню действий (ENTER).");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
