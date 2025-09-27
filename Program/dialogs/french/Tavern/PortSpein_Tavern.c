// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions as-tu ?","Comment puis-je vous aider, "+GetAddress_Form(NPChar)+"?"),"Vous avez essayé de me poser une question il n'y a pas longtemps, "+GetAddress_Form(NPChar)+"... ","Durant toute cette journée, c'est la troisième fois que tu parles d'une question quelconque...","D'autres questions, je présume ?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Humph, où est passée ma mémoire...","Oui, c'est vraiment la troisième fois...","Non, quelles questions?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin" && sti(pchar.money) >= 3000)
			{
				link.l1 = "J'ai entendu dire que la consomption sévit dans votre fort. Pensez-vous que l'épidémie va se répandre dans la ville ?";
				link.l1.go = "Consumption";
			}
			if (CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.Commandant") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "Que pouvez-vous dire du commandant du fort ?";
				link.l1.go = "Consumption_8";
			}
			if (!CheckAttribute(npchar, "quest.Consumption_1") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Dis-moi, le nom 'Juan' te dit-il quelque chose ?";
				link.l1.go = "Consumption_12";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Ecoutez, en avril 1654, une frégate a accosté dans votre port sous le commandement du capitaine Miguel Dichoso et il a disparu ensuite. Y a-t-il quelque chose que vous puissiez me dire à ce sujet ?";
				link.l1.go = "guardoftruth";
			}
			//--> Оковы Азарта
			if (CheckAttribute(pchar, "questTemp.OZ_Tavern_1"))
			{
				link.l2 = "Dis-moi, "+npchar.name+", qui est donc cet oiseau nommé Javier Castillo?";
				link.l2.go = "OZ_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.OZ_Tavern_2"))
			{
				link.l2 = "Revenons à la conversation au sujet de la personne qui peut influencer Javier.";
				link.l2.go = "OZ_Tavern_2_1";
			}
			//<-- Оковы Азарта
		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "Le commandant affirme qu'il n'y a aucun danger. Ceux qui sont trop curieux finissent enfermés dans les casemates. Je ne suis pas de ceux-là, désolé.";
			link.l1 = "Vraiment ? Un tavernier qui n'a pas envie d'écouter les rumeurs - c'est du jamais vu ! Peut-être que le tintement des pesos ravivera votre curiosité ?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "L'argent est tentant bien sûr, mais ma propre peau a plus de valeur. Peut-être puis-je vous parler d'autre chose, señor ? Je suis en fait toujours heureux de discuter, commencez simplement la conversation !";
			link.l1 = "Alors, voilà comment se déroule l'affaire... Très bien, dans cette bourse se trouvent trois mille pièces de huit et nous aurons une petite conversation agréable sur le temps, d'accord ?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3000);
			dialog.text = "Oh, vous êtes persistant, señor. Souvenez-vous simplement que cette conversation n'a jamais eu lieu. (chuchotant) J'ai déjà entendu plusieurs fois pendant toute une année que des gens brûlaient dans nos prisons, mourant de consomption. Vous pouvez blâmer les autorités, vous pouvez blâmer Dieu ou le Diable, mais la plupart d'entre elles sont attribuées à la mauvaise fortune. Cette maudite maladie vole des vies si rapidement. Parfois, ils mettront un homme parfaitement sain là-dedans et en une ou deux semaines, il est parti. Juste comme ça...";
			link.l1 = "Ouah... Une année entière, tu dis? Et quoi, personne n'a pris l'initiative de faire quoi que ce soit à ce sujet ?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Qui s'en soucie, señor ? Qui se soucie des prisonniers ? La lie de la société - c'est ce que disent les grands hommes en soie. Il y avait un médecin qui travaillait dans les cachots. Il essayait de soigner ces pauvres âmes. Il n'a pas duré longtemps, il semble que la maladie l'ait emporté aussi.\nLe commandant ne laisse plus entrer personne maintenant, et nos autorités ne prêtent pas attention à ces questions, surtout quand elles peuvent payer moins pour les rations de prison.";
			link.l1 = "Intéressant, mais qu'y a-t-il dans cette maladie qui te terrifie au point que, enfermés derrière des murs sûrs, nous chuchotons comme des nonnes au confessionnal ?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Il m'est difficile de te le dire, mais il y avait un gars ici. Il a été arrêté pour contrebande et enfermé pendant environ six mois jusqu'à ce que ses camarades le rachètent. Eh bien, tu sais - ils ont mesuré l'or pour ceux qui en avaient besoin, ils ont attendu autant qu'on leur a dit, et le gars est sorti. Mais depuis, il est devenu complètement fou.";
			link.l1 = "Plus fou qu'un rat de cale?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Je suppose. Il était inutile pour ses compagnons depuis lors, passant toute la journée ici, à boire jusqu'à en mourir. On aurait dit qu'il voulait effacer quelque chose de sa tête. Chaque fois qu'il se saoulait, il racontait des histoires sur la consomption qui frappe les gens en silence\nC'étaient ses mots exacts. Selon lui, la 'consomption' est la pire chose qui puisse arriver à un homme.";
			link.l1 = "Les divagations d'un ivrogne. Et alors ?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			if (CheckAttribute(pchar, "questTemp.Consumption.Commandant"))
			{
				dialog.text = "Rien, si ce n'est qu'il a trouvé un peu de courage liquide et s'est mis à parler de plus en plus, et puis, juste comme ça, quelqu'un lui a tranché la gorge et l'a jeté dans le caniveau... et qui que ce soit qui a fait ça et pourquoi, cela m'est bien égal.";
				link.l1 = "Que pouvez-vous dire du commandant ?";
				link.l1.go = "Consumption_8";
			}
			else
			{
				dialog.text = "Rien, si ce n'est qu'il a pris son courage à deux mains et a commencé à parler de plus en plus, et puis comme ça, quelqu'un lui tranche la gorge et le jette dans le caniveau... et celui qui l'a fait et pour quelle raison, c'est tout pareil pour moi. (hausse la voix) Oui, les baies et les récifs sont vraiment dangereux ici, señor. Il faut être prudent quand les tempêtes arrivent des Grandes Antilles, ratez le vent favorable et vous êtes fichu ! Reposez-vous bien, señor, merci de vous être arrêté !";
				link.l1 = "Tempêtes... d'accord. Merci à toi aussi.";
				link.l1.go = "Consumption_7";
			}
			pchar.questTemp.Consumption.Contra = "true";
		break;
		
		case "Consumption_7":
			DialogExit();
			npchar.quest.Consumption = "true";
			AddQuestRecord("Consumption", "2");
		break;
		
		case "Consumption_8":
			dialog.text = "Que dire de lui ? C'est un colonel, il est arrivé d'Europe il y a quelques années après avoir reçu cet endroit. Il aurait été rétrogradé là-bas dans le Vieux Monde pour quelque sale affaire à laquelle il s'adonnait. Je ne sais pas si c'est vrai, mais il y avait des rumeurs au début. Mais qui n'a pas de rumeurs à son sujet, n'est-ce pas ?";
			link.l1 = "Des actes sordides, dites-vous... C'est intéressant. Quelque chose d'autre?";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			dialog.text = "Eh bien, que puis-je dire... Le colonel ressemble à un homme qui se soucie profondément de sa propre sécurité. Bien sûr, ces endroits ne sont pas sûrs à cause des pirates, des bandits, des Indiens et d'autres canailles, mais le señor commandant ne quitte jamais sa maison sans plusieurs gardes du corps\nIl y a son manoir dans cette ville et il l'a transformé en une petite forteresse - ses serviteurs sont bien armés et gardent les fenêtres barricadées.";
			link.l1 = "Mais pendant la journée, il sert à la prison, n'est-ce pas ?";
			link.l1.go = "Consumption_10";
		break;
		
		case "Consumption_10":
			dialog.text = "Oui, mais ce manoir attend essentiellement là-bas pour une embuscade ou une invasion. Quoi qu'il en soit, le Señor Commandant n'y retourne apparemment pas souvent, une vraie forteresse est plus son fort, héhé.";
			link.l1 = "Merci, vous avez été d'une grande aide. À plus tard, "+npchar.name+" !";
			link.l1.go = "Consumption_11";
		break;
		
		case "Consumption_11":
			DialogExit();
			if (CheckAttribute(npchar, "quest.Consumption")) AddQuestRecord("Consumption", "4");
			else AddQuestRecord("Consumption", "5");
			DeleteAttribute(pchar, "questTemp.Consumption.Commandant");
			pchar.questTemp.Consumption = "current";
		break;
		
		case "Consumption_12":
			dialog.text = "Juan ? Lequel ? Il y en a beaucoup ici, les gens ont généralement aussi des noms de famille... ou au moins un surnom...";
			link.l1 = "Je pensais juste... Peut-être que son surnom est 'Consommation', tu as déjà entendu ça ?";
			link.l1.go = "Consumption_13";
		break;
		
		case "Consumption_13":
			dialog.text = "Mon Dieu, tu parles encore de ça! Non, Dieu merci, je n'ai pas entendu. Je le jure! Et maintenant, changeons de sujet. S'il te plaît!";
			link.l1 = "D'accord, d'accord, ne fais pas une crise cardiaque...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption_1 = "true";
		break;
		//<-- Цена чахотки
		
		//--> Оковы Азарта
		case "OZ_Tavern_1":
			dialog.text = "Javier est un joueur de cartes, un tricheur et un escroc. Il traîne toujours à la taverne, à la recherche de quelqu’un à qui soutirer quelques pesos.";
			link.l1 = "Donc, il n’a pas été remarqué dans d’autres affaires louches? Peut-être a-t-il des ennemis?";
			link.l1.go = "OZ_Tavern_2";
			DeleteAttribute(pchar, "questTemp.OZ_Tavern_1");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Tavern_2":
			dialog.text = "Disons que ses amis sont bien moins nombreux que ceux qui rêvent de lui tordre le cou. Mais si vous voulez le nom d’une personne qui pourrait réellement avoir de l’influence sur lui, cela vous coûtera mille pesos. Payez, et je vous dirai tout.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "D’accord, prends ton argent, vieux maître-chanteur.";
				link.l1.go = "OZ_Tavern_3";
			}
			else
			{
				link.l1 = "Nous reprendrons cette conversation plus tard. Je n’ai pas la somme pour l’instant.";
				link.l1.go = "exit";
				pchar.questTemp.OZ_Tavern_2 = true;
				AddLandQuestMark(npchar, "questmarkmain");
			}
		break;
		
		case "OZ_Tavern_2_1":
			dialog.text = "Capitaine, avez-vous apporté les mille pesos?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Oui. Tiens, vieux maître-chanteur.";
				link.l1.go = "OZ_Tavern_3";
			}
			else
			{
				link.l1 = "Diable. Je reviendrai bientôt.";
				link.l1.go = "exit";
			}
		break;
		
		case "OZ_Tavern_3":
			dialog.text = "Voilà qui est mieux. Voyez-vous, Javier n’a pas seulement des dettes de jeu. Un jour, il a voulu se lancer dans le commerce d’antiquités, mais, comme on pouvait s’y attendre, cela ne s’est pas terminé de la meilleure façon pour lui. Au début, les affaires marchaient plutôt bien, puis il a eu l’occasion d’acquérir une pièce rare\nIl s’est tellement emballé qu’il a fait le tour de tous les prêteurs pour trouver de l’argent. Bien sûr, personne ne lui a donné un sou. Alors, il a trouvé un autre passionné d’antiquités et lui a emprunté cent cinquante mille pesos. La suite, je crois que vous la devinez\nIl s’est fait rouler, et maintenant cette dette lui pèse comme une pierre autour du cou. Il n’a remboursé qu’une somme dérisoire et, à en juger par son comportement, il n’a pas l’intention de payer le reste, même si son créancier a engagé des hommes pour l’intimider\nL’homme à qui il doit s’appelle Felipe Alarcón. Sa maison se trouve en face de la banque, vous la reconnaîtrez facilement : c’est un magnifique manoir avec des colonnes à l’entrée.";
			link.l1 = "Merci!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			DeleteAttribute(pchar, "questTemp.OZ_Tavern_2");
			AddDialogExitQuestFunction("OZ_Felip_1");
			DelLandQuestMark(npchar);
		break;
		//<-- Оковы Азарта
		
		case "guardoftruth":
			dialog.text = "Je me souviens de lui. Souvent passé par ma taverne, mais ne parlait pas beaucoup. Prenait quelques verres de rhum, partageait un murmure avec certains clients et partait. Très sombre et sérieux comme tout le monde sur cette frégate. Des mercenaires d'apparence dangereuse qui gardaient leurs lames prêtes\nIl y avait une rumeur que la frégate était pleine de trésors, mais je ne crois pas à ces contes. Une cargaison précieuse n'est jamais transportée sur un seul navire sans convoi. Ils ont passé une journée ici, puis sont partis. Vers l'Europe, j'ai entendu. C'est tout ce que je sais.";
			link.l1 = "Je vois. Eh bien, c'est au moins quelque chose...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "40");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
