// общий диалог ростовщиков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle, sDepositType1, sDepositType2;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp, iTotalDublonQty;
	int iRes, iPer, iDep;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;
	sDepositType1 = NPC_Area + "_Type1";
	sDepositType2 = NPC_Area + "_Type2";
 
	if(!CheckAttribute(npchar, "quest.item_date"))
	{
		npchar.quest.item_date = "";
	} 
 
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
    }

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				//--> работорговец
				if(pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text = "C'est fini. Maintenant quittez cet endroit, "+pchar.name+"Je vais nettoyer tout ce bazar.";
					link.l1 = "D'accord, je vais prendre la mer !";
					link.l1.go = "exit";
					break;
				}
				//<-- работорговец
			
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("La ville est en alerte et ils te cherchent partout ! Si j'étais toi, je ne resterais pas ici longtemps.","Tous les gardes te recherchent. Je ne suis pas idiot et je ne prendrai pas le risque de te parler !","Courez, "+GetSexPhrase("pote","fille")+", avant que les soldats ne te transforment en passoire..."),LinkRandPhrase("Que veux-tu, vile créature ?! Les gardes de la ville sont au courant de ta position et tu ne t'enfuiras pas, "+GetSexPhrase("pirate immonde","putain de pirate")+"!","Sale meurtrier, éloigne-toi de chez moi ! Gardes !","Je ne te crains pas, vile créature ! Bientôt tu seras pendu dans notre fort, tu ne t'en sortiras pas..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, ce n'est pas un problème pour moi...","Ils ne m'attraperont jamais."),RandPhraseSimple("Ferme ta gueule, "+GetWorkTypeOfMan(npchar,"")+", ou je te couperai la maudite langue !","Heh, "+GetWorkTypeOfMan(npchar,"")+", veux-tu attraper un pirate aussi ? Écoute, garçon, assieds-toi ici tranquillement et tu vivras..."));
				link.l1.go = "fight";
				break;
			}
		//Jason ---------------------------------------Бремя гасконца------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_bank")
			{
				dialog.text = "Besoin de quelque chose, monsieur?";
				Link.l1 = "J'ai besoin d'informations... Je veux vous poser une question.";
				Link.l1.go = "quests";
				Link.l2 = "Que diriez-vous d'un petit prêt ?";
				Link.l2.go = "sharlie_credit";
				Link.l3 = "Non, j'ai changé d'avis.";
				Link.l3.go = "exit";
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Regardez ces boucles d'oreilles, monsieur. Je les ai trouvées dans la poche d'un bandit dans la jungle. C'est clairement l'œuvre d'un bon bijoutier qui, j'en suis sûr, ne vient pas de cette contrée sauvage. Qu'en dites-vous ?";
					link.l4.go = "Sharlie_junglejew";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
				{
					link.l1 = "Je sais que vous avez un débiteur du nom de Folke Deluc. Dites-moi, à quel point est-il... en retard?";
					link.l1.go = "Sharlie";
				}	
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
				{
					link.l1 = "Je suis ici au sujet de la dette de Folke Deluc.";
					link.l1.go = "Sharlie_repeat";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
				{
					link.l1 = "J'ai accompli votre mission, monsieur. Voici votre... ami espagnol.";
					link.l1.go = "Sharlie_14";
				}
				break;
			}			
		//<-- Бремя гасконца
			
			//--> работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Eh bien, enfin un capitaine digne de ce nom a visité mon établissement, je suis tellement fatigué des idiots qui pensent que je plante simplement leurs doublons et guinées et que je récolte chaque mois afin de leur payer leurs intérêts\nIls surveillent chaque sou, tout en n'ayant aucune idée de la façon dont le pauvre usurier recourt à divers stratagèmes pour éviter de mourir de faim lui-même et, en même temps, leur offrir l'opportunité d'acheter une oie pour Noël.";
				Link.l1 = "Je suppose que vos clients ne seront pas ravis d'entendre de telles paroles de la part de l'homme qui détient leurs économies.";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "Ecoute, vieux hamster, tu dois vraiment faire de ton mieux maintenant pour tout m'expliquer ! Il n'y avait pas d'esclaves dans la cargaison de ce navire mais une compagnie de soldats ! Ce fut une mission vraiment ardue de les affronter ! Je suis très en colère, alors tu ferais mieux de t'expliquer !";
				Link.l1.go = "Slaveshore_5";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Ah, te voilà enfin ! Tout l'archipel bavarde de ton audacieuse attaque. Ravi de te voir !";
				Link.l1 = "Je préférerais l'obscurité à ce genre de renommée... C'est trop dangereux.";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "As-tu apporté mes cinq mille esclaves ?";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
					Link.l1 = "Je les ai. Ils sont dans ma cale.";
					Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "Non, je travaille encore dessus.";
					Link.l1.go = "exit";
				}
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Hm.. Tu es encore en vie ? Étrange. Mais ça ne durera pas longtemps. Soldats ! À l'aide ! J'ai un bandit ici !";
				link.l1 = "Quel salaud !";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}
			
			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Bonne journée. Mon nom est "+GetFullName(npchar)+"Que puis-je faire pour vous être utile ?";
				link.l1 = "Oh ! Que faites-vous ici, monsieur ?";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<-- работорговец
			// ФМК-Гваделупа
			if(CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers" && npchar.location == "BasTer_bank")
			{
				dialog.Text = "...";
				link.l1 = "Hé là, salaud. As-tu eu une idée brillante ? As-tu engagé des brutes pour me tuer ? Vouliez-vous me faire taire ? Parle, maintenant !";
				link.l1.go = "FMQG_x";
				break;
			}
			// Леди Бет -->
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_Bank" && !CheckAttribute(pchar, "questTemp.LadyBeth_Usurer")) // Блеквуд в городе
			{
				dialog.Text = "Oh, capitaine ! Regardez ce que j’ai aujourd’hui. J’ai acquis certaines choses auprès des hommes de Blackwood. Ils ont besoin d’argent pour une nouvelle expédition, et nous - nous y gagnons, n’est-ce pas ?";
				link.l1 = "Blackwood sait-il que ses hommes vendent leurs découvertes ?";
				link.l1.go = "LadyBeth_Usurer_1";
				break;
			}
			// Леди Бет <--
			
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase("Bonne journée à vous, "+GetAddress_Form(NPChar)+". Comment puis-je vous aider? Vous connais-je?","Entrez, capitaine. Mon nom est "+GetFullName(npchar)+" et je suis le banquier local.","Enchanté de faire votre connaissance, "+GetAddress_Form(NPChar)+"Je suis un banquier local et si vous avez un problème d'argent, je peux vous aider."),LinkRandPhrase("Nous sommes-nous déjà rencontrés, capitaine ? Je suis "+GetFullName(npchar)+", et je suis un banquier local.","Entrez, capitaine. Mon nom est "+GetFullName(npchar)+" et je suis le banquier local.","Salutations, "+GetAddress_Form(NPChar)+". Je suis "+GetFullName(npchar)+", le banquier local."),LinkRandPhrase("Enchanté de vous rencontrer, "+GetAddress_Form(NPChar)+", je suis "+GetFullName(npchar)+" juste un modeste banquier dans cette merveilleuse ville.","C'est à vous de décider, capitaine ! Voulez-vous emprunter quelques pièces chez moi ou prêter de l'argent avec intérêt ?","Capitaine ! Je suis si heureux que vous ayez visité mon modeste bureau !"));
				link.l1 = RandPhraseSimple(LinkRandPhrase("Mon plaisir ! Je me promenais juste en ville et j'ai décidé de vous rendre visite.","Tout le plaisir est pour moi, je suis "+GetFullName(pchar)+", enchanté de faire votre connaissance.",""+GetFullName(pchar)+" , capitaine du navire nommé "+pchar.ship.name+" , ravi de vous rencontrer. Ceci est une banque, n'est-ce pas ?"),RandPhraseSimple("Enchanté de vous rencontrer. Je suis "+GetFullName(pchar)+". Un capitaine du navire nommé "+pchar.ship.name+"Je voulais juste faire votre connaissance.","Ah, donc vous avez une banque ici, n'est-ce pas? Enchanté de vous rencontrer, je suis "+GetFullName(pchar)+", capitaine de mon propre navire."));
				link.l1.go = "next";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_bank")
				{
					dialog.text = "Lady MacArthur, bienvenue, entrez donc.";
					link.l1 = "Et à vous, "+npchar.lastname;
					link.l1.go = "Helen_next";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("C'est vous ! Que voulez-vous, "+GetAddress_Form(NPChar)+"?","Quelle est votre affaire ici, capitaine ? Je suis désolé, mais votre réputation ne fait pas de vous un client très recherché.","Aha, un autre client ! Au début, j'ai pensé que vous étiez un voleur... ha-ha je plaisante juste."),LinkRandPhrase("Oh ! Que voulez-vous ? C'est une banque, pas une taverne.","Bonne journée à vous, capitaine. Je dois vous informer que je suis assez sélectif dans le choix de mes clients.","Que voulez-vous, "+GetFullName(pchar)+" ? J'espère que vous vous souvenez que votre renommée ne vous permettra pas d'obtenir un prêt important ?"),LinkRandPhrase("J'espère que vous souhaitez investir de l'argent, "+GetAddress_Form(NPChar)+"? Il ne sera pas facile de vous accorder un prêt.","Capitaine "+GetFullName(pchar)+" que voulez-vous du modeste banquier ? Je suis désolé mais je ne pourrai pas vous accorder un prêt. Vous ne pouvez me prêter de l'argent qu'avec intérêt.","Entrez, "+GetAddress_Form(NPChar)+"Je suis désolé de vous informer que vous n'êtes pas le client le plus bienvenu, mais je ne rejette généralement pas les gens immédiatement.")),LinkRandPhrase(LinkRandPhrase("Bonjour, monsieur "+GetFullName(pchar)+"Je suis toujours prêt à vous aider dans vos affaires.","Bonjour, monsieur "+GetAddress_Form(NPChar)+"Je suis toujours prêt à accorder un prêt ou à accepter tout investissement.","Cher "+GetFullName(pchar)+" ! Heureux de vous voir ! Que souhaitez-vous ? "),LinkRandPhrase("Capitaine "+GetFullName(pchar)+"Je suis toujours à votre service. Voulez-vous emprunter de l'argent ou investir à intérêt ?","Salutations à vous, capitaine ! Vous êtes toujours un client désiré ici. Vous avez une excellente réputation commerciale !","Bonne journée, "+GetFullName(pchar)+"Je suis ravi que vous m'ayez rendu visite à nouveau. J'espère que vous êtes venu pour un accord commercial profitable ?"),LinkRandPhrase("Bonjour à vous, capitaine ! Que désirez-vous ? Voulez-vous contracter un prêt ou faire un investissement ?","Capitaine "+GetFullName(pchar)+"! Voulez-vous prêter de l'argent à des conditions avantageuses ? Je suis toujours ravi de voir un client aussi respectable.","Ravi de vous revoir, capitaine ! Je suis toujours prêt à vous aider, que ce soit pour contracter un prêt ou réaliser un investissement.")));
				link.l1 = pcharrepphrase(RandPhraseSimple(LinkRandPhrase("Sans blague, banquier, j'ai une affaire ici.","Tu parles trop, l'ami. Allons droit au but.","As-tu entendu dire que l'argent n'a pas d'odeur ? Alors bouche-toi le nez et passons aux affaires."),LinkRandPhrase("Et c'est ainsi que vous accueillez vos clients ? Vous avez de la chance que je sois de bonne humeur aujourd'hui.","Ha ! Ne suis-je pas content de te voir, hein ? Et ne suis-je pas comme un doublon d'or pour te faire bonne impression. Enfin, faisons des affaires, usurier.","Eh, j'aimerais t'apprendre le respect mais je n'ai pas le temps pour ça. Parlons plutôt d'argent.")),RandPhraseSimple(LinkRandPhrase("Ravi de voir mon vieil ami !","C'est toujours un plaisir de venir ici, l'ami. Allons droit au but.","Je suis très heureux aussi. Parlons affaires, ami."),LinkRandPhrase("Vraiment ravi de vous rencontrer. Quelles sont les nouvelles dans les mers financières ?","Ravi que tu te souviennes encore de moi. Je suis pressé, alors allons droit au but.","Bonjour, vieil ami ! Heureux de te revoir !")));
				link.l1.go = "next";
			}
			break;
			
			case "next":
			dialog.text = NPCStringReactionRepeat("Comment puis-je vous aider ?","Que souhaitez-vous cette fois-ci ?","Hm... quelles sont vos préoccupations ?","Eh, "+GetAddress_Form(npchar)+", vous ne pouvez même pas imaginer à quel point les clients peuvent être agaçants...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Non merci, je ne fais que me promener et discuter.","Moi encore. Je voulais juste parler avec vous.","Oui, c'est encore moi. Rien de grave, je voulais juste discuter avec vous.","Oui, être banquier n'est pas toujours facile. Je voulais juste parler...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Je veux discuter de nos affaires financières.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Je suis intéressé par les bijoux et les idoles ou les pierres précieuses inhabituelles.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "J'ai besoin de quelques informations. Eh bien, j'ai quelque chose à vous demander.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Je vous ai apporté les documents d'affaires de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Je suis ici sur les ordres d'un homme. Il est un gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" m'a envoyé ici. Je dois obtenir quelque chose de vous.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Bonjour, j'ai été invité par votre fils."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Je suis intéressé de savoir qui est le propriétaire du document.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "Je veux parler de la dette de votre client. Son nom est "+pchar.GenQuest.Noblelombard.Name+"Il a mis en gage la relique de sa famille. Je représente ses intérêts ici et j'ai le droit de discuter avec vous de son retour.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Nous avons eu une réunion il y a trois mois et avons parlé de la relique d'un homme. Son nom était "+pchar.GenQuest.Noblelombard.Name+". Souvenez-vous de cela ? Il devait ouvrir un dépôt à mon nom. La somme est  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "C'est au sujet de votre ... mission d'esclave.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonjour, "+NPChar.name+", parlons de votre mission.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonne journée, "+NPChar.name+", parlons de votre mission.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonne journée, "+NPChar.name+", parlons de votre mission.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Je suis venu, comme convenu. Un travail pour moi ?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Je suis venu comme promis. Que diriez-vous d'un travail ?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonne journée, "+npchar.name+"Comment allez-vous ? Avez-vous une nouvelle mission pour moi ?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Votre mission est accomplie. J'ai pu retrouver ces fugitifs. Cela n'a cependant pas été si facile.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonjour, "+npchar.name+"Je suis venu pour une nouvelle mission lucrative.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Mauvaises nouvelles,"+npchar.name+" . J'ai échoué à obtenir le brigantin.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Regarde,  "+npchar.name+". J'ai pourchassé la brigantine, mais je n'ai trouvé aucun document. Êtes-vous certain qu'ils étaient bien là?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonnes nouvelles,"+npchar.name+"J'ai pu traquer cette brigantine et trouver les papiers. Les voici.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonne journée, "+npchar.name+"Avez-vous préparé une nouvelle mission pour moi ?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", j'ai pu intercepter ce soi-disant 'galion'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Je suis navré mais je n'ai pas pu aborder ce galion.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonne journée, "+npchar.name+" Je suis venu pour mon argent.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", ta mission est accomplie. Ce salaud de Gontier est mort, ainsi que son équipage.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", je suis désolé mais j'ai échoué à attraper Francois Gontier, bien que je le suive jusqu'à Tortuga. Il a réussi à s'échapper avec sa corvette.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonne journée,"+npchar.name+"Parlez-moi de cette nouvelle mission que vous avez préparée pour moi.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;
		
		case "Helen_next":
			dialog.text = NPCStringReactionRepeat("Je ne dirais pas que vous avez besoin d'argent ou que vous cherchez à faire fructifier votre richesse. Qu'est-ce qui vous amène dans mon bureau ?","Que désirez-vous cette fois-ci ?","Hm... quelles sont vos préoccupations ?","Eh, "+GetAddress_Form(npchar)+", vous ne pouvez même pas imaginer à quel point les clients peuvent être agaçants...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Non merci, je fais juste un tour et je discute.","Moi encore. Je voulais juste vous parler.","Oui, c'est encore moi. Rien de sérieux, je voulais juste vous parler.","Oui, être banquier n'est pas toujours si facile. Je voulais juste discuter...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Je souhaite discuter de nos affaires financières.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Je suis intéressé par les bijoux et les idoles ou gemmes inhabituels.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "J'ai besoin de renseignements. Eh bien, j'ai quelque chose à vous demander.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Je vous ai apporté les papiers d'affaires de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Je suis ici sur les ordres d'un homme. Il est un gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" m'a envoyé ici. Je dois obtenir quelque chose de vous.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Bonjour, j'ai été invité par votre fils."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Je suis intéressé à savoir qui est le propriétaire du document.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "Je veux parler de la dette de votre client. Son nom est "+pchar.GenQuest.Noblelombard.Name+". Il a mis en gage la relique de sa famille. Je représente ses intérêts ici et j'ai le droit de discuter avec vous de son retour.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Nous avons eu une rencontre il y a trois mois et avons parlé de la relique d'un homme. Son nom était "+pchar.GenQuest.Noblelombard.Name+". Te souviens-tu ? Il devait ouvrir un dépôt à mon nom. La somme est "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "C'est à propos de votre ... mission d'esclave.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonne journée, "+NPChar.name+", parlons de votre mission.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonne journée, "+NPChar.name+"Discutons de votre mission.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonne journée, "+NPChar.name+", parlons de votre mission.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Je suis venu, comme convenu. Vous avez un travail pour moi ?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Je suis venu comme promis. Que diriez-vous d'un travail?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonne journée, "+npchar.name+". Comment allez-vous ? Avez-vous une nouvelle tâche pour moi ?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Votre mission est accomplie. J'ai pu retrouver ces fugitifs. Ce n'était pas si facile cependant.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonne journée, "+npchar.name+"Je suis venu pour une nouvelle mission lucrative.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Mauvaises nouvelles,"+npchar.name+"J'ai échoué à obtenir la brigantine.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Regardez,  "+npchar.name+". J'ai pourchassé le brigantin, mais je n'ai trouvé aucun document. Es-tu sûr qu'ils étaient là ?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonne nouvelle,"+npchar.name+". J'ai réussi à traquer cette brigantine et à trouver les documents. Les voici.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonne journée, "+npchar.name+" . Avez-vous préparé une nouvelle mission pour moi?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = " "+npchar.name+", j'ai pu intercepter ce soi-disant 'galion'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+"Je suis désolé mais je n'ai pas pu prendre d'assaut ce galion.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonjour, "+npchar.name+"Je suis venu pour mon argent.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", votre mission est accomplie. Ce salaud de Gontier est mort ainsi que son équipage.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", je suis désolé mais j'ai échoué à attraper Francois Gontier, bien que je le suivais jusqu'à Tortuga. Il a réussi à s'échapper de moi sur sa corvette.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bonne journée,"+npchar.name+"Parlez-moi de cette nouvelle mission que vous avez préparée pour moi.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;

		case "items_0":
			dialog.text = "Voulez-vous acheter quelques doublons d'or ou des coffres pour eux ? Croyez-moi, c'est un investissement très précieux.";
			link.l1 = "Oui, c'est très intéressant.";
			link.l1.go = "items";
			AddQuestRecordInfo("Recipe", "Gold_dublon");
			SetAlchemyRecipeKnown("gold_dublon");
			SetAlchemyRecipeKnown("Chest");
			npchar.quest.meeting = "1"; 			
		break;
		
		case "items_1":
			dialog.text = "Voulez-vous échanger contre des pesos ou des doublons ?";
			link.l1 = "Pour des pesos.";
			link.l1.go = "items";
			link.l2 = "Pour des doublons.";
			link.l2.go = "items_dub";
		break;
		
		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "items_dub":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		//<<<<----------генератор -"Shipping documents". ------		
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = "Ca prendra beaucoup de mon temps pour lire ces papiers et mon temps coûte cher.";
			link.l1 = "Peut-être, "+sti(pchar.questTemp.different.GiveShipLetters.price1)+"pesos compenseront votre temps ?";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "Comme vous le souhaitez. Adieu !";
			link.l2.go = "exit";
		break;
		
		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Laissez-moi jeter un coup d'œil ! Non, je n'ai jamais vu ce nom auparavant. Montrez-les à notre maître de port.";
				link.l1 = "Je suis désolé mais nous avions un accord ! Vous m'avez promis de me parler de ce capitaine !";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "Well... I know the owner of this ship. He is not a very rich man, but he has some wealth.";
				dialog.text = s1+"On dit qu'il est un contrebandier prospère. Est-ce ce que vous vouliez entendre ?";
				link.l1 = "Il semble que oui...";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "Well... I am not sure that I can congratulate you for your found.";
				dialog.text = s1+"Ces documents sont signés pour notre navire de patrouille colonial et son capitaine est connu pour ses principes fermes.";
				link.l1 = "Une patrouille ? Sous les ordres du commandant ?";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;
		
		case "ShipLetters_Usurer2_1":
			dialog.text = "Je vous ai promis de jeter un oeil à ces papiers et rien de plus. Vous pouvez partir.";
			link.l1 = "Merci... je suppose.";
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_Usurer2_2":
			dialog.text = "C'est votre décision. Notre commandant a montré un certain 'intérêt' pour cette personne depuis longtemps. Vous avez déjà des idées ? Et ici, nous avons des connaissements sans aucune marque...";
			link.l1 = "Je vois. Ma gratitude !";
			link.l1.go = "exit";		
		break;
		
		case "ShipLetters_Usurer2_3":
			s1 = "Exactly. Our smugglers are bearing a grudge against this captain by the way.";
			dialog.text = s1+"Et comme je l'ai mentionné auparavant, le propriétaire du document est un homme de principes et n'aime pas vraiment les crimes locaux.";
			link.l1 = "Je vois. Ma gratitude !";
			link.l1.go = "exit";		
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ah, je suppose que vous êtes un capitaine qui a ramené mon fils prodigue avec sa jeune épouse ?";
				link.l1 = "Oui, c'était moi qui les ai aidés à s'échapper.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ah, vous voilà, mon bienfaiteur. Vous attendez une récompense, je suppose ?";
				link.l1 = "Votre gratitude suffirait au moins...";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Je vous suis vraiment reconnaissant d'avoir aidé mon enfant et de ne pas l'avoir laissé dans cette situation difficile. Permettez-moi de vous remercier du mieux que je peux. Acceptez cette modeste somme et un petit cadeau de ma part.";
			link.l1 = "Mes remerciements. Ce fut un plaisir d'aider ce jeune couple.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Merci ? Pour quoi ? Ce lourdaud a été sans emploi pendant la moitié de l'année et il a déjà trouvé le temps de se dégoter une fille ! À son âge, je dirigeais ma propre affaire. Il y a une fille à marier du gouverneur et il a ramené cette catin ici, Seigneur, pardonnez-moi de le dire ! Et maintenant, il cherche ma bénédiction !";
			link.l1 = "Je suppose que vous ne croyez pas aux sentiments ?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Sentiments ? Quel genre de sentiments ? Vous êtes un homme adulte et vous parlez aussi de ces sentiments ? Quelle honte pour vous d'être un entremetteur pour la jeunesse. Vous avez enlevé la fille à ses parents et détruit la vie de mon fils. Vous n'obtiendrez aucun remerciement de ma part. Adieu.";
			link.l1 = "Adieu alors...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("saw","saw"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer":
			if (npchar.id == "Panama_Usurer")
			{
				if (sti(pchar.reputation.nobility) > 70 && ChangeCharacterNationReputation(pchar, SPAIN, 0) >= 80 && !CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
				{
					dialog.text = "Discutons-en. Je vous écoute.";
				}
				else
				{
					dialog.text = "Hum, hum. J'ai bien peur de devoir vous refuser, "+GetAddress_Form(NPChar)+"Je suis désolé, mais ma banque ne fournit pas de services aux ennemis de l'Espagne.";
					link.l1 = "L'argent n'a pas de nationalité, señor banquier.";
					if (CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
					{
						if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
						{
							dialog.text = "Mm-hmm, "+GetAddress_Form(NPChar)+" Je dois vous informer que votre dépôt n'est plus valide.";
							Link.l1 = "Sur quelle base ?!";
							Link.l1.go = "Panama_Deposit_SgorelVklad";
							DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
							break;						
						}
						else
						{
							link.l1.go = "Panama_Deposit_Cartahena";
							break;
						}
					}
					if (sti(pchar.reputation.nobility) < 71 || ChangeCharacterNationReputation(pchar, SPAIN, 0) < 80)
					{
						link.l1.go = "Panama_Deposit_NoReputation";
						break;
					}
				}
			}
			dialog.text = "Discutons-en. Je vous écoute.";
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "Je vous dois "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+LinkRandPhrase(", je suis prêt à vous rendre votre argent","Je veux rembourser la dette.",".  Enfin, il est temps de rembourser.");
					Link.l5.go = "loan_return";	
					sTemp = "credit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase("Je veux emprunter quelques pièces.","J'ai vraiment besoin d'obtenir quelques pesos.","Que diriez-vous d'un petit prêt ?");
				Link.l6.go = "loan";					
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("Je voudrais déposer mon argent pour des intérêts.","Accepteriez-vous de garder quelques sacs d'argent pour moi ?","Puis-je vous laisser de l'argent pour un jour de malchance ?"); // patch
					Link.l7.go = "deposit";				
				}			
				if(CheckUseDublons(NPChar))
				{
					Link.l8 = "Je veux déposer quelques doublons contre intérêts.";
					Link.l8.go = "deposit_dub";				
				}
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType1).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType1).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType1).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType1).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType1).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths;
				}
				Link.l9 = LinkRandPhrase("Je suis ici pour récupérer mon investissement, en pesos.","Il est temps de récupérer mon argent que tu me dois.","J'ai besoin de récupérer mon investissement en pesos avec tous les intérêts.");
				Link.l9.go = "Deposit_return";									
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)) && makeint(Pchar.Quest.Deposits.(sDepositType2)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType2).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType2).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType2).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType2).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType2).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths;
				}
				Link.l10 = LinkRandPhrase("Je veux récupérer mon investissement en doublons.","Il est temps de récupérer mon or que vous me devez.","J'ai besoin de récupérer mon investissement en doublons avec tous les intérêts.");
				Link.l10.go = "Deposit_return_dub";									
			}
/*			
			
*/			
			//выход
			if (sTemp == "credit")
			{
				link.l11 = "Je me souviens de ma dette, mais je ne suis pas prêt à la rembourser...";
				link.l11.go = "Loan_Remind";
			}
			else
			{
				link.l11 = "Mon erreur, je n'ai pas de questions financières avec vous. Adieu.";
				link.l11.go = "exit";
			}
		break;
		
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "Non, je ne peux pas vous aider. Je ne peux qu'accepter des investissements dans cet endroit tumultueux. Vous pouvez investir des pesos en argent ou des doublons en or.";				
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "Je veux investir des pesos et discutons de la somme.";
	                Link.l1.go = "deposit";
				}				
				if(CheckUseDublons(NPChar))
				{
					Link.l2 = "Je veux investir des doublons. Clarifions la somme.";
					Link.l2.go = "deposit_dub";
				}
                Link.l3 = "Pas intéressé.";
				link.l3.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear()+"Votre nom est "+GetFullName(pchar)+", n'est-ce pas ? Vous avez "+RandPhraseSimple("une mauvaise réputation ","une mauvaise réputation ")+" et je ne veux pas faire affaire avec vous.";
				link.l1 = RandPhraseSimple("Un homme ne peut-il pas faire une erreur ?",RandSwear()+"Peu importe !");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = "Oh, vous êtes toujours le bienvenu. Quelle somme avez-vous besoin ?";
			Link.l1 = "Un petit.";
			Link.l1.go = "Small";
			Link.l2 = "Modéré.";
			Link.l2.go = "Medium";
			Link.l3 = "Aussi grand que possible.";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank)+125*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = "Excellent ! C'est toujours beaucoup plus facile de gérer de petites sommes - moins de risque pour les deux parties. Je peux vous offrir "+FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum))+"...";
			Link.l1 = "Marché conclu. Qu'en est-il de vos intérêts ?";
			Link.l1.go = "Interest";
			Link.l2 = "Ça ne me convient pas. Changeons-le.";
			Link.l2.go = "Loan";
			Link.l3 = "Je suppose qu'il vaut mieux éviter de s'endetter pour moi. Adieu.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 22 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank)+325*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = "Aucun problème. J'espère que "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+" vous aidera à résoudre vos problèmes. C'est une somme assez conséquente.";
			Link.l1 = "Marché conclu. Qu'en est-il de vos intérêts ?";
			Link.l1.go = "Interest";
			Link.l2 = "Ça ne marchera pas pour moi. Changeons cela.";
			Link.l2.go = "Loan";
			Link.l3 = "Je suppose qu'il vaut mieux éviter les dettes pour moi. Adieu.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 27 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank)+600*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = "Eh bien... c'est risqué. Très bien, je suis prêt à vous accorder un prêt pour "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+". J'espère que vous comprenez, capitaine, c'est une somme vraiment considérable. Je vous demande d'y être sérieux.";
			Link.l1 = "Marché conclu. Qu'en est-il de vos intérêts ?";
			Link.l1.go = "Interest";
			Link.l2 = "Ça ne marchera pas pour moi. Changeons ça.";
			Link.l2.go = "Loan";
			Link.l3 = "Je suppose qu'il vaut mieux éviter les dettes pour moi. Adieu.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 37 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Interest":
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			// Rebbebion, добавил фикс отображения знака процента
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest+"%% par mois. Je ne peux pas vous offrir de meilleures conditions en fonction de ce que je sais de vous."; 
			Link.l1 = "Ça me convient. Parlons du temps.";
			Link.l1.go = "Period";
			Link.l3 = "Je suppose qu'il vaut mieux éviter les dettes pour moi. Adieu.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation.nobility)/20) + 1;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text = "Tenant compte de mes informations à votre sujet, "+Pchar.name+", j'attendrai le remboursement de ce prêt pendant "+FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period))+"Après cela, je prendrai certaines mesures. J'espère que vous comprenez cela."; 
			Link.l1 = "J'accepte volontiers vos conditions... et vos pièces.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Excusez-moi, mais cela ne me convient pas. Adieu.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "Je suis sincèrement ravi. Mais laissez-moi vous avertir. Je fais cela depuis longtemps et je sais comment récupérer mes investissements. Donc, si jamais vous aviez des idées saugrenues, je vous suggère de les laisser tomber\nPas d'offense, seulement un avertissement.";
			Link.l1 = "Hm.. Eh bien. Adieu.";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "C'est votre choix, capitaine. Mon intérêt croît et vous n'avez pas tant de temps.";
			Link.l1 = "Ne t'inquiète pas. À bientôt.";
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
            if (npchar.quest.trade_date != lastspeak_date) // дыра с прокачкой была
            {
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 700);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase("Magnifique ! Venez me voir lorsque vous avez besoin de pièces. Je serai à votre service à tout moment.","Ma gratitude. C'est toujours un plaisir de traiter avec un homme capable de rembourser ses dettes à temps. Des choses arrivent parfois, et je peux le comprendre vous savez... mais je préfère que les problèmes soient résolus.","Oh, j'avais raison de vous faire confiance, "+GetAddress_Form(NPChar)+"! J'espère que ce n'est pas la dernière fois que vous utilisez mes services. Peut-être pourrions-nous même conclure de meilleures affaires pour vous, maintenant que je sais que vous êtes un homme honnête.");
			Link.l1 = LinkRandPhrase("Je veux emprunter de l'argent.","J'ai vraiment besoin d'obtenir quelques pesos.","Que diriez-vous d'un petit prêt ?");
			Link.l1.go = "loan";			
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("Je voudrais investir mon argent.","Voulez-vous garder un peu de butin pirate ?","Puis-je vous laisser un peu d'argent pour un jour de malchance ?");
				Link.l2.go = "deposit";				
			}		
			if(CheckUseDublons(NPChar))	
			{
				Link.l3 = "Je veux investir quelques doublons pour des intérêts";
				Link.l3.go = "deposit_dub";				
			}
			Link.l4 = "Adieu, "+NPchar.name+".";
			Link.l4.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("Je vois un homme sage ! Quelle somme souhaitez-vous investir ?","D'accord. Faites-moi confiance, cette somme vous attendra ici en toute sécurité avec tous ses intérêts.","Je vois que vous savez ce qui est vraiment important dans cette vie. Combien souhaiteriez-vous investir ?");
			link.l1.edit = 3;
			link.l1 = " ";	
			Link.l1.go = "result";
		break;
		
		case "result":
			Pchar.QuestTemp.Deposits.(sDepositType1).Interest = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10.0/4.0 + 0.66) + 1; 
			Pchar.QuestTemp.Deposits.(sDepositType1).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Tu plaisantes, hein ?";
				link.l1 = "Mon erreur.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "Hm, malheureusement vous n'avez pas autant d'argent. Soyons sérieux...";
				link.l1 = "D'accord.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "D'accord. Je peux vous offrir... disons..."+Pchar.QuestTemp.Deposits.(sDepositType1).Interest+" %. Par mois, bien sûr.";
			Link.l1 = "Ça me convient.";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "Je ferais mieux de changer la somme.";
			Link.l2.go = "Deposit";
			Link.l3 = "On dirait que c'était une mauvaise idée... Adieu.";
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType1).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = "Veuillez m'excuser, capitaine, mais cette somme est trop importante pour ma banque coloniale. Je ne pourrai pas vous payer vos intérêts. Et l'absence d'une garde fiable... J'espère que vous comprenez. Quoi qu'il en soit, la somme maximale que je peux accepter de vous est "+FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "Dommage, je dois trouver un autre banquier alors.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Tu peux désormais être assuré qu'aucune tempête, même la plus violente, ne te laissera sans un sou.";
				Link.l1 = "D'accord. À bientôt.";
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Compte tenu de l'intérêt promis et du temps écoulé, je vous dois "+FindRussianMoneyString(sti(Pchar.Quest.Deposits.(sDepositType1).Result))+"... Es-tu sûr de vouloir prendre l'argent ?";
			Link.l1 = "Absolument. Donnez-le moi.";			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = "Je veux retirer une partie de mon argent.";			
			Link.l2.go = "Deposit_return_part";
			Link.l3 = "Vous avez raison. Je vais le laisser chez vous pour un moment. Passez une bonne journée.";			
			Link.l3.go = "Exit";		
		break;		
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType1)+ ".Rem");
			}
			Pchar.Quest.Deposits.(sDepositType1).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Interest);
			Pchar.Quest.Deposits.(sDepositType1).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1).city 	  = NPC_Area;	

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)));
			// общий долг
			Pchar.Quest.Deposits.(sDepositType1).Sum = sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.Quest.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1) = true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
			DialogExit();
		break;
		
		//--> Jason забор денег по частям
		case "Deposit_return_part":
			dialog.text = "Et combien?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_part";
		break;

		case "result_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "C'etait une plaisanterie si stupide, monsieur !";			
				link.l1 = "Merde ! Je suis tellement désolé... Changeons la somme.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "Vous n'avez pas autant d'argent sur votre compte.";			
				link.l1 = "Diantre ! Mon erreur. Changeons la somme.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "Tout ? D'accord, comme vous dites. Voici votre argent.";			
				link.l1 = "Gratitude !";	
				Link.l1.go = "Deposit_return_all";
				break;
			}
			dialog.text = "Très bien. Prenez-le. Voici votre argent.";			
			link.l1 = "Merci !";	
			Link.l1.go = "result_part_1";
		break;
		
		case "result_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType1).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType1).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType1).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType1).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType1).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType1).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType1).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType1) 			= true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
		break;
		
		case "Deposit_return_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(sDepositType1).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Oh... C'est si dur de le perdre. Je m'étais vraiment habitué à cet argent. Revenez de toute façon.";			
			Link.l1 = "Je le ferai si besoin est. Adieu.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		
		//  ugeen -> вклады в дублонах	
		case "deposit_dub":
			dialog.text = LinkRandPhrase("Je vois un homme sage ! Quelle somme souhaitez-vous investir ?","Très bien. Croyez-moi, cette somme vous attendra ici en toute sécurité et avec tous vos intérêts.","Je vois que vous savez ce qui est vraiment important dans cette vie. Combien voudriez-vous investir ?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result_dub";
		break;
		
		case "result_dub":		
			iTotalDublonQty = GetCharacterItem(pchar,"gold_dublon") + CheckItemMyCabin("gold_dublon");		
			Pchar.QuestTemp.Deposits.(sDepositType2).Interest = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/20.0/4.0 + 0.66) + 1; 
			Pchar.QuestTemp.Deposits.(sDepositType2).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Tu plaisantes, hein ?";
				link.l1 = "Hm, ma faute...";
				link.l1.go = "exit";
				break;
			}						
			if (iTemp > iTotalDublonQty)
			{
				dialog.text = "Hm, malheureusement vous n'avez pas autant d'argent. Soyons sérieux...";
				link.l1 = "Hm... bien.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "D'accord. Je peux vous offrir... disons..."+Pchar.QuestTemp.Deposits.(sDepositType2).Interest+" %. Par mois, bien sûr.";
			Link.l1 = "Ça me convient.";
			Link.l1.go = "Deposit_placed_dub";
			Link.l2 = "Je ferais mieux de changer la somme.";
			Link.l2.go = "Deposit_dub";
			Link.l3 = "Je suppose qu'il vaut mieux garder mon or. Adieu.";
			Link.l3.go = "Exit";
		break;
		
		case "Deposit_placed_dub":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType2).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum)) > sti(NPChar.UsurerDeposit)*10)
			{
			    dialog.text = "Excusez-moi, capitaine, mais cette somme est trop importante pour ma banque coloniale. Je ne pourrai pas vous verser vos intérêts. Et l'absence d'une garde fiable... J'espère que vous comprenez. Quoi qu'il en soit, la somme maximale que je peux accepter de vous est "+FindRussianDublonString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*10,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "Hélas, je dois trouver un autre banquier alors.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Vous pouvez être sûr maintenant que même la plus forte tempête ne vous laisserait pas sans un sou.";
				Link.l1 = "Bien. Adieu.";
				Link.l1.go = "Deposit_Exit_dub";
			}
		break;
		
		case "Deposit_return_dub":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Considérant l'intérêt promis et le temps écoulé, je vous dois "+FindRussianDublonString(sti(Pchar.Quest.Deposits.(sDepositType2).Result))+"... Es-tu sûr de vouloir prendre l'argent ?";
			Link.l1 = "Absolument. Donnez-le-moi.";			
			Link.l1.go = "Deposit_return_dub_1";		
			Link.l2 = "Je veux retirer une partie de mon argent.";			
			Link.l2.go = "Deposit_return_dub_part";
			Link.l3 = "Vous avez raison. Je vais le laisser chez vous pour un moment. Passez une bonne journée.";			
			Link.l3.go = "Exit";		
		break;	

		case "Deposit_exit_dub":
			NextDiag.CurrentNode = NextDiag.TempNode;		
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType2)+ ".Rem");
			}	
			Pchar.Quest.Deposits.(sDepositType2).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Interest);
			Pchar.Quest.Deposits.(sDepositType2).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2).city 	  = NPC_Area;	
			
			iTemp = GetCharacterItem(pchar,"gold_dublon");
			if(iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Sum))
			{
				TakeNItems(pchar,"gold_dublon", -sti(Pchar.Quest.Deposits.(sDepositType2).Sum));
			}
			else
			{
				TakeNItems(pchar,"gold_dublon", -iTemp));
				iTemp = sti(Pchar.Quest.Deposits.(sDepositType2).Sum) - iTemp;
				GetItemMyCabin("gold_dublon", iTemp);
			}
						
			// общий долг
			Pchar.Quest.Deposits.(sDepositType2).Sum = sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.Quest.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2) = true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
			DialogExit();
		break;	
		
		//-->забор дублонов по частям
		case "Deposit_return_dub_part":
			dialog.text = "Et combien?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_dub_part";
		break;
		
		case "result_dub_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "Une plaisanterie si stupide, monsieur !";			
				link.l1 = "Bon sang ! Je suis vraiment désolé... Changeons la somme...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "Vous n'avez pas autant d'or sur votre compte, monsieur.";			
				link.l1 = "Mince ! Mon erreur. Changeons la somme...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "Tout cela ? Bien, comme vous dites. Voici votre argent.";			
				link.l1 = "Merci !";	
				Link.l1.go = "Deposit_return_dub_all";
				break;
			}
			dialog.text = "D'accord. Prends-le. Voici ton argent.";			
			link.l1 = "Gratitude!";	
			Link.l1.go = "result_dub_part_1";
		break;
		
		case "result_dub_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType2).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType2).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType2).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType2).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType2).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType2).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType2).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType2) 			= true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
		break;
		
		case "Deposit_return_dub_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_dub_1":
			TakeNItems(pchar,"gold_dublon", sti(Pchar.Quest.Deposits.(sDepositType2).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Oh... C'est si dur de le perdre. Je me suis vraiment habitué à cet argent. Reviens quand même.";			
			Link.l1 = "Je le ferai si j'en ai besoin. Adieu.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//  ugeen <- вклады в дублонах	
		
		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Tu es encore en vie ? Tu veux peut-être me rendre mon argent ? Que le diable t'emporte ! J'ai perdu tellement d'argent que tu ne me rembourseras jamais ! Et je ne trouverai pas de repos tant que je n'aurai pas vu ton corps sans vie !";
            Link.l1 = "Je veux simplement régler les choses de manière pacifique.";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("Très bien, voyons cela ! Sachez que vous n'êtes pas non plus à l'abri de la mort !","Une menace ?! Voyons donc ce que tu vas faire...","L'argent n'est pas la chose la plus importante dans notre vie. Ne t'afflige pas trop pour cela et tue des gens, allez, je te défie.");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Sors d'ici ! J'aimerais ne jamais te revoir.";			
			Link.l1 = "... ";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "Vraiment ? Et quelles sont vos préoccupations ?";
			Link.l1 = "Aujourd'hui, je vous dois "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+"Et je vous offre cet argent.";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "Je vous offre ma dette pour rétablir de bonnes relations avec vous. C'est "+FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result))+".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = "Maintenant, nous parlons affaires ! Je peux finalement faire affaire avec vous.";
			Link.l1 = "Merci. Je ne te décevrai plus.";
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";			
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;
		
        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;			
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";
			
			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;
        
		//работорговец
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 100;
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;
			dialog.Text = "Ah, allez! Nous sommes des gens sérieux, vous et moi, nous valons mieux que ces idiots prêts à mourir pour un seul doublon, mais qui n'essaient jamais d'en faire deux.\nJe cherche un homme à qui proposer une affaire sérieuse. Un homme courageux et actif, honnête et ponctuel, mais pas accablé par... eh... trop de scrupules concernant les dilemmes moraux. Et j'espère que vous êtes l'homme que je cherche.";
			Link.l1 = "Ça dépendra du type de 'marché' que vous comptez me proposer.";
			Link.l1.go = "GiveTaskSlave_1";
		break;
			
		case "GiveTaskSlave_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(npchar.city);
			dialog.Text = "Très bien, écoutez donc. L'esclavage est le commerce le plus rentable des Caraïbes de nos jours. Je ne suis pas un planteur, mais j'ai des clients dignes de confiance\nDonc, j'ai besoin de la quantité suivante d'esclaves - "+pchar.questTemp.Slavetrader.iSlaveQuantity+" têtes. Je suis prêt à vous payer 250 pesos pour chacune. Croyez-moi, c'est un bon prix. Au total, vous gagnerez "+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+" pesos.";
			Link.l1 = "Non, je ne suis pas un marchand d'esclaves. Trouvez-vous un autre assistant qui ne se soucie pas de sa conscience.";
			Link.l1.go = "exit_slaves";
			Link.l2 = "Une offre tentante. J'aimerais faire cela. Dans combien de temps aurez-vous besoin des esclaves ?";
			Link.l2.go = "GiveTaskSlave_2";
		break;
			
		case "exit_slaves":
			dialog.Text = "Bah, il semble que personne n'est pressé de bouger son cul et de prendre l'or sous ses pieds. Je suis déçu, vraiment. Adieu et n'ose même pas répandre des ragots sur notre conversation. Mon bras a une longue portée...";
			Link.l1 = "Votre influence est 'sale'... tout comme votre langue. Adieu.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;
			
		case "GiveTaskSlave_2":
			dialog.Text = "Je ne limiterai pas votre temps, mais essayez d'accomplir votre mission dès que possible. La demande pour l' 'ivoire noir' est énorme. Si vous faites bien votre travail, alors je vous confierai ce genre de missions de temps en temps à l'avenir.";
			Link.l1 = "Ça semble agréable. Eh bien, attends les bonnes nouvelles.";
			Link.l1.go = "exit";						
			pchar.questTemp.Slavetrader = "Seek_slaves"; // это ввод имени квеста и состояния квеста
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", makeint(pchar.questTemp.Slavetrader.iSlaveQuantity));
			AddQuestUserData("Slavetrader", "sSum", makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], true); // блокируем вход офицеров 2015
		break;
			
		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "As-tu réussi à obtenir ce chargement d'ivoire noir?";
            if (amount < 0)
			{
				Link.l1 = "Pas encore. Je vérifie juste si notre accord est toujours en vigueur.";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "Je les ai. Ils sont tous dans ma cargaison.";
            	Link.l1.go = "Takeslaves";
			}
		break;
		
		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Splendide. Mes hommes les prendront... Ne vous inquiétez pas des douanes ou du commandant du fort. Je mène une opération de grande envergure ici, alors ne vous attendez pas à des ennuis et personne ne vous accusera de contrebande.";
			Link.l1 = "Il semble que vous ayez une position solide ici... Alors, qu'en est-il de mon paiement ?";
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;
		
		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "Le voici. Je ne parle pas à la légère. Restez avec moi, capitaine, et bientôt vous posséderez tant d'or qu'il vous faudra un galion pour le transporter !";
			Link.l1 = "Ce serait formidable ha-ha... Quelle est la suite ?";
            Link.l1.go = "Takeslaves_2";
		break;
		
		case "Takeslaves_2":
			dialog.Text = "Ensuite ? Revenez ici dans trois semaines. Je prépare actuellement une affaire qui devrait être prête d'ici là.";
			Link.l1 = "Très bien, marché conclu. Adieu.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
		break;
		
		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = "J'ai un travail, mais ton navire est trop faible. Je ne veux pas que tu échoues la mission, et je ne veux pas non plus t'envoyer à ta propre mort. Il y a encore du temps, alors procure-toi un navire plus grand, comme un barkentine, une brigantine, un brig ou au moins une flûte. Ne perds pas de temps !";
				Link.l1 = "Je vois, je m'en occupe. À bientôt.";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "Enfin ! Je vous attendais. Passons directement au but. Comme vous le savez, il y a toujours des concurrents dans toute affaire... et j'ai les miens. Ces salauds avides et sans scrupules sont toujours prêts à me voler un client ! En fait, je veux éliminer l'un d'eux et en même temps gagner une bonne pièce.";
				Link.l1 = "Je suis tout ouïe.";
            	Link.l1.go = "Takeslaves_4";
			}
		break;
		
		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//выбор бухты
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Très bien. Maintenant écoute. Ce gredin appelé "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+", a apporté des esclaves d'Afrique et a jeté l'ancre à "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+", c'est sur une île appelée "+XI_ConvertString(pchar.questTemp.Slavetrader.Island)+". Il attend des contrebandiers là-bas. Son galion s'appelle '"+pchar.questTemp.Slavetrader.ShipName+" Leur accord doit être rompu à tout prix !";
			link.l1 = "Et que diriez-vous des esclaves? Ce serait un tel gâchis de les couler!";
			link.l1.go = "Takeslaves_5";
		break;
		
		case "Takeslaves_5":
			dialog.Text = "Pourquoi feriez-vous cela ? Il n'y a pas besoin de cela. "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" a une mauvaise renommee et personne ne sera contrarie de sa disparition. Abordez son galion, tuez cet homme et assurez-vous qu'il reste mort, apportez-moi la cargaison et je la vendrai. Selon mes sources, il y a environ mille cinq cents esclaves.";
			Link.l1 = "Eh bien. C'est un sacré chiffre. Qu'en est-il de mon paiement ?";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "Non, monsieur, ces intrigues ne sont pas pour moi. Pourquoi devrais-je gâcher mes relations avec les contrebandiers ?";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "exit_slaves_1":
			dialog.Text = "Eh bien.. Il semble que je me sois trompé sur votre compte... Adieu et oubliez notre conversation. Et ne colportez pas de ragots sur ce que vous avez entendu ici. Cette ville m'appartient. Et si vous envisagez d'embarquer sur le '"+pchar.questTemp.Slavetrader.ShipName+"pour vous-même... Je m'assurerai que vous finissiez à la potence. Réfléchissez-y.";
			Link.l1 = "Ne vous inquiétez pas, je ne ferai pas de rapport aux autorités et je n'ai pas besoin de votre galion. Adieu.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(" agreed"," agreed"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста
		break;
		
		case "Takeslaves_6":
			dialog.Text = "Considérant que je vous ai donné l'emplacement de la cargaison et que vous n'avez pas besoin de naviguer à la recherche d'une 'prise', le paiement est un peu plus bas - 200 pesos par tête. Et c'est toujours une grande somme - trois cent mille pesos en cas de succès et le navire.";
			Link.l1 = "Marché conclu. Combien de temps ai-je ?";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "Ho-ho ! Vous dites cela comme si ces esclaves nageaient d'eux-mêmes jusqu'à mon navire, espérant entrer dans ma cargaison aussi vite que possible ! Voulez-vous vraiment que mes hommes risquent leur tête pour une somme si dérisoire ? Augmentez ma récompense ou je me retire des affaires.";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "Takeslaves_7":
			dialog.text = "Tu as deux semaines. Ne sois pas en retard ou il transférera sa cargaison et tout sera fini.";
			link.l1 = "Je dois donc me dépêcher. Attendez-vous à de bonnes nouvelles de ma part.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Voc")); // belamour gen
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;
            pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это заглушка
		break;
		
		case "Takeslaves_4_lose":
			dialog.text = "Eh bien, "+GetFullName(pchar)+", qu'en est-il de notre mission ? Ton visage morne me dit que tu as échoué.";
			link.l1 = "Merde, tu as raison... Je... enfin, tu sais... J'étais en retard. Il semblait qu'il était déjà parti, car je n'ai trouvé personne là-bas. J'ai dû naviguer au gré du vent tout le chemin, bon sang... ";
			link.l1.go = "Takeslaves_5_lose";
		break;
		
		case "Takeslaves_4_win":
			dialog.text = "Eh bien, "+GetFullName(pchar)+", quel est ton butin pour aujourd'hui ? Ils m'ont dit que "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+"nourrit les poissons ! Ha-ha-ha !";
			link.l1 = "Oui, j'étais juste à temps ! "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" était en train de transférer des esclaves sur le navire du contrebandier. J'ai dû les aborder tous les deux et les envoyer eux-mêmes à Davy Jones, donc tu as moins de concurrents maintenant.";
			link.l1.go = "Takeslaves_5_win";
		break;
		
		case "Takeslaves_5_lose":
			dialog.text = "Oui, je suppose que je me suis trompé à votre sujet. Vous étiez en retard ? Ou étiez-vous simplement trop effrayé pour vous battre ? Peu importe. Cela n'a plus de sens maintenant. Fichez le camp. J'en ai fini avec vous. Oubliez tout ce que vous avez vu ou entendu ici.";
			link.l1 = "Adieu alors.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if (amount < 0)
			{
				dialog.text = "J'avais raison à votre sujet - "+GetSexPhrase(" tu es un bandit fringant","   tu es une farouche Demoiselle")+" ! J'ai besoin d'hommes comme vous. Vous avez réussi votre mission d'une manière des plus excellentes - vous avez apporté plus de mille cinq cents esclaves ! Malheureusement, je ne peux vous payer que pour mille six cents esclaves. Je n'ai pas assez de pièces pour vous payer le reste, donc vous devrez les vendre vous-même. Votre récompense est de 320 000 pesos.";
				link.l1 = "Gratitude. Ravi de faire affaire avec vous, "+npchar.name+" !";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", 1600);
				AddQuestUserData("Slavetrader", "sMoney", 320000);
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				dialog.text = "J'avais raison à ton sujet - "+GetSexPhrase(" tu es un bandit éblouissant"," tu es une farouche demoiselle")+"! J'ai besoin d'hommes comme vous. Vous avez accompli votre mission de la manière la plus excellente - vous m'avez apporté "+sTemp+" esclaves. Votre récompense est "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Gratitude. Ravi de faire affaire avec vous, "+npchar.name+" !";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				dialog.text = "Au moins, vous avez survécu à la situation la plus difficile avec tout honneur. Bien que le prix soit moins que ce à quoi je m'attendais, je suis tout de même satisfait. Vous avez apporté "+sTemp+"esclaves. Votre récompense est "+FindRussianMoneyString(iSlaveMoney)+"";
				link.l1 = "Gratitude. C'est un plaisir de faire affaire avec vous, "+npchar.name+" !";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Je vois... Je peux comprendre cela, mais je m'attendais à beaucoup plus. Vous n'avez apporté que "+sTemp+"esclaves. Au moins, vous avez détruit mes concurrents et cela vaut quelque chose. Votre récompense est "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Je vous remercie. J'apprécie votre compréhension, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = "Ça a l'air bien, mais... hmmm. On dirait que je me suis trompé sur vous. Qu'avez-vous apporté ? "+sTemp+" esclaves ? Et qu'en est-il du reste ? Et ne me dis pas que tu les as coulés. Je suis sûr que tu les as vendus à des contrebandiers, ou pire encore - à ce salaud de Lavoisier. Dégage, je ne veux plus avoir affaire à toi !";
				link.l1 = "Comme vous le souhaitez, au revoir.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Ça a l'air bien, mais... où sont nos esclaves? Où est notre cargaison? Et ne me dis pas que tu l'as coulée. Tu as dû la vendre aux contrebandiers ou pire, à cet enfoiré de Lavoisier. Dégage, j'en ai fini avec toi.";
			link.l1 = "Comme vous le souhaitez, au revoir.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "node_hanter_1":
			dialog.text = "Ce n'est pas fini. Personne n'ose me duper ! Et tu paieras pour ta tentative - je veillerai à ce que tu aies des problèmes. Maintenant, fiche le camp d'ici !";
			link.l1 = "Va te faire foutre, toi et ton commerce d'esclaves ! Je devrais te trancher là où tu te tiens, mais je suis un meilleur homme que tu ne le seras jamais.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Takeslaves_6_win":
			dialog.text = "Il semble que nous nous entendons bien ensemble, "+pchar.name+". Je suis très content. Venez me voir dans un mois et, peut-être, je trouverai un travail juste pour vous. J'ai déjà quelques idées.";
			link.l1 = "Bien sûr, je vous verrai dans un mois. Mon travail avec vous est très rentable.";
			link.l1.go = "Takeslaves_7_win";
		break;
			
		case "Takeslaves_7_win":
			dialog.text = " Cela vous fera une fortune... Encore une question, "+pchar.name+", avez-vous trouvé quelque chose d'inhabituel dans la cabine de la galéon ?";
			link.l1 = "Rien de spécial vraiment... Ai-je manqué quelque chose ?";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "talisman8"))
			{
				link.l2 = "Vous voulez dire cette vieille boucle, une sorte d'amulette de 'scorpion' ?";
				link.l2.go = "Yestatue";
			}
		break;
			
		case "Nostatue":
			dialog.text = "Peut-être que vous l'avez fait, peut-être pas ... Cela n'a plus d'importance maintenant. Rendez-vous dans un mois. Adieu !";
			link.l1 = "À bientôt, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Yestatue":
			dialog.text = "Exactement ! C'est une fibule de Médicis... en avez-vous déjà entendu parler ? Cela signifie qu'elle était vraiment dans la cabine du salaud... Puis-je y jeter un œil ?";
			link.l1 = "Bien sûr, prends-le.";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "talisman8", 1);
		break;
			
		case "Yestatue_1":
			Log_Info("You gave a talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "Eh bien, eh bien... C'est vraiment le cas. Écoutez, "+pchar.name+", vendez-le moi. Je suis prêt à payer cent mille pesos.";
			link.l1 = "Cent mille? Hm.. Je suis d'accord. Voilà!";
			link.l1.go = "Buystatue";
			link.l2 = "Non, je ne la vendrai pas. La véritable valeur de cette fibule ne peut être estimée en argent ou en or. Je sais comment fonctionnent ces choses.";
			link.l2.go = "Nobuystatue";
		break;
			
		case "Buystatue":
			dialog.text = "Parfait ! Je suis ravi que nous ayons conclu un accord. Prenez votre argent. J'ai hâte de vous revoir dans un mois.";
			link.l1 = "Adieu, "+npchar.name+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue":
			dialog.text = "Voyez-vous, j'ai désespérément besoin de cette fibule ! Je suis tout à fait d'accord avec vous, elle ne peut pas être estimée en argent, même un marchand idiot ne vous en donnerait pas cinq mille. Mais il semble que vous sachiez vraiment ce qu'elle peut faire, puisque vous refusez de la vendre pour une telle somme.\n Puis-je vous proposer un échange, si vous ne voulez pas d'argent. J'ai quelque chose qui pourrait vous intéresser. Regardez ici. Une armure légère incroyable ! Voyez par vous-même ! Je vous l'offre en échange de la fibule.\nElle n'est pas unique d'ailleurs. Vous, marins, vous pouvez toujours en trouver d'autres pour vous-même et moi je ne peux pas. Êtes-vous d'accord maintenant ?";
			link.l1 = "Heh... Je suppose. Donne-moi l'armure et prends cette fibule.";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "Non, cette fibule a pour moi une valeur bien plus grande que cette armure. Je la garderai pour moi.";
			link.l2.go = "Nobuystatue_no";
		break;
			
		case "Nobuystatue_yes":
			dialog.text = "Splendide ! Heureux que nous ayons conclu un marché. Voici votre armure maintenant. Prenez-la. À dans un mois. Adieu.";
			link.l1 = "À bientôt, "+npchar.name+".";
			link.l1.go = "exit";
			TakeNItems(pchar, "cirass7", 1);
			Log_Info("You have received a Brigandine");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue_no":
			dialog.text = "Dommage... Vraiment dommage. Eh bien, prends-le. Je ne te juge pas. À dans un mois. Adieu.";
			link.l1 = "Adieu.";
			link.l1.go = "exit";
			TakeNItems(pchar, "talisman8", 1);
			Log_Info("You have received a talisman");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "EscapeSlave":
			dialog.text = "Vous arrivez juste à temps, "+pchar.name+". J'ai une mission pour vous si vous êtes prêt à la commencer.";
			link.l1 = "Bien sûr, je suis prêt.";
			link.l1.go = "EscapeSlave_1";
		break;
			
		case "EscapeSlave_1":
			dialog.text = "Excellent ! Maintenant, venons-en directement au fait. Avez-vous entendu les dernières nouvelles ?";
			link.l1 = "Hm, que voulez-vous dire? Il y a beaucoup de nouvelles qui arrivent chaque jour.";
			link.l1.go = "EscapeSlave_2";
		break;
			
		case "EscapeSlave_2":
			dialog.text = "Celui-ci concerne entièrement notre affaire. Il y a eu la plus grande évasion d'esclaves de l'histoire du Nouveau Monde ! Plus d'un millier d'âmes se sont échappées et, en attendant, ils ont détruit et incendié quelques postes avancés hollandais.";
			link.l1 = "Intrigant. Continuez.";
			link.l1.go = "EscapeSlave_3";
		break;
			
		case "EscapeSlave_3":
			dialog.text = "Mais ils ne se sont pas simplement enfuis, ils ont réussi à quitter l'île d'une manière ou d'une autre ! Aucune trace laissée. Mathias Beck est outré. Mais ce n'est pas le propos... Le propos est que je vous demande de naviguer vers Curaçao, d'apprendre ce qui s'est passé là-bas, de trouver les réfugiés et de les capturer\nEt, bien sûr, de les sauver des mains de la justice hollandaise, qui serait impitoyable envers eux. Je paierai 300 pesos par tête - j'ai entendu dire qu'ils sont de très bons esclaves.";
			link.l1 = "Compris. Je mets le cap sur Curaçao. Attends-moi avec de bonnes nouvelles.";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "Vous savez, je ne prendrais pas la mission. Je ne priverai pas les gens de leur liberté. Ils ont risqué leur vie pour l'obtenir. Ils l'ont méritée.";
			link.l2.go = "EscapeSlave_no";
		break;
			
		case "EscapeSlave_no":
			dialog.text = "Quel dommage... Je ne m'attendais pas à cela de votre part... et au moment le plus inopportun. Je suppose qu'il est clair pour vous que notre partenariat est terminé. Adieu.";
			link.l1 = "Passez une bonne journée.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
		break;
			
		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum)*100;
			if (amount < 0)
			{
				dialog.text = "Ha ! Non seulement vous avez réussi votre mission difficile, mais vous avez amené plus d'esclaves que je n'avais demandé - "+sTemp+" esclaves. Mais "+sNum+" des esclaves ne se sont pas échappés de Curaçao. Je vous paie 100 pesos par tête. Je suppose que cela vous conviendra. Votre récompense est de 330 000 pesos et "+FindRussianMoneyString(iSlaveMoneyH)+"pour un excès, ha-ha.";
				link.l1 = "Ha ! Vous ne pouvez décidément pas être dupé. Je suis d'accord, quoi que vous disiez, "+npchar.name+" !";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, makeint(iSlaveMoneyH));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoneyH));
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				dialog.text = "Vous avez achevé cette mission difficile de la manière la plus excellente et m'avez apporté "+sTemp+" esclaves. Votre recompense est "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Je vous remercie. C'est un plaisir de faire affaire avec vous, "+npchar.name+" !";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				dialog.text = "Vous avez réussi cette mission difficile. Le prix n'est pas aussi riche que je l'avais espéré, mais je suis satisfait quand même. Donc, vous avez amené ici "+sTemp+" esclaves. Votre récompense est "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Merci. C'est un plaisir de faire affaire avec vous, "+npchar.name+" !";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Vous les avez trouvés ? Hm... qu'avez-vous apporté pour moi ?"+sTemp+" esclaves ? Où est le reste de la cargaison ? Et n'essaie même pas de me dire que tu l'as coulée. Tu as dû la vendre à des contrebandiers, ou pire encore - à ce salaud de Lavoisier d'Isla-Tesoro. Va-t'en d'ici, je n'ai plus envie de travailler avec toi.";
				link.l1 = "Adieu.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Vous les avez trouvés ? Qu'en est-il des esclaves ? Où est notre cargaison ? Et n'essayez même pas de me dire que vous l'avez coulée. Vous devez l'avoir vendue à des contrebandiers ou, pire encore, à ce salaud de Lavoisier d'Isla-Tesoro. Allez-vous-en, je n'ai plus envie de travailler avec vous.";
			link.l1 = "Adieu.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "Escape_slaves_win_1":
			dialog.text = "Je vous apprécie vraiment, "+pchar.name+"Vraiment. Revenez ici dans un mois et je préparerai une nouvelle affaire, profitable pour nous deux.";
			link.l1 = "Je suis également satisfait de notre partenariat, "+npchar.name+"À dans un mois.";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;
			
		case "Slaveshore":
			dialog.text = "Vous arrivez juste à temps, "+pchar.name+". Je cherche un marin courageux et peu scrupuleux, ha-ha. Es-tu prêt à t'occuper de mon travail ?";
			link.l1 = "Je suis tout ouïe.";
			link.l1.go = "Slaveshore_1";
		break;
			
		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "C'est assez simple cette fois. Aujourd'hui, une pinasse '"+pchar.questTemp.Slavetrader.ShipName+"sous le pavillon de "+NationNameGenitive(sti(npchar.nation))+"a jeté l'ancre à "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+" baie. Il était chargé d'un grand lot d''ébène' avec l'aide des contrebandiers locaux. Deux mille têtes, pas moins\nPas de soldats dans l'équipage et le capitaine est un marchand. En somme, aucune menace. Abordez le navire et apportez-moi la cargaison. 200 pesos par tête comme d'habitude.";
			link.l1 = "Hm... Ce n'est pas la même chose que la dernière mission. Vous me suggérez d'attaquer un navire de votre propre nation !";
			link.l1.go = "Slaveshore_2";
		break;
			
		case "Slaveshore_2":
			dialog.text = "Je ne comprends pas, "+pchar.name+". Le pavillon du navire a-t-il de l'importance ? Cela vous préoccupe vraiment ?";
			link.l1 = "Vraiment ? Non, je m'en fiche, l'or n'a pas de nationalité. C'était juste un peu inattendu...";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "Je m'en soucie. Je ne veux pas avoir "+NationNameAblative(sti(npchar.nation))+" parmi mes ennemis.";
			link.l2.go = "Slaveshore_3_no";
		break;
			
		case "Slaveshore_3_no":
			dialog.text = "Vous êtes sérieux ? Vous devez plaisanter, on ne peut faire confiance à personne de nos jours... Dans ce cas, partez. Et oubliez tout ce que vous avez vu ou entendu ici !";
			link.l1 = "À plus,"+npchar.name+".";
			link.l1.go = "node_hanter_1";
		break;
			
		case "Slaveshore_3_yes":
			dialog.text = "Pourquoi êtes-vous surpris ? Parce que je me fiche de la nationalité des pièces ? Je vous assure, en effet, je m'en moque. Pour être honnête, le patriotisme est mauvais pour un banquier professionnel, à moins qu'il ne veuille faire faillite un jour\nMais assez de philosophie. Allons droit au but - le navire restera ici jusqu'à minuit, donc il ne vous reste plus beaucoup de temps. Êtes-vous prêt à continuer ?";
			link.l1 = "Oui, "+npchar.name+", je suis en route.";
			link.l1.go = "Slaveshore_4";
		break;
			
		case "Slaveshore_4":
			dialog.text = "Splendide. Je n'ai aucun doute que vous réussirez dans notre mission. Bonne chance."+pchar.name+".";
			link.l1 = "Merci ! Adieu.";
			link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
            pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//заглушка
		break;
			
		case "Pinas_lose":
		dialog.text = "Eh bien, "+GetFullName(pchar)+", qu'en est-il de votre mission ? Votre visage morose me dit que vous l'avez échouée.";
			link.l1 = "Tu as foutrement raison... Je... Eh bien... J'étais trop tard. J'étais à la taverne et quand je suis parti, il n'y avait personne en mer.";
			link.l1.go = "Takeslaves_5_lose";
		break;
			
		case "Slaveshore_5":
			dialog.text = ""+pchar.name+", s'il vous plaît, calmez-vous. Ce n'est pas ma faute ! Bon sang, j'ai reçu le rapport trop tard... Il y a eu trahison ! Un de mes hommes de confiance m'a vendu !";
			link.l1 = "Bien, je vois que tu dis la vérité. Tu as de la chance que le capitaine de la pinasse m'ait dit que notre 'affaire' avait été découverte. Je t'aurais déjà tué s'il n'avait pas bavardé. Mais toi, foutu sac d'argent, tu m'as toujours dit que tu 'possèdes cette ville' !";
			link.l1.go = "Slaveshore_6";
		break;
			
		case "Slaveshore_6":
			dialog.text = "L'embuscade n'a pas été organisée par les autorités locales, sinon je l'aurais su... "+pchar.name+", ce n'est pas le bon moment pour des querelles. Nous sommes tous les deux en danger, un de mes anciens contractants nous a piégés.\nJ'ai réussi à découvrir que toutes les preuves rassemblées - un paquet de papiers - sont en cours de transport vers notre gouverneur général. S'il les obtient, nous sommes finis ! Vous en souffrirez le plus, d'ailleurs.";
			link.l1 = "Maintenant, je comprends ce que ce salaud de capitaine voulait dire !";
			link.l1.go = "Slaveshore_7";
		break;
			
		case "Slaveshore_7": //выбор острова, куда бригантина пойдёт
			switch (sti(NPChar.nation))
            {
                case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
                break;
                case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Nevis";
                break;
                case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";  
                break;
                case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";     
                break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя бригантины
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "Ecoutez attentivement. Nous avons encore une chance. Le colis a été envoyé sur la brigantine '"+pchar.questTemp.Slavetraderbrig.ShipName+". C'est la seule chose dont je suis certain. Les papiers sont livrés au gouverneur général à sa résidence le "+XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island)+"Vous devez l'intercepter, l'aborder et trouver ces preuves compromettantes.";
			link.l1 = "Je n'ai pas vraiment le choix ici. Priez pour moi, pour vous-même et espérez que je pourrai l'attraper. Nous reparlerons de tout cela quand je serai de retour. Ne pensez pas que je vais simplement laisser tomber.";
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//отправляем в локацию
            pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//создание бригантины
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это нода ожидания, пустая
		break;
		
		case "Slaveshore_8":
			dialog.text = "Obtenir ce paquet est votre priorité principale ! Je ne serai pas sûr de ma sécurité tant que vous ne me l'aurez pas livré... Nom d'un chien..."+pchar.name+"On dirait que nous avons un problème ici...";
			link.l1 = "Qu'est-ce que c'est ?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;
			
		case "Brig_lose":
			dialog.text = "Merde... Je comptais sur toi, "+pchar.name+"Très bien, alors. Mais nous ne ferons plus d'affaires ensemble. Si je ne parviens pas à soudoyer un enquêteur, je devrai m'enfuir. Et je ne vous recommande pas de rester ici - les soldats peuvent arriver à tout moment. Adieu.";
			link.l1 = "Adieu, "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Letter_lose":
			dialog.text = "Ils étaient là. Eh bien, nous ne pouvons plus faire d'affaires ensemble, ce n'est plus sûr. Adieu.";
			link.l1 = "Adieu, "+npchar.name+".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Brig_win":
			dialog.text = "Excellent ! Je n'avais aucun doute en vous, "+pchar.name+". Je vous prie de me donner ces papiers, je suis trop nerveux.";
			link.l1 = "Prenez-les.";
			link.l1.go = "Brig_win_1";
		break;
			
		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "Bien... Maintenant je suis en sécurité. Le gouverneur-général ne saura rien et j'ai déjà résolu tous les problèmes avec les autorités locales, mais cela m'a coûté cher, je vous le dis.";
			link.l1 = "Ça a l'air formidable, mais ne pensez-vous pas que vous devez me dédommager pour les ennuis causés par vos actions irréfléchies ?";
			link.l1.go = "Brig_win_2";
		break;
			
		case "Brig_win_2":
			dialog.text = "Bien sûr, "+pchar.name+" En plus, je vous dois beaucoup. Et j'espère vraiment continuer notre affaire. Mais je vous demande de me comprendre - j'ai dépensé une somme énorme - la loyauté du gouverneur et du commandant coûte cher. Et j'ai dû gérer ce meurtre de toute la patrouille dans ma banque...";
			link.l1 = "Vous voulez dire que vous ne compensez pas mes frais ?!";
			link.l1.go = "Brig_win_3";
		break;
			
		case "Brig_win_3":
			dialog.text = "Ne soyez pas si dur, "+pchar.name+"J'ai vraiment des ennuis avec l'argent maintenant, alors je vous propose un autre type de paiement.";
			link.l1 = "Je vous écoute alors.";
			link.l1.go = "Brig_win_4";
		break;
			
		case "Brig_win_4":
			dialog.text = "Moi et mon compagnon avons été pris dans une tempête près des côtes sud du Main il y a un an. Nos navires ont été projetés sur les rochers de la côte de Boca de la Serpienta, bien qu'ils aient coulé rapidement, nous avons réussi à traîner notre cargaison à terre. Des coffres remplis de pierres précieuses et de bijoux. La baie semblait assez abritée, alors nous avons caché les trésors sans problème\nMais nous avons été attaqués par les Indiens le lendemain matin dès que la tempête s'est terminée. C'est ainsi que la majorité des survivants sont morts, y compris mon compagnon. Moi et quelques marins avons réussi à nous échapper sur une chaloupe\nNous avons atteint Cumana en toute sécurité, mais je n'ai pas osé retourner chercher les trésors. Je suis sûr que les sauvages locaux protègent encore leur rivage ainsi que mes coffres. Mais vous pouvez vous occuper de cette bande de peaux-rouges\nLes bijoux que vous trouverez là-bas sont suffisants pour couvrir toutes vos dépenses, y compris une expédition vers le sud du Main.";
			link.l1 = "Hm... bien. Alors, je me dirige vers Cumana";
			link.l1.go = "Brig_win_5";
		break;
			
		case "Brig_win_5":
			dialog.text = "Vous pouvez être sûr, "+pchar.name+", que tout ce que j'ai dit était la vérité. J'espère vous revoir dans un mois. J'ai déjà en tête une autre affaire et comment je devrais aider mon commerce vacillant. Adieu.";
			link.l1 = "À bientôt, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;
			
		case "SlaveGalleon":
			dialog.text = "Et vous voilà, "+pchar.name+". Bien, vous êtes juste à temps comme toujours. J'aimerais vous donner plus d'informations sur le marché des esclaves des Caraïbes avant de vous confier une nouvelle mission. Savez-vous ce que signifie le mot 'repartimiento'?";
			link.l1 = "Hm, non, "+npchar.name+", je ne le fais pas. Mais je suppose qu'il s'agit de prendre quelque chose à quelqu'un. Ai-je raison ?";
			link.l1.go = "SlaveGalleon_1";
		break;
			
		case "SlaveGalleon_end":
			dialog.text = "Tu me surprends. Que t'attendais-tu de moi ? Va-t'en !";
			link.l1 = "Un commerce illégal est trop dur pour ma moralité. Surtout le commerce des esclaves.";
			link.l1.go = "node_hanter_1";
		break;
			
		case "SlaveGalleon_1":
			dialog.text = "Vous y êtes presque,"+pchar.name+". Enlever la liberté de quelqu'un. Le repartimiento est une façon astucieuse et légale d'asservir les Indiens locaux. Pour ainsi dire. Les autorités espagnoles l'utilisent contre les peuples autochtones du continent. Seriez-vous intéressé à en savoir plus ?";
			link.l1 = "Pourquoi pas ?";
			link.l1.go = "SlaveGalleon_2";
		break;
			
		case "SlaveGalleon_2":
			dialog.text = "Des représentants de la couronne espagnole visitent les colonies indiennes. Par la tromperie cynique et les menaces directes, ils forcent les Indiens à acheter toutes sortes de camelote comme de la viande pourrie et de vieux rasoirs à des prix fabuleux. À crédit \nQuelques temps plus tard, disons un an, les représentants reviennent et exigent un paiement. Si les Indiens ne peuvent pas payer, ce qui arrive généralement, les Espagnols prennent une partie de leurs hommes capables de travailler, soi-disant pour un temps et pour 'leur apprendre à cultiver la terre' \nComme vous le comprenez, ils ne retournent jamais dans leurs colonies. Voilà comment nos peaux-rouges crédules finissent dans les plantations de sucre et les fabriques de bois de santal.";
			link.l1 = "Mince... vraiment... Que font les Indiens à ce sujet ? Résistent-ils lorsque les Espagnols les réduisent en esclavage ? Ou ne comprennent-ils simplement pas ce qui se passe ?";
			link.l1.go = "SlaveGalleon_3";
		break;
			
		case "SlaveGalleon_3":
			dialog.text = "Je suppose qu'ils le voient toujours venir, mais seuls quelques-uns osent s'opposer ouvertement, surtout lorsque les Espagnols montrent un papier avec l'empreinte digitale du chef. Bien sûr, de telles tactiques sont normalement appliquées aux tribus pacifiques comme les Arawaks ou les Miskitos. Un tel stratagème ne fonctionnera pas avec les belliqueux Itza ou Akawoys\nEh bien, parlons de votre mission.";
			link.l1 = "Je sens déjà l'odeur de nombreuses pièces ! Je vous écoute, "+npchar.name+" . ";
			link.l1.go = "SlaveGalleon_4";
		break;
			
		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "Bientôt de Caracas, un lourd galion prendra la mer. Il s'appelle "+pchar.questTemp.Slavetrader.ShipName+". Il contient une énorme quantité d'esclaves - environ 3000 hommes - des Indiens de l'Orénoque, capturés selon la politique des repartimentos. Le galion fait voile vers Santiago, les plantations de sucre de Cuba ont besoin de beaucoup de travailleurs. Vous devez capturer le galion avec sa cargaison. Je prendrais au moins deux navires avec moi si j'étais vous, on dit que le galion est le meilleur de sa catégorie. Les taux de paiement restent habituels - 200 pesos par tête. ";
			link.l1 = "Heh ! Cela semble bon. Je suis d'accord.";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "Vous savez que je n'aime pas votre repartimiento. C'est trop cynique. Je ne vais pas faire ça.";
			link.l2.go = "SlaveGalleon_end";
		break;
			
		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			dialog.text = "Je te souhaite bonne chance alors. Sache que le capitaine de ce galion est un marin de guerre très habile et expérimenté. Ce ne sera pas un combat facile, alors prépare-toi. Ne perds pas de temps, il lui faudra quinze ou vingt jours pour atteindre "+sTemp+" Santiago. Essayez de ne pas le manquer, bien que ce galion soit vraiment difficile à manquer \nOui ! J'ai presque oublié ! Il y a plein de babioles indiennes sur le navire, les peaux-rouges paient souvent leurs dettes avec leurs objets de culte et leur artisanat. Apportez-moi tout ce que vous pourriez trouver de spécial, je vous paierai une bonne somme pour chaque objet de valeur que vous apporterez.";
			link.l1 = "Je comprends.";
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 20, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;
			
		case "Lostgalleon":
			dialog.text = "Eh bien, "+pchar.name+", c'était mon tout dernier espoir... C'est pourquoi je vous ai offert ce travail. Personne d'autre que vous n'est capable de le faire... et je vois que vous n'en êtes pas capable non plus. Disons-nous adieu alors. Après le dernier échec et toutes ces rumeurs, tous mes clients sont partis. Et je suis presque en faillite, peut-être dois-je quitter cette ville. Je ne vous en veux pas - ce travail était trop dur. Eh... Adieu,"+pchar.name+".";
			link.l1 = "Je suis tellement désolé, "+npchar.name+", cela est allé trop loin. Je suis vraiment désolé. Peut-être que tout cela s'apaisera. Adieu.";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if(amount < 1) 
			{
				dialog.text = "Fuh, je me sens mieux maintenant... J'avais raison de te faire confiance... D'où vient cette ironie ? Quel est le problème ?";
				link.l1 = "Mon cher monsieur, ce n'était pas un galion... ou un très grand galion... Mille sabords ! C'était un vaisseau de ligne ! Et vous ne m'avez même pas prévenu ! Mais j'ai réussi à l'aborder. J'ai "+sTemp+"esclaves et je suis prêt à vous les transférer. Selon notre accord, vous me devez -"+FindRussianMoneyString(iSlaveMoney)+"Ce serait formidable d'obtenir une compensation pour vos fausses informations.";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "As-tu trouvé le galion ? Et les esclaves ? Il est censé y en avoir trois mille, pas moins ! Bon sang, tout le monde est un rat et un traître ! Je ne m'y attendais pas de ta part... tu étais mon dernier espoir\nTrès bien... Je jure, je dépenserai chaque pièce qu'il me reste pour te détruire, pour te tuer ! Toute la flotte de "+NationNameGenitive(sti(npchar.nation))+" te chassera ! Va-t'en d'ici !";
				link.l1 = "Eh bien...";
				link.l1.go = "Wingalleon_goaway";
			}
		break;
			
		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			DialogExit();
		break;
			
		case "Wingalleon_1":
			dialog.text = "Pas possible! Je le jure, je n'en avais aucune idée. Un lourd galion était censé naviguer, pas un foutu vaisseau de ligne! Il semble qu'ils aient changé leurs plans à la dernière minute... Mais vous avez quand même réussi!\nJe suis entièrement d'accord avec vous concernant l'argent et la compensation de vos dépenses, le problème est que je ne possède pas une telle somme en ce moment. Vous savez, avec mes récents soucis... Mais ne vous fâchez pas, "+pchar.name+", pour l'amour de Dieu. Vous me donnez la cargaison et je la vendrai, mon client attend déjà\nJ'aurai la somme entière dans cinq jours, donc vous recevrez ce que vous méritez. Vous pouvez compter sur moi. Tenez, prenez tout l'argent que j'ai en ce moment.";
			link.l1 = "Hm... Je m'attendais à recevoir l'argent maintenant. J'aimerais que vous sachiez quel genre de bataille j'ai dû traverser ! Ah, peu importe... Je vais compatir avec vous. Mais gardez à l'esprit que si vous essayez de me duper, je vous trouverai même en Europe !";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "Tu sais, "+npchar.name+", va te faire voir ! Ce n'était pas un marché. Tu n'imagines même pas quel genre de combat j'ai dû mener. Je prends tous les esclaves pour moi et les vends sans passer par ton agence.";
			link.l2.go = "Wingalleon_no";
		break;
			
		case "Wingalleon_no":
			dialog.text = "Ah, maintenant tu parles ! On dirait un imprudent "+npchar.name+" n'était qu'une vache à traire, un simple retard suffit pour que tu me roules et que tu démarres une opération par toi-même. On dirait que tu as oublié que c'est moi qui t'ai donné le travail et l'indice sur le butin\nTrès bien... Je jure, je dépenserai chaque pièce qu'il me reste pour te détruire, pour te tuer ! Toute la flotte de "+NationNameGenitive(sti(npchar.nation))+" te chassera ! Hors de ma vue !";
			link.l1 = "N'osez pas me faire peur, un coffre vide d'argent. Je coulerai toutes vos flottes et les donnerai à manger aux crabes.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon_yes":
			dialog.text = "Merci pour votre compréhension, "+pchar.name+". Je promets que tout ira bien, pas besoin de vos menaces\nPrenez ceci comme une avance. Quinze coffres. Cinq d'entre eux serviront de compensation pour les dommages moraux. Venez me voir dans cinq jours pour récupérer le reste.\nN'oubliez pas d'apporter tous les objets indiens que vous avez trouvés sur le navire... si vous en avez trouvé, bien sûr. Je n'ai rien pour vous les payer de toute façon.";
			link.l1 = "Dans cinq jours,"+npchar.name+"Dans cinq jours...";
			link.l1.go = "Wingalleon_yes_1";
		break;
			
		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info("You've received credit chests");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp)*200-120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
		break;
	
		case "FindRat":
			dialog.text = "Comme je l'ai promis, "+pchar.name+", je suis prêt à vous payer. Les esclaves sont vendus, le client est content et nous aussi. Après déduction d'une avance, votre récompense est"+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+" Je vous prie de prendre votre argent.";
			link.l1 = "Splendide, "+npchar.name+"Il est bon de traiter avec un homme qui sait tenir parole...";
			link.l1.go = "FindRat_1";
		break;
			
		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "Vous pouvez toujours faire confiance à ma parole, "+pchar.name+". Je ne vous ai jamais donné de raison de douter de moi. Les partenaires doivent être honnêtes l'un envers l'autre, c'est la clé des affaires\nParlons maintenant des artefacts indiens. Montrez-moi ce que vous avez, ne faites pas attendre un collectionneur comme moi.";
			link.l1 = "Hm... Jetez un oeil.";
			link.l1.go = "FindRat_2";
		break;
			
		case "FindRat_2":
			if (CheckCharacterItem(pchar, "talisman16"))
			{
				dialog.text = "Oui! Excellent! Un couteau rituel en or! C'est une chose rare. J'ai toujours voulu avoir quelque chose comme ça dans ma collection. Je vous offre 30 000 pour cela ou un amulette d'Ehecatl en échange. J'en ai de toute façon deux.";
				link.l1 = "Je prendrais de l'argent.";
				link.l1.go = "BG_money";
				link.l2 = "Je prendrais un amulette d'Ehecatl en échange.";
				link.l2.go = "BG_change";
				link.l3 = "Je ferais mieux de garder ce couteau avec moi.";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "Hmm... Malheureusement, vous n'avez rien d'intéressant pour moi.";
				link.l1 = "Quoi que vous disiez.";
				link.l1.go = "BG_PF";
			}
		break;
			
		case "BG_money":
			dialog.text = "Splendide. Prenez vos 30 000 et ce couteau indien est à moi maintenant.";
			link.l1 = "Bien. Et est-ce tout ce qui vous intéresse...";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("You've given a golden knife");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
		break;
			
		case "BG_change":
			dialog.text = "Splendide ! Voici votre amulette et ce couteau indien est désormais à moi.";
			link.l1 = "Bien. Et c'est tout ce qui vous intéresse...";
			link.l1.go = "BG_PF";
			Log_Info("You've given a golden knife");
			Log_Info("You've received an amulet of 'Ehecatl'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
			TakeNItems(pchar, "obereg_9", 1);
		break;
			
		case "BG_no":
			dialog.text = "Peu importe. Mais c'est vraiment dommage quand même...";
			link.l1 = "Bien. Et c'est tout ce qui vous intéresse...";
			link.l1.go = "BG_PF";
		break;
			
		case "BG_PF":
			dialog.text = "Attendez ! Laissez-moi jeter un œil encore une fois...";
			link.l1 = "Bien sûr. Venez jeter un œil et choisissez ce que vous voulez.";
			link.l1.go = "PF_check";
		break;
			
		case "PF_check":
			if (CheckCharacterItem(pchar, "mineral31"))
			{
				dialog.text = "Ça ! Et je ne l'avais même pas remarqué au début. Je suis intéressé par cet os avec une bague en cuivre. Une chose si intéressante je vous dirais... Je peux vous payer 20 000 pesos ou vous donner un amulette de 'Cimaruta' en échange.";
				link.l1 = "Je prendrais de l'argent.";
				link.l1.go = "PF_money";
				link.l2 = "Je prendrais un amulette de 'Cimaruta' en échange.";
				link.l2.go = "PF_change";
				link.l3 = "Je garderais cet artefact avec moi.";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "Non... vous n'avez rien d'autre d'intéressant ici.";
				link.l1 = "Quoi que ce soit !";
				link.l1.go = "FindRat_3";
			}
		break;
			
		case "PF_money":
			dialog.text = "Excellent ! Voici vos 20 000 pesos et cet os m'appartient maintenant.";
			link.l1 = "Bien. Je me sens satisfait de notre accord.";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You've given a magic bone");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
		break;
			
		case "PF_change":
			dialog.text = "Splendide ! Voici ton amulette et cet os est à moi maintenant.";
			link.l1 = "Chouette. Je me sens bien à propos de notre accord.";
			link.l1.go = "FindRat_3";
			Log_Info("You've given a magic bone");
			Log_Info("I've received an amulet of 'Cimaruta'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
			TakeNItems(pchar, "amulet_11", 1);
		break;
			
		case "PF_no":
			dialog.text = "Quoi qu'il en soit. Mais c'est quand même bien dommage...";
			link.l1 = "J'ai besoin de cet os pour moi-même, je suis vraiment désolé.";
			link.l1.go = "FindRat_3";
		break;
			
		case "FindRat_3":
			dialog.text = "Eh bien... en abordant le galion, oh je suis désolé, le Vaisseau de Ligne, vous m'avez sauvé. J'apprécie vraiment notre partenariat, "+pchar.name+". Vous êtes mon meilleur agent.";
			link.l1 = "Je suis flatté. Vous surestimez quelque peu mes accomplissements...";
			link.l1.go = "FindRat_4";
		break;
			
		case "FindRat_4":
			dialog.text = "Je suis tout à fait sérieux. Et je vais vous demander d'accomplir une autre mission en raison de vos compétences extraordinaires et parce que j'ai confiance en vous.";
			link.l1 = "Hé ! Surprenant ! J'écoute. Où est un autre galion avec des esclaves ?";
			link.l1.go = "FindRat_5";
		break;
			
		case "FindRat_5":
			dialog.text = "Il ne s'agit pas d'esclaves cette fois. Surpris ? Je vous paierai bien pour la mission... Très bien.";
			link.l1 = "Allons droit au but.";
			link.l1.go = "FindRat_6";
		break;
			
		case "FindRat_6":
			dialog.text = "Cette affaire est liée aux récents événements auxquels vous avez également participé... Donc, comme vous le savez peut-être, je mène une affaire assez illégale - la traite des esclaves. Vous savez peut-être aussi que j'engage des corsaires comme vous pour toutes sortes de missions\nUn de mes hommes m'a trahi il n'y a pas longtemps pour des raisons inconnues. Il a rassemblé des preuves et a fait un rapport aux autorités. Vous avez eu le plaisir de voir les conséquences de vos propres yeux. Un navire avec des soldats est arrivé ici... vous connaissez la suite\nIl m'a fallu pas mal d'efforts pour régler la situation. Comme vous le comprenez probablement, je ne peux pas laisser cette trahison sans réponse. De plus, je ne peux pas vivre et travailler paisiblement en sachant que le rat est toujours en vie. J'ai envoyé des chasseurs de primes mais il n'y a toujours pas de résultat\nJe vous demande de vous occuper personnellement de cette affaire. D'autant plus que ses actions vous ont également affecté.";
			link.l1 = "Hm... ce salaud doit être pendu à la vergue ! Dis-m'en plus sur lui et sur mon paiement pour ce travail bien sûr.";
			link.l1.go = "FindRat_7";
		break;
			
		case "FindRat_7":
			dialog.text = "Ne t'inquiète pas pour cela. Je paierai une belle somme pour son élimination et je ne parle pas seulement d'argent. Je n'épargnerai pas les meilleurs objets de mes collections. Parlons de l'homme. Il s'appelle Francois Gontier\nIl est au courant de ma chasse, alors il a vendu sa frégate pour cacher ses traces. Mes collègues m'ont dit qu'il a été vu à Panama. Je crois que vous devriez commencer vos recherches là-bas.";
			link.l1 = "Eh bien, je suis en route alors.";
			link.l1.go = "FindRat_8";
		break;
			
		case "FindRat_8":
			dialog.text = "Je vous souhaite bonne chance alors. Sachez que ce Gontier est un marin très expérimenté et il a un équipage de ruffians téméraires. Il n'a rien à perdre, donc il se battra de manière très désespérée.";
			link.l1 = "Je n'ai pas peur des gens comme lui, mais je prendrai en compte ce que vous avez dit. Adieu, et soyez sûr que je le retrouverai même en enfer.";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;
			
		case "Wincorvette":
			dialog.text = "Splendide ! Maintenant, il peut rédiger ses rapports aux méduses. Personne n'ose m'embêter. Mes remerciements à vous, "+pchar.name+", vous êtes un homme indispensable.";
			link.l1 = "Merci, "+npchar.name+", pour une évaluation si positive de mes actions. Qu'en est-il de mon paiement ?";
			link.l1.go = "Wincorvette_1";
		break;
			
		case "Wincorvette_1":
			dialog.text = "Bien sûr. Je paierais le bon prix pour un travail aussi difficile. Tout d'abord, je vous présente cet excellent télescope.";
			link.l1 = "Hé bien, quel cadeau !";
			link.l1.go = "Wincorvette_2";
		break;
			
		case "Wincorvette_2":
			dialog.text = "En outre, voici 100 000 pesos comme votre paiement principal et 50 000 comme compensation pour vos propres frais.";
			link.l1 = "Merci, "+npchar.name+"Je le répète, c'est un réel plaisir de traiter avec vous.";
			link.l1.go = "Wincorvette_3";
			Log_Info("You've received an excellent spyglass");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "spyglass4", 1);
		break;
			
		case "Wincorvette_3":
			dialog.text = "Je t'attendrai dans un mois comme d'habitude. C'est une affaire de grande envergure et tu auras besoin d'une escadre bien équipée. Je te demande de comprendre cela et de te préparer correctement. Si mon plan fonctionne, nous serons riches.";
			link.l1 = "Bien,"+npchar.name+"Je reviendrai quand je serai prêt.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
			
		case "Lostcorvette":
			dialog.text = "Quel dommage, quelle honte... Eh bien, ne sois pas contrarié, tu n'es pas le premier homme que cette canaille a trompé. Je l'attraperai un jour de toute façon\nQuant à toi, reviens me voir dans un mois. Ce sera grand, alors rassemble une escadre bien équipée et armée. S'il te plaît, prends cela au sérieux et fais de ton mieux pour te préparer. Si mon plan fonctionne, nous serons riches.";
			link.l1 = "Bien, "+npchar.name+" Je reviendrai quand je serai prêt.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
		
		case "Havana_fort":
			dialog.text = "Tu arrives juste à temps, "+pchar.name+"! J'étais sur le point de commencer à m'inquiéter, j'allais envoyer un homme pour te trouver\nCommençons! Ta mission est vraiment grande et risquée maintenant, mais la récompense est adéquate. Tu recevras plus d'un million de pesos une fois le travail accompli.";
			link.l1 = "Maintenant, nous parlons ! Je vous écoute, "+npchar.name+".";
			link.l1.go = "Havana_fort_1";
		break;
		
		case "Havana_fort_1":
			dialog.text = "Les Indiens réduits en esclavage étaient déplacés par petits groupes vers La Havane depuis tout le continent, et quelques galions venaient d'Afrique et étaient déchargés. À présent, il y a presque cinq mille esclaves derrière les hauts murs du fort de La Havane.";
			link.l1 = "J'ai l'impression que l'affaire concerne l'assaut de La Havane.";
			link.l1.go = "Havana_fort_2";
		break;
		
		case "Havana_fort_2":
			dialog.text = "Vous avez un bon pressentiment, "+pchar.name+" . C'est exactement ce que je veux vous demander de faire. Vous et seulement vous. Je doute que l'un de mes autres agents soit capable de faire cela\nJe crois que vous êtes partant?";
			link.l1 = "Pour être honnête, "+npchar.name+", je suis un peu abasourdi maintenant. Je n'avais aucune idée que votre activité était si... à grande échelle. Bien sûr, je suis partant. "+RandSwear()+"";
			link.l1.go = "Havana_fort_3";
			link.l2 = "Tu sais quoi, "+npchar.name+", cela va trop loin. J'en ai assez de tes surprises. La prochaine fois, ta cupidité voudra que je déclare la guerre à l'Espagne et je devrais les combattre tout seul. Si tu as vraiment besoin de ces esclaves, alors prends d'assaut La Havane par toi-même.";
			link.l2.go = "Havana_fort_not";
		break;
		
		case "Havana_fort_not":
			dialog.text = "Je ne m'attendais pas à cela de votre part... Bon sang, que suis-je censé dire à mon client ? Très bien. C'est votre décision et je dois trouver un nouveau partenaire. Adieu, "+pchar.name+". Et je n'utiliserai pas vos services à l'avenir. Souvenez-vous que vous avez laissé tomber l'affaire qui aurait pu enrichir vos descendants jusqu'à la septième génération.";
			link.l1 = "Vous ne pouvez pas obtenir tout l'argent du monde, et vous mordez plus que vous ne pouvez mâcher. Adieu, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Havana_fort_3":
			dialog.text = "Je savais que vous seriez d'accord. Maintenant, écoutez les détails. Le fort de La Havane a toujours été une cible difficile, mais il l'est encore plus maintenant\nDeux vaisseaux de ligne gardent les côtes de Cuba et vous devez d'abord vous en occuper avant de prendre d'assaut le fort...";
			link.l1 = "Je vois. Ce ne sera pas la première fois que je combats des vaisseaux de ligne, ha-ha. Combien de temps ai-je ?";
			link.l1.go = "Havana_fort_4";
		break;
		
		case "Havana_fort_4":
			dialog.text = "Pas beaucoup. Pas plus de trois semaines, et après cela les esclaves seront transférés aux avant-postes espagnols de Cuba. Il faut vous dépêcher. ";
			link.l1 = "Ne perdons pas notre temps alors. Je suis en route !";
			link.l1.go = "Havana_fort_5";
		break;
		
		case "Havana_fort_5":
			dialog.text = "Un instant !"+pchar.name+", vous et moi n'avons jamais eu de malentendus ni de désaccords. Néanmoins, je veux que vous sachiez ce qui se passe ici. Je compte sur vous, et le client compte sur moi\nNous avons investi beaucoup d'efforts et d'argent dans cette opération. Chaque esclave, tous les cinq mille doivent m'être livrés\nSinon, nous prendrons des mesures très radicales contre vous. Sans vouloir vous offenser, ceci n'est qu'un avertissement. ";
			link.l1 = "Ne vous inquiétez pas, "+npchar.name+", je comprends ce qu'est le commerce, c'est pourquoi tu devrais aussi te souvenir de me payer, une fois que je les aurai livrés. Adieu.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//отправляем в локацию
            pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//создание линейных кораблей
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);	//таймер
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //капитулянтская нода мэра
			pchar.questTemp.Slavetrader = "wait1";
		break;
		
		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = "Eh bien... Et qu'en est-il du prix de votre victoire ?";
				link.l1 = "J'ai "+sTemp+" esclaves.";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "Eh bien, eh bien. As-tu oublié ce que j'ai dit ? Tu devais m'amener ici pas moins de cinq mille esclaves et tu as "+sTemp+"Pourquoi donc ?";
				link.l1 = "Hmm... Certains d'entre eux n'ont pas survécu au voyage depuis La Havane... la nourriture et les médicaments venaient à manquer.";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "Eh bien, eh bien... Tu veux me duper ? As-tu oublié ce que j'ai dit ? Où sont mes esclaves, je te demande ! Où sont-ils ?!";
			link.l1 = "Hm.. Eh bien, voyez-vous...";
			link.l1.go = "Havana_Fort_no";
		break;
		
		case "Havana_Fort_no":
			dialog.text = "Très bien. Je n'ai pas besoin de vos explications. Nous avions un accord et je vous donnerai une semaine pour obtenir pas moins de cinq mille esclaves. Vous aurez beaucoup de problèmes sinon.";
			link.l1 = "Très bien, très bien, détends-toi, je vais les obtenir pour toi.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 14, false);
			} 
			else SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;
		
		case "Havana_Fort_yes":
			dialog.text = "Splendide ! Vous avez accompli ma tâche comme toujours. Je suis très satisfait de vous.";
			link.l1 = "Moi aussi... Mais je serais encore plus satisfait lorsque je recevrai mon argent pour la cargaison.";
			link.l1.go = "Havana_Fort_yes_1";
		break;
		
		case "Havana_Fort_yesA":
		dialog.text = "Je suis très heureux pour cela. Vous êtes arrivé en retard, mais vous avez accompli ma tâche de la manière la plus excellente.";
			link.l1 = "Et maintenant, je veux obtenir de l'argent pour la cargaison.";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;
		
		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "Bien sûr. Je vais vendre les esclaves à mon client, il paiera et vous recevrez vos pièces. Comme la dernière fois. Voyons voir, vous avez amené ici "+sTemp+"esclaves. La somme est "+FindRussianMoneyString(iSlaveMoney)+". Reviens ici pour le paiement dans une semaine.";
			link.l1 = "D'accord, "+npchar.name+", nous avons un accord. Je serai ici dans une semaine. Mais soyez très prudent...";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;
		
		case "Havana_Fort_yes_2":
			dialog.text = ""+pchar.name+", s'il vous plaît, ne faites pas ça. Nous sommes partenaires et il n'y a pas de place pour la tromperie et la méfiance entre nous. Je vous ai promis beaucoup de pièces et vous les avez reçues. Je vous ai promis des tâches intéressantes et vous les avez eues aussi. J'ai toujours compensé vos coûts même dans les jours les plus sombres pour mon commerce. N'ai-je jamais tenu ma parole ?";
			link.l1 = "Hmm... Non... Je veux juste être payé, c'est tout.";
			link.l1.go = "Havana_Fort_yes_3";
		break;
		
		case "Havana_Fort_yes_3":
			dialog.text = "Voyez maintenant..."+pchar.name+", vous êtes mon meilleur agent et je compte faire affaire avec vous à nouveau à l'avenir. ";
			link.l1 = "D'accord, "+npchar.name+" . Mais vous devez aussi me comprendre - un million de pesos est une somme énorme.";
			link.l1.go = "Havana_Fort_yes_4";
		break;
		
		case "Havana_Fort_yes_4":
			dialog.text = "Je vous comprends très bien, mais je dois d'abord vendre les esclaves et ce n'est qu'alors que je recevrai de l'argent.";
			link.l1 = "Très bien. Je pense que nous nous sommes compris.";
			link.l1.go = "Havana_Fort_yes_5";
		break;
		
		case "Havana_Fort_yes_5":
			dialog.text = "Splendide. À la semaine prochaine. Et maintenant, je dois me préparer et partir pour commercer avec mon client.";
			link.l1 = "Je ne vous dérangerai pas alors. À dans une semaine, "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city +"_town";
			LocatorReloadEnterDisable(npchar.city +"_town", "reload8_back", true);//чтобы не ходил неделю сюда вообще
		break;

		case "Usurer_Escape":
			dialog.text = "Que fais-je ici ? Eh bien... c'est ma banque. Je l'ai achetée il y a deux jours. Vous êtes mon premier client et je peux vous offrir des conditions de crédit très tentantes...";
			link.l1 = "Merde les crédits ! Où est "+pchar.questTemp.Slavetrader.Name+"?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "Calmez-vous, je vous prie ! Il s'est enfui il y a longtemps.";
			link.l1 = "Comment ?";
			link.l1.go = "Usurer_Escape_2";
		break;
		
		case "Usurer_Escape_2":
			dialog.text = "Vous ne savez pas ? Il a disparu il y a une semaine. Il s'avère qu'il a pris tous les investissements de ses clients. On dit même que le gouverneur en a souffert. Cette maison a été laissée et je l'ai achetée de la colonie.";
			link.l1 = "Disparu ? Comment ?";
			link.l1.go = "Usurer_Escape_3";
		break;
		
		case "Usurer_Escape_3":
			dialog.text = "J'ai entendu dire qu'il s'est enfui de notre colonie... Je suppose qu'il vous doit aussi. Beaucoup?";
			link.l1 = "Plus d'un million ! Mais j'attraperai ce rat de toute façon ! Où est-il parti ? Nom de son navire ?";
			link.l1.go = "Usurer_Escape_4";
		break;
		
		case "Usurer_Escape_4":
			dialog.text = "Personne n'en est conscient. Sérieusement. Il est juste parti. Le navire nommé 'Mauritius' ou 'Maurdius' avait pris la mer ce jour-là, peut-être l'a-t-il utilisé pour s'échapper.";
			link.l1 = "Merde ! Et j'ai fait confiance à ce salaud ! Il avait une odeur de traître dès le premier jour ! Et j'étais assez fou pour croire que nous étions de vrais partenaires ! Mais je lui ferai regretter un jour... Bien,"+npchar.name+", Je m'excuse pour mon comportement... Si vous êtes un homme de bien, je traiterai avec vous à l'avenir, soyez-en sûr, mais pour l'instant, adieu.";
			link.l1.go = "Usurer_Escape_5";
		break;
		
		case "Usurer_Escape_5":
			string sColony;
			sColony = npchar.city;
			SetNull2Deposit(sColony);
			dialog.text = "Tout va bien. Je comprends. Si vous avez besoin d'argent ou si vous souhaitez investir, je suis toujours à votre service.";
			link.l1 = "Merci. Mais je ferais mieux de garder mon argent avec moi. À bientôt.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "wait1";
			pchar.questTemp.SanBoxTarget.Slavetrader = true;
			ChangeCharacterComplexReputation(pchar, "fame", 25);
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], false); // разблокируем вход офицеров 2015
		break;
	//<--работорговец	

	//--> семейная реликвия
		case "Noblelombard":
			dialog.text = "Oh vraiment? Il semble qu'il ne veuille pas parler à moi-même.... Très bien, discutons de la question avec vous. "+pchar.GenQuest.Noblelombard.Name+" me doit "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+": "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Money))+" et aussi mon intérêt - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent))+" pour trois mois. Si je ne vois pas d'argent d'ici demain, alors je vendrai sa relique et peu m'importe sa valeur pour lui. Les affaires sont les affaires.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Summ))
			{
				link.l1 = "Splendide ! Dans ce cas, je vais vous régler la somme entière avec tous les intérêts immédiatement - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+". Il prendra sa relique lui-même. Voici votre argent.";
				link.l1.go = "Noblelombard_1";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent)*2)
			{
				link.l2 = "Mon client disposera des fonds dans trois mois. Faisons affaire, je vous paierai les intérêts pour les trois derniers mois et pour les trois prochains mois."+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent)*2)+"Et la dette elle-même vous sera payée plus tard.";
				link.l2.go = "Noblelombard_2";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent))
			{
				link.l3 = "Mon client aura de l'argent dans trois mois. Que diriez-vous si je vous paye les intérêts pour les trois derniers mois et que vous attendiez que mon client ait assez d'argent ?";
				link.l3.go = "Noblelombard_3";
			}
			link.l4 = "Cette rareté coûte une fortune ! On dirait que mon client devra payer lui-même pour cela.";
			link.l4.go = "Noblelombard_4";
			pchar.quest.noblelombard = "true";//лесник с нпчара на пчара
		break;
		
		case "Noblelombard_1":
			dialog.text = "Excellent ! Tout s'est bien passé, j'ai récupéré mon argent et "+pchar.GenQuest.Noblelombard.Name+"récupérera sa relique.";
			link.l1 = "Enchanté de faire affaire avec vous, "+npchar.name+"Adieu pour l'instant.";
			link.l1.go = "exit";
			pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Summ)*2;
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Summ));
			pchar.GenQuest.Noblelombard = "full";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
	
		break;
		
		case "Noblelombard_2":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 7)
			{
				dialog.text = "Hm.. Bien. Cela me convient. Mais si "+pchar.GenQuest.Noblelombard.Name+" ne trouve pas l'argent dans les trois mois, alors je ne ferai plus de délai. Assurez-vous qu'il le sache.";
				link.l1 = "Je le ferai ! Je suis heureux que nous ayons conclu un accord. Adieu pour l'instant.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*4;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent)*2);
				pchar.GenQuest.Noblelombard = "maxpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
			
			}
			else
			{
				dialog.text = "Non. Cela ne marchera pas. J'ai besoin de la somme entière et avant le coucher du soleil. Assurez-vous que votre 'client' le sache. Je n'ai rien de plus à vous dire.";
				link.l1 = "Hm... très bien. Dommage que vous ne vouliez pas faire de compromis.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			
			}
		break;
		
		case "Noblelombard_3":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 3)
			{
				dialog.text = "Hm.. Soit. Je l'accepte uniquement par respect pour votre client. Mais si "+pchar.GenQuest.Noblelombard.Name+"ne trouve pas l'argent dans trois mois, alors je ne ferai plus de délai. Assurez-vous qu'il le sache.";
				link.l1 = "Je vais le faire ! Je suis ravi que nous ayons conclu un accord. Adieu pour l'instant.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*2;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent));
				pchar.GenQuest.Noblelombard = "minpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 150);
			}
			else
			{
				dialog.text = "Non. Cela ne fonctionnera pas. J'ai besoin de la somme entière et avant le coucher du soleil. Assurez-vous que votre 'client' le sache. Je n'ai rien d'autre à vous dire.";
				link.l1 = "Hm... très bien. Dommage que vous ne vouliez pas faire de compromis.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 60);
	
			}
		break;
		
		case "Noblelombard_4":
			DialogExit();
			pchar.GenQuest.Noblelombard = "fail";
		break;
		
		case "Noblelombard_5":
			if(sti(pchar.GenQuest.Noblelombard.Chance) == 9)
			{
				dialog.text = "Tu ne dis pas! "+pchar.GenQuest.Noblelombard.Name+"n'a pas ouvert de dépôt à votre nom. Il n'est même pas dans notre colonie - il est parti pour l'Europe. Je vous dis que je n'ai jamais vu un homme aussi malhonnête. Il a voulu me tromper mais a échoué - j'ai quelques tours dans mon sac...";
				link.l1 = "Salaud ! Il m'a donné sa parole....";
				link.l1.go = "Noblelombard_6";
			}
			else
			{	// Addon-2016 Jason уменьшаем раздачу дублонов
				dialog.text = "Correct. "+pchar.GenQuest.Noblelombard.Name+"a fait un dépôt à votre nom. S'il vous plaît, prenez-le...";
				link.l1 = "Splendide ! Adieu, "+npchar.name+".";
				link.l1.go = "Noblelombard_9";
			}
		break;
		
		case "Noblelombard_6":
			dialog.text = "Il n'y a pas de telle chose pour des gens comme "+pchar.GenQuest.Noblelombard.Name+" parce qu'ils n'ont ni honneur ni conscience. Je suppose qu'il vous a trompé ?";
			link.l1 = "Il l'a fait, je suppose. Quoi qu'il en soit, "+npchar.name+", je ne vais pas rester ici longtemps non plus et l'Europe est petite... Peut-être que nous nous rencontrerons un jour. Adieu !";
			link.l1.go = "Noblelombard_7";
		break;
		
		case "Noblelombard_7":
			DialogExit();
			AddQuestRecord("Noblelombard", "6");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(Pchar, "quest.noblelombard"); // лесник с нпчара на пчара
		break;
		
		case "Noblelombard_9":
			DialogExit();
			iTemp = sti(pchar.GenQuest.Noblelombard.Regard); // Addon-2016 Jason уменьшаем раздачу дублонов
			AddMoneyToCharacter(pchar, iTemp);
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Noblelombard", "7");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(Pchar, "quest.noblelombard");// с нпчара на пчара  лесник
		break;
//<-- семейная реликвия

		// Бремя гасконца
		case "sharlie_credit":
			dialog.text = "Monsieur, je ne vous connais pas. Je prête de l'argent uniquement aux citoyens locaux ou aux capitaines. Pardonnez-moi...";
			link.l1 = "Je vois. Dommage, cependant.";
			link.l1.go = "exit";
		break;
		// Бремя гасконца
		
		// Addon-2016 Jason, французские миниквесты (ФМК)
		// ФМК-Гваделупа
		case "FMQG_x":
			DelLandQuestMark(npchar);
			dialog.text = "Qu-quoi... Que voulez-vous dire ?";
			link.l1 = "Tu es un foutu rat ! Maintenant écoute-moi très attentivement : je ne suis pas si stupide. Pinette avait écrit deux copies de la lettre. Je t'en ai donné une, la deuxième est en possession de mon agent de confiance. Si quelque chose m'arrive - mon gars la remettra directement entre les mains du gouverneur...";
			link.l1.go = "FMQG_x1";
		break;
		
		case "FMQG_x1":
			dialog.text = "Bonjour, ami.";
			link.l1 = "Je vous suggère donc de prier pour ma bonne santé à l'église à chaque sermon du matin au lieu d'envoyer des assassins pour ma vie. Un dernier avertissement ! Faites un geste contre moi et vous êtes foutu. Compris ? Bien. Prenez une grande respiration et continuez à compter vos doublons.";
			link.l1.go = "FMQG_x2";
		break;
		
		case "FMQG_x2":
			DialogExit();
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "27");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Sneak", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		// Другое
		case "NeHochuRazgovarivat":
			dialog.text = "Je ne veux pas te parler.";
			link.l1 = "... ";
			link.l1.go = "exit";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Usurer_1":
			dialog.text = "Bien sûr ! Beaucoup veulent juste récupérer leur argent et s’en aller. Surtout avec les rumeurs récentes...";
			link.l1 = "Quelles rumeurs ?";
			link.l1.go = "LadyBeth_Usurer_2";
		break;
		
		case "LadyBeth_Usurer_2":
			dialog.text = "On dit que les conditions dans l’équipage se dégradent. Monsieur Blackwood tolérerait même des pertes régulières - ce qui n’était jamais le cas avant. Mais ce n’est pas mon affaire. Moi, je vends. Alors, qu’est-ce qui vous intéresse ?";
			link.l1 = "Passons aux choses sérieuses.";
			link.l1.go = "next";
			npchar.quest.item_date = "LadyBeth";
			pchar.questTemp.LadyBeth_Usurer = true;
		break;
		// Леди Бет <--
	}	
}

// ugeen проверка, можем ли мы использовать дублоны в качестве вклада
bool CheckUseDublons(ref NPChar)
{
	int iTest 	= FindColony(NPChar.City); // город банка
	if(iTest == -1) return false;
	
	ref rColony = GetColonyByIndex(iTest);
	 	 
	bool bOk1 = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea); 
	bool bOk2 = (GetCharacterItem(pchar,"gold_dublon") > 10) || (CheckItemMyCabin("gold_dublon") > 10);
	
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk1 && bOk2) return true;

	return false;
}

void SlavetraderGalleonInWorld()
{
	//создаем галеон с рабами
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "", "man", "man", 45, SPAIN, 20, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_LINESHIP, sName, CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
	sld.Ship.Mode = "war";	
	SetCaptanModelByEncType(sld, "war");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;
	sld.DontRansackCaptain = true;
	sld.WatchFort = true;
	sld.AlwaysEnemy = true;
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//положить в трюм рабов
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//в морскую группу кэпа
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";
	sld.city = pchar.questTemp.Slavetrader.Island; //определим колонию, из бухты которой выйдет
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //определим колонию, в бухту которой он придёт
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	//Log_TestInfo("Captain of the galleon sailed away from " + sld.city + "and heading to " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Galleon '" + sName + " '";
	int daysQty = 20; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//вот он, сам запуск энкаунтера
}
