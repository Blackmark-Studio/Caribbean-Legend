// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Questions, "+GetAddress_Form(NPChar)+"?","Comment puis-je vous aider, "+GetAddress_Form(NPChar)+"?"),"Bonjour, monami."+GetSexPhrase("Hm, quelle est la grande idée, "+GetAddress_Form(NPChar)+"? ","Encore avec les questions étranges ? Ma grande, va prendre du rhum ou quelque chose comme ça...")+"","Pendant toute cette journée, c'est la troisième fois que tu parles d'une question..."+GetSexPhrase(" Est-ce là quelques signes d'attention ?","")+" ","Plus de questions, je présume, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis","Je n'ai rien à dire pour le moment."),"Non, non belle...","Pas question, ma chère...","Non, quelles questions ?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_2"))
			{
				link.l1 = "Je dois te poser quelques questions. Tu travaillais à la taverne le jour où le tonneau de gin a disparu, n’est-ce pas ? Qu’est-ce que tu peux me dire sur ce qui s’est passé ici ?";
				link.l1.go = "OS_Tavern2_1";
			}
			//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern2_1":
			dialog.text = "Je... je ne sais pas quoi dire. Tout était comme d’habitude, rien d’étrange.";
			link.l1 = "Ah oui ? Rien d’étrange ? Et ce marin du 'Sea Wolf' qui t’a draguée ce jour-là ? Il semblait penser que tu étais partante pour passer la nuit avec lui.";
			link.l1.go = "OS_Tavern2_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern2_2":
			dialog.text = "Ah, lui ! Il... il avait juste un peu trop bu, voilà tout. Ça arrive souvent ici, vous savez. Je ne l’ai évidemment pas encouragé, mais il s’est montré insistant. Alors je lui ai tenu tête.";
			link.l1 = "Tu ne l’as pas encouragé ? Pourtant, lui voit les choses autrement. Pourquoi as-tu crié cette fois, et pas les autres ?";
			link.l1.go = "OS_Tavern2_3";
		break;

		case "OS_Tavern2_3":
			dialog.text = "Je... je ne sais pas quoi vous dire d’autre ! Je ne sais vraiment rien ! J’étais... j’étais à la vue de tous, toute la soirée ! Je n’ai rien vu, rien entendu ! Et pour le tonneau... je ne suis pas au courant, je ne sais pas ce qu’il est devenu ! Pourquoi cet interrogatoire ? J’étais juste... je faisais juste mon travail, comme toujours !";
			link.l1 = "Je crois que tu caches quelque chose. Tu sais, une nuit dans la cale, sans lumière ni nourriture, ça fait des merveilles sur la mémoire. Tu veux essayer ? Ou on en parle calmement ?";
			link.l1.go = "OS_Tavern2_4_HO";
			link.l2 = "Moi, je crois que tu sais bien plus que ce que tu dis. Tu as une chance unique : raconte tout maintenant, et je tairai ton rôle dans cette histoire. Mais si tu te tais, ce sera pire pour toi. Je finirai bien par découvrir la vérité.";
			link.l2.go = "OS_Tavern2_4_harizma";
		break;

		case "OS_Tavern2_4_HO":
			dialog.text = "Je... je... je vais tout vous dire ! C’est... c’est mon prétendant, Jack. Jack Veils ! C’est lui qui m’a demandé de séduire un marin quelconque du 'Sea Wolf'. Et quand l’un d’eux se montrerait trop audacieux, je devais faire un esclandre pour faire sortir le patron de derrière le comptoir. Quand les choses se seraient un peu calmées, deux autres marins devaient se battre pour le retenir dans la salle. C’est exactement ce qui s’est passé\nPendant ce temps, le capitaine du 'Sea Wolf' a volé le tonneau. C’est... c’est tout ce que je sais, "+GetSexPhrase("monsieur","madame")+" ! Je vous en supplie, ne me dénoncez pas ! Je voulais juste que Jack commence enfin à me respecter ! Je l’ai aidé...";
			link.l1 = "Tu en as aidé un, mais tu as sacrifié l’autre sans scrupules ? Très bien, j’ai promis de ne pas te dénoncer – je tiendrai parole. Mais tu devras vivre avec ça ! À cause de ta stupidité, l’aubergiste aurait pu avoir de graves ennuis. Où est ton Jack ? Et attention : si tu mens, je reviendrai. Et crois-moi, tu ne veux pas que ça arrive.";
			link.l1.go = "OS_Tavern2_5";
			AddComplexSelfExpToScill(40, 40, 40, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;

		case "OS_Tavern2_4_harizma":
			dialog.text = "Je... je... je vais tout vous dire ! C’est... c’est mon prétendant, Jack. Jack Veils ! C’est lui qui m’a demandé de séduire un marin quelconque du 'Sea Wolf'. Et quand l’un d’eux se montrerait trop audacieux, je devais faire un esclandre pour faire sortir le patron de derrière le comptoir. Quand les choses se seraient un peu calmées, deux autres marins devaient se battre pour le retenir dans la salle. C’est exactement ce qui s’est passé\nPendant ce temps, le capitaine du 'Sea Wolf' a volé le tonneau. C’est... c’est tout ce que je sais, "+GetSexPhrase("monsieur","madame")+" ! Je vous en supplie, ne me dénoncez pas ! Je voulais juste que Jack commence enfin à me respecter ! Je l’ai aidé...";
			link.l1 = "Tu en as aidé un, mais tu as sacrifié l’autre sans scrupules ? Très bien, j’ai promis de ne pas te dénoncer – je tiendrai parole. Mais tu devras vivre avec ça ! À cause de ta stupidité, l’aubergiste aurait pu avoir de graves ennuis. Où est ton Jack ? Et attention : si tu mens, je reviendrai. Et crois-moi, tu ne veux pas que ça arrive.";
			link.l1.go = "OS_Tavern2_5";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "OS_Tavern2_5":
			dialog.text = "Je ne pensais pas que c'était si grave ! Après tout, ce n'est qu’un tonneau... Jack habite en face. Il loue une maison, je... je ne sais rien de plus ! Pardonnez-moi, je vous en supplie ! Capitaine, je vous jure que je ne referai jamais ça !";
			link.l1 = "Retourne à ton service, et ne commence pas à pleurnicher, que le patron ne soupçonne rien.";
			link.l1.go = "OS_Tavern2_6";
		break;
		
		case "OS_Tavern2_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_2");
			AddQuestRecord("OS", "4");
			
			//
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.cask_gin = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.map_full = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.jewelry2 = 10;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.GunPowder = 50;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.bullet = 50;
			
			PChar.quest.OS_Zasada.win_condition.l1 = "item";
			PChar.quest.OS_Zasada.win_condition.l1.item = "cask_gin";
			PChar.quest.OS_Zasada.function = "OS_Zasada";
		break;
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
