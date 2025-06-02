//Jason общий диалог дворянок
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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
			//первая встреча
            if(NPChar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = "Hm. Vous naviguez sous le drapeau de "+NationNameGenitive(sti(pchar.nation))+", capitaine. Je n'ai aucune envie de parler avec l'ennemi de mon pays. Hmph!";
					link.l1 = "Ah, oui. Un vrai patriote...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = RandPhraseSimple("Que veux-tu de moi, "+GetAddress_Form(NPChar)+"? Ce n'est pas approprié pour un simple marin de parler avec une noble dame, mais je vous écoute.","Oh, et que veut un capitaine si brave de moi ?");
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+"Je ne prendrai pas beaucoup de votre temps, je veux juste demander...";
					link.l1.go = "question";
					link.l2 = RandPhraseSimple("J'ai besoin de savoir ce qui se passe dans ta colonie.","J'ai besoin de quelques renseignements.");
					link.l2.go = "quests";//(перессылка в файл города)
				}
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("  Toute la ville est sur le qui-vive - don Fernando de Alamida, l'inspecteur royal, est arrivé. Vous savez, j'en ai vu beaucoup ici, mais ça... Ce n'est pas le chagrin qui change les gens, mais la façon dont ils y font face. On dit qu'il est devenu un autre homme après la mort de son père. Maintenant, vous ne trouverez pas de serviteur de la Couronne plus incorruptible et... impitoyable dans tout l'Archipel.  ","Regardez donc le 'Saint Miséricorde' ! On dit que le roi lui-même a ordonné sa construction selon des plans spéciaux. Et remarquez - pas une seule égratignure. Comme si la Vierge Marie elle-même le protégeait. Bien que j'aie entendu des rumeurs... peut-être que ce n'est pas la Vierge du tout.","Vous savez combien de fois ils ont essayé de tuer don Fernando ? Douze attaques en pleine mer - et c'est rien que l'année dernière ! Eh bien, avec un équipage aussi loyal et entraîné, et sous la protection du Seigneur - il survivra aussi à la treizième !"),LinkRandPhrase("As-tu entendu? Don Fernando de Alamida est arrivé dans notre ville, et il paraît qu'il se promène quelque part dans les rues en ce moment. J'adorerais le voir de mes propres yeux...","Un homme compliqué, ce don Fernando. Certains disent qu'il est un sauveur, purifiant la Mère Patrie de la vermine. D'autres chuchotent que quelque chose s'est brisé en lui après la mort de son père et que bientôt nous pleurerons tous. Mais je vais te dire ceci : ne le crains pas. Crains ceux qui ont fait de lui ce qu'il est.","Quel bel homme, ce don Fernando ! Mais sais-tu ce qui est étrange ? C'est comme s'il ne remarquait personne. Tout devoir et service. J'ai entendu dire qu'il y avait une fille... mais après avoir rencontré un prêtre, il a complètement rejeté les plaisirs mondains. Comme s'il avait fait un vœu."),RandPhraseSimple(RandPhraseSimple("Satané inspecteur ! Tant qu'il est là - la ville est comme morte. Pas de commerce, pas de divertissement. Même respirer, il semble, doit être plus silencieux. Et tu sais ce qui est le plus effrayant ? C'est pareil dans chaque port. Comme une horloge. Sa Majesté Royale n'aurait pas pu inventer délibérément ce supplice pour nous tous !","Don Fernando a de nouveau visité l'orphelinat. Il fait des dons généreux, prie pendant des heures. Un homme si digne devrait être tenu en exemple face à ces maudits escrocs !"),RandPhraseSimple("Ha ! 'Saint' Fernando a fermé tous les bordels encore une fois. Bah, ça ne fait rien, il repartira bientôt en mer et ils rouvriront aussitôt.","L'insp... inspecteur est arrivé, c'est ça ! Don Fernando de Almeyda, ou, comment il s'appelle, Alamida ! Si important que le gouverneur lui-même marche sur des oeufs autour de lui. On dit qu'il te regarde dans les yeux et voit tous tes péchés immédiatement. Terrifiant !")));
					link.l1 = "... ";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Dois-je me répéter? Je ne veux pas être soupçonné d'être un ami de "+NationNameAblative(sti(pchar.nation))+"Pars ou je vais appeler les gardes! Ils seraient ravis de te parler.";
					link.l1 = "D'accord, d'accord, calme-toi. Je m'en vais.";
					link.l1.go = "exit";
				}
				else
				{
				dialog.text = NPCStringReactionRepeat("Quoi ? Vous encore ? Cherchez quelqu'un d'autre à qui parler. Il y a beaucoup de manants qui se promènent, ils sont plus de votre genre. Je dois y aller maintenant, il y aura un banquet ce soir à la résidence du gouverneur et ma coiffure n'est pas encore prête !","Non, maintenant tu deviens vraiment agaçant ! Ne comprends-tu pas ? Ou es-tu lent d'esprit ?","Monsieur, je commence à soupçonner que vous n'êtes pas seulement un idiot mais aussi un vaurien et un rustre. Je vous avertis que j'appellerai mon mari si vous ne cessez de m'importuner avec vos questions stupides !","Un mot de plus et je dirai au commandant de faire quelque chose avec toi !","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Je vois. Adieu.","Oui-oui, je me souviens, j'ai juste oublié de demander...","Tu t'es trompé sur moi...","Du calme, madame, je m'en vais déjà...",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				}
			}
			NextDiag.TempNode = "First time";
		break;

		//сюда вставляем любые проверки и направления на квесты
		case "question":
			dialog.text = LinkRandPhrase("D'accord, écoutons.","Oh, très bien. Que veux-tu ?","Des questions ? Très bien, matelot, je t'écoute.");
			link.l1 = LinkRandPhrase("Peux-tu me raconter les derniers ragots de cette ville ?","Y a-t-il eu quelque chose d'intéressant ici récemment ?","Des nouvelles des Caraïbes, ma dame ?");
			link.l1.go = "rumours_noblegirl";
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Es-tu fou ?! Tu me fais peur ! Rengaine ton arme ou je dirai au commandant de te pendre dans le fort !","Es-tu fou ?! Tu me fais peur ! Rengaine ton arme ou je dirai au commandant de te pendre au fort !");
			link.l1 = LinkRandPhrase("D'accord.","Comme vous le souhaitez.","Très bien.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
