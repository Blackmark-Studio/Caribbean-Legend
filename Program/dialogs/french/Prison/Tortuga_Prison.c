// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Parle, j'écoute";
			link.l1 = "Je me suis trompé. Adieu.";
			link.l1.go = "Exit";
		break;
		
		case "tonzag_bail":
			NextDiag.TempNode = "First_officer";
		
			dialog.text = "Quel est le but de votre visite à Tortuga, Capitaine ?";
			link.l1 = "Je vous en supplie ! Aidez mon camarade, et je répondrai à toutes vos questions !";
			link.l1.go = "tonzag_bail_a";
			link.l2 = "Vous êtes une personne si importante, et vous êtes venu ici sans aucune garde, juste après que toute la prison ait entendu un coup de feu?!";
			link.l2.go = "tonzag_bail_b";
		break;
		
		case "tonzag_bail_a":
			dialog.text = "Tandis que tu tardes à répondre, il est en train de se vider de son sang. Je répète la question.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_b":
			dialog.text = "Je sais assez bien ce qui s'est passé. Je répète la question.";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Dernière chance, Capitaine.";
			link.l1 = "J'accomplis la tâche qui m'a été confiée par le gouverneur général !";
			link.l1.go = "tonzag_bail_truth";
			link.l2 = "Tu sais très bien que je suis Capitaine de mon propre navire, et que je travaille sous contrat. Et je visite votre charmante île quelques fois par an !";
			link.l2.go = "tonzag_bail_lies";
		break;
		
		case "tonzag_bail_truth":
			dialog.text = "J'avais mes doutes, mais je n'étais pas complètement sûr. Tu as de la chance qu'il y a quelques jours seulement, une réunion importante ait eu lieu à Capsterville. Des personnes très influentes ont réussi à trouver un accord. Ainsi, tu n'es plus mon ennemi.";
			link.l1 = "Nous aiderez-vous ?";
			link.l1.go = "tonzag_bail_truth_1";
			
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
		case "tonzag_bail_truth_1":
			dialog.text = "Je vous libère immédiatement. Votre camarade sera transféré sur le navire et recevra des soins.";
			link.l1 = "Merci...";
			link.l1.go = "tonzag_bail_truth_2";
		break;
		
		case "tonzag_bail_truth_2":
			dialog.text = "Tu as failli t'échouer, Charles ! Pars et ne reviens pas à Tortuga pendant au moins un mois. Laisse la poussière retomber et les esprits se calmer.";
			link.l1 = "Je vais faire cela. À la revoyure !";
			link.l1.go = "exit";
			link.l2 = "Ne vas-tu rien expliquer du tout ? Même un petit peu ? ...";
			link.l2.go = "tonzag_bail_truth_3";
		break;
		
		case "tonzag_bail_truth_3":
			dialog.text = "Quelqu'un vous a dénoncé. Apparemment, vous êtes un catholique fanatique arrivé sur notre belle île pour tuer sournoisement son honorable gouverneur.";
			link.l1 = "Je ne suis pas un fanatique !";
			link.l1.go = "tonzag_bail_truth_4";
		break;
		
		case "tonzag_bail_truth_4":
			dialog.text = "C'est écrit avec habileté, crois-moi. Je suis bon dans ce genre de choses - les meilleures calomnies sont celles qui contiennent au moins un grain de vérité.";
			link.l1 = "Qui a écrit le rapport ?";
			link.l1.go = "tonzag_bail_truth_a";
			link.l2 = "Qui a laissé entrer le meurtrier dans la prison?";
			link.l2.go = "tonzag_bail_truth_b";
		break;
		
		case "tonzag_bail_truth_a":
			dialog.text = "Quelqu'un qui voulait que tu sois enfermé dans la prison pendant quelques jours, au lieu de t'envoyer immédiatement sur la table de torture des Huguenots dans le sous-sol de La Roche.\nAssez, Charles. Pars. Occupe-toi d'abord de ce que tu as devant toi, et après... eh bien, tu me comprends!";
			link.l1 = "Oui. Je le ferai. Adieu, Commandant.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail_truth_b":
			dialog.text = "Je l'ai fait.";
			link.l1 = "Tu ferais mieux d'en envoyer chercher un autre avant que je ne parte d'ici.";
			link.l1.go = "tonzag_bail_truth_b_threat";
			link.l2 = "Je suis tout ouïe, commandant.";
			link.l2.go = "tonzag_bail_truth_b_charm";
		break;
		
		case "tonzag_bail_truth_b_threat":
			AddComplexSelfExpToScill(100, 100, 100, 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "Je ne suis pas obligé de t'expliquer quoi que ce soit, Charles. Sois heureux que tu sois tombé entre mes mains et non entre celles de mon supérieur direct. Et sois heureux que ce soit ton patron qui me dédommagera pour tous ces troubles, et non toi.";
				link.l1 = "Riiiiiiight... Vous ne connaissez pas mon patron comme moi. Adieu, commandant.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "Tu sais quoi ? Je pense que je vais te le dire. Un don généreux, exempt d'impôts, a été fait au fonds de pension spécial de la garnison. En signe de gratitude, le donateur a été autorisé à contribuer à l'exécution rapide et légale d'un criminel notoire !";
				link.l1 = "Mon officier ?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "Mon ami ?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_charm":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "Je ne suis point obligé de t'expliquer quoi que ce soit, Charles. Réjouis-toi d'être tombé entre mes mains et non celles de mon supérieur direct. Et réjouis-toi que ce soit ton patron qui me dédommagera pour tous ces désagréments, et non toi.";
				link.l1 = "Riiiiiiight... Vous ne connaissez pas mon patron comme moi. Adieu, commandant.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "Tu sais quoi ? Je pense que je vais te le dire. Un don généreux, exempt d'impôts, a été fait au fonds spécial de pension de la garnison. En guise de gratitude, le donateur a été autorisé à contribuer à l'exécution rapide et légale d'un criminel notoire !";
				link.l1 = "Mon officier ?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "Mon ami?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_1":
			dialog.text = "Pars, Charles. Et emmène cette vermine avec toi. Ton choix de compagnons... est décevant.";
			link.l1 = "Au moins, dis-moi où trouver ton... bienfaiteur ?";
			link.l1.go = "tonzag_bail_truth_b_2";
		break;
		
		case "tonzag_bail_truth_b_2":
			dialog.text = "Sur le continent. Adieu, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.TonzagQuest.KnowMain = true;
			AddQuestRecord("Tonzag", "3.2");
		break;
		
		case "tonzag_bail_lies":
			dialog.text = "Un rapport a été déposé contre vous. Un très vilain. Capitaine, il est évident que vous avez été piégé, mais... je suis pleinement dans mon droit de vous garder ici encore quelques semaines et de laisser votre ami mourir. À moins que...";
			link.l1 = "Combien ?";
			link.l1.go = "tonzag_bail_lies_a";
			link.l2 = "Qui m'a piégé ? Avez-vous laissé entrer le meurtrier dans la prison ?";
			link.l2.go = "tonzag_bail_lies_b";
			
			AddDialogExitQuestFunction("Tonzag_Bailed");
		break;
		
		case "tonzag_bail_lies_a":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Veuillez déposer cinq cents doublons dans le fonds de pension de la garnison de Tortuga chez le prêteur local.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" Et ajoutons une centaine de doublons supplémentaires pour les vieux ennuis que tu as causés en te mêlant d'une dame de haut rang sur cette île.";
			}
			link.l1 = "Ouvre cette satanée porte déjà!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bail_lies_b":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Tu as déjà pris trop de mon temps. Va chez l'usurier et dépose cinq cents doublons dans le fonds de pension de la garnison de Tortuga.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" Et ajoutons encore cent doublons pour les vieux ennuis que tu as causés en te mêlant d'une dame de haut rang sur cette île.";
			}
			link.l1 = "Ouvre-moi cette foutue porte déjà !";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bailed":
			dialog.text = "";
			link.l1 = "Les fonds sont déposés. Où est Hercule ?";
			link.l1.go = "tonzag_bailed_1";
		break;
		
		case "tonzag_bailed_1":
			dialog.text = "Nous lui avons prodigué les premiers soins et l'avons envoyé à votre navire. Le gredin est coriace, il s'en sortira probablement. Adieu, Capitaine, et ne laissez pas que je vous surprenne sur notre île pendant un moment !";
			link.l1 = "Eh bien, après un tel accueil, je resterai bien loin d'ici! Adieu, commandant.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
