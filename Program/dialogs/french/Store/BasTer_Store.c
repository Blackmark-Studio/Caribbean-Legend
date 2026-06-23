// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Allez-y, que désirez-vous ?","Nous en parlions justement. Vous devez avoir oublié...","C'est la troisième fois aujourd'hui que tu parles d'une question...","Ecoutez, c'est une boutique. Les gens achètent des choses ici. Ne me dérangez pas !","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tu sais, "+NPChar.name+"Peut-être la prochaine fois.","D'accord, j'ai oublié pour une raison quelconque...","Oui, c'est vraiment la troisième fois...","Hm, je ne vais pas...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			//Jason --> ----------------------------------мини-квест Бесчестный конкурент------------------------------------
			if (CheckAttribute(pchar, "questTemp.Shadowtrader"))
			{
				if(pchar.questTemp.Shadowtrader == "begin" && GetNpcQuestPastDayParam(npchar, "Shadowtrader_date") < 5 && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Merci, capitaine, d'avoir exaucé ma demande. Maintenant, quand "+pchar.questTemp.Shadowtrader.Guardername+" est ici, je peux au moins me sentir un peu plus détendu.";
					link.l1 = "Hmm... Je ne voudrais pas paraître importun, mais il me semble que vous avez des ennuis. Pouvez-vous me dire ce qui se passe - peut-être pourrais-je vous aider ?"; 
					link.l1.go = "Shadowtrader_fort";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.Trouble") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Alors ? As-tu remis ma lettre ?";
					link.l1 = "Je l'ai fait. Le commandant a répondu verbalement que les preuves dans votre lettre sont insuffisantes pour que la garde de la ville prenne des mesures."; 
					link.l1.go = "Shadowtrader_trouble";
					pchar.quest.ShadowtraderTimeFort_Over.over = "yes";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store" && CheckAttribute(pchar, "questTemp.Shadowtrader.EndFort"))
				{
					dialog.text = "J'ai déjà entendu la nouvelle - cette nuit, les gardes ont découvert un poste de traite illégal de contrebandiers et les ont tous arrêtés. Il était sous le commandement d'une sale ordure, mais c'est bon maintenant, il ne pourra plus faire de mal à qui que ce soit pendant un moment\nLe Commandant m'a parlé de votre rôle dans tout ça, vous avez ma gratitude ! Vous avez tenu parole ! Tenez, prenez l'argent - 15 000 pesos. Vous m'avez sauvé. Rien ne menace mon commerce désormais !";
					link.l1 = "Je vous en prie. C'était facile."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Escape") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Alors, des bonnes nouvelles, "+pchar.name+"?";
					link.l1 = "J'ai localisé votre rival. Il ne sera plus une épine dans votre pied - j'ai réussi à le convaincre... de quitter cette île. Sa 'boutique' était dans une maison près des portes de la ville. C'est à vous de décider quoi faire avec la cargaison abandonnée. Vous pouvez la remettre aux autorités ou tenter de la récupérer pour vous-même."; 
					link.l1.go = "Shadowtrader_Escape_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Free") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "J'ai déjà entendu la nouvelle - cette nuit, les gardes ont découvert un repaire de contrebandiers sous l'une des maisons. Deux vauriens retrouvés morts. Beau travail, "+pchar.name+", je vous admire ! Tenez, prenez la récompense - 15 000 pesos. Vous venez de me sauver ! Maintenant, je vais commercer pour de bon !\nSatisfaites ma curiosité - leur chef... fait-il partie des deux morts ?";
					link.l1 = "Non. Mais il ne montrera plus jamais son visage dans votre ville. Je crois qu'il devrait être à plusieurs dizaines de milles de cette île, pendant que nous parlons."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Kill") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "J'ai déjà entendu les nouvelles - cette nuit, les gardes ont localisé un magasin de contrebandiers secret dans l'une des maisons. Trois scélérats ont été retrouvés morts. Excellent travail, "+pchar.name+", je vous admire ! Tenez, prenez la récompense - 15 000 pesos. Vous venez de me sauver ! Maintenant, je vais commercer pour de bon !\nSatisfaites ma curiosité - leur chef... était-il aussi parmi les deux morts ?";
					link.l1 = "Oui. Tu t'es débarrassé de ton rival pour toujours. Il ne te causera plus jamais de problèmes."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
			}
			//<-- мини-квест Бесчестный конкурент
		break;
		
		// --> мини-квест Бесчестный конкурент
		case "Shadowtrader_begin":
			pchar.questTemp.Shadowtrader = "true";
			pchar.questTemp.Shadowtrader_Block = true;
			pchar.questTemp.Shadowtrader.Guardername = GenerateRandomName_Generator(int(npchar.nation), "man");
			dialog.text = "Pourriez-vous aller à la taverne, trouver un homme du nom de "+pchar.questTemp.Shadowtrader.Guardername+" et lui dire de venir ici dès que possible ? Je ne peux pas quitter le magasin, et cet imbécile est assis à la taverne, à se bourrer de rhum, et il ne pensera sûrement même pas à venir ici, malgré qu'il soit de service.";
			link.l1 = "Je suis toujours heureux de vous aider, camarade - d'autant plus que j'allais de toute façon me rendre à la taverne.";
			link.l1.go = "Shadowtrader_begin_1";
			link.l2 = "Te moques-tu de moi ? Ai-je l'air de ton larbin ? La taverne est à quelques pas d'ici - tu peux t'y rendre toi-même.";
			link.l2.go = "exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		
		case "Shadowtrader_begin_1":
			dialog.text = "Merci ! Dites-lui de venir ici tout de suite, je vous prie. Oh là là, pourquoi doit-il être si casse-pieds...";
			link.l1 = "Ne t'inquiète pas. Je l'enverrai vers toi.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.City = npchar.City;
			pchar.questTemp.Shadowtrader.nation = int(npchar.nation);
			//создаем охранника
			sld = GetCharacter(NPC_GenerateCharacter("ShadowGuarder" , "officer_7", "man", "man", 10, int(npchar.nation), 5, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "topor_2", "pistol3", "bullet", 50);
			sld.name = pchar.questTemp.Shadowtrader.Guardername;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\LineMiniQuests\ShadowTrader.c";
			sld.dialog.currentnode = "ShadowGuarder";
			sld.greeting = "pirat_common";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator(pchar.questTemp.Shadowtrader.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "sit", "sit_front1");
			SaveCurrentNpcQuestDateParam(npchar, "Shadowtrader_date");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Shadowtrader_fort":
			dialog.text = "Oh, capitaine, j'aimerais vraiment votre aide. Pourriez-vous, s'il vous plaît, remettre cette lettre au commandant dès que possible ? Je vous paierais 300 pièces pour cette affaire triviale - comme je l'ai déjà dit, je ne peux pas quitter ma boutique.";
			link.l1 = "Aucun problème. Donnez-moi cette lettre.";
			link.l1.go = "Shadowtrader_fort_1";
			link.l2 = "Non, mon bonhomme, je n'ai plus de temps pour ces conneries.";
			link.l2.go = "Shadowtrader_fort_end";
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fort_1":
			dialog.text = "Voici pour vous. Remettez-lui cela aujourd'hui et apportez-moi sa réponse.";
			link.l1 = "Ne t'inquiète pas, je m'en occupe.";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1"); // 240912
			pchar.questTemp.Shadowtrader.Tradername = GetFullName(npchar);
			SetFunctionTimerCondition("ShadowtraderTimeFort_Over", 0, 0, 1, false);
			pchar.questTemp.Shadowtrader = "current"
			pchar.questTemp.Shadowtrader.Fort = "true";
			AddQuestRecord("Shadowtrader", "1");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
		break;
		
		case "Shadowtrader_fort_end":
			dialog.text = "Eh bien, apparemment je vais devoir demander à quelqu'un d'autre. Désolé de vous avoir dérangé, capitaine.";
			link.l1 = "Aucun problème. Au revoir !";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_trouble":
			dialog.text = "C'est ce qu'il a dit ? Quelle preuve a-t-il besoin de moi, alors ?! Mon cadavre ? Eh bien, il y en aura bientôt un, si ça continue comme ça !..";
			link.l1 = "Eh, eh, "+npchar.name+", calmez-vous, ou vous allez avoir une attaque. Tenez, buvez un peu d'eau... Maintenant dites-moi, quel est le problème - peut-être pourrais-je vous aider ?";
			link.l1.go = "Shadowtrader_trouble_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Trouble");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_trouble_1":
			dialog.text = "Oh, capitaine ! Prenez vos 300 pesos, j'avais presque oublié... Bien sûr, je vous le dirai, mais je ne suis pas sûr de la façon dont vous pourriez m'aider. Mon commerce est presque ruiné - tout cela à cause de ces maudits contrebandiers et de cet inconnu de salaud qui les dirige.";
			link.l1 = "Contrebandiers ?";
			link.l1.go = "Shadowtrader_trouble_2";
			AddMoneyToCharacter(pchar, 300);
		break;
		
		case "Shadowtrader_trouble_2":
			dialog.text = "C'est ça ! Ces vauriens ont évidemment décidé de me chasser de la ville ! Jusqu'à présent, tout se passait comme d'habitude - ils revendaient des articles interdits, et quand les patrouilles les attrapaient, ils se cachaient ou les payaient. Mais récemment, ils ont ouvert quelque part une boutique dans une ruelle et ont commencé à vendre les marchandises les plus populaires à des prix incroyablement bas !\nJe ne peux pas me permettre ce luxe - en fait, je dois payer des taxes - je m'appauvris progressivement et les marins ne veulent presque plus de mes marchandises - toutes les marchandises, ils les achètent à ces scélérats.";
			link.l1 = "Mais tu aurais dû faire appel aux autorités ! Après tout, c'est leur travail - arrêter une telle anarchie.";
			link.l1.go = "Shadowtrader_trouble_3";
		break;
		
		case "Shadowtrader_trouble_3":
			dialog.text = "Vous avez vu le dernier résultat de l'appel vous-même. Le gouverneur est trop occupé et le commandant n'a pas cru que des contrebandiers avaient organisé des échoppes clandestines, ou il fait semblant de ne pas y croire - et, je suppose, c'est le cas\nBien sûr, pourquoi feraient-ils cela ? Et je dis : Je suis sûr que quelque gredin qui veut me détruire et m'expulser de la ville a tout inventé, et ensuite il arrangera tranquillement mes affaires pour laver leurs petites mains sales.";
			link.l1 = "Hm... votre opinion n'est pas infondée. C'est dans la nature des marchands - faire un faire-valoir de quelqu'un... Oh, je suis désolé, je ne parlais pas de vous, bien sûr. ";
			link.l1.go = "Shadowtrader_trouble_4";
		break;
		
		case "Shadowtrader_trouble_4":
			dialog.text = "Oh, rien... Et récemment, un vaurien est venu me voir et a effrontément dit que si je continuais à faire du bruit, ils brûleraient ma boutique\nAlors j'ai engagé un garde du corps. "+pchar.questTemp.Shadowtrader.Guardername+" n'est pas bon marché, mais c'est un professionnel et sous sa protection je peux me sentir un peu plus calme.";
			link.l1 = "Je vois... Une histoire désagréable, en effet. Apparemment, vous aviez raison - il n'y a rien que je puisse faire pour vous. Mais je suis certain que les choses s'arrangeront - ces établissements louches ne durent généralement pas longtemps. Eh bien, bonne chance !";
			link.l1.go = "Shadowtrader_end";
			link.l2 = "Je vois. Eh bien, peut-être pourrais-je quand même vous aider...";
			link.l2.go = "Shadowtrader_trouble_5";
		break;
		
		case "Shadowtrader_trouble_5":
			dialog.text = "Vous m'offrez quand même votre aide ? Mais que comptez-vous faire ?";
			link.l1 = "Je vais essayer de retrouver ce 'collègue' à vous et... le persuader de vous laisser tranquille. Vous savez, j'ai certaines compétences pour persuader les gens.";
			link.l1.go = "Shadowtrader_trouble_6";
		break;
		
		case "Shadowtrader_trouble_6":
			dialog.text = "Es-tu sérieux ? Que le Seigneur bénisse ta juste cause ! Si tu me débarrasses de cette vermine, je te serai redevable.";
			link.l1 = "D'accord, c'est un accord. Je vais commencer à chercher, alors.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.seeksmugglers = "true";
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
			AddQuestRecord("Shadowtrader", "2");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddQuestUserData("Shadowtrader", "sSex1", GetSexPhrase("ся","ась"));
		break;
		
		case "Shadowtrader_end":
			pchar.questTemp.Shadowtrader = "true";
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DialogExit();
		break;
		
		case "Shadowtrader_Escape_complete":
			dialog.text = "Est-ce vrai ? Je peux maintenant faire des affaires sans aucune crainte ? Oh, merci beaucoup ! Voici votre récompense - 15000 pesos. Quant aux marchandises dans leur maison, je suppose qu'il vaut mieux les remettre au commandant. Merci encore !";
			link.l1 = "De rien. Ce n'était pas trop difficile. Je t'avais dit que j'étais doué pour la persuasion.";
			link.l1.go = "Shadowtrader_complete";
		break;
		
		case "Shadowtrader_complete":
			dialog.text = "Revenez me voir, capitaine - je serai toujours heureux de vous voir.";
			link.l1 = "Bien sûr ! Et maintenant permettez-moi de prendre congé - j'ai des affaires à régler ! Adieu et bonne chance dans votre commerce, "+npchar.name+"!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.End");
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.Shadowtrader = "complete";
			AddQuestRecord("Shadowtrader", "11");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DeleteAttribute(pchar, "questTemp.Shadowtrader.EndFort");
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		//<-- мини-квест Бесчестный конкурент
	}
	UnloadSegment(NPChar.FileDialog2);
}
