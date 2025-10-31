// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions as-tu ?","Comment puis-je vous aider, "+GetAddress_Form(NPChar)+"?"),"Tu as essayé de me poser une question il n'y a pas longtemps, "+GetAddress_Form(NPChar)+"I need a room for the night.","Pendant toute cette journée, c'est la troisième fois que tu parles de cette question...","Encore des questions, je présume ?","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Oumph, où est passée ma mémoire...","Oui, c'est vraiment la troisième fois...","Non, quelles questions ?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";			
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Ecoutez, avez-vous vu un corsaire du nom de Francois Gontier ? Il a récemment été ici dans votre ville.";
                link.l1.go = "Portobello_rat_1";
            }			
			// карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && !CheckAttribute(npchar, "quest.trial"))
            {
                link.l1 = "Ecoute, pourrais-tu me dire où trouver un marchand nommé Jaime Silicio ? Il était censé venir te voir...";
                link.l1.go = "trial";
            }
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && !CheckAttribute(npchar, "quest.FMQG"))
            {
                link.l1 = "Écoute, je suis à la recherche d'un homme nommé Bertrand Pinette, as-tu entendu parler de lui ? Il est arrivé à Portobello il n'y a pas longtemps. Un gentleman imposant avec une perruque bouclée. Un marchand. Il aurait pu être ici...";
                link.l1.go = "FMQG";
            }
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Tavern_1"))
            {
                link.l1 = "Vous ne sauriez pas où je pourrais trouver Marisa Caldera ?";
                link.l1.go = "LFD_Tavern_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("Non, je ne sais pas. Il n'est pas passé à la taverne et je ne l'ai pas vu en ville non plus.","Tu as déjà posé cette question et je t'ai déjà répondu.","Je t'ai dit 'tu as déjà demandé à propos de ce Gontier'.","Ecoute, va-t'en et cesse de m'importuner ! As-tu complètement perdu la caboche ?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Eh bien, je continuerai à chercher.","Hm, je suppose que oui...","Oui, c'est ça, j'ai demandé ça...","Désolé, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;		

		case "trial":
			DelLandQuestMark(npchar);
			npchar.quest.trial = true;
			
			dialog.text = "Excusez-moi, señor, mais seul un traître ou un ivrogne discuterait de telles affaires avec un étranger. Je ne veux pas d'ennuis.";
			link.l1 = "Un ivrogne, tu dis ? À la prochaine, l'ami.";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Jamais entendu parler de lui, l'ami.";
			link.l1 = "Il est une connaissance de don Carlos de Milyar. Tu es sûr que tu n'as jamais entendu parler de lui ?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Je le suis. S'il est un ami de de Milyar - allez voir un gouverneur et demandez le senor Carlos. Il vous parlera de votre marchand.";
			link.l1 = "Je vais le faire. Merci pour le conseil !";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "9");
			npchar.quest.FMQG = true;
		break;
		//--> Письмо от покойника
		case "LFD_Tavern_1_1":
			dialog.text = "Marisa ? Hmm... Je ne l’ai pas vue depuis longtemps. Depuis qu’elle a appris la mort de son mari, elle ne s’est plus montrée en ville.";
			link.l1 = "Donc, elle est veuve ?";
			link.l1.go = "LFD_Tavern_1_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LFD_Tavern_1_2":
			dialog.text = "Oui. Son mari était le capitaine du pinas marchand 'Brise-Vague'. Grâce à une licence de la Compagnie néerlandaise des Indes occidentales, il avait accès à presque tous les ports de l’archipel. On raconte qu’il n’a pas survécu à une attaque de pirates entre Belize et Capsterville. Ce genre d’événement est fréquent ici, mais pour elle, ce fut un véritable choc.";
			link.l1 = "Et elle a tout simplement disparu ?";
			link.l1.go = "LFD_Tavern_1_3";
		break;
		
		case "LFD_Tavern_1_3":
			dialog.text = "Disparue, c’est peut-être un peu exagéré. Mais on la voit rarement depuis. Fait étrange... De temps en temps, des hommes demandent après elle. Comme vous, capitaine. Si elle n’était pas aussi pieuse, j’aurais cru qu’elle s’était cachée pour... gagner sa vie autrement. Mais Marisa, avant la mort de son mari, ne manquait jamais une messe. Elle vivait littéralement à l’église. Alors c’est peu probable.";
			link.l1 = "C’est tout ? Tu ne sais rien d’autre ?";
			link.l1.go = "LFD_Tavern_1_4";
		break;
		
		case "LFD_Tavern_1_4":
			dialog.text = "Tout ce que je sais, capitaine, je vous l’ai déjà dit.";
			link.l1 = "...";
			link.l1.go = "LFD_Tavern_1_5";
		break;
		
		case "LFD_Tavern_1_5":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Tavern_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
