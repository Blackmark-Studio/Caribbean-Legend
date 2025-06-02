// Ян Свенсон - пиратский барон Западного Мэйна
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson")) {
				if (pchar.questTemp.HelenDrinking.Result == "won") {
					dialog.text = "Ah, Charles. Merci d'être passé. Je voulais juste te remercier d'avoir passé du temps avec Helen. La fille avait besoin de guérir ses blessures, et j'ai entendu dire que tu t'es bien amusé aussi, ha-ha ! Diable, je suis même jaloux !";
					link.l1 = "Tu n'es pas fâché ? À propos du tonneau et... tout le reste ?";
					link.l1.go = "after_drinking";
				} else {
					dialog.text = "Ah, Charles. Merci d'être passé. Je voulais simplement te remercier d'avoir passé du temps avec Helen. La fille avait besoin de guérir ses blessures, et j'ai entendu dire que tu t'es bien amusé aussi, ha-ha ! Bonne chance à toi à Carthagène !";
					link.l1 = "Oui, moi aussi je suis content que tout se soit bien passé hier. Jusqu'à notre prochaine rencontre, Jan.";
					link.l1.go = "exit";
				}
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson");
				break;
			}
		
			if(CheckAttribute(pchar, "questTemp.Saga"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga_Late")) // отсекание при провале по времени
				{
					dialog.text = "Oh, mon ami "+pchar.name+"Ravi de vous voir ! Que puis-je faire pour vous ?";
					link.l1 = "Je fais juste un arrêt pour voir comment vous allez.";
					link.l1.go = "exit";
					if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
					{
						if (GetDataDay() == 14 || GetDataDay() == 28)
						{
							link.l2 = "Jan, je voudrais acheter du bois de fer.";
							link.l2.go = "trade_bakaut";
						}
					}
					break;
				}
				if(pchar.questTemp.Saga == "svenson")
				{
					dialog.text = "Comment puis-je vous aider, Monsieur ?";
					link.l1 = "Je voudrais demander votre aide, Diable de la Forêt.";
					link.l1.go = "saga";
					break;
				}
				if(pchar.questTemp.Saga == "svenson1")
				{
					dialog.text = "Ah ah, mon ami "+pchar.name+" ! Quelles sont les nouvelles ?";
					link.l1 = "J'ai réussi à apprendre beaucoup de choses intéressantes de la part du Bourreau.";
					link.l1.go = "saga_11";
					break;
				}
				if(pchar.questTemp.Saga == "svenson2")
				{
					dialog.text = "Alors, "+pchar.name+", avez-vous parlé à Gladys?";
					link.l1 = "Oui, je l'ai fait. Jan, regarde ici... Peux-tu me dire quelque chose à propos de ce bout de parchemin ici ?";
					link.l1.go = "saga_17";
					break;
				}
				if(pchar.questTemp.Saga == "helena1" || pchar.questTemp.Saga == "helena2" || pchar.questTemp.Saga == "svenson_wait")
				{
					dialog.text = "Je n'ai encore rien de nouveau à te dire, "+pchar.name+"Mais je travaille sur une solution pour notre affaire. Reviens plus tard.";
					link.l1 = "D'accord, Jan. Je te verrai plus tard.";
					link.l1.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests") // старт трех квестов баронов
				{
					// первая проверка времени. Свенсон очень недоволен растяпством ГГ. Счищаем Элен, к Свенсону доступ закроем
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = ""+pchar.name+", tu m'as complètement déçu. Je m'attendais à ce que tu sois un homme sérieux, mais il s'avère que tu n'es qu'un garçon stupide. Où étais-tu pendant tout ce temps, hein ? Les Anglais ont revendiqué Isla Tesoro pendant que tu faisais dieu sait quoi !\nTous mes plans sont ruinés ! Pour être honnête, j'ai presque oublié ton existence et je ne veux pas qu'on me le rappelle. Dégage !";
						link.l1 = "Je n'arrive pas à y croire !";
						link.l1.go = "saga_l1";
					}
					else
					{
						dialog.text = "Te voilà, "+pchar.name+". J'ai un peu ruminé notre sort. Je n'appellerais pas ça un plan, mais...";
						link.l1 = "Je suis tout ouïe, Jan.";
						link.l1.go = "saga_25";
					}
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests_1") // идут три квеста баронов
				{
					dialog.text = "Comment cela se passe-t-il ? Y a-t-il quelque chose avec quoi je puisse vous aider ?";
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "after_marlow")
					{
						link.l3 = "J'ai parlé au Pasteur Noir. Hélas, le résultat de notre conversation m'a renvoyé vers vous pour des conseils, je suis perplexe.";
						link.l3.go = "shark_hunt_2";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "LSC" && !CheckAttribute(pchar, "questTemp.Saga.BaronReturn"))
					{
						link.l3 = "J'ai trouvé Dios et nous avons eu une conversation agréable. Il m'a raconté beaucoup de choses intéressantes, mais malheureusement, nous n'avons pas abordé le fond du problème.";
						link.l3.go = "shark_hunt_7";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "third_teleport")
					{
						link.l3 = "Oh, Jan. J'ai tant à te raconter que cela prendrait toute la nuit pour tout te transmettre, alors je serai bref.";
						link.l3.go = "return_LSC";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "shamane" && !CheckAttribute(npchar, "quest.shamane"))
					{
						link.l3 = "J'ai récupéré Nathaniel Hawk de l'île de la Justice. Il est sur mon navire en ce moment.";
						link.l3.go = "nathaniel";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "treatment")
					{
						link.l3 = "J'ai déposé Nathaniel Hawk au village Miskito pour qu'il soit soigné par un chaman nommé Œil de Serpent. Il m'a promis de rétablir la santé de Nathan.";
						link.l3.go = "nathaniel_2";
					}
					link.l4 = "Pas grand-chose à te dire pour le moment. Je fais juste un saut pour voir comment tu vas.";
					link.l4.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "fail_centurion") // провал - потоплен Центурион
				{
					dialog.text = "Quelles sont les nouvelles, "+pchar.name+"? Comment ça va ?";
					link.l1 = "Oh, ça ne pourrait pas être pire. J'ai fait tellement de travail... J'ai retrouvé Jackman, nous avons jeté les fourreaux, et je l'ai noyé comme le plus grand imbécile avec tout ce qui aurait pu être dans sa cabine. Maintenant, je n'ai rien pour m'aider à ôter la mauvaise réputation de Shark et mettre la pression sur Barbazon. J'ai bien peur que ce soit une cause perdue, Jan.";
					link.l1.go = "saga_f_1";
					break;
				}
				if(pchar.questTemp.Saga == "calendar") // квесты баронов завершены
				{
					// вторая проверка времени. Отбираем Элен, со Свенсоном нейтральные отношения - ну не выщло и не вышло, хоть попытались. Данни и Натана - в Марун-Таун
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = "J'ai entendu parler de tes exploits héroïques ! Dannie m'a raconté la version courte. D'ailleurs, nous sommes amis maintenant. Et Nathan a complètement changé ! Toute sa dépression s'est envolée quand il a vu son 'Centurion'.\nMais j'ai de mauvaises nouvelles pour toi, "+pchar.name+"Nous avons perdu tellement de temps que les droits d'héritage du testament de Sharp sont depuis longtemps révolus et Isla Tesoro est devenue une base militaire anglaise. Je ne peux plus rien faire pour vous aider avec Levasseur."link.l1 ="Je suis absolument sans voix... Nous avons traversé tant de péripéties pour rien. Y a-t-il vraiment rien que nous puissions faire ?";
						link.l1.go = "saga_l2";
					}
					else
					{
						dialog.text = "J'ai entendu parler de tous vos exploits ! Dannie m'a mis au courant. Au fait, nous nous sommes réconciliés. Vous ne reconnaîtriez même pas Nathan. Dès qu'il a vu son 'Centurion', il a laissé derrière lui ses grognements comme un mauvais rêve...";
						link.l1 = "Nathan est à nouveau en forme ? Je suis heureux de l'entendre !";
						link.l1.go = "saga_26";
					}
					break;
				}
				if(pchar.questTemp.Saga == "mine") // рудник взят
				{
					dialog.text = "Te voilà, "+pchar.name+" ! Maintenant, j'ai quelque chose à te dire.";
					link.l1 = "Bonjour, Jan. Je suis ravi ! Quelles nouvelles ? J'espère, quelque chose de positif ?";
					link.l1.go = "saga_32";
					break;
				}
				if(pchar.questTemp.Saga == "mine_1") // рудник взят совместно
				{
					dialog.text = "Te voilà, "+pchar.name+" ! Bien reposé ? Et puis-je conclure que vous êtes de nouveau prêt pour de grandes aventures ?";
					link.l1 = "Bonjour, Jan. Oui, je suis prêt.";
					link.l1.go = "saga_32a";
					break;
				}
				if(pchar.questTemp.Saga == "late_l3") // провал по времени у адвоката
				{
					dialog.text = "Quelles sont les nouvelles, "+pchar.name+" ? Comment ça va ? ";
					link.l1 = "Oh. Les choses sont absolument horribles. J'ai lutté bec et ongles, mais j'ai quand même fini par perdre. Comme tu te souviens, le testament de Sharp avait une limite de temps. Eh bien, ce délai est écoulé et Isla Tesoro est maintenant une base militaire anglaise. C'est une cause perdue, Jan.";
					link.l1.go = "saga_l3";
					break;
				}
				if(pchar.questTemp.Saga == "bakaut") // пришёл от адвоката за деньгами
				{
					dialog.text = "Salutations, "+pchar.name+" ! Bonne nouvelle : la réunion du Conseil a eu lieu et les Frères de la Côte ont trouvé un nouveau chef.";
					link.l1 = "Bon après-midi, Jan. Je suis content pour toi.";
					link.l1.go = "saga_44";
					break;
				}
				if(pchar.questTemp.Saga == "sellbakaut" && GetSquadronGoods(pchar, GOOD_SANDAL) >= 1) // отдает бакаут
				{
					dialog.text = "Eh bien, "+pchar.name+"Avez-vous rattrapé Molligan ?";
					link.l1 = "Je l'ai fait. C'est lui qui a volé ton bois de fer.";
					link.l1.go = "saga_55";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut") && GetNpcQuestPastDayParam(npchar, "bakaut_date") >= 1) // за деньгами за бакаут
				{
					dialog.text = "À l'heure comme toujours, "+pchar.name+" J'ai vendu le bois de fer que tu m'as apporté.";
					link.l1 = "Excellent. Combien d'argent as-tu gagné ?";
					link.l1.go = "saga_57";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut_sum")) // сам продал бакаут
				{
					dialog.text = "Eh bien, "+pchar.name+"? As-tu rattrapé Molligan ?";
					link.l1 = "Je l'ai fait. C'était lui qui a volé ton bois de fer. Je suis aussi tombé sur son acheteur. C'était un commandant militaire néerlandais. Je lui ai vendu la marchandise.";
					link.l1.go = "saga_59";
					link.l2 = "Je l'ai fait. J'ai essayé de le forcer à me montrer sa cale... nous nous sommes affrontés et... il n'y a plus de Molligan maintenant. Mais il n'y a rien que tu puisses voir dans la cale à part de l'ébène et de l'acajou.";
					link.l2.go = "saga_59_1";
					break;
				}
				if(CheckAttribute(npchar, "quest.jessika")) // информация о Джессике
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"Quoi de neuf ?";
					link.l1 = "Jan, je voudrais te parler d'une affaire. J'ai fouillé dans le passé de la mère d'Helen, Beatrice, et je suis tombé par hasard sur quelqu'un que tu connais très bien. D'après ce qu'on m'a dit...";
					link.l1.go = "saga_62";
					break;
				}
				if(pchar.questTemp.Saga == "lastpages") 
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Comment avancent les choses ? À en juger par votre visage, puis-je vous féliciter ? ";
					link.l1 = "Oui. J'ai enfin réussi à démêler ce chaos. Helen a reçu tous les droits sur Isla Tesoro. Plus jamais personne n'empiétera sur le refuge des Frères de la Côte !";
					link.l1.go = "saga_82";
					break;
				}
				if (pchar.questTemp.Saga == "end") sTemp = "Oh, my friend "+pchar.name+"! Pleased to see you! What brings you here?";
				else sTemp = "Anything else, "+pchar.name+"?";
				dialog.text = sTemp;
				link.l1 = "Non, Jan. Rien pour le moment.";
				link.l1.go = "exit";
				if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
				{
					if (GetDataDay() == 14 || GetDataDay() == 28)
					{
						link.l2 = "Jan, je voudrais acheter un peu de ton bois de fer.";
						link.l2.go = "trade_bakaut";
					}
				}
				NextDiag.TempNode = "First time";
			}
			else
			{
				// заглушка Элен
				if(startHeroType == 4)
				{
					dialog.text = "Helen, bonjour, ma chère. Quelles nouvelles as-tu ? Y avait-il quelque chose que tu voulais ?";
					link.l1 = "Bonjour, Jan ! Tout de même, je suis juste passé te voir.";
					link.l1.go = "exit";
					NextDiag.TempNode = "First time";
					break;
				}
				dialog.text = "Puis-je vous aider en quoi que ce soit ?";
				link.l1 = "Non, je vais bien.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First time";
			}
		break;
		
		case "saga":
			dialog.text = "Je te connais, bon sang! Tu es le brave capitaine qui a sauvé Rumba et affronté les canons de la corvette anglaise de front ! Quel plaisir de te voir ! Helen est comme une fille pour moi. À partir d'aujourd'hui, je te suis à jamais redevable. Tu peux m'appeler Jan ou Svenson, si tu le souhaites. Que puis-je faire pour toi ?";
			link.l1 = "Je dois éliminer Levasseur, le gouverneur de la Tortue. Je sais qu'il ne sera pas facile de l'atteindre sur son île, c'est pourquoi je suis venu vous demander conseil.";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "Ma foi, où étiez-vous il y a quelques années ! J'avais prévu de faire la même escapade moi-même. Il a gâché tout le jeu pour nous avec les Français. Mais à cette époque, tout était différent. Blaze était vivant, Shark avait de l'autorité, et Nathan menait la danse à Maroon Town... Maintenant tout a changé et, Dieu sait, pas pour le mieux. Savez-vous quelque chose sur nous, sur les Frères ?";
			link.l1 = "Je suis récemment arrivé ici, donc je ne sais pratiquement rien. À part le fait que vous et Jackman faites partie du Conseil.";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			dialog.text = "Oh, je ne peux pas supporter ce Jackman ! C'est à son arrivée que tous nos problèmes ont commencé. Je vais réfléchir à votre requête. À première vue, rien ne me vient à l'esprit.";
			link.l1 = "J'ai quelque chose d'intéressant à propos de Jackman.";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			dialog.text = "Hm. Qu'est-ce que c'est ?";
			link.l1 = "Jackman cherche Gladys Chandler et sa fille. Après avoir parlé à Higgins, j'ai commencé à penser qu'il cherche Rumba. Il semble que Gladys n'est pas la mère biologique d'Helen et son nom de famille était Chandler avant qu'elle n'épouse Sean McArthur.";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			dialog.text = "Mille sabords ! Voilà une mauvaise nouvelle. Jackman est plus fort que jamais maintenant. En plus de ça, j'ai un mauvais pressentiment qu'il ne travaille pas seul. Il a une ombre assez sinistre derrière lui. S'il a vraiment besoin d'Helen, alors la fille a cruellement besoin d'un protecteur. J'ai bien peur d'être un peu trop vieux pour le faire moi-même...";
			link.l1 = "Ce n'est pas tout. Jackman cherche aussi quelqu'un nommé Henry le Bourreau, ancien maître d'équipage du 'Neptune', de l'équipage du capitaine Boucher.";
			link.l1.go = "saga_5";
		break;
		
		case "saga_5":
			dialog.text = "Caramba ! Mes pires soupçons se sont avérés vrais ! Ce Boucher et son 'Neptune' faisaient trembler tout l'archipel. Il n'y avait pas de Frères à l'époque, chacun était pour soi. Cet homme a fait beaucoup de mauvaises choses, une personne qui m'était chère est morte à cause de lui.\nJe n'ai jamais eu l'occasion de le rencontrer. Le 'Neptune' a été coulé par une frégate anglaise, et le Boucher a été exécuté à St. John's. Bon débarras ! Bien qu'il y ait eu beaucoup de gens qui admiraient sa chance et son audace téméraire.\nJackman lui-même était sa main droite et son premier lieutenant sur le 'Neptune'. Surpris ? Les anciens criminels sont devenus des héros de la Nation, tout cela grâce à Cromwell ! Où est passée la bonne vieille Angleterre ?\nNous devons trouver Henry le Bourreau avant que les hommes de Jackman ne le fassent. Peut-être détient-il la clé de ce mystère, s'il est encore en vie.";
			link.l1 = "Je parie que ce serait plus facile de trouver une aiguille dans une botte de foin. As-tu au moins quelques pistes ?";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Je connaissais Henry quand il était gamin. Le fils d'une prostituée de Carthagène, à moitié espagnol, bien qu'il l'ait toujours gardé secret. Sa mère était torride! Je ne dirais pas qu'elle était jolie, mais il y avait très peu de danseuses de flamenco comme elle. Tout le bordel regardait les spectacles de la Chica Gonzales nue et ses castagnettes.\nPauvre fille. Elle a attrapé une sale maladie et est morte comme une chandelle. C'est alors que j'ai persuadé Henry d'aller à Providence où il s'est rapidement fait un nom et a rejoint l'équipage de Thomas Beltrope, un ami proche de Nicolas Sharp. Ces deux-là étaient les derniers chiens de la reine Élisabeth et travaillaient toujours ensemble. Bonnes époques!\nThomas est retourné en Angleterre quand son partenaire est mort. Il a emmené son équipage avec lui, mais Henry est resté dans les Caraïbes. Il a navigué sous différents capitaines jusqu'à ce que Boucher apparaisse. D'ailleurs, il a obtenu son surnom à cause d'un coutelas qu'il gardait toujours à portée de main.";
			link.l1 = "Et que nous dit cette information ?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Si Pendard a décidé de se cacher des pirates, le meilleur endroit pour lui serait dans une ville espagnole. Surtout chez lui à Carthagène, où il a des amis et des parents. Henry était assez religieux. Il est donc peu probable qu'il aille à une autre église de saint. Il a probablement toujours le même nom qu'il avait depuis qu'il était enfant, Enrique.";
			link.l1 = "Ouais... La cueillette est maigre, mais au moins c'est mieux que rien.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Essaie de le trouver, Charles ! Peu de gens connaissent les racines espagnoles d'Henry, donc nous avons un petit avantage ici. Je vais réfléchir à comment convaincre Rumba de rejoindre ton équipage. La fille a du cran, elle n'a jamais servi sous les ordres de quelqu'un d'autre que son père.\nMais elle n'a ni navire ni équipage, et elle doit gagner sa vie. Bien sûr, je continuerai d'aider Gladys, comme je l'ai toujours fait, mais je ne pourrai pas garder Helen à Blueweld longtemps. Et tu trouveras un tel officier très utile. Sean lui a appris tout ce qu'il savait et l'a élevée comme un garçon.\nJe me sentirais mieux si elle était sous le commandement d'un capitaine comme toi.";
			link.l1 = "Rumba s'est révélée très digne. J'ai besoin de plus de gens comme elle dans mon équipage. Donc, si tu réussis à la convaincre, je ferai d'elle un officier. Mais d'abord, je veux comprendre qui elle est vraiment et pourquoi Jackman a besoin d'elle. Je crains que, contrairement à Donovan, il ne soit pas intéressé par ses charmes. Je vais donc essayer de trouver Hangman, bien que je ne puisse rien promettre.";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Eh bien, splendide. Prenez cette licence de la Compagnie néerlandaise des Indes occidentales pour trois mois. Écrivez votre nom ici, cela pourrait bien vous être utile dans vos recherches. En attendant, je réfléchirai à ce que vous avez dit concernant Levasseur et la Tortue.";
			link.l1 = "Merci mille fois ! Ce papier va m'être très utile. Dans ce cas, je pars pour Carthagène alors.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			DialogExit();
			GiveNationLicence(HOLLAND, 90);
			AddQuestRecord("Saga", "14");
			pchar.questTemp.Saga = "cartahena";//идем в Картахену
			pchar.quest.Saga_Gonsales.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales.win_condition.l1.location = "Cartahena_town";
			pchar.quest.Saga_Gonsales.function = "Saga_CreateGonsalesB";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			LocatorReloadEnterDisable("FortOrange_town", "reload6", true); // закрыть резиденцию Джекмана
			npchar.greeting = "svenson_3";
			
			AddQuestRecord("HelenDrinking", "1");
			pchar.questTemp.HelenDrinking.CanDrink = true;
			SetFunctionTimerConditionParam("HelenDrinking_NoVisit", 0, 0, 1, 24 - GetHour(), false);
			
			pchar.questTemp.Saga.HelenRelation = 0;
		break;
		
		case "saga_11":
			dialog.text = "Henry est mort ?  Attends, l'as-tu tué ?";
			link.l1 = "Ne me regarde pas avec ces yeux écarquillés ! Je n'y suis pour rien. Il est mort de lui-même, de sa conscience pourrie et de sa peur de Jackman. Le vieux pirate avait des problèmes de cœur et il n'avait plus longtemps à vivre. Voici ce que j'ai réussi à découvrir...";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "S'il te plaît, dis-moi !";
			link.l1 = "Il y a vingt ans, Henry devait remettre un coffre d'or au nom du Capitaine Boucher à la mère adoptive de sa fille biologique. Il n'y a absolument aucun doute que cette mère adoptive était Mme McArthur. À cette époque, elle portait le nom de Chandler et vivait à Belize. Mais les circonstances ont retenu Hangman à St. John's pendant un mois entier supplémentaire et quand il est enfin arrivé à Belize, c'était en ruines après un raid espagnol, et tante Gladys et Sean avaient déjà pris la route sous votre aile.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "";
			link.l1 = "Ils ont fait passer Hélène pour leur fille biologique et l'ont élevée comme la leur. Henry a perdu leur trace et s'est fait discret, conscient de la vengeance de Jackman, vivant depuis lors, ces vingt dernières années, dans la peur. Il s'avère que Jackman recherche la fille de son capitaine. Mais pourquoi, je ne sais pas.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "Peut-être qu'il exécute les ordres de quelqu'un...";
			link.l1 = "J'en doute. Qui pourrait lui donner des ordres ? Le Boucher est mort. Sa mort est confirmée par des documents officiels. Des dizaines, voire des centaines de personnes ont été témoins de sa mort.";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "Peut-être que cela ne concerne pas le père d'Helen. Peut-être que tout tourne autour de sa mère biologique. Je peux déjà deviner qui elle était, mais j'ai peur de l'admettre. Mais Gladys ! Comment a-t-elle pu garder ce secret pendant tant d'années sans même le révéler à son mari ! Sean McArthur m'en aurait sûrement parlé. Nous n'avons jamais eu de secrets que nous ne nous disions pas.";
			link.l1 = "Je vais avoir une conversation à cœur ouvert avec Gladys. Je pense que j'ai les moyens de la faire parler. À la prochaine, Jan !";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			DialogExit();
			pchar.questTemp.Saga = "gladis1";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_history";
			AddQuestRecord("Saga", "21");
		break;
		
		case "saga_17":
			dialog.text = "D'où as-tu obtenu ça !?";
			link.l1 = "Gladys me l'a donné. Elle a dit que c'était 'l'héritage de la mère d'Helen'. Elle ne connaît pas son nom. Quelque chose me dit que ce n'est pas un vulgaire bout de papier.";
			link.l1.go = "saga_18";
		break;
		
		case "saga_18":
			dialog.text = "Rappelle-toi quand je t'ai dit que j'avais une intuition sur qui était la vraie mère d'Helen ? Maintenant, j'en suis sûr. Elle s'appelait Beatrice Sharp. Elle était la fille biologique de mon maître et ami Nicholas Sharp, la sœur déclarée du fondateur de notre Fraternité, Blaze Sharp, et copropriétaire de l'Isla Tesoro. C'est ce morceau de carte que Jackman recherche.";
			link.l1 = "Eh bien, qu'en dites-vous ! Mais pourquoi aurait-il besoin de la moitié d'une carte de l'île ?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "L'île a été découverte par Nicolas Sharp. Il l'a nommée Isla Tesoro, l'a cartographiée et en a pris possession grâce à la Providence Island Company où il avait de bonnes connexions.\nNicolas a écrit dans son témoignage que l'île ne peut être héritée que par ceux qui produisent deux parties de la carte. Il l'a fait afin d'éviter toute discorde. Il a donné les parties à Beatrice et à son beau-fils Blaze avant de mourir tragiquement de la main des Espagnols.";
			link.l1 = "Eh bien, que le diable m'emporte ! Comme c'est étrange.";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "Tu as raison. Ce n'était pas la meilleure idée. Et un notaire rusé a ajouté que l'île appartiendra à la couronne anglaise si personne ne présente les deux parties de la carte dans l'année suivant la mort des héritiers.\nPersonne ne s'y attendait à l'époque. Et maintenant nous payons le prix de notre stupidité. Béatrice est morte il y a vingt ans. Toutes ces années ont passé et nous n'avons toujours aucune idée de l'emplacement de sa tombe avec sa partie de la carte. Blaze Sharp a été assassiné il n'y a pas longtemps. Sa partie a également disparu.\nSi personne ne présente la carte entière de l'Isla Tesoro aux autorités dans l'année, alors Sharptown sera réclamée par l'Angleterre. Ils enverront un gouverneur avec une garnison là-bas et les Frères seront terminés.";
			link.l1 = "Que suggères-tu que nous fassions ?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "Nous ne pouvons pas laisser cela se produire. J'ai besoin de vous, Charles, j'ai besoin que vous empêchiez une telle issue. Et je ne pourrai vous aider à éliminer Levasseur qu'après avoir pris le contrôle de l'Isla Tesoro et élu Shark Dodson comme nouveau chef des Frères de la Côte. Il est le plus digne d'entre nous. Je vous propose une alliance.\nEt, au fait, j'ai parlé à Helen. Elle a accepté de rejoindre votre équipage.";
			link.l1 = "Tu ne me laisses pas le choix, Jan. Je ne peux pas retourner en France sans restaurer l'honneur de ma famille. Et pour cela, je dois éliminer Levasseur avec ou sans ton aide. Les morts inutiles ne sont pas ce que je veux et j'espère que tu pourras trouver un moyen de prendre Tortuga sans trop de sang versé. Cependant, je dois admettre que j'aimerais éclaircir moi-même le passé brumeux entourant l'héritage de Sharps.";
			link.l1.go = "saga_22";
		break;
		
		case "saga_22":
			dialog.text = "C'est agréable d'entendre des pensées sensées ! Nous trouverons le bon moyen de prendre la Tortue. Je te le promets. Alors, on y va ?";
			link.l1 = "Allons-y ! Je repasserai un peu plus tard. Pour l'instant, réfléchis à par où commencer pour aborder le problème.";
			link.l1.go = "saga_23";
		break;
		
		case "saga_23":
			dialog.text = "Passez à nouveau dans deux ou trois jours. D'ici là, je pense que mon plan sera arrivé à son apogée. Et n'oubliez pas d'emmener Helen avec vous sur votre navire. La pauvre fille dépérit sans la mer. Elle sera une assistante fidèle et vous pourrez compter sur elle sans hésiter.";
			link.l1 = "D'accord, Jan. Je vais la chercher tout de suite.";
			link.l1.go = "saga_24";
		break;
		
		case "saga_24":
			DialogExit();
			pchar.questTemp.Saga = "helena1";
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);//закрыть выходы из города
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			AddQuestRecord("Saga", "23");
		break;
		
		case "saga_25":
			dialog.text = "Tout d'abord, tu dois trouver le Requin. Il voulait se débarrasser de Levasseur lui-même et je t'assure qu'il a des idées lumineuses. Bien sûr, nous pourrions aussi persuader Marcus d'accepter le leadership. Après tout, il est le gardien du Codex. Mais je doute qu'il puisse nous être d'une quelconque aide, il a délibérément limité tout contact avec Levasseur et Tortuga. Un homme de principes.\nJe n'ai aucune idée où se cachent Steven et ses hommes, mais sa frégate 'Fortune' a été vue à Puerto Principe. Peut-être que Zachary Marlow, également connu sous le nom de Pasteur Noir, peut nous indiquer où chercher le Requin. Ensuite, nous devons gagner le soutien des autres barons pour élire Dodson. Et pour cela, nous devons rassembler leurs éclats indiens - les votes. Le nouveau chef doit les avoir tous les cinq. C'est ce que le Code nous dit de faire au cas où le précédent chef serait mort.\nRidicule ! Il est temps de changer les lois, mais seul le nouveau chef peut le faire. Nous avons déjà mon vote. Je crois que le Pasteur Noir se fiche de qui est assis à Sharptown. J'espère que Jackman ne lui a pas parlé en premier. Nous devons aussi persuader à la fois Tyrex et Jacques Barbazon, qui se détestent. Mais tout cela est sans importance tant que nous ne savons pas ce qui est arrivé au Requin. Troisièmement, un jour, nous devrons tuer Jackman et le remplacer par quelqu'un d'autre. Il ne négociera pas avec nous.\nDommage que Hawk soit mort ! Les gens lui faisaient confiance et nous aurions pu utiliser sa parole. Nous ne trouverons pas de meilleur baron pour Maroon Town. Il est possible que Jackman ait quelque chose à voir avec le meurtre de Blaze, donc il est aussi la clé pour trouver la deuxième partie de la carte. Jacob ne fait confiance à personne et garde très probablement la partie de la carte dans sa cabine sur le 'Centurion'.\nLa famille de Hawk possédait autrefois la frégate, mais Jackman l'a revendiquée tout comme la baronnie de Hawk. Si nous trouvons la deuxième partie de la carte en possession de Jackman, ce serait un excellent argument pour l'élection de Steven. Surtout pour Marcus Tyrex, le gardien du Code, et son scrupule exagéré en termes d'honneur. Nous rendrons à Helen ses droits sur Isla Tesoro dès que nous aurons acquis les deux parties de la carte.\nNous devons être prudents cependant, Jackman ne restera pas inactif et ne te regardera pas simplement chercher.";
			link.l1 = "Eh bien... Je m'apprête à rendre visite au Pasteur Noir. Parle-moi de lui.";
			link.l1.go = "shark_hunt";
			pchar.questTemp.Saga = "baronsquests_1";
		break;
		
		case "shark_hunt":
			dialog.text = "Diable si je sais ce qui lui passe par la tête. Parfois, il ressemble à un véritable cinglé, mais néanmoins, je crois que c'est juste un jeu habile. De plus, ses hommes sont prêts à affronter le diable en personne pour leur bien-aimé Pasteur.\nIls ont établi une sorte de secte protestante proche de l'inquisition espagnole à Cuba. Alors ne commence même pas à parler de théologie là-bas, ils ne les approuveront pas.";
			link.l1 = "Je prendrai cela en compte...";
			link.l1.go = "shark_hunt_0";
		break;
		
		case "shark_hunt_0":
			dialog.text = "Et, "+pchar.name+": ne perds pas une minute de ton temps. Je suis sérieux. Souviens-toi de la clause dans le testament qui dit que si les héritiers ne réclament pas l'île dans un délai d'un an, alors Isla Tesoro ira à la couronne anglaise, n'est-ce pas ? Eh bien, le temps n'est pas en notre faveur en ce moment. Quand toi et moi nous sommes vus la dernière fois, il ne restait qu'environ onze mois avant que le temps ne soit écoulé.";
			link.l1 = "Je me souviens, Jan.  Tu as raison, le temps c'est de l'argent. Je m'en occupe !";
			link.l1.go = "shark_hunt_1";
		break;
		
		case "shark_hunt_1":
			DialogExit();
			AddQuestRecord("SharkHunt", "1");
			pchar.questTemp.Saga.SharkHunt = "begin";
			pchar.GenQuest.LigaAttack = "true"; // киллеры Лиги активированы
		break;
		
		case "shark_hunt_2":
			dialog.text = "Hm... Qu'est-ce que Zachary t'a dit ?";
			link.l1 = "Avant sa disparition, Shark est venu lui rendre visite et a laissé sa frégate à Zachary en gage d'une goélette avec de la nourriture, puis est parti quelque part au nord-ouest vers Cuba.";
			link.l1.go = "shark_hunt_3";
		break;
		
		case "shark_hunt_3":
			dialog.text = "C'est vraiment louche. Continue.";
			link.l1 = "Un mois plus tard, Dodson ne revint pas et le Pasteur, selon les termes de l'accord, prit la frégate pour lui-même et la vendit à bon prix à un certain Paterson. Quant à nos affaires, Zachary a mentionné que Shark aurait pu partir pour une légendaire Île de la Justice, supposément située quelque part non loin au nord-ouest de Cuba.";
			link.l1.go = "shark_hunt_4";
		break;
		
		case "shark_hunt_4":
			dialog.text = "J'ai entendu parler de l'Île de la Justice. On dit qu'il y a une île où blancs et noirs vivent paisiblement, ensemble en égaux. Des foutaises répandues par toutes sortes de rêveurs. Mais il est possible qu'une sorte de base de contrebandiers existe au Nord-Ouest. Leurs barques étaient régulièrement vues en haute mer il y a dix ans. Ils apportaient différents types de marchandises à Cuba en échange de nourriture.";
			link.l1 = "Des trésors pour de la nourriture ? Le Pasteur m'a également parlé des boucaniers expédiant du bœuf. C'est presque une contradiction ambulante.";
			link.l1.go = "shark_hunt_5";
		break;
		
		case "shark_hunt_5":
			dialog.text = "Ces commérages doivent avoir une source, ces barques de contrebandiers ou de flibustiers naviguaient vers cette région pour une raison. Je me souviens que le Requin m'a raconté des histoires sur sa jeunesse, il était une sorte d'esclave dans une étrange formation faite d'épaves de navires au milieu de la mer.\nPeut-être que c'est notre endroit? Aucune idée. Quoi qu'il en soit, le Pasteur a raison, il y a quelque chose là-bas, soit une base secrète, soit une île où le Requin pourrait être allé. Écoute, navigue vers Saint-Domingue et trouve un scientifique nommé Jose Dios.\nC'est un cartographe espagnol. Je l'ai une fois sauvé d'une racaille sale, je respecte les gens instruits. Il t'aidera, dis-lui juste mon nom. Va à Hispaniola, trouve Dios et parle-lui.\nIl connaît parfaitement la géographie de notre région et s'il ne peut pas t'aider - personne ne pourra.";
			link.l1 = "D'accord, Jan. Ça semble être un plan. J'y vais !";
			link.l1.go = "shark_hunt_6";
		break;
		
		case "shark_hunt_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "dios";
			AddQuestRecord("SharkHunt", "3");
		break;
		
		case "shark_hunt_7":
			dialog.text = "C'est bien dommage. J'espérais que José nous donnerait un coup de main.";
			link.l1 = "Je comptais là-dessus aussi, mais hélas. Eh bien, ne nous apitoyons pas sur notre sort. Je vais passer encore un peu de temps à réfléchir à cette affaire. Oui, Jan, dis-moi, comment est mort Hawk ?";
			link.l1.go = "baron_return";
		break;
		
		case "baron_return":
			dialog.text = "Personne n'a été témoin de sa mort, tout comme personne n'a vu son corps. Il a simplement disparu il y a plusieurs mois. Depuis, c'est comme avec Shark, ni vue ni connue. Mais contrairement à Steven, Nathan n'avait aucune raison de se cacher. C'est pour cette raison que tout le monde a supposé qu'il était mort dans la selva. Sans cela, ils n'auraient pas accepté d'élire Jackman à sa place.";
			link.l1 = "Que diable faisait Hawk dans la selva ?";
			link.l1.go = "baron_return_1";
		break;
		
		case "baron_return_1":
			dialog.text = "C'était ma faute, je suis un vieux fou ! Je l'avais persuadé de s'occuper des bandits nouvellement arrivés. Je n'ai aucune idée de qui ils sont et qui est leur chef. Normalement, je ne m'en soucierais pas, mais ils ont commencé à kidnapper des Miskitos amicaux. Leur chef de guerre Kumvana a menacé de déclarer le Sentier de Guerre et a demandé mon aide. Je n'avais pas d'autre choix que d'intervenir.\nHawk a débarqué avec une petite unité sur la Côte des Mosquitos, est tombé dans une embuscade parfaitement organisée et a ensuite été vaincu. On aurait dit que lui et ses hommes étaient attendus pour débarquer là-bas. Le corps de Hawk n'a pas été retrouvé parmi les autres dans la jungle.";
			link.l1 = "Tu as toutes sortes de manigances qui se passent sous ton nez ! Aucun des gars de Hawk n'a essayé de s'occuper des bandits ?";
			link.l1.go = "baron_return_2";
		break;
		
		case "baron_return_2":
			dialog.text = "Jackman a devancé tout le monde. Il s'est proclamé pour résoudre le problème au conseil des Frères et a pris la décision. Les Miskitos ont cessé de disparaître, mais les bandits sont restés là, se faisant relativement discrets.\nJackman a dit qu'ils ne retenaient en otage personne parmi ceux qui venaient les attaquer et qu'il n'y avait aucune raison pour les Frères de leur déclarer la guerre. Hawk les a attaqués le premier, donc selon nos lois, les bandits avaient le droit de se défendre. Tout le monde était d'accord. Tout le monde sauf...";
			link.l1 = "Tout le monde sauf qui ?";
			link.l1.go = "baron_return_3";
		break;
		
		case "baron_return_3":
			dialog.text = "Nathan avait une femme. Elle s'appelle Danielle Hawk et c'est une sacrée garce ! Je doute qu'elle se soit jamais remise de la perte de son capitaine, sans parler du fait qu'elle soupçonnait quelque chose depuis le début et a essayé de dissuader Hawk. Je me souviens qu'ils ont eu une énorme dispute à ce sujet, mais ce n'était rien d'inhabituel pour eux.";
			link.l1 = "Et où est Danielle maintenant ?";
			link.l1.go = "baron_return_4";
		break;
		
		case "baron_return_4":
			dialog.text = "Qui sait ! Jackman s'est assuré qu'elle quitte Maroon Town. Elle ne me rend pas visite. Nous ne nous sommes jamais aimées, elle est devenue encore plus garce au fil des ans, et maintenant elle doit vraiment me haïr, car elle pense probablement que je suis la cause de ses malheurs.\nPeut-être qu'elle cherche Hawk par elle-même, mais que peut faire une femme, même si elle porte un pantalon et un sabre ! D'ailleurs, elle a maîtrisé le sabre. Je ne recommande pas de la défier si vous la rencontrez. Oui, et il n'y a pas de sens à parler aux bandits non plus. Ils ont monté un camp très impressionnant là-bas et sont armés jusqu'aux dents.\nOn dirait qu'ils sont d'anciens militaires et connaissent bien leur affaire. Ils n'autorisent personne sur leur territoire. On dit que les Espagnols y extrayaient de l'or. Mais l'or s'est épuisé et ils ont abandonné la mine. Je n'ai aucune idée de ce que ces salauds font là-bas.";
			link.l1 = "Eh bien, puisque personne n'a vu le cadavre de Hawk, l'espoir de le retrouver vivant persiste. Dieu sait, nous pourrions même le ramener à la baronnie.";
			link.l1.go = "baron_return_5";
		break;
		
		case "baron_return_5":
			dialog.text = "Ouais, que dirais-tu de ça. Tiens, prends cette lettre. Quand tu rencontreras Steve Dodson, remets-la-lui immédiatement. Le contenu de cette lettre garantira ta sécurité. Eh bien, juste au cas où.";
			link.l1 = "Merci, Jan. Je veillerai à le faire !";
			link.l1.go = "baron_return_6";
		break;
		
		case "baron_return_6":
			DialogExit();
			GiveItem2Character(pchar, "letter_svenson");
			AddQuestRecord("BaronReturn", "1");
			pchar.questTemp.Saga.BaronReturn = "begin";
			pchar.quest.Saga_DannyMeeting.win_condition.l1 = "location";
			pchar.quest.Saga_DannyMeeting.win_condition.l1.location = "SantaCatalina_town";
			pchar.quest.Saga_DannyMeeting.function = "Saga_DannyMeeting";
		break;
		
		case "return_LSC":
			dialog.text = "Eh bien, pourquoi cette mine triste. Tu es fatigué? Peut-être un verre de rhum pour toi?";
			link.l1 = "Je ne dirais pas non...";
			link.l1.go = "return_LSC_1";
		break;
		
		case "return_LSC_1":
			LAi_AlcoholSetDrunk(pchar, 51, 5600);
			dialog.text = "Tiens, prends un verre. Maintenant parle.";
			link.l1 = "(buvant) Ah, c'est bien mieux... Eh bien, Jan, toi et le Pasteur Noir aviez raison tous les deux. L'île de la Justice existe. J'y étais.";
			link.l1.go = "return_LSC_2";
		break;
		
		case "return_LSC_2":
			dialog.text = "Je t'avais dit qu'il devait y avoir une base de contrebande là-bas !";
			link.l1 = "Il n'y a en fait aucune base de quelque sorte que ce soit. Et les rumeurs autour des Caraïbes ne mentaient pas. Noirs et blancs vivent vraiment ensemble là-bas, sûrement pas nécessairement en paix, mais plutôt comme chiens et chats. Et l'île elle-même se compose d'une multitude innombrable d'épaves.";
			link.l1.go = "return_LSC_3";
		break;
		
		case "return_LSC_3":
			dialog.text = "Je n'y crois pas ! Jose Dios sera très intéressé par votre histoire, j'en suis sûr. Rendez-lui visite un jour, au fait.";
			link.l1 = "Je lui rendrai visite plus tard. Ce n'est pas le meilleur moment pour ça maintenant. J'ai des affaires plus urgentes à régler pour le moment. J'ai trouvé Nathaniel Hawk sur l'île.";
			link.l1.go = "return_LSC_4";
		break;
		
		case "return_LSC_4":
			dialog.text = "Vous avez trouvé Nathan ? C'est remarquable ! Comment va-t-il ?";
			link.l1 = "Eh bien... Il est malade, constamment ivre, et profondément déprimé.";
			link.l1.go = "return_LSC_5";
		break;
		
		case "return_LSC_5":
			dialog.text = "Sacré nom d'un chien, c'est décourageant. Où est-il ? Sur ton navire ?";
			link.l1 = "Non, il est sur son propre navire. Sur l'île.";
			link.l1.go = "return_LSC_6";
		break;
		
		case "return_LSC_6":
			dialog.text = "Quoi, tu ne l'as pas amené ici ? Pourquoi ?";
			link.l1 = "Parce qu'il n'y avait rien pour l'affronter. J'ai fait mon chemin vers l'île sans navire.";
			link.l1.go = "return_LSC_7";
		break;
		
		case "return_LSC_7":
			dialog.text = "Sacrebleu, "+pchar.name+", tu as à peine bu un verre de rhum et tu parles du charabia comme si tu t'étais saoulé jusqu'à l'oubli. Quoi, as-tu traversé les Caraïbes à la nage? Ou bien t'es-tu attaché des tortues aux pieds?";
			link.l1 = "Non, je n'ai pas nagé. Jan, je suis arrivé sur l'île directement depuis la jungle du continent, tout comme Nathan, à travers une idole magique indienne. J'ai déjà raconté cette histoire à tant de gens et je suis fatigué de prouver que je n'ai pas perdu la tête, alors tout ce que j'ai à dire, c'est : crois-moi, d'accord !?";
			link.l1.go = "return_LSC_8";
		break;
		
		case "return_LSC_8":
			dialog.text = "Idole indienne ?";
			link.l1 = "Il existe au moins trois idoles dans les Caraïbes connues sous le nom de statues de Kukulcan : une près du village Miskito de West Main, une au fond des eaux peu profondes de l'île de la Justice, et une autre au village caribéen de la Dominique. Ces idoles, avec l'aide de la magie indienne, sont capables de transférer instantanément les êtres humains à travers le temps et l'espace.";
			link.l1.go = "return_LSC_9";
		break;
		
		case "return_LSC_9":
			dialog.text = "";
			link.l1 = "J'ai traversé les trois statues en cercle et je suis sorti exactement là où j'ai commencé mon voyage dans le village Miskito. Si tu ne me crois pas, je peux appeler Danielle. Elle a tout vu de ses propres yeux !";
			link.l1.go = "return_LSC_10";
		break;
		
		case "return_LSC_10":
			dialog.text = "Danielle ? La femme de Hawk ? Elle était avec vous ?";
			link.l1 = "En partie, oui. Elle m'a trouvé elle-même à Blueweld et m'a amené au village Miskito, à un chaman qui m'a envoyé à la statue magique. Maintenant, elle sert comme l'un de mes officiers, temporairement bien sûr.";
			link.l1.go = "return_LSC_11";
		break;
		
		case "return_LSC_11":
			dialog.text = "Je suis absolument sidéré, "+pchar.name+"! C'est comme disent les Anglais. Tu as été nourri avec une cuillère en argent. T'as vraiment une sacrée veine, fils de chien! Bon, je vais te croire, même si c'est dur. Mais l'affaire avec Nathan reste la même, il faut l'aider.";
			link.l1 = "C'est ce que je vais faire. Je prépare une expédition vers l'île de la Justice. Maintenant, j'ai tout ce qu'il me faut : les coordonnées de l'île et les instructions de navigation.";
			link.l1.go = "return_LSC_12";
		break;
		
		case "return_LSC_12":
			dialog.text = "Fantastique. Puis-je faire quelque chose pour vous aider ?";
			link.l1 = "Non, merci. Mais j'ai omis un petit détail. En plus de Nathan, j'ai aussi trouvé Shark Dodson sur l'île.";
			link.l1.go = "return_LSC_13";
		break;
		
		case "return_LSC_13":
			dialog.text = "Alors, il y est vraiment allé ! Eh bien, "+pchar.name+", tu as fait un excellent travail. Comment va Dodson là-bas ? Tu as bien sûr parlé avec lui, n'est-ce pas ?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				link.l1 = "Je n'ai pas seulement parlé avec lui. Nous sommes aussi devenus amis. C'est lui qui m'a donné les instructions de navigation dont j'aurai besoin pour retourner sur l'île. Steven a accepté d'échanger la cabine de son navire de guerre contre la résidence de Sharptown.";
				link.l1.go = "return_LSC_14";
			}
			else
			{
				link.l1 = "Nous avons parlé, oui, mais au final cela s'est avéré inutile. Steven a été tué pendant que je séjournais sur l'île, lorsqu'un complot, organisé par son maître d'équipage, Chad Kapper, a été mis en action.";
				link.l1.go = "return_LSC_17";
			}
		break;
		
		case "return_LSC_14":
			dialog.text = "Ha ! Et comment le Requin a-t-il réussi à devenir capitaine d'un navire de guerre ?";
			link.l1 = "Le navire est dans un 'calme' perpétuel depuis plus d'un demi-siècle. Il est piégé avec son équipage sur l'île. C'est pourquoi il ne s'est pas montré dans les Caraïbes depuis si longtemps. Quoi qu'il en soit, je le ramènerai bientôt ici et il vous racontera lui-même ses aventures.";
			link.l1.go = "return_LSC_15";
		break;
		
		case "return_LSC_15":
			dialog.text = "Je ne peux pas attendre ça ! Maintenant, les choses commencent à s'améliorer. Nous venons de devenir plus puissants, "+pchar.name+" Quand comptez-vous repartir pour l'île ?";
			link.l1 = "À l'instant. Je suis juste entré ici pour une minute pour te parler de la nouvelle, pendant que Danielle se prépare pour l'expédition. Elle meurt d'envie de voir son Nathan. Et tu sais quoi, Jan, elle n'est pas si garce que ça.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_16":
			dialog.text = "Oui ? Eh bien, peut-être que je ne me suis pas trompé sur elle. Très bien, "+pchar.name+", Je ne vais pas te retenir plus longtemps. Va et que la chance soit avec toi ! J'attendrai avec impatience ton retour.";
			link.l1 = "À plus tard, Jan.";
			link.l1.go = "return_LSC_19";
		break;
		
		case "return_LSC_17":
			dialog.text = "Chad Kapper ? Putain, je connaissais ce gaillard. Il a tué Steven ? Ce salaud...";
			link.l1 = "Kapper est mort. Mais nous ne pouvons pas ramener Steven, alors nous devons réfléchir à une manière de continuer à organiser notre politique.";
			link.l1.go = "return_LSC_18";
		break;
		
		case "return_LSC_18":
			dialog.text = "Hah ! C'est bien dommage... Que reste-t-il à réfléchir ? Nous devrons simplement convaincre Tyrex de prendre la tête de la Confrérie. De plus, après Blaze, Tyrex, en tant que gardien du Code, est notre figure la plus respectable. Mais d'abord, nous devons ramener Hawk pour avoir au moins un atout dans notre manche. Quand pars-tu pour l'Île ?";
			link.l1 = "Tout de suite. Je suis juste venu ici pour te parler des nouvelles, pendant que Danielle prépare l'expédition. Elle meurt d'envie de revoir son Nathan. Et tu sais quoi, Jan, elle n'est pas si garce que ça.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_19":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "return_LSC";
			// LSC ждёт своего героя!
			i = FindIsland("LostShipsCity");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			pchar.quest.return_LSC.win_condition.l1 = "location";
			pchar.quest.return_LSC.win_condition.l1.location = "LostShipsCity";
			pchar.quest.return_LSC.function = "LSC_ReturnCheckShips"; // проверка типов кораблей
			pchar.quest.return_LSC_attack.win_condition.l1 = "location";
			pchar.quest.return_LSC_attack.win_condition.l1.location = "Beliz";
			pchar.quest.return_LSC_attack.function = "LSC_ReturnJackmanAttack"; // атака наймитов Джекмана
			pchar.quest.return_LSC_main.win_condition.l1 = "Ship_location";
			pchar.quest.return_LSC_main.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.return_LSC_main.function = "LSC_ReturnMain"; // основная функция возвращения
		break;
		
		case "nathaniel":
			dialog.text = "Comment va-t-il ? Vous avez dit qu'il ne se sentait pas bien.";
			link.l1 = "Oui, c'est exactement ça. Je vais l'emmener avec moi pour être soigné dans le village Miskito par Œil de Serpent, le chaman.";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "Alors pas de temps à perdre ! Dépêche-toi, "+pchar.name+" ! Dès que vous livrez Nathan à votre chaman, revenez immédiatement vers moi.";
			link.l1 = "D'accord, Jan. Cela semble être un plan.";
			link.l1.go = "exit";
			npchar.quest.shamane = "true";
		break;
		
		case "nathaniel_2":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				if (CheckAttribute(npchar, "quest.shark")) //и на месте
				{
					dialog.text = "Très bien. Steven est déjà passé me voir. Maintenant, nous pouvons enfin continuer à discuter de nos plans.";
					link.l1 = "Je suis tout ouïe, Jan.";
					link.l1.go = "barbazon";
				}
				else
				{
					dialog.text = "C'est bien sûr agréable, mais pourquoi Dodson n'est-il pas encore venu me voir ? Quoi, l'as-tu laissé sur l'île ?";
					link.l1 = "Hm... J'étais pressé d'amener Nathan à l'Oeil de Serpent...";
					link.l1.go = "nathaniel_wait";
				}
			}
			else
			{
				dialog.text = "Très bien. Mon cœur pleure pour Shark. Mais c'est la vie, donc Tyrex prendra sa place. Eh bien, maintenant nous pouvons enfin continuer à discuter de nos plans.";
				link.l1 = "Je suis tout ouïe, Jan.";
				link.l1.go = "barbazon";
			}
		break;
		
		case "nathaniel_wait":
			dialog.text = "... et tu as oublié de prendre Requin ? Je n'arrive pas à le croire, "+pchar.name+"Livrez Steven à Blueweld maintenant ! M'entendez-vous ? Allez !";
			link.l1 = "Calme-toi, Jan. Je m'occuperai de tout.";
			link.l1.go = "exit";
			NextDiag.TempNode = "nathaniel_wait_1";
		break;
		
		case "nathaniel_wait_1":
			if (CheckAttribute(npchar, "quest.shark"))
			{
				dialog.text = "Steven est passé me voir. Maintenant, nous pouvons enfin continuer à discuter de nos plans.";
				link.l1 = "Je suis tout ouïe, Jan.";
				link.l1.go = "barbazon";
			}
			else
			{
				dialog.text = "Oh, "+pchar.name+"... Il me semble que tu as bu trop de rhum dernièrement. Tu vois, cela ne finit jamais bien. D'abord, tes mains commencent à trembler, puis tu commences à perdre la mémoire, et ensuite tu reçois une marque noire...";
				link.l1 = "J'ai compris, Jan. Je pars chercher Steven tout de suite !";
				link.l1.go = "exit";
				NextDiag.TempNode = "nathaniel_wait_1";
			}
		break;
		
		case "barbazon":
			dialog.text = "Le Pasteur Noir a été très clair, il n'est intéressé que par ce livre théologique. J'ai envoyé mes hommes à sa recherche, peut-être que quelqu'un le trouvera. Marcus Tyrex n'est pas un problème, nous n'aurons aucun mal à le persuader. Jackman a quitté Maroon Town peu après ta visite. Il a navigué quelque part sur le 'Centurion', la frégate des Hawks.\nIl ne reste que Barbazon - il est aussi connu sous le nom de Jacques le Gentilhomme. Nous devons trouver un moyen de le faire coopérer avec nous. Je ne suis pas encore sûr de comment procéder. Mais une chose est évidente - tu devrais lui rendre visite.";
			link.l1 = "Parle-moi de Barbazon."; // Addon 2016-1 Jason пиратская линейка патч 17/1
			link.l1.go = "barbazon_1";
		break;
		
		case "barbazon_1":
			dialog.text = "Type secret. Faisant semblant d'être pauvre, pourtant il est peut-être l'homme le plus riche des Caraïbes. Il contrôle toutes les opérations de contrebande de l'Est. Si ce n'était pas pour Marcus qui lui tient tête, il régnerait sur tout le trafic de contrebande des Îles du Vent. Tyrex est comme un os dans sa gorge. \nIls se querellent toujours au conseil, mais Barbazon n'a pas les tripes de déclarer une guerre ouverte. Peut-être qu'il a vraiment été un pirate de Dunkerque comme il le prétend, mais maintenant il me rappelle plus un usurier.";
			link.l1 = "Comment diable a-t-il été élu baron ?";
			link.l1.go = "barbazon_2";
		break;
		
		case "barbazon_2":
			dialog.text = "L'or, mon ami, règne sur tout et partout, celui qui a l'or fait les lois. De plus, Barbazon est vraiment doué pour inventer toutes sortes d'opérations lucratives et illégales. Il n'y participe pas lui-même, mais il prend toujours sa part. Ainsi, il a constamment autour de lui une foule de vauriens courageux, mais pour la plupart faibles d'esprit. Ils mourraient tous de faim ou finiraient sur l'échafaud sans lui.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				link.l1 = "Il me rappelle Marcus... Jan, le truc, c'est que... je n'ai aucune idée de comment aborder Barbazon. Il y a un problème dont tu n'es pas au courant.";
				link.l1.go = "barbazon_5";
			}
			else
			{
				link.l1 = "Comment puis-je me rendre à Barbazon ?";
				link.l1.go = "barbazon_3";
			}
		break;
		
		case "barbazon_3":
			dialog.text = "Fais simplement semblant d'être l'un de ces imbéciles qui ont besoin d'un tuyau pour un gros boulot. Ne pense même pas à essayer de le tromper sur sa part. Barbazon le Bienveillant ne pardonne pas.";
			link.l1 = "Ça va sans dire. Je ne m'implique pas avec lui pour mon propre intérêt. Quoi qu'il en soit, il est temps de lui rendre visite.";
			link.l1.go = "barbazon_4";
		break;
		
		case "barbazon_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "1");
			pchar.questTemp.Saga.BarbTemptation = "begin";
			pchar.questTemp.Saga.BaronReturn = "barbazon";
			NextDiag.CurrentNode = "First time";
			// тут вычищаем квестовый мусор от LSC
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
			if (CheckCharacterItem(pchar, "letter_chad_1")) RemoveItems(pchar, "letter_chad_1", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "barbazon_5":
			dialog.text = "Vraiment ? Vas-y, tire.";
			link.l1 = "Vous avez déjà entendu parler de Charlie Prince ?"; 
			link.l1.go = "barbazon_6";
		break;
		
		case "barbazon_6":
			dialog.text = "Oui, j'ai entendu les rumeurs. Ce gars travaillait pour Marcus Tyrex il n'y a pas si longtemps. Il a fait pas mal de choses en très peu de temps, s'est fait un nom en pillant Carthagène. Et alors ?";
			link.l1 = "Ce gars, c'est moi. Je suis Charlie Prince. Je l'étais. Vous voyez maintenant ?"; 
			link.l1.go = "barbazon_7";
		break;
		
		case "barbazon_7":
			dialog.text = "Nom d'un chien ! Vous êtes Charlie Prince ? Quel retournement de situation ! "+pchar.name+", je suis impressionné ! Maintenant, je vois d'où vient votre prise... Mais quel rapport a Barbazon avec tout cela ?";
			link.l1 = "Que dirais-tu que Prince rende visite à Barbazon, Jan ?.."; 
			link.l1.go = "barbazon_8";
		break;
		
		case "barbazon_8":
			dialog.text = "Hm... Je comprends cela. Vous avez déjà eu affaire avec lui auparavant ?";
			link.l1 = "Pas exactement. Un de ses sbires du nom d'Ignacio Marco a essayé de me foutre en l'air sur ordre direct de Barbazon. C'était une partie de leur petite guerre."; 
			link.l1.go = "barbazon_9";
		break;
		
		case "barbazon_9":
			dialog.text = "A-t-il vu ton visage ? Lui as-tu fait des présentations ?";
			link.l1 = "Non."; 
			link.l1.go = "barbazon_10";
		break;
		
		case "barbazon_10":
			dialog.text = "Je ne vois donc pas de problème ici. J'ai aussi entendu parler du corsaire Charlie Prince, mais je ne savais pas que c'était vous avant que vous ne me le disiez.";
			link.l1 = "Tu penses que Barbazon ne verra pas clair à travers moi ?"; 
			link.l1.go = "barbazon_11";
		break;
		
		case "barbazon_11":
			dialog.text = "Comment aurait-il pu s'il n'a jamais vu ton visage ? Tout ce qu'il a fait, c'est donner des ordres pour se débarrasser d'un des employés de Marcus.";
			link.l1 = "Hm... Vous pourriez avoir raison sur ce point."; 
			link.l1.go = "barbazon_12";
		break;
		
		case "barbazon_12":
			dialog.text = "Pas moyen de s'en sortir sans Barbazon. Va le voir mais sois prudent. Fuis s'il te reconnaît, nous réfléchirons à une autre approche dans ce cas.";
			link.l1 = "D'accord. Je devrais y aller maintenant. J'attendais avec impatience de rencontrer ce salaud."; 
			link.l1.go = "barbazon_13";
		break;
		
		case "barbazon_13":
			dialog.text = "Ne fais pas l'imbécile et n'essaie pas d'entuber Jacques. Il ne pardonne jamais. Agis comme un idiot avide de se faire de l'argent facile.";
			link.l1 = "Il semble que ce soit mon rôle préféré... Adieu, Jan!"; 
			link.l1.go = "barbazon_4";
		break;
		
		case "saga_26":
			dialog.text = "Oui. Le chaman indien a fait tout son possible, Hawk est comme neuf. Il est censé être déjà à Maroon Town avec Dannie, donc si tu veux, vas-y et dis bonjour. Ils seraient ravis de te voir.";
			link.l1 = "Je passerai certainement voir comment ils vont... Jan, j'ai pu trouver la deuxième partie de la carte de Sharp ! Elle était dans la cabine de Jackman. Maintenant, nous n'aurons aucun problème à prouver les droits d'Helen sur Isla Tesoro.";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			dialog.text = "Génial, montre-moi ça.\nNous avions raison, c'est Jacob qui a tué Blaze. Maintenant, la tache sur le nom de Shark doit être effacée pour de bon. Quant aux preuves, c'est une question plus délicate. Et cela doit être abordé seulement après une réflexion très approfondie.";
			link.l1 = "Une autre chose, Jan. Jette un œil à cette note. Elle était aussi parmi les affaires de Jackman.";
			link.l1.go = "saga_28";
		break;
		
		case "saga_28":
			RemoveItems(pchar, "letter_parol", 1); // удалить записку
			dialog.text = "Eh bien, voyons voir... Ha, alors c'est pour cela que les bandits ont écouté Jackman et ont cessé d'enlever les Miskitos ! Ça ne pouvait pas se passer autrement ! Ce salaud avait tout planifié et avait plusieurs longueurs d'avance.";
			link.l1 = "Ouais, et je vois aussi pourquoi les hommes de Hawk ont été massacrés. Mais il y a deux choses que je ne comprends pas : d'abord, que font les complices de Jackman dans la mine et ensuite, pourquoi réagissez-vous si calmement au fait que tout ce bazar se passe sur votre territoire ?";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "J'ai honte... Tu as raison. Jackman est vraiment devenu incontrôlable. Et ses sbires n'ont rien à faire dans mon domaine. Il semble que le moment est venu de rappeler aux Caraïbes à qui ils ont affaire.";
			link.l1 = "Qu'as-tu en tête, Jan ?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_30":
			dialog.text = "Réveiller le passé... J'ai l'intention d'organiser une expédition punitive et d'éliminer chaque bandit aux mines. Maintenant, nous avons la preuve qu'ils sont les hommes de Jackman et je suis obligé de débarrasser mes territoires de cette racaille.\n"+pchar.name+", tu as fait un excellent travail. Il est temps que je me bouge le cul. Repose-toi pour l'instant. Va rendre visite aux Hawks. Reviens dans dix jours !";
			link.l1 = "D'accord, Jan. Je le ferai. Je serai de retour exactement au moment que tu as dit !";
			link.l1.go = "saga_31";
			link.l2 = "Ha ! Je veux aussi participer à cette croisade. Pourquoi donc avez-vous décidé de me mettre en congé ?";
			link.l2.go = "saga_31_1";
		break;
		
		case "saga_31_1":
			dialog.text = "Pardonne-moi, vieux compère. Je pensais juste qu'il était enfin temps pour moi de travailler un peu et pour toi de te reposer. Mais si tel est ton désir, je serais plus qu'heureux ! Affrontons la tempête ensemble ! Et tout ce que nous trouverons dans la mine, nous le partagerons équitablement entre nos équipages, comme écrit dans les lois des Frères.";
			link.l1 = "Marché conclu, Jan ! Quand partons-nous ?";
			link.l1.go = "saga_31_2";
		break;
		
		case "saga_31_2":
			dialog.text = "Venez avec vos gens à la Côte des Mosquitos dans trois jours. J'aurai rassemblé mon équipage d'ici là et je serai déjà prêt, vous attendant. Ne soyez pas en retard !";
			link.l1 = "D'accord, Diable des Forêts. J'ai hâte de me battre dos à dos avec toi ! À bientôt !";
			link.l1.go = "saga_31";
			npchar.quest.mine_tw = "true";
		break;
		
		case "saga_31": 
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if (CheckAttribute(npchar, "quest.mine_tw"))
			{
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1 = "location";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1.location = "Shore53";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2 = "Timer";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.hour  = sti(GetTime());
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.function = "Saga_MineBanditsPrepareAttack";
				SetFunctionTimerCondition("Saga_MineBanditsAttackOver", 0, 0, 4, false); // таймер
			}
			else SetFunctionTimerCondition("Saga_MineBanditsDestroyed", 0, 0, 10, false); // таймер
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
		break;
		
		case "saga_32a":
			dialog.text = "Excellent. J'ai déniché quelque chose à propos du mystérieux propriétaire de la mine, Lawrence Beltrope.";
			link.l1 = "Alors, qui est cet oiseau?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_32":
			dialog.text = "Je l'ai extorqué aux sbires de Jackman dans la mine. Ils se sont révélés être des durs à cuire, mais mes gars non plus ne sont pas nés de la dernière pluie. En plus de ça, nous avons pu endormir leur vigilance après leur avoir donné le mot de passe de la note que tu as trouvée. Nous avons pénétré dans la mine et nous leur avons offert un départ en fanfare.";
			link.l1 = "Tu as pris la mine ? Exceptionnel !";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "Que cela serve de leçon à quiconque pense que le Diable des Forêts est rouillé. J'ai vraiment trop flemmardé ces dernières années et voyez ce qui est arrivé ? Jackman déroulait son plan maléfique juste sous mon nez !";
			link.l1 = "Qu'as-tu vu dans cette mine ? Parle-moi de cela !";
			link.l1.go = "saga_34";
		break;
		
		case "saga_34":
			dialog.text = "La mine a été abandonnée par les Espagnols pour de bon, cependant Lawrence Beltrope de Port Royal l'a achetée pour une bouchée de pain et a secrètement continué l'exploitation. Apparemment, les Espagnols ont laissé le puits trop tôt, car bien que nous n'ayons pas trouvé d'or nous-mêmes, nous avons trouvé plusieurs esclaves qui ont affirmé qu'il y avait de l'or à découvrir jusqu'à très récemment.";
			link.l1 = "Lawrence Beltrope ? Jamais entendu parler de lui. Qui est-ce ?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_35":
			dialog.text = "C'est un autochtone local, le fils de Thomas Beltrope, autrefois frère juré de Nicholas Sharp et corsaire de la Providence Island Company. Je connaissais très bien Thomas moi-même. Il y a un an, Lawrence est revenu aux Caraïbes. Il s'avère que Jackman travaillait pour lui. Gardez cela à l'esprit et restez vigilant !";
			link.l1 = "Donc le mystérieux 'patron' de Jackman, mentionné dans cette lettre, est Lawrence Beltrope... D'accord, je me souviendrai de ce nom.";
			link.l1.go = "saga_36";
		break;
		
		case "saga_36":
			dialog.text = "Une chose de plus. Je me souviens de quelque chose d'étrange. Blaze a mentionné une fois une mine d'or espagnole abandonnée et qu'il allait investir son or dans Sharptown. Mais la carte de la mine a disparu après que sa sœur se soit enfuie avec le capitaine Boucher. Peut-être parlait-il de notre mine ?\nQuoi qu'il en soit, c'était il y a trop longtemps et cela ne change pas grand-chose... Vous et moi devrions nous occuper du Conseil. As-tu les cinq fragments ?";
			link.l1 = "Oui. Ces quatre-là : Nathaniel, Tyrex, Marlow et Barbazon. Tous ont donné leur accord.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			sTemp = "Shark";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			dialog.text = "Formidable. Je suis sûr qu'il n'y aura aucun problème pour élire "+sTemp+"en tant que chef des Frères de la Côte. Je vais immédiatement m'atteler à convoquer une réunion du Conseil.";
			link.l1 = "Alors Jan, pouvons-nous considérer que tous les problèmes sont sous contrôle pour l'instant ? Nathaniel est à Maroon Town, Jackman est mort, et la Confrérie a maintenant un nouveau chef... Peut-être est-il temps de revenir à notre point de départ, c'est-à-dire prendre la Tortue ?";
			link.l1.go = "saga_38";
		break;
		
		case "saga_38":
			dialog.text = "Je me souviens, "+pchar.name+", mais nous devons patienter un peu. En plus de cela, le temps pour régler l'héritage de Sharp s'épuise et ce problème, comme vous le savez, doit être sérieusement traité.";
			link.l1 = "Quel est le problème avec l'héritage ? J'ai les deux parties de la carte. Tout ce que nous avons à faire, c'est les présenter et c'est tout...";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = ""+pchar.name+", je vous assure qu'ils ne donnent pas simplement des îles aux gens de nos jours. Même aux héritiers légitimes avec chaque paragraphe du testament rempli. Les autorités anglaises veulent ardemment cette île, je suis bien conscient de cela.\nJe ne pense pas que le colonel Doyle restera les bras croisés pendant que nous prenons l'île qu'il considère déjà comme propriété anglaise. De plus, vous et moi devrions rester dans l'ombre.";
			link.l1 = "Et que suggérez-vous ?";
			link.l1.go = "saga_40";
		break;
		
		case "saga_40":
			dialog.text = "Allez à Port Royal et trouvez un homme du nom d'Albert Loxley. C'est le meilleur avocat de toute la Caraïbe. Il est devenu très habile dans les affaires louches de toutes sortes, donc il prendra n'importe quel type de travail si on lui offre des honoraires exorbitants. Il a un appétit royal, mais il en vaut la peine.";
			link.l1 = "Tu penses que le testament de Sharp pourrait contenir des chausse-trappes?";
			link.l1.go = "saga_41";
		break;
		
		case "saga_41":
			dialog.text = "Je ne le pense pas seulement, j'en suis sûr. As-tu déjà eu affaire aux fonctionnaires ? Sache que s'ils veulent quelque chose de toi, ils te tireront l'âme, pointeront ton nez sur une virgule mal placée, interpréteront tout à leur guise et te laisseront aussi nu qu'un chaton aveugle.\nC'est pourquoi les avocats ont été créés. Ils combattent les fonctionnaires avec leurs propres armes - le verbiage, l'encre versée et la chicane. Par conséquent, tu devrais rendre visite à Loxley et l'engager pour protéger nos intérêts pendant que je m'occupe des élections.";
			link.l1 = "D'accord. Je pars pour Port Royal. Combien de temps faudra-t-il pour que le Conseil se réunisse et tienne une élection ?";
			link.l1.go = "saga_42";
		break;
		
		case "saga_42":
			dialog.text = "Dix jours. Donc ne te fatigue pas à me chercher à Blueweld avant.";
			link.l1 = "Compris. Eh bien, Jan. Dans ce cas, à tout à l'heure !";
			link.l1.go = "saga_43";
		break;
		
		case "saga_43":
			DialogExit();
			AddQuestRecord("Testament", "1");
			pchar.questTemp.Saga = "loxly"; // обновляем флаг
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			SetFunctionTimerCondition("Saga_GoldForLoxly", 0, 0, 10, false); // таймер
		break;
		
		case "saga_44":
			sTemp = "Steven Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = ""+sTemp+"envoie ses salutations les plus chaleureuses. Il sera toujours heureux de vous voir dans sa résidence sur Isla Tesoro. Allez lui rendre visite, si l'occasion se présente.";
			link.l1 = "Pour s'assurer "+sTemp+"ne quittera pas sa nouvelle résidence, toi et moi, Jan, avons un peu de travail devant nous.";
			link.l1.go = "saga_45";
		break;
		
		case "saga_45":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "Je suppose que vous avez déjà rendu visite à Loxley...";
			link.l1 = "Oui, je l'ai fait. Il prend notre affaire, mais il a exigé une pile d'or pour ses services. "+sTemp+"des doublons d'avance. À l'avance ! Et nous devrons aussi lui payer encore plus, selon comment la preuve des droits d'Hélène se passera. La somme doublera ou triplera, comme il l'a dit.";
			link.l1.go = "saga_46";
		break;
		
		case "saga_46":
			dialog.text = "Ha ! Eh bien, je n'attendais pas moins d'un vieux filou comme lui. Il sent la proie de loin, tout comme une hyène. Bien sûr, nous parlons ici d'une île entière. C'est ridicule de penser qu'Albert ne demanderait pas quelques centaines. Donc, le montant total pourrait être quelque part autour de mille cinq cents pièces d'or...";
			link.l1 = "Jan, c'est une tonne d'argent !";
			link.l1.go = "saga_47";
		break;
		
		case "saga_47":
			dialog.text = "Je sais où tu veux en venir. Je suis d'accord que tu n'es pas un gorille stupide payant tout cela de ta propre poche. Mais malheureusement, pour le moment, je n'ai pas cette quantité d'or cachée. J'avais prévu de telles dépenses, mais l'intervention d'un misérable vaurien a tout gâché.";
			link.l1 = "De quoi parles-tu ?";
			link.l1.go = "saga_48";
		break;
		
		case "saga_48":
			dialog.text = "Écoute. Peut-être sais-tu déjà que notre colonie n'est qu'à moitié légale. Les Anglais maintiennent une garnison ici et nous leur fournissons de l'acajou à bon prix. Mais il existe un type de bois très lourd et durable - le Lignum Vitae, que tu devrais connaître sous le nom de bois de fer.\nIl est rare et difficile à travailler même avec de l'acier trempé. On dit qu'il y a longtemps les Maya-Itza fabriquaient leurs terribles massues avec. Tu ne peux pas acheter du bois de fer sur le marché ouvert et en contrebande cela coûte son poids en argent.\nLes hommes de Doyle viennent de temps en temps et achètent la totalité de la quantité que nous avons transformée, pour pas cher. Mais j'arrive toujours à en garder un peu pour mes besoins personnels.";
			link.l1 = "J'ai entendu parler de cet arbre. Ils disent que les balles de mousquet s'enfoncent dans son bois huileux comme du goudron ! Sa robustesse est suffisante pour en faire des engrenages pour des mécanismes en acier.";
			link.l1.go = "saga_49";
		break;
		
		case "saga_49":
			dialog.text = "Ils racontent des bobards à propos des engrenages, mais le reste est exact. Donc, en prévoyant les dépenses, j'ai préparé un grand lot de bois de fer, mais un salaud a vidé mon entrepôt il y a quelques jours. C'est quelqu'un de chez nous, je le sais. J'ai un soupçon, mais je ne peux pas en être sûr.";
			link.l1 = "Les rats doivent être écrasés ! Qui soupçonnez-vous ?";
			link.l1.go = "saga_50";
		break;
		
		case "saga_50":
			dialog.text = "Paul Molligan. Son 'Huitre' des Indes orientales a navigué vers la Barbade hier. Je n'ai pas eu la chance de vérifier ses cales. Mais il n'apporterait pas le bois de fer à Bridgetown de toute façon, lord Willoughby a des douaniers sérieux là-bas et le bois de fer est une matière première d'importance stratégique pour la marine anglaise.\nS'il a vraiment mon bois de fer, alors il le vendra avant d'arriver à Bridgetown. Si seulement tu pouvais intercepter Molligan et inspecter ses cales !..";
			link.l1 = "Tu dis qu'il est parti pour Bridgetown hier ? Tout n'est pas encore perdu. Je vais essayer de le rattraper.";
			link.l1.go = "saga_51";
		break;
		
		case "saga_51":
			dialog.text = "Tu sais quoi faire, si Molligan est le rat. Mais essaie d'apprendre d'abord le nom de son client. Ensuite, tu peux soit livrer la cargaison au client toi-même, soit me la retourner.\nAmène aussi l' 'Oyster' à Blueweld, c'est un bon navire, j'aimerais bien le prendre pour moi et le rééquiper selon mes besoins. Tu es autorisé à prendre ce que tu veux comme prix aussi... Et au cas où Molligan n'est pas le coupable... non, je suis sûr qu'il est le rat qui a volé mon bois-fer.";
			link.l1 = "Je ferai bon usage de mon temps !";
			link.l1.go = "saga_52";
		break;
		
		case "saga_52":
			dialog.text = "Si tu vends le bois de fer toi-même, mets de côté mille cinq cents doublons d'or pour Loxley et nous partagerons le reste en deux. Je peux te faire confiance pour ça, n'est-ce pas ?";
			link.l1 = "Bien sûr. Je ne suis pas un rat.";
			link.l1.go = "saga_53";
		break;
		
		case "saga_53":
			dialog.text = "Je n'ai aucun doute. Bonne chance, "+pchar.name+" ! J'espère qu'il te sourit cette fois-ci.";
			link.l1 = "Merci. À plus tard !";
			link.l1.go = "saga_54";
		break;
		
		case "saga_54":
			DialogExit();
			pchar.questTemp.Saga = "molligan"; // обновляем флаг
			AddQuestRecord("Testament", "3");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			Saga_CreateMolliganInWorld(); // ставим корабль Моллигана на карту
		break;
		
		case "saga_55":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Je le savais. Combien avait-il dans ses cales ?";
			link.l1 = "J'ai trouvé "+FindRussianQtyString(sti(npchar.quest.bakaut))+" sur l' 'Huître'.";
			link.l1.go = "saga_56";
		break;
		
		case "saga_56":
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp > 100)
			{
				dialog.text = "Ouah ! Je n'ai jamais eu autant dans mon entrepôt. Regarde qui a mis la main sur une fortune. Merci, "+pchar.name+", tu ne me déçois jamais. Je vais vendre le produit tout de suite, nous avons déjà un acheteur. J'aurai l'argent pour toi demain.";
				link.l1 = "D'accord. Je ne te distrairai plus alors. À demain.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 90 && iTemp < 101)
			{
				dialog.text = "Ouais, j'en ai eu ma claque. Sale rat ! Merci, "+pchar.name+", tu ne me laisses jamais tomber. Je vais vendre le produit tout de suite, nous avons déjà un acheteur. J'aurai l'argent pour toi demain.";
				link.l1 = "D'accord. Je ne te distrairai plus alors. À demain.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Il a probablement déjà réussi à vendre une partie de la cargaison à quelqu'un, car il aurait dû y en avoir plus. Mais ce n'est pas grave, nous avons récupéré la plupart. Merci, "+pchar.name+", je vendrai le produit immédiatement, nous avons déjà un acheteur. J'aurai l'argent pour toi demain.";
				link.l1 = "D'accord. Je ne te distrairai plus alors. À demain.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 50 && iTemp < 70)
			{
				dialog.text = "Bon sang, ce salaud a déjà réussi à vendre une bonne part de la cargaison... Ah, c'est dommage. Tant pis. Je vendrai ce que j'ai, j'ai déjà un acheteur. J'aurai l'argent demain.";
				link.l1 = "D'accord. Je ne te distrairai plus alors. À demain.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 20 && iTemp < 50)
			{
				dialog.text = "Nom de Dieu, c'est déplorable ! Ce salaud a déjà réussi à vendre plus de la moitié de la cargaison... Ah, c'est bien dommage. Tant pis. Je vendrai ce que j'ai, j'ai déjà trouvé un acheteur. J'aurai l'argent demain.";
				link.l1 = "D'accord. Je ne te distrairai pas davantage alors. À demain.";
				link.l1.go = "saga_oust";
				break;
			}
			dialog.text = "Mince alors, j'ai vraiment pas de bol. Il a presque tout vendu... Tiens, garde ce bois de fer pour toi,"+pchar.name+", fais ce que tu veux avec. Tu es mon seul espoir pour gagner de l'argent maintenant.";
			link.l1 = "Compris. Très bien, je vais chercher moi-même. Ce n'est pas ma première aventure... Adieu, Jan.";
			link.l1.go = "saga_oust";
		break;
		
		case "saga_oust":
			if (CheckAttribute(npchar, "quest.bakaut"))
			{
				if (sti(npchar.quest.bakaut) < 20) DeleteAttribute(npchar, "quest.bakaut");
				else 
				{
					SaveCurrentNpcQuestDateParam(npchar, "bakaut_date");
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(npchar.quest.bakaut));
				}
				pchar.questTemp.Saga = "removebakaut";
			}
			int iUst = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN && sld.ship.name == "Oyster") iUst = 1;
				}
			} // есть ли у нас Устрица
			dialog.text = "Attendez ! Avez-vous capturé l'«Huître» ?";
			if (iUst == 1)
			{
				link.l1 = "Oui. Elle est dans le port en ce moment. Je l'ai ancrée pour toi, comme tu l'as demandé.";
				link.l1.go = "saga_oust_yes";
			}
			else
			{	
				link.l1 = "Non. Le navire a été si gravement endommagé lors de la bataille que j'ai dû le couler.";
				link.l1.go = "saga_oust_no";
			}
		break;
		
		case "saga_oust_no":
			dialog.text = "Quel dommage. Mais c'est ainsi. À plus tard, "+pchar.name+" !";
			link.l1 = "Adieu, Jan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_oust_yes":
			dialog.text = "Remarquable ! Je vais gréer cette beauté comme elle le mérite. Et plus tard, tu pourras toujours l'emprunter un moment, comme convenu. Je pense qu'elle sera prête d'ici deux mois.";
			link.l1 = "D'accord. Un navire comme celui-ci pourrait vraiment être utile parfois... À plus tard, Jan !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_RemoveOuster");
			npchar.quest.ouster = "true";
			SaveCurrentNpcQuestDateParam(npchar, "ouster_date"); // через 2 месяца
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_57":
			int idlt;
			iTemp = sti(npchar.quest.bakaut)*30; // Ян за 1 шт бакаута даёт 30 дублонов
			if (iTemp > 1600)
			{
				idlt = makeint(iTemp-1500)/2; // доля Бонса :)
				dialog.text = "J'ai reçu "+iTemp+"  pieces pour cela. Mille cinq cents pour l'avocat, plus ta part des doublons - "+idlt+"  Voilà.";
				link.l1 = "Remarquable ! Maintenant, je peux facilement m'envoler pour Loxley.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500+idlt);
				break;
			}
			if (iTemp > 1450 && iTemp <= 1600)
			{
				dialog.text = "J'ai reçu mille cinq cents doublons pour cela. C'est juste assez pour l'avocat. Tenez.";
				link.l1 = "Fantastique. Maintenant, je peux m'envoler vers Loxley.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500);
				break;
			}
			dialog.text = "J'ai reçu "+iTemp+" doubloons pour cela. Tiens, vas-y. Il te faudra déterrer le reste toi-même.";
			link.l1 = "Eh bien, si c'est moi-même, alors moi-même. D'accord, je suis en route pour voir Loxley.";
			link.l1.go = "saga_58";
			TakeNItems(pchar, "gold_dublon", iTemp);
		break;
		
		case "saga_58":
			DialogExit();
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.bakaut");
		break;
		
		case "saga_59":
			dialog.text = "Comment donc ? C'est intéressant. Et combien le Hollandais est-il prêt à payer pour ça ?";
			link.l1 = "Quarante doublons chacun.";
			link.l1.go = "saga_60";
		break;
		
		case "saga_60":
			dialog.text = "Whoa! Mes acheteurs paient moins...";
			link.l1 = "En tout, j'ai deux mille pièces d'or pour Loxley et "+sti(npchar.quest.bakaut_sum)*2+"   doublons par-dessus le marché.";
			link.l1.go = "saga_61";
		break;
		
		case "saga_61":
			dialog.text = "Fort bien. Alors, nous le partagerons en deux.";
			if (CheckCharacterItem(pchar, "gold_dublon"))
			{
				npchar.quest.bakaut_pay = GetCharacterItem(pchar, "gold_dublon"); // дублоны в кармане
				link.l1 = "Voilà. J'ai "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "J'ai laissé les doublons sur le navire. Je vais y faire un saut rapide et je reviens tout de suite.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "saga_61_1":
			dialog.text = "Joyeux bon. Combien avez-vous apporté ?";
			if (CheckCharacterItem(pchar, "gold_dublon"))
			{
				npchar.quest.bakaut_pay = GetCharacterItem(pchar, "gold_dublon"); // дублоны в кармане
				link.l1 = "Voilà. J'ai "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "Que se passe-t-il avec ma mémoire ! Il est temps d'arrêter de jouer avec ce rhum. Encore une fois, j'ai laissé les doublons dans mon coffre. Je vais y faire un saut rapide et les apporter.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay": // оплата
			if (sti(npchar.quest.bakaut_sum) < sti(npchar.quest.bakaut_pay)) // полная сумма
			{
				npchar.quest.bakaut_pay = sti(npchar.quest.bakaut_sum);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.bakaut_sum)-sti(npchar.quest.bakaut_pay);
			npchar.quest.bakaut_sum = iTemp; // запоминаем остаток
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.bakaut_pay));
			Log_Info("You have given "+sti(npchar.quest.bakaut_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "Bon travail, "+pchar.name+" ! Je suis à nouveau rappelé que tu es une bonne personne à fréquenter.";
				link.l1 = "Je m'efforce, Jan...";
				link.l1.go = "bakaut_done";
			}
			else
			{
				dialog.text = "Super. Apporteras-tu le reste "+FindRussianQtyString(sti(npchar.quest.bakaut_sum))+" doublons plus tard ?";
				link.l1 = "Oui. Je ne pouvais tout simplement pas transporter un si grand tas d'or en une seule fois.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay_wait":
			dialog.text = "Alors, "+pchar.name+", comment vont mes doublons ?";
			link.l1 = "Je suis prêt à te donner un peu plus d'or.";
			link.l1.go = "saga_61_1";
		break;
		
		case "bakaut_done": // рассчитались
			dialog.text = "J'ai une proposition à te faire. Puisque tu as pu trouver un acheteur lucratif, alors je pourrais te vendre du bois de fer. J'avais l'habitude de recevoir trente doublons par pièce. Si tu veux, tu peux l'acheter chez moi à ce prix-là. Je préfère te le vendre à toi qu'à quelqu'un d'autre.";
			link.l1 = "Combien de bois de fer es-tu capable de vendre ?";
			link.l1.go = "bakaut_done_1";
		break;
		
		case "bakaut_done_1":
			dialog.text = "J'évite de stocker de gros lots. Celui de Molligan était une exception. Les autorités n'apprécieront pas la nouvelle d'un marché noir local. Alors, voici l'accord : je mettrai de côté 25 pièces de bois de fer pour vous le 14 et le 24 de chaque mois. \nSi vous voulez l'acheter, apportez sept cent cinquante doublons et prenez tout le lot. Si vous ne vous présentez pas ce jour-là, je le vendrai à un autre client. Ainsi, vous pourrez avoir 50 pièces par mois. Marché conclu ?";
			link.l1 = "Nous avons un accord, Jan ! Faisons-le. Maintenant, il est temps pour moi de m'en aller...";
			link.l1.go = "saga_oust";
			DeleteAttribute(npchar, "quest.bakaut_sum");
			npchar.quest.trade_bakaut = "true"; // генератор купли-продажи бакаута
			AddQuestRecordInfo("Unique_Goods", "1");
		break;
		
		case "saga_59_1": // укрысил у Яна - нет генератора на бакаут, потерял больше
			dialog.text = "Ah, donc soit ce n'était pas lui, soit il a déjà vendu le bois de fer avant... Quel dommage. Eh bien, tu es mon seul espoir pour obtenir l'argent pour l'avocat maintenant.";
			link.l1 = "Je suis prêt à assumer cette responsabilité. Ce n'est pas ma première chevauchée.";
			link.l1.go = "exit";
			// Ян расстроен и забыл про Устрицу - так что и Устрицы тоже не будет
			DeleteAttribute(npchar, "quest.bakaut_sum");
		break;
		
		case "saga_62":
			dialog.text = "Vraiment ? C'est intéressant. Vas-y, demande. De qui veux-tu parler ?";
			link.l1 = "À propos d'une fille. Son nom était... Jessica Rose.";
			link.l1.go = "saga_63";
		break;
		
		case "saga_63":
			dialog.text = "Hum. Le nouveau chef de notre Confrérie t'a-t-il parlé d'elle ?";
			link.l1 = "Il l'a fait aussi. Mais j'ai appris son existence par Baker, l'ancien bourreau de St. John's. Le même homme qui a exécuté le capitaine Butcher.";
			link.l1.go = "saga_64";
		break;
		
		case "saga_64":
			dialog.text = "Bien. Hum. Eh bien, cela fait plus de vingt ans que j'ai vu Jessica pour la dernière fois. Que sais-tu d'elle ?";
			link.l1 = "Eh bien, je sais comment elle a fini avec le capitaine Boucher et comment ils ont piraté ensemble. Je sais qu'il l'a laissée pour Béatrice. Plus tard, elle s'est vengée de lui pour cela avec l'aide d'un certain Joshua Leadbeater, aussi connu sous le nom de Masque...";
			link.l1.go = "saga_65";
		break;
		
		case "saga_65":
			dialog.text = "";
			link.l1 = "Je sais aussi que toi, Jan, pardonne ma franchise, tu étais intéressé par Jessica. C'est la raison pour laquelle je suis venu te voir. Jessica est une figure importante dans mes recherches. C'est elle qui a assassiné Beatrice Sharp, par jalousie, si je comprends bien.";
			link.l1.go = "saga_66";
		break;
		
		case "saga_66":
			dialog.text = "Eh bien, tu en sais beaucoup. Oui, je courtisais vraiment Jess, mais ce n'était pas une surprise, tous les pirates de l'Isla Tesoro étaient divisés en deux groupes à l'époque : ceux qui voulaient baiser Béatrice et ceux qui voulaient Jessica.\nJe me souviens bien d'elle... Elle était belle, très belle !..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Jess");
			NextDiag.TempNode = "saga_66a";
		break;
		
		case "saga_66a":
			dialog.text = "Elle était spéciale... Il est aussi fort probable que Jess ait tué Beatrice. Après que le Boucher l'ait éjectée du 'Neptune', elle n'a probablement pensé à rien d'autre qu'à assouvir sa vengeance sur lui et Beatrice. Au fait, sais-tu comment le Boucher s'est débarrassé de Jessica ?";
			link.l1 = "Non. Soit il l'a simplement relâchée à la Barbade, soit il l'a mise en rançon.";
			link.l1.go = "saga_67";
		break;
		
		case "saga_67":
			dialog.text = "Le second. Il l'a rabaissée au-delà de toute croyance. Il l'a simplement enfermée dans la cabine, l'a emmenée à la Barbade, a commencé à négocier avec son père Oliver Rose et l'a effectivement vendue pour un tas de doublons... après tout ce qu'elle avait fait pour lui.";
			link.l1 = "Hm. Je pensais que le Boucher avait protégé son honneur lorsque les pirates avaient saisi le 'Neptune' de Joshua Leadbeater...";
			link.l1.go = "saga_68";
		break;
		
		case "saga_68":
			dialog.text = "C'est vrai aussi. Mais elle lui a également payé cher en récompense. Jessica a sauvé la misérable vie de cette crapule à plusieurs reprises, le tirant du lit de clous qu'il se préparait régulièrement à cause de ses beuveries et de son tempérament fougueux. C'est en fait uniquement grâce à elle qu'il a atteint la gloire d'un pirate prospère.";
			link.l1 = "Ouais, ouais, son 'talisman rouge'. J'ai entendu parler de ça. Ils disent que dès que Boucher a largué Jess, sa chance l'a quitté aussi...";
			link.l1.go = "saga_69";
		break;
		
		case "saga_69":
			dialog.text = "Mais bien sûr. Sans Jessica, il était devenu juste un autre flibustier commun, même s'il était imprudemment courageux. Mais Jessica n'était pas là pour lui, c'était elle qui l'aidait à planifier toutes ses opérations risquées et il pouvait toujours compter sur sa lame.\nCertes, Beatrice n'était pas non plus une fille sage, mais elle ne pouvait pas égaler Jess, les charmes de Bea étaient complètement différents... Elle a fait l'erreur de s'en prendre au Boucher.";
			link.l1 = "J'ai déjà entendu ça quelque part...";
			link.l1.go = "saga_70";
		break;
		
		case "saga_70":
			dialog.text = "Tous les pirates le pensaient, y compris Blaze Sharp, son frère. Il ne pouvait pas supporter Boucher... Mais revenons à Jessica. Je n'osais même pas penser à elle pendant qu'elle était sur le 'Neptune', elle ne quitterait jamais son capitaine bien-aimé. Mais quand Boucher s'est débarrassé d'elle de façon si ignoble...\nJe suis arrivé à la Barbade et suis devenu ami avec elle. Ce n'était pas facile pour elle, elle aimait la mer et les aventures dangereuses. Cette vie ennuyeuse de colonie la tuait. De plus, elle était devenue une personne très infâme dans les Caraïbes en servant sur le 'Neptune' et les habitants de Bridgetown avaient des raisons de la considérer comme la complice de Boucher...";
			link.l1 = "Mais ils n'ont pas pu prouver que dalle...";
			link.l1.go = "saga_71";
		break;
		
		case "saga_71":
			dialog.text = "Non. Mais personne ne voulait avoir affaire à elle non plus. Elle était considérée comme maudite, malgré son statut à Bridgetown. Je suppose que j'étais le seul homme à avoir passé plus d'une demi-heure avec Jessica là-bas.\nJe lui ai proposé de venir avec moi vers la Grande Terre de l'Ouest et de commencer une nouvelle vie là-bas. La vie qu'elle a toujours voulue - la mer, les navires, les voyages, les aventures. J'avais déjà monté une grande opération à Blueweld à ce moment-là et j'étais capable de lui offrir cent fois plus que cette ordure de Boucher. Mais Jess était très blessée. Elle n'avait pas pardonné à Boucher sa trahison et la façon dont il l'avait traitée ensuite. Et je crois qu'elle avait encore des sentiments pour lui, même à ce moment-là... Malgré tous mes efforts, je n'ai pas pu lui faire oublier le passé, elle était obsédée par des pensées de vengeance.";
			link.l1 = "Oui, je ne l'envie pas. Pauvre fille...";
			link.l1.go = "saga_72";
		break;
		
		case "saga_72":
			dialog.text = "Je ressentais la même chose à son égard. Plus tard, elle a commencé à s'intéresser aux anciens cultes et rituels indiens. Cela s'est produit après qu'un mage indien ait été capturé et amené des profondeurs des jungles du Yucatán à la plantation locale. Jessica l'a acheté et lui a donné une maison sur sa plantation.\nElle passait beaucoup de temps avec le mage. Elle disait que c'était à cause de son intérêt historique pour les rituels magiques indiens. Les habitants de Bridgetown s'inquiétaient, surtout le pasteur local. En fait, il était l'un des rares à être bienveillant envers Jessica.\nLe prêtre lui parlait souvent, la persuadant de se débarrasser du mage, la menaçant des dangers et de l'inquisition, mais essayer de faire peur à Jessica était une entreprise inutile. Une nuit, des étrangers sont entrés par effraction dans la maison du mage et l'ont assassiné.\nLa même nuit, deux hommes ont attaqué Jessica dans sa propre chambre, mais cela ne s'est pas bien terminé pour eux - personne à Bridgetown ne savait à quel point Jess maniait bien son épée à lame flamboyante. Elle les a littéralement découpés en tranches.";
			link.l1 = "Oui, bien sûr... cette virago téméraire !";
			link.l1.go = "saga_73";
		break;
		
		case "saga_73":
			dialog.text = "Après cela, toute la ville a commencé à la craindre. Et puis le Masque est arrivé. Ils se sont trouvés assez rapidement.";
			link.l1 = "Selon les écrits, le Masque est Joshua Leadbeater, l'ancien capitaine du 'Neptune'...";
			link.l1.go = "saga_74";
		break;
		
		case "saga_74":
			dialog.text = "J'ai appris cela bien plus tard. Une semaine après l'arrivée du Masque, Jess a pris ses affaires, m'a dit adieu et s'est embarquée sur une frégate militaire vers des directions inconnues. Elle n'est jamais revenue... tout comme Béatrice n'est jamais revenue à Isla Tesoro.\nPeu après, ils ont pendu le Boucher à St. John's, il y a été livré par le Masque lui-même. Mais il a survécu au Boucher seulement d'un jour.";
			link.l1 = "Oui... Notre Steven Dodson a montré de la classe...";
			link.l1.go = "saga_75";
		break;
		
		case "saga_75":
			dialog.text = "Oui, c'est ce qu'on m'a dit. Il a vengé Béatrice... Et c'est ainsi que l'histoire de Jessica se termine, elle est décédée quelque part sur une île déserte lors d'une escarmouche avec les pirates de Boucher. Personne ne sait où se trouve cet endroit. Boucher est mort, tout comme Jackman et Bourreau.";
			link.l1 = "C'est là que tu te trompes, Jan. Le Boucher est vivant.";
			link.l1.go = "saga_76";
		break;
		
		case "saga_76":
			dialog.text = " Quoi!? Ce n'est pas possible! Il a été pendu!";
			link.l1 = "Lis le témoignage de Raymond Baker. C'est mieux que n'importe quelle histoire.";
			link.l1.go = "saga_77";
		break;
		
		case "saga_77":
			PlaySound("interface\important_item.wav");
			dialog.text = "Montre-moi cela...(lisant) Hum. Incroyable ! Il s'avère que son exécution a été mise en scène !";
			link.l1 = "Malin, hein ? Mais ce n'est pas tout. Vous connaissez le Boucher. Vous ne savez juste pas qui il est maintenant.";
			link.l1.go = "saga_78";
		break;
		
		case "saga_78":
			dialog.text = "Ouais? Et qui est-il?";
			link.l1 = "Lawrence Beltrope de Port Royal. Le propriétaire de la mine, cette ombre très mystérieuse derrière Jackman. Je l'ai découvert par Baker et Baker l'a appris du Masque.";
			link.l1.go = "saga_79";
		break;
		
		case "saga_79":
			dialog.text = "Sainte putain ! Alors, il s'avère que c'est lui qui a orchestré tout ça ? Bon, d'accord... Nous nous rendrons aussi chez le Boucher. Je vais réfléchir à comment descendre cette mauvaise pièce. Bien que cela ne soit pas facile, il est sous la protection durable des autorités anglaises.";
			link.l1 = "Son heure viendra, Jan. Bientôt, il rencontrera son maître d'équipage et son quartier-maître. D'accord, merci pour l'histoire. Il est temps pour moi de partir.";
			link.l1.go = "saga_80";
		break;
		
		case "saga_80":
			dialog.text = "Où allez-vous en ce moment ?";
			link.l1 = "Vers une île. Je crois que c'est le même endroit où Jess et Béatrice sont décédées et où le Masque a fondu sur Boucher-Beltrope. J'ai besoin de preuves que Hélène appartient à la famille Sharp et j'espère les déterrer là-bas.";
			link.l1.go = "saga_81";
		break;
		
		case "saga_81":
			dialog.text = "D'accord. Alors, "+pchar.name+"Bonne chance à toi. Donne-moi les détails quand tu reviendras.";
			link.l1 = "Bien sûr. À plus tard, Jan !";
			link.l1.go = "saga_81a";
		break;
		
		case "saga_81a":
			DialogExit();
			LAi_SetHuberType(npchar);
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(npchar, "quest.jessika");
			npchar.quest.jessika_peace = "true"; // атрибут на мирное разрешение после боя
		break;
		
		case "saga_82":
			dialog.text = "Bon travail, "+pchar.name+"Vous avez accompli l'impossible. Nous, tous les barons de la Fraternité de la Côte, vous sommes redevables.";
			link.l1 = "Oui, le chemin vers la victoire était étroit. Si seulement j'avais su à l'avance que je devrais supporter autant...";
			link.l1.go = "saga_83";
		break;
		
		case "saga_83":
			dialog.text = "Comment va Hélène ? Que compte-t-elle faire ?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Elle reste sur mon navire avec moi. Elle n'est plus un simple officier ordinaire. Le contrôle de l'île sera donné au chef des Frères, et tout ce qu'elle obtiendra, c'est un loyer. Helen l'a décidé par elle-même.";
				link.l1.go = "saga_84";
			}
			else
			{
				link.l1 = "Elle est partie pour Isla Tesoro pour prendre le baronnie en main.";
				link.l1.go = "saga_85";
			}
		break;
		
		case "saga_84":
			dialog.text = "Eh bien, "+pchar.name+"... Félicitations ! Beaucoup d'hommes ont rêvé d'être à votre place. Je suis heureux qu'Helen ait choisi un homme qui la mérite. Il ne pourrait jamais y avoir de meilleur candidat que vous pour être son compagnon de vie.";
			link.l1 = "Merci, Jan ! Maintenant, j'aimerais revenir à notre conversation sur Tortuga et Levasseur.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "Merci, Jan !";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_85":
			dialog.text = "Merveilleux. Elle le mérite. Je pense que le nouveau chef de la Confrérie l'aidera à gérer ses affaires. C'est une jeune fille talentueuse et brillante qui peut rapidement s'adapter et apprendre n'importe quoi. Merci, "+pchar.name+" ! Helen est comme une fille pour moi et je suis ravi qu'un avenir aussi merveilleux s'ouvre à elle.";
			link.l1 = "Je t'en prie, Jan... Quoi qu'il en soit, j'aimerais revenir à notre conversation sur Tortuga et Levasseur.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "De rien, Jan.";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_86":
			sTemp = "Shark Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = "Tandis que tu étais parti, "+sTemp+" et j'ai déjà discuté de cela et nous sommes parvenus à un avis commun concernant l'élimination de Levasseur. Naviguez vers Isla Tesoro et parlez avec notre nouveau chef, il vous donnera les détails de notre plan et vous apportera toute l'assistance qu'il pourra vous offrir.";
			link.l1 = "Je sens enfin le parfum de la poudre à canon ! Pas de temps à perdre, je pars pour Isla Tesoro !";
			link.l1.go = "saga_87";
		break;
		
		case "saga_87":
			dialog.text = ""+pchar.name+", attends une minute. J'ai quelques cadeaux pour toi en remerciement de ton aide concernant Hélène et les Frères. Le premier est l'amulette enchantée de Sarrazin venant de l'Extrême-Orient. Ses charmes fortifient la discipline à bord du navire, vérifié par moi personnellement. Tiens, la voilà.";
			link.l1 = "Merci !";
			link.l1.go = "saga_88";
		break;
		
		case "saga_88":
			GiveItem2Character(pchar, "talisman4");
			Log_Info("You've received the 'Janissary' amulet.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Le second n'est qu'un souvenir des aventures passées. J'ai convaincu le Conseil de jeter ce ridicule vestige d'utiliser des fragments de pierre aux vents. Ils ne sont plus nécessaires. Je vais te les donner. Peut-être que tu leur trouveras une certaine utilité.";
			link.l1 = "Une utilité pour ces fragments ? Hm. Je ne sais pas... mais comme souvenir, je vous suis fort reconnaissant !";
			link.l1.go = "saga_89";
		break;
		
		case "saga_89":
			GiveItem2Character(pchar, "splinter_js"); 
			GiveItem2Character(pchar, "splinter_nh"); 
			GiveItem2Character(pchar, "splinter_mt"); 
			GiveItem2Character(pchar, "splinter_zm"); 
			GiveItem2Character(pchar, "splinter_jb"); 
			Log_Info("You've received five ornamental pattern fragments");
			dialog.text = "Eh bien, n'oublie pas ton ami, "+pchar.name+". Passe chez moi quand tu jetteras l'ancre à Blueweld. On s'assiéra et boira du rhum. Je suis toujours heureux de te voir.";
			link.l1 = "Absolument, Jan. Nous avons quelque chose à nous rappeler maintenant, n'est-ce pas ? Ha-ha ! Quoi qu'il en soit, je devrais y aller.";
			link.l1.go = "saga_90";
		break;
		
		case "saga_90":
			dialog.text = "Bonne chance, "+pchar.name+"!";
			link.l1 = "À bientôt...";
			link.l1.go = "saga_91";
		break;
		
		case "saga_91":
			DialogExit();
			pchar.questTemp.Saga = "end";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock")) AddQuestRecord("Saga", "26_1");
			else 
			{
				AddQuestRecord("Saga", "26");
				pchar.questTemp.Terrapin = "islatesoro";
			}
			CloseQuestHeader("Saga");
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
	// --> провалы Саги
		case "saga_f_1":
			dialog.text = "Ouais... On dirait bien que notre plan est tombé à l'eau. Maintenant, nous ne pourrons pas mettre qui nous voulions à la tête de la Confrérie. Jackman est mort, c'est bien et bon. Mais hélas, mon plan ne va pas fonctionner maintenant. Nous devrons élire le chef de la Confrérie de la manière habituelle et Dieu sait quel genre de tournure cela va prendre...";
			link.l1 = "C'est bien regrettable. Fort regrettable. Et on dirait qu'Helen se retrouvera sans son héritage.";
			link.l1.go = "saga_f_2";
		break;
		
		case "saga_f_2":
			dialog.text = "Oui, "+pchar.name+"Et je voudrais vous aider à prendre Tortuga, vraiment, je le voudrais, mais maintenant je ne sais même pas comment. Il n'y a probablement rien que je puisse faire pour aider. Il semble que vous devrez compter uniquement sur vos propres forces et votre capacité à vous battre.";
			link.l1 = "Il semble qu'il n'y ait pas d'autre option... Très bien, Jan, je vais réfléchir à ce qu'il faut faire ensuite. À plus tard...";
			link.l1.go = "saga_f_3";
		break;
		
		case "saga_f_3":
			dialog.text = "Passez donc, "+pchar.name+". Je suis toujours heureux de te voir.";
			link.l1 = "... ";
			link.l1.go = "exit";
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			CloseQuestHeader("Testament");
		break;
		
		case "saga_l1": // проход первый - отбираем Элен и закрываем вход к Свенсону
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l1";
			pchar.quest.Saga_Late_1.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_1.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_1.function = "Saga_HelenaTalk";
			pchar.questTemp.Saga.Jackman = "true";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
		break;
		
		case "saga_l2": // проход второй - отбираем Элен, Натана и Данни в Марун-Таун, чистим квестовый лут
			dialog.text = "Hélas, il est trop tard pour agir maintenant. Isla Tesoro est officiellement transférée sous l'autorité de la couronne anglaise. Il y a une garnison qui s'y trouve maintenant. C'est un coup dur pour les Frères, dont, je crains, nous ne pourrons pas nous relever.";
			link.l1 = "Quelle horreur... Ah, j'aurais dû agir plus vite. Alors, tu vois, tout se serait bien passé. D'accord, Jan, je vais réfléchir à ce que je dois faire ensuite. À plus tard...";
			link.l1.go = "saga_l2_1";
		break;
		
		case "saga_l2_1":
			dialog.text = "Arrête-toi par ici, "+pchar.name+". Je suis toujours heureux de te voir.";
			link.l1 = "...";
			link.l1.go = "saga_l2_2";
		break;
		
		case "saga_l2_2":
			DialogExit();
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "letter_parol", 1);
			RemoveItems(pchar, "map_sharp_full", 1);
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l2";
			pchar.quest.Saga_Late_2.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_2.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_2.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
		
		case "saga_l3":
			dialog.text = "Oui... Nous venons vraiment de subir une défaite sévère. Et le pire, c'est que nous étions littéralement à un pas de la victoire. Caramba ! Comment cela a-t-il pu arriver, hein, "+pchar.name+" ? Tu t'es donné tant de mal, tu as fait tant de choses et... quelle poisse!";
			link.l1 = "Je suis l'imbécile responsable de ça. J'aurais dû être plus rapide. Et à cause de moi, Hélène va perdre son héritage. Et le plan de Tortuga ne verra jamais le jour.";
			link.l1.go = "saga_f_2";
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
	// <-- провалы Саги
		
	//-----------------------------------генератор торговли бакаутом--------------------------------------------
		case "trade_bakaut":
			if (CheckAttribute(pchar, "questTemp.UpgradeBakaut"))
			{
				dialog.text = "D'accord, cela ne me dérange pas. J'ai vingt-cinq unités dans mon entrepôt. Le prix, comme vous vous en souvenez, est de 3150 doublons.";
				if (PCharDublonsTotal() >= 3150)
				{
					link.l1 = "D'accord, marché conclu. Voilà. Voici 3150 doublons.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "N'est-ce pas une sacrée malchance. J'ai oublié mon argent sur mon navire. Je reviens avec dans une seconde.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "D'accord, cela ne me dérange pas. J'ai vingt-cinq unités dans mon entrepôt. Le prix, comme vous vous en souvenez, est de trente doublons par pièce.";
				if (PCharDublonsTotal() >= 750)
				{
					link.l1 = "D'accord, marché conclu. Voilà. Voici sept cent cinquante doublons.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "N'est-ce pas une sacrée malchance. J'ai oublié mon argent sur mon navire. Je reviens avec dans une seconde.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && !CheckAttribute(pchar, "questTemp.SvensonBakautBlock")) // увеличить объём поставок бакаута
			{
				link.l4 = "Jan, serait-il possible d'augmenter la taille des livraisons de gaïac ?";
				link.l4.go = "UpgradeBakaut";
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && CheckAttribute(pchar, "questTemp.SvensonBakautPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок бакаута, если в первый раз не принесли
			{
				link.l4 = "Jan, j'ai rassemblé trois mille pièces d'or. Tiens, tu peux offrir ce cadeau à nos parasites. Je suppose qu'ils auront une journée heureuse aujourd'hui.";
				link.l4.go = "UpgradeBakaut_Agreed";
			}
		break;
		
		case "trade_bakaut_1":
			RemoveDublonsFromPCharTotal(750);
			Log_Info("You have given 750 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Remarquable. Je vais ordonner à mes gens de transporter le bois de fer sur votre navire.";
			link.l1 = "Merci !";
			link.l1.go = "trade_bakaut_2";
		break;
		
		case "trade_bakaut_2":
			dialog.text = "Si tu veux en acheter plus, reviens dans deux semaines. J'aurai préparé un autre lot d'ici là.";
			link.l1 = "Très bien, Jan. À la prochaine !";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SANDAL, 25);
			DeleteAttribute(npchar, "quest.trade_bakaut");
			SetFunctionTimerCondition("Bakaut_SvensonAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "UpgradeBakaut": //
			if (startHeroType == 1) sStr = "mon ami";
			if (startHeroType == 2) sStr = "mon ami";
			if (startHeroType == 3) sStr = "mon ami";
			if (startHeroType == 4) sStr = "Helen";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Ravi que le gaïac te plaise, " + sStr + ". Augmenter les livraisons n'est pas un problème, mais il y a un hic, tu comprends. Avec l'augmentation des volumes apparaît une trace qui peut attirer l'attention indésirable, surtout des autorités anglaises. Mais si nous ajoutons à l'affaire des mains fiables, des oreilles fidèles, et des gens dans la résidence qui aideront à rester dans l'ombre, tout peut s'arranger. C'est vrai que cela ne sera pas bon marché - trois mille doublons pour contourner le trésor de la ville et les besoins de l'Angleterre. Alors je pourrai te fournir cinq fois plus. Qu'en dis-tu ?";
				link.l1 = "Trois mille doublons ? Jan, c'est du vol en plein jour ! Ne pourrait-on pas s'en sortir avec moins de dépenses ? Peut-être y a-t-il un moyen de régler l'affaire sans de telles sommes fabuleuses ?";
				link.l1.go = "UpgradeBakaut_1";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Bonne idée, mais je dois dire que pour de tels volumes dans les affaires commerciales, il faut un peu plus d'expérience et d'habileté. Se précipiter apporte plus de risque que de profit. Faisons ainsi : acquiers encore un peu d'expérience, et quand tu seras prêt"+GetSexPhrase("","e")+" pour de plus grands lots, reviens. Alors nous discuterons de tout comme il se doit.";
				link.l1 = "Hmm... D'accord. Revenons à cette conversation plus tard.";
				link.l1.go = "exit";
				notification("Skill Check Failed (80)", SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeBakaut_1":
			dialog.text = "Hélas, "+pchar.name+", tel est aujourd'hui le prix de la tranquillité - les appétits de ces messieurs en perruques et uniformes grandissent chaque jour. Rien ne les attire plus que les doublons qui tintent dans leurs coffres. Je te garantis une remise de quinze pour cent sur toutes les livraisons suivantes, si cela te console.";
			link.l1 = "Au diable ! Demander de telles sommes ! Avec une telle avidité, ils devraient acheter des trésors de rois, pas marchander le silence ! Jan, peut-être devrions-nous... leur montrer qui est la vraie force dans l'archipel, hein ?";
			link.l1.go = "UpgradeBakaut_2";
		break;
		
		case "UpgradeBakaut_2":
			if (startHeroType == 1) sStr = "mon ami";
			if (startHeroType == 2) sStr = "mon ami";
			if (startHeroType == 3) sStr = "mon ami";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "Ha ! Quelle fougue tu as, " + sStr + " ! Mais aller contre toute l'Angleterre n'est pas dans mon intérêt maintenant, et je ne suis plus aussi jeune qu'avant. Payons simplement ces sangsues, et qu'ils restent tranquilles - nous avons nos affaires à faire. Rassemble la somme nécessaire, et notre chemin sera dégagé, sans questions superflues !";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Bon, d'accord, Jan, tu m'as convaincu. Qu'il en soit ainsi, puisqu'il n'y a pas d'autre moyen. Voici tes trois mille doublons. Rappelle-toi simplement : je n'ai pas l'intention de nourrir ces avares éternellement.";
				link.l1.go = "UpgradeBakaut_Agreed";
			}
			link.l2 = "Que le diable les emporte, Jan ! Penses-tu vraiment qu'il n'y a pas d'autre issue ? Bon. Je trouverai ces doublons. Mais je n'ai pas cette somme pour l'instant.";
			link.l2.go = "UpgradeBakaut_4";
			link.l3 = "Bon sang, Jan, veux-tu vraiment que je nourrisse ces fonctionnaires avec leurs dames soignées ? Ils sont assis sur leurs fauteuils, ne font rien, et ne demandent que de l'argent ! Non, cela ne me plaît pas ! Je ne vais pas remplir leurs poches de ma sueur et de mon sang ! Revenons aux conditions précédentes. Cela me suffit.";
			link.l3.go = "UpgradeBakaut_3";
		break;
		
		case "UpgradeBakaut_Agreed":
			dialog.text = "Voilà qui est mieux ! Avec ta contribution, nos affaires se dérouleront sans accroc, et ces avares auront leur dû - et cesseront même de regarder dans la direction du gaïac. Je t'assure, nous récupérerons bientôt tous les investissements au centuple.";
			link.l1 = "Je l'espère, Jan, je l'espère.";
			link.l1.go = "UpgradeBakaut_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "1_1");
			pchar.questTemp.UpgradeBakaut = true;
			pchar.questTemp.SvensonBakautBlock = true;
			DeleteAttribute(pchar, "questTemp.SvensonBakautPotom");
		break;
		
		case "UpgradeBakaut_Agreed_1":
			dialog.text = "Les affaires iront comme il faut, tu n'as pas à t'inquiéter. Et maintenant, quant à nos futures transactions : je garderai prêts pour toi 125 troncs de gaïac, comme avant, pour le 14 et le 28 de chaque mois. Tu pourras prendre tout le lot pour 3150 doublons.";
			link.l1 = "J'aime beaucoup mieux ces conversations ! Cent vingt-cinq troncs, alors ? Excellent, Jan. Eh bien, à bientôt, j'attendrai la livraison !";
			link.l1.go = "exit";
		break;
		
		case "UpgradeBakaut_3":
			if (startHeroType == 1) sStr = "mon ami";
			if (startHeroType == 2) sStr = "mon ami";
			if (startHeroType == 3) sStr = "mon ami";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "Comme tu voudras, " + sStr + ". Et ne t'énerve pas comme ça. C'est ainsi que ce monde est fait.";
			link.l1 = "Oui, Jan, je sais comment ce monde est fait. Mais cela ne signifie pas que je doive le tolérer. Bon, je dois partir.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
		break;
		
		case "UpgradeBakaut_4":
			dialog.text = "J'attendrai que tu rassembles l'argent. Je sais que tu trouveras un moyen. Dès que tu seras prêt"+GetSexPhrase("","e")+" - je t'attendrai avec l'argent, et nous continuerons.";
			link.l1 = "D'accord.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
			pchar.questTemp.SvensonBakautPotom = true;
		break;
		// <-- генератор бакаута
		
	//----------------------------------- штурм рудника --------------------------------------------
		case "mine_attack":
			dialog.text = "Ravi de te voir, "+pchar.name+". Mes gens sont prêts. En route pour la selva ?";
			link.l1 = "Oui, Jan. Mon escouade est prête pour la bataille.";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			dialog.text = "Allons-y alors. La mine se trouve dans la grande profondeur de la jungle juste le long de ce sentier. Restez à droite à la bifurcation. En avant !";
			link.l1 = "En avant !";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_attack_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("shore53", "boat", true);
			LocatorReloadEnterDisable("mine_03", "reload3_back", true);
			LocatorReloadEnterDisable("mine_02", "reload3_back", true);
			pchar.quest.Saga_MineAttack_01.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_01.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_01.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_3":
			dialog.text = "Alors, "+pchar.name+", il est temps de discuter de la manière dont nous allons procéder à cette opération. J'ai déjà envoyé plusieurs Indiens Miskito au préalable pour explorer la région et j'ai composé un plan d'action basé sur leurs observations.";
			link.l1 = "Raconte-moi tout !";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "La fosse représente la mine sous les montagnes dans la jungle. Il y a un camp près d'une entrée de la mine. Quelques maisons et une palissade. Il y a un chemin menant à la palissade. Regarde, il mène à un petit espace dégagé dans la jungle non loin d'ici. C'est là que se trouve l'entrée principale de la fosse.\nCela représente un haut mur de pierre entre deux collines escarpées empêchant quiconque de s'infiltrer à l'intérieur. Les portes sont protégées par une garde de six hommes. Pas un gros problème, mais ils ont aussi installé deux canons là-bas. C'est le plus gros problème.\nDeux volées de mitraille peuvent abattre la moitié de notre escouade, ce qui serait un désastre, donc une attaque de front n'est pas une option...";
			link.l1 = "Ha ! Mais nous avons un atout, nous connaissons le mot de passe qui nous fera entrer...";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			dialog.text = "C'est exact. Nous utiliserons cela à notre avantage, mais pour l'instant, permettez-moi de vous exposer l'intégralité de mon plan jusqu'à la fin.";
			link.l1 = "Bien sûr, Jan. Je suis tout ouïe.";
			link.l1.go = "mine_attack_6";
		break;
		
		case "mine_attack_6":
			dialog.text = "Il y a une autre entrée vers la fosse - par ce sentier dans la jungle. Il contourne les collines protégeant la mine et mène à une petite cavité étroite qui peut être utilisée pour entrer. Mais les bandits ont érigé une haute clôture et y ont mis des gardes. La clôture a de petites portes mais elles sont barricadées de l'autre côté.\nMaintenant écoutez ce que nous allons faire. Nous allons nous débarrasser de ceux qui gardent la seconde entrée de la mine. Une partie de notre escouade restera là et trouvera une bûche pour l'utiliser comme bélier.\nNous retournerons à l'entrée principale et tuerons les équipes de canon. Le mot de passe que nous avons nous aidera deux fois. Ensuite, nous attaquerons la mine de deux côtés. Je dirigerai la première unité d'assaut et vous dirigerez la seconde.";
			link.l1 = "Eh bien, c'est logique. Nous les ferons se battre sur deux fronts. En avant !";
			link.l1.go = "mine_attack_7";
		break;
		
		case "mine_attack_7":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.quest.mine01 = "true";
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_02.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_02.win_condition.l1.location = "Mine_04";
			pchar.quest.Saga_MineAttack_02.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_8":
			dialog.text = "Bien, nous y voilà... C'est le chemin vers la clôture des bandits. Maintenant, nous devons décider comment les gérer. Si nous envoyons toute l'escouade là-bas, ce sera trop suspect et ils donneront l'alarme.\nNous devrions envoyer un petit groupe de trois, pas plus, ce groupe pourra s'approcher suffisamment sans éveiller de soupçons et attaquer par surprise. Je ne peux pas diriger le groupe, mon visage est trop connu par ici.\nDonc c'est à vous de décider, "+pchar.name+", parce que tu es le seul en qui j'ai confiance pour commander sans risquer toute l'opération. Je te donnerai Gregory et un mousquetaire pour t'assister...";
			link.l1 = "Combien de gardes y a-t-il à la barrière ?";
			link.l1.go = "mine_attack_9";
		break;
		
		case "mine_attack_9":
			dialog.text = "Quatre. Deux mousquetaires et deux soldats.";
			link.l1 = "On les prendra...";
			link.l1.go = "mine_attack_10";
		break;
		
		case "mine_attack_10":
			dialog.text = "Sachant qui tu es, je n'en doute même pas une seconde. Approche-les et dis-leur que Jackman t'a envoyé. Dis-leur le mot de passe. Et puis, une fois qu'ils sont détendus... agis selon les circonstances.";
			link.l1 = "D'accord. Nous les maintiendrons sur le qui-vive.";
			link.l1.go = "mine_attack_11";
		break;
		
		case "mine_attack_11":
			dialog.text = "Bonne chance, "+pchar.name+" !";
			link.l1 = "...";
			link.l1.go = "mine_attack_12";
		break;
		
		case "mine_attack_12":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 2)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 12)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				LAi_CharacterDisableDialog(sld);//запрет диалога
			}
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(npchar, "quest.mine01");
			npchar.quest.mine02 = "true";
			pchar.questTemp.Saga.MineAttack = "true";
			pchar.quest.Saga_MineAttack_03.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_03.win_condition.l1.location = "Mine_01";
			pchar.quest.Saga_MineAttack_03.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_13":
			dialog.text = "Beau travail, "+pchar.name+" ! Vous êtes encore sorti vainqueur, comme toujours. Maintenant, mes gars vont se préparer à déclencher une tempête de ce côté de la mine et nous dégagerons l'entrée principale.";
			link.l1 = "Je suppose que je vais encore m'approcher des gardes ?";
			if (GetCharacterIndex("Svensons_off_2") != -1 && GetCharacterIndex("Svensons_sold_12") != -1) link.l1.go = "mine_attack_14";
			else link.l1.go = "mine_attack_14a";
		break;
		
		case "mine_attack_14a":
			dialog.text = "Oui, "+pchar.name+", encore une fois. J'aimerais y aller moi-même, mais ils me reconnaîtraient sûrement et toute l'opération partirait en vrille. Ce sera plus dangereux car il y a plus d'ennemis, et n'oublie pas les armes.";
			link.l1 = "Je prendrai mes officiers avec moi.";
			link.l1.go = "mine_attack_14_1";
		break;
		
		case "mine_attack_14":
			dialog.text = "Oui, "+pchar.name+", encore une fois. J'aimerais y aller moi-même, mais ils me reconnaîtraient sûrement et toute l'opération tomberait à l'eau. Ce sera plus dangereux car il y a plus d'ennemis, et n'oublie pas les armes. Qui emmèneras-tu avec toi pour t'aider ? Tes officiers ou Gregory et le mousquetaire comme la dernière fois ?";
			link.l1 = "Je prendrai mes officiers.";
			link.l1.go = "mine_attack_14_1";
			link.l2 = "Je prendrai Gregory et le mousquetaire.";
			link.l2.go = "mine_attack_14_2";
		break;
		
		case "mine_attack_14_1":
			dialog.text = "D'accord. Vos propres hommes sont votre meilleur soutien. Maintenant, nous allons retourner vers l'entrée principale. Vous souvenez-vous du chemin ?";
			link.l1 = "Bien sûr. Retournez par où nous sommes venus, puis restez à gauche, et ensuite prenez le sentier autour de la colline.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "officer";
		break;
		
		case "mine_attack_14_2":
			dialog.text = "D'accord. Tu as déjà réussi une fois, donc le refaire devrait être un jeu d'enfant. Nous allons maintenant retourner à l'entrée principale. Te souviens-tu du chemin ?";
			link.l1 = "Bien sûr. Reviens sur nos pas, puis prends à gauche, et suis le sentier autour de la colline.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "soldiers";
		break;
		
		case "mine_attack_15":
			dialog.text = "Pas de temps à perdre. En avant !";
			link.l1 = "En avant !";
			link.l1.go = "mine_attack_16";
		break;
		
		case "mine_attack_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 12) LAi_ActorFollowEverywhere(sld, "", -1);
				else LAi_ActorRunToLocation(sld, "reload", "reload3_back", "mine_01", "goto", "goto"+i, "", 5);
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			if (pchar.questTemp.Saga.MineAttack == "soldiers") LAi_LocationDisableOfficersGen("mine_exit", true);//офицеров не пускать
			LocatorReloadEnterDisable("mine_03", "reload3_back", false);
			LocatorReloadEnterDisable("mine_02", "reload3_back", false);
			DeleteAttribute(npchar, "quest.mine02");
			npchar.quest.mine03 = "true";
			pchar.quest.Saga_MineAttack_05.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_05.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_05.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_17":
			dialog.text = "D'accord, "+pchar.name+", écoute ces dernières instructions. Ces diables qui gardent les portes sont coriaces, donc cela ne sera pas facile pour toi. Ton objectif principal est de tuer les canonniers près des portes car nous ne pourrons pas venir t'aider s'ils respirent encore.\nUne fois qu'ils seront tous deux morts et qu'il n'y a plus de risque de salve, nous viendrons tous les abattre en quelques secondes. As-tu compris cela, "+pchar.name+"? Ne joue pas au héros, tue les canonniers et laisse-nous le reste.";
			link.l1 = "D'accord, Jan. Je vais essayer de tout faire comme prévu. Et si quelque chose tourne mal, je vais improviser.";
			link.l1.go = "mine_attack_18";
		break;
		
		case "mine_attack_18":
			dialog.text = "Ça semble bien. Que Dieu soit avec vous !";
			link.l1 = "Merci...";
			link.l1.go = "mine_attack_19";
		break;
		
		case "mine_attack_19":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 2)
					{
						LAi_SetActorType(sld);
						LAi_ActorFollowEverywhere(sld, "", -1);
					}
					else LAi_SetStayTypeNoGroup(sld);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			DeleteAttribute(npchar, "quest.mine03");
			pchar.quest.Saga_MineAttack_06.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_06.win_condition.l1.location = "Mine_exit";
			pchar.quest.Saga_MineAttack_06.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_20":
			dialog.text = "Ouf ! Nous avons fauché ces fils de putain... Sacrés petits vauriens qu'ils étaient. Je peux dire que ces mercenaires servaient autrefois dans les troupes régulières. Nous avons fait du bruit ici, j'ai peur qu'on nous ait entendus. Pas une minute à perdre ! "+pchar.name+", il est temps pour nous d'attaquer la mine.\nJe retournerai vers mon groupe à la deuxième entrée - ils doivent déjà avoir trouvé et préparé un tronc pour enfoncer la barrière. Vous et vos hommes passerez par les portes centrales. Attendez-nous une demi-heure, n'attaquez pas immédiatement...";
			link.l1 = "Jan, s'ils ont entendu les tirs à la mine, nous n'avons pas cette demi-heure. Ces bandits pourraient établir une ligne de défense ou probablement venir directement aux portes centrales et attaquer mon groupe avec tout ce qu'ils ont...";
			link.l1.go = "mine_attack_21";
		break;
		
		case "mine_attack_21":
			dialog.text = "Merde! C'est bien possible. Que suggérez-vous que nous fassions?";
			link.l1 = "Hm... Ha! J'ai une idée! Des canons! Regarde autour. Il n'y a pas seulement de la mitraille, mais des bombes peuvent être trouvées aussi! Maintenant, ces bandits sont finis! Pourquoi n'y ai-je pas pensé plus tôt?!";
			link.l1.go = "mine_attack_22";
		break;
		
		case "mine_attack_22":
			dialog.text = "Que penses-tu que nous devrions faire ?";
			link.l1 = "Nous prendrons un seul canon. Avec un, nous pourrons nous déplacer beaucoup plus rapidement et plus efficacement. Nous le roulerons à l'intérieur, au-delà des portes, jusqu'à la mine et le mettrons en position. S'ils engagent une attaque eux-mêmes, ils auront un grand boum, et s'ils restent en arrière, nous bombarderons simplement leur camp. Peux-tu me dire où exactement le camp est situé derrière les portes ?";
			link.l1.go = "mine_attack_23";
		break;
		
		case "mine_attack_23":
			dialog.text = "Le camp est sur un terrain bas au pied d'une montagne. Il y a un sentier juste derrière les portes qui descend et serpente autour de la colline. Le camp est situé juste derrière cette colline.";
			link.l1 = "Splendide ! On va s'installer au sommet du sentier et lancer quelques bombes par-dessus la colline dans leur nid ! Oh, on les fera danser dans tous les sens !";
			link.l1.go = "mine_attack_24";
		break;
		
		case "mine_attack_24":
			dialog.text = "Nom de Dieu, "+pchar.name+", bien joué! Toute vitesse en avant! Je laisse Randolf sous votre commandement, c'est mon meilleur canonnier. Faites-en votre artilleur et il ne vous laissera pas tomber. Je pars rejoindre mon unité tout de suite.";
			link.l1 = "D'accord. Je bombarderai leurs positions en enfer pendant une demi-heure jusqu'à ce que vous brisiez les portes.";
			link.l1.go = "mine_attack_25";
		break;
		
		case "mine_attack_25":
			dialog.text = "Je vais essayer d'arriver à temps. Je te rejoins au camp !";
			link.l1 = "Marché conclu... Escouade ! Écoutez mon commandement ! Préparez-vous à déplacer le canon vers une nouvelle position ! Prenez de la poudre, des bombes et de la mitraille avec vous ! Vers la mine à travers les portes. En avant, marche !";
			link.l1.go = "mine_attack_26";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 5);
			if (GetCharacterIndex("Svensons_off_2") != -1)
			{
				sld = characterFromId("Svensons_off_2");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 5);
			}
		break;
		
		case "mine_attack_26":
			DialogExit();
			int n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "mine_bandits");
			LocatorReloadEnterDisable("mine_exit", "reload1_back", false);
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.location = "Mine";
			pchar.quest.Saga_MineAttack_07.function = "Saga_MineGunAttack";
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine_exit", "reload2_back", true);
			LAi_LocationDisableOfficersGen("mine_exit", false); // офицеров пускать
			n = Findlocation("mine");
			locations[n].models.always.Gun = "mortair";
			Locations[n].models.always.Gun.locator.group = "goto";
			Locations[n].models.always.Gun.locator.name = "fire"; // орудие - к бою!
			Locations[n].hidden_sound = true;
		break;
		
		case "mine_attack_27":
			dialog.text = "Ouf, ne sommes-nous pas trop tard, "+pchar.name+"?";
			link.l1 = "Jan, bon sang ! Qu'est-ce qui t'a pris autant de temps ? Mon escouade vient de subir un coup dur !";
			link.l1.go = "mine_attack_28";
		break;
		
		case "mine_attack_28":
			dialog.text = "Cette foutue palissade en bois s'est avérée vraiment robuste. Nous l'avons brisée par la force... Nous avons entendu ton boucan. On dirait que tu as bien nettoyé cet endroit ! Ça brûle jusqu'au sol !";
			link.l1 = "Les agissements de Randolf... J'aurais aimé que tu voies combien de salauds nous avons enterrés avant d'enfin engager le combat au corps à corps !";
			link.l1.go = "mine_attack_29";
		break;
		
		case "mine_attack_29":
			dialog.text = "Caramba! Je vous tire mon chapeau, "+pchar.name+"Bien joué ! Eh bien, à propos des pertes... tu en as à chaque fois que tu es en guerre.";
			link.l1 = "Maintenant, ce que nous devons faire, c'est nettoyer la mine elle-même. Il est possible que des survivants s'y cachent.";
			link.l1.go = "mine_attack_30";
		break;
		
		case "mine_attack_30":
			dialog.text = "Allons-y juste nous deux. Explorons la situation là-bas.";
			link.l1 = "Ça a l'air d'un plan !";
			link.l1.go = "mine_attack_31";
		break;
		
		case "mine_attack_31":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, "");
			TakeNItems(npchar, "potion2", 8); 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "Mine_mines", "reload", "reload1", "", -1);
			LAi_LocationDisableOfficersGen("Mine_mines", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_08.win_condition.l1 = "locator";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.location = "mine";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator_group = "reload";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator = "reload4";
			pchar.quest.Saga_MineAttack_08.function = "Saga_MineAttackMines";
		break;
		
		case "mine_attack_32a":
			dialog.text = "Nous n'avons pas encore fouillé toute la mine ! Je te garantis que d'autres de ces gredins se cachent ici !";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_32a";
		break;
		
		case "mine_attack_32":
			dialog.text = "Je ne pense pas qu'il reste un autre salaud...";
			link.l1 = "Jan, je pensais que nous venions juste ici pour explorer la situation...";
			link.l1.go = "mine_attack_33";
		break;
		
		case "mine_attack_33":
			dialog.text = "Ha-ha, eh bien, je ne t'avais pas dit que ce serait une exploration spéciale, une exploration sanglante... Cela faisait longtemps que je n'avais pas eu un échauffement pareil ! Maintenant, tout le monde peut être sûr qu'il n'y a pas un seul salaud qui ait échappé à cette mine !";
			link.l1 = "Alors, qu'allons-nous faire ensuite, Jan ?";
			link.l1.go = "mine_attack_34";
		break;
		
		case "mine_attack_34":
			dialog.text = "Qu'entends-tu par qu'est-ce qu'on va faire ensuite ? On va chercher de l'or et de l'argent. Je ne pense pas que Jackman tenait une telle forteresse ici par ennui. Il a placé une garnison entière ici. As-tu vu les esclaves dans la mine ? Tu devrais te renseigner sur l'endroit où ils stockent les extractions.";
			link.l1 = "D'accord. Alors, tu vas interroger les esclaves et moi je grimperai pour fouiller toutes les maisons du camp, peut-être que je trouverai quelque chose.";
			link.l1.go = "mine_attack_35";
		break;
		
		case "mine_attack_35":
			dialog.text = "Je te tiens ! Il est temps de bouger !";
			link.l1 = "... ";
			link.l1.go = "mine_attack_36";
		break;
		
		case "mine_attack_36":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine", "reload1", true);
			LocatorReloadEnterDisable("mine", "reload6", true);//закрыть выходы с рудника
			pchar.quest.Saga_Mine_letter.win_condition.l1 = "item";
			pchar.quest.Saga_Mine_letter.win_condition.l1.item = "letter_mine";
			pchar.quest.Saga_Mine_letter.function = "Saga_FindMineLetter";
			NextDiag.CurrentNode = "mine_attack_36a";
		break;
		
		case "mine_attack_36a":
			dialog.text = "Va, mon gars. Et retourne ces misérables masures de fond en comble !";
			link.l1 = "Je suis en route !";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_36a";
		break;
		
		case "mine_attack_37":
			dialog.text = "Ha-ha ! "+pchar.name+", c'est formidable que tu aies proposé de venir avec moi pour démanteler cette mine ! C'est un autre signe clair que tu es né sous une bonne étoile.";
			link.l1 = "Avez-vous trouvé de l'or ?";
			link.l1.go = "mine_attack_38";
		break;
		
		case "mine_attack_38":
			dialog.text = "Oui, bon sang ! Pas de l'or, mais de l'argent, une bonne pile. Un jour de plus et ils l'auraient déplacée hors du camp. C'est pourquoi il y avait tant de ruffians ici - ils formaient un groupe d'escorte.\nGrâce à vous, nous sommes arrivés à temps, sans vous je serais encore en train de rassembler des gens. Félicitations partenaire !";
			link.l1 = "Ha ! Je vois... Combien d'argent avons-nous ?";
			link.l1.go = "mine_attack_39";
		break;
		
		case "mine_attack_39":
			dialog.text = "Nous avons environ quatre mille unités. Nous les partagerons en deux parts - moitié pour moi, moitié pour toi, comme convenu.";
			link.l1 = "Exceptionnel ! Nous pouvons toucher un sacré paquet d'argent pour ces trucs !";
			link.l1.go = "mine_attack_40";
		break;
		
		case "mine_attack_40":
			dialog.text = "C'est sûr... As-tu trouvé quelque chose de précieux ?";
			link.l1 = "Non. Il n'y a même pas un seul doublon dans ces taudis. Bien que j'aie trouvé quelques papiers. Je les ai lus et appris que le propriétaire de cette mine est un certain Lawrence Beltrope de Port Royal.";
			link.l1.go = "mine_attack_41";
		break;
		
		case "mine_attack_41":
			dialog.text = "Oh, vraiment ? Laisse-moi voir ces documents...";
			link.l1 = "Voilà.";
			link.l1.go = "mine_attack_42";
		break;
		
		case "mine_attack_42":
			RemoveItems(pchar, "letter_mine", 1);
			dialog.text = "(lisant)... Bien... Beltrope ? Je connais ce nom de quelque part. Ah, oui ! Thomas Beltrope ! C'est intéressant... Très bien, je vérifierai cela quand je retournerai à Bleuweld. Je garderai ces documents avec moi si ça ne te dérange pas ?";
			link.l1 = "Pas du tout. Je n'ai besoin d'eux pour rien.";
			link.l1.go = "mine_attack_43";
		break;
		
		case "mine_attack_43":
			dialog.text = "Bien. Maintenant, il reste la meilleure partie, je vais transporter l'argent vers les navires. Les Miskitos nous aideront avec ça. Nous allons assembler un chariot... Pendant ce temps, repose-toi un peu, "+pchar.name+"Tu l'as mérité plus que quiconque!";
			link.l1 = "Merci, Jan. Nous allons établir un campement sur cette colline, l'odeur de cendre est insupportable. Oui, et nous devons éteindre les feux sur ces masures, qui sait, peut-être qu'elles nous seront utiles un jour...";
			link.l1.go = "mine_attack_44";
		break;
		
		case "mine_attack_44":
			dialog.text = "Tu penses à revendiquer la mine ? Ha-ha ! J'avais déjà réfléchi à l'idée, mais piller c’est une chose, la prendre comme propriété en est une autre. Mon ami, elle a déjà un propriétaire. Nous pourrions avoir des ennuis avec les autorités anglaises.\nDe plus, les esclaves avec qui j'ai parlé m'ont dit que toutes les veines ici étaient pratiquement épuisées - de gros lots d'argent avaient été déplacés d'ici plusieurs fois auparavant. Je crains que cette mine ne soit finie.";
			link.l1 = "Hm... On verra. Peut-être que tout n'est pas épuisé. D'accord, je devrais vraiment me reposer. À plus tard, Jan";
			link.l1.go = "mine_attack_45";
		break;
		
		case "mine_attack_45":
			dialog.text = "Allez-y. Et ne vous inquiétez de rien. Nous nous occuperons de tout le reste nous-mêmes.";
			link.l1 = "...";
			link.l1.go = "mine_attack_46";
		break;
		
		case "mine_attack_46":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "attack1", "Saga_MineWaitTime", -1);
			n = Findlocation("mine");
			DeleteAttribute(&locations[n], "hidden_sound");
			DeleteAttribute(&locations[n], "hidden_fire");
			n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "models.always.Gun1");
		break;
		
		case "mine_attack_47":
			dialog.text = "Tu t'es bien reposé, "+pchar.name+"?";
			link.l1 = "Ce n'était pas mauvais... Bien que, honnêtement, je tuerais pour trouver une taverne, boire un coup, et dormir dans un lit propre.";
			link.l1.go = "mine_attack_48";
		break;
		
		case "mine_attack_48":
			dialog.text = "Les Indiens ont livré l'argent à la côte et le chargent sur votre navire sous la supervision de mes officiers. Vous pouvez déjà repartir. Votre souhait de rhum, de taverne et de lit se réalisera bientôt. Et j'aimerais que vous passiez me voir dans cinq jours chez moi, nous avons encore beaucoup de choses à faire.";
			link.l1 = "D'accord, Jan. À Blueweld dans cinq jours ! Bonne chance !";
			link.l1.go = "mine_attack_49";
		break;
		
		case "mine_attack_49":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4", "none", "", "", "", 15.0);
			LocatorReloadEnterDisable("shore53", "boat", false);
			LocatorReloadEnterDisable("mine", "reload1", false);
			LocatorReloadEnterDisable("mine", "reload6", false);
			LocatorReloadEnterDisable("mine_01", "reload3_back", false);
			LocatorReloadEnterDisable("mine_exit", "reload2_back", false); //открыть выходы с рудника
			LAi_LocationDisableOfficersGen("mine_mines", false); // офицеров пускать
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			SetFunctionTimerCondition("Saga_ReturnFromMine", 0, 0, 5, false); // таймер
			pchar.questTemp.Saga.Mines = "true"; // после Саги рудник будет разрабатываться
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			DoQuestReloadToLocation("Shore53", "goto", "goto6", "");
		break;
		// <-- штурм рудника
		
		case "helensleep":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "Jan, ne me crie pas dessus. Réglons cela comme des gens raisonnables - rappelle-toi, nous avons des affaires à mener !";
			link.l1.go = "helensleep_1";
		break;
		
		case "helensleep_1":
			dialog.text = "Je vais lâcher mes chiens sur toi sur-le-champ, espèce de crapaud ! Oublie Levasseur, et fiche le camp !";
			link.l1 = "Jan ! Ecoute-moi...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenSleep_SvensonThrowOut");
		break;
		
		case "after_drinking":
			dialog.text = "Quel tonneau ? Quant à Helene, je vais m'assurer de lui donner une bonne raclée... Je plaisante, Charles, je plaisante ! Je sais comment ça se passe, et pour Joanna - cette histoire la fera peut-être réfléchir un peu - elle a été particulièrement grincheuse ces derniers temps, tu sais... Eh bien, c'est la vie. Quoi qu'il en soit, bonne chance à toi à Carthagène !";
			link.l1 = "Jusqu'à notre prochaine rencontre, Jan.";
			link.l1.go = "exit";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
