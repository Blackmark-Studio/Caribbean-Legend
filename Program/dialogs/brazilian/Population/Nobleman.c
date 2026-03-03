//Jason общий диалог дворян
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iTest;
	string sTemp, sTitle;
	float locx, locy, locz;

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
	
	iTest = FindColony(NPChar.City); // 170712
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> проверка межнациональных отношений
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
				dialog.text = NPCStringReactionRepeat("Hm. Você está navegando sob a bandeira de "+NationNameGenitive(sti(pchar.nation))+", camarada. Que diabos você está fazendo aqui na nossa cidade? Cai fora!","Eu não quero que desconfiem que sou amigo de "+NationNameAblative(sti(pchar.nation))+"! Cai fora ou vou chamar os guardas!","É sua última chance de sair daqui. Caso contrário, só poderá culpar a si mesmo.","Eu te avisei. Agora você vai pagar pela sua insolência, bastardo!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Que patriota, hein!","Tá bom, tá bom, calma. Eu já estou indo.","Não faça tanto barulho. Estou indo embora.","O quê?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> проверка репутации - дворяне гнобят супернегодяев
			if (sti(pchar.reputation.nobility) < 10)
			{
				dialog.text = NPCStringReactionRepeat("Olha só! E como é que nossos guardas deixam um bastardo como você andar livremente pela cidade? Impossível...","Cai fora, nem quero falar com você! Carrasco...","É sua última chance de fugir. Caso contrário, só poderá culpar a si mesmo.","Eu te avisei. Agora você vai pagar pela sua insolência, bastardo!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Ei, ei! Mostre um pouco de respeito, senhor!","Olhe para si mesmo, santo...","Calma...","O quê?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> диалог первой встречи
            if(NPChar.quest.meeting == "0")
			{
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)//дворянин-пассажир
				{
					dialog.text = "Saudações, "+GetAddress_Form(NPChar)+". Vejo que você é o capitão de um belo navio. Quero lhe pedir um favor. Você pode aceitar ou recusar.";
					link.l1 = "Estou ouvindo, "+GetAddress_FormToNPC(NPChar)+". O que você quer dizer?";
					link.l1.go = "passenger";
					link.l2 = "Com licença, "+GetAddress_FormToNPC(NPChar)+", mas estou com pressa.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsUniversalShipType(pchar), IsMerchantShipType(pchar)))//дворянин-пассажир
				{
					dialog.text = "Saudações, "+GetAddress_Form(NPChar)+". Vejo que você é o capitão de um belo navio. Tenho um favor a lhe pedir. Você pode aceitar ou recusar.";
					link.l1 = "Estou ouvindo, "+GetAddress_FormToNPC(NPChar)+". O que você quer dizer?";
					link.l1.go = "passenger";
					link.l2 = "Com licença, "+GetAddress_FormToNPC(NPChar)+", mas estou com pressa.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (CheckAttribute(npchar, "quest.donation"))//клянчит деньги
				{
					dialog.text = "Aha, é bom ver um cavalheiro em nossa pequena cidade! Tenho certeza de que acabou de chegar da Europa. Escute, quero lhe pedir um favor – de cavalheiro para cavalheiro. Espero que me compreenda corretamente.";
					link.l1 = "Bom dia para você, senhor. Estou ouvindo.";
					link.l1.go = "donation";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.lombard") && !CheckAttribute(pchar, "GenQuest.Noblelombard"))//семейная реликвия
				{
					dialog.text = "Bom dia, "+GetAddress_Form(NPChar)+"! Que bom encontrar um cavalheiro nas ruas da nossa cidade! Permite-me tomar alguns minutos do seu tempo?";
					link.l1 = "Claro, senhor. Estou ouvindo.";
					link.l1.go = "lombard";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.slaves") && !CheckAttribute(&Colonies[FindColony(npchar.city)], "questslaves"))//привезти рабов
				{
					dialog.text = "Bom dia para você, capitão! Fico feliz em vê-lo, pois parece alguém que sabe resolver problemas.";
					link.l1 = "Depende do problema. Eu sou especialista em resolver as coisas na base da violência. É isso que você procura, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "slaves";
					npchar.quest.meeting = "1";
					break;
				}
				dialog.text = RandPhraseSimple("Olá, "+GetAddress_Form(NPChar)+". Você quer algo de mim?","O que deseja, senhor?");
				link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Não vou tomar muito do seu tempo, só queria perguntar...";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Preciso de informações sobre a sua colônia.","Preciso de informações.");
				link.l2.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("A cidade inteira está em alerta – dom Fernando de Alamida, o inspetor real, chegou. Olha, já vi muita coisa por aqui, mas isso... Não é o luto que muda as pessoas, e sim como elas lidam com ele. Dizem que ele se transformou depois da morte do pai. Agora, não há servidor da Coroa mais incorruptível e... implacável em todo o Arquipélago.","Olhe só para o 'Santa Misericórdia'! Dizem que o próprio rei mandou construir esse navio seguindo projetos especiais. E repare – não tem um arranhão sequer. Como se a própria Virgem Maria o protegesse. Mas ouvi uns boatos... talvez nem seja a Virgem, afinal.","Você sabe quantas vezes já tentaram matar Dom Fernando? Doze ataques em mar aberto – e isso só no ano passado! Bem, com uma tripulação tão leal e bem treinada, e sob a proteção do Senhor – ele vai sobreviver ao décimo terceiro também!"),LinkRandPhrase("Você ficou sabendo? Dom Fernando de Alamida chegou à nossa cidade, e dizem que ele está pelas ruas neste momento. Eu adoraria vê-lo com meus próprios olhos...","Um homem complicado, esse dom Fernando. Uns dizem que ele é um salvador, limpando a Mãe-Pátria da sujeira. Outros sussurram que algo se quebrou nele depois da morte do pai e que logo todos estaremos chorando. Mas vou te dizer uma coisa: não tenha medo dele. Tema aqueles que o fizeram ser quem é.","Que homem bonito, esse dom Fernando! Mas sabe o que é estranho? Parece que ele não repara em ninguém. Só pensa em dever e serviço. Ouvi dizer que havia uma moça... mas depois de conversar com um padre, ele largou totalmente os prazeres do mundo. Como se tivesse feito um voto."),RandPhraseSimple(RandPhraseSimple("Maldito inspetor! Enquanto ele está aqui, a cidade parece morta. Nada de comércio, nada de diversão. Até respirar, parece, tem que ser mais baixo. E sabe o que é mais assustador? É assim em todo porto. Sempre igual. Sua Majestade Real não poderia ter inventado tortura pior pra todos nós!","Dom Fernando visitou o orfanato novamente. Ele faz doações generosas, reza por horas. Um homem tão digno deveria servir de exemplo para aqueles malditos ladrões!"),RandPhraseSimple("Ha! O 'santo' Fernando fechou todos os bordéis de novo. Mas deixa pra lá, logo ele vai embora e eles abrem de novo.","O insp... inspetor chegou, isso sim! Dom Fernando de Almeida, ou, como é mesmo o nome dele, Almeida! Tão importante que até o governador anda nas pontas dos pés perto dele. Dizem que ele olha nos seus olhos e enxerga todos os seus pecados na hora. Assustador!")));
					link.l1 = "...";
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
			else //--> повторные обращения
			{
				dialog.text = NPCStringReactionRepeat("O quê? De novo? Não tenho tempo pra você. Procure outra pessoa pra conversar. Tem um monte de gente comum andando pelas ruas. E eu preciso ir, vai ter um banquete hoje à noite na residência do governador e preciso preparar minha roupa...","Não, agora isso está realmente irritante! Você não entende? Ou é lento da cabeça?","Senhor, começo a suspeitar que o senhor não é só um idiota, mas também um caipira grosseiro. Aviso: me deixe em paz ou vai se arrepender de me importunar.","Chega. Vou te ensinar uma lição, seu insolente!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Entendi. Adeus.","Sim, sim, só esqueci o que queria perguntar...","Você me entendeu mal...","O quê?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = LinkRandPhrase("Continue.","O que você quer?","Perguntas? Tudo bem, marinheiro, estou ouvindo.");
			link.l1 = LinkRandPhrase("Você não vai me contar as últimas fofocas da sua cidade?","Aconteceu algo interessante por aqui ultimamente?","Alguma novidade do Caribe, senhor?");
			link.l1.go = "rumours_nobleman";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------дворянин-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Noblepassenger", false);
			else SetPassengerParameter("Noblepassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				dialog.text = ""+GetSexPhrase("Senhor","Madame")+", preciso chegar à colônia"+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+", assim que possível, está em "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+", por "+FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty))+". Seu navio parece robusto e veloz comparado à maioria dessas barcaças que navegam por aqui. Posso lhe pagar "+FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money))+". O que você diria?"; // belamour gen
			}
			else
			{
				dialog.text = "Olá, "+GetSexPhrase("senhor","senhora")+"! Preciso chegar a "+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+"! Isso está em "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+", aliás. Sim, sim, eu sei – aqueles desgraçados estão só esperando a gente aparecer por lá. Mas eu tenho uma reunião muito urgente e importante lá! Não sou mão de vaca – embora eu não goste de pagar, sempre pago. Larga tudo o que estiver fazendo e, assim que a gente chegar, eu te dou "+FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money))+".";
			}
			link.l1 = "Hm. Também estou indo nessa direção, então posso te levar a bordo nessas condições.";
			link.l1.go = "passenger_1";
			link.l2 = "Me desculpe, "+GetAddress_FormToNPC(NPChar)+", mas estou navegando em outra direção. Não posso te ajudar.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Que pena. Bem, vou esperar por outro navio. Adeus.";
			link.l1 = "Até mais.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Noblepassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Ótimo! Estou cansado de esperar. Você receberá seu pagamento quando chegarmos lá.";
			link.l1 = "Vá para o meu navio, "+GetAddress_FormToNPC(NPChar)+". Vamos partir em breve.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Noblepassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "nobleman");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Noblepassenger.City+"Gen") + ", at " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Dat")+".";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Noblepassenger.win_condition.l1 = "location";
			pchar.quest.Noblepassenger.win_condition.l1.location = pchar.GenQuest.Noblepassenger.City+"_town";
			pchar.quest.Noblepassenger.function = "Noblepassenger_complete";
			SetFunctionTimerCondition("Noblepassenger_Over", 0, 0, sti(pchar.GenQuest.Noblepassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Noblepassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Aqui estamos, excelente! Viajar no seu navio foi realmente agradável. Sua tripulação é disciplinada e o convés está impecável! Meus agradecimentos. Pegue seu dinheiro, senhor.";
			link.l1 = "Boa sorte, "+GetAddress_FormToNPC(NPChar)+"! Adeus.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Noblepassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Noblepassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
		break;
//<-- дворянин-пассажир

//-------------------------------------------------помощь деньгами------------------------------------------------
		case "donation":
			sTemp = DonationText();
			dialog.text = "Tenho um negócio bastante delicado..."+sTemp+" Preciso de dinheiro agora ou estarei em sérios apuros. Eu nunca pediria dinheiro a outro cavalheiro normalmente, mas a situação é realmente desesperadora.";
			link.l1 = "Quanto você precisa?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			iTemp = hrand(4)+1;
			pchar.GenQuest.Nobledonation.Money = iTemp*1000+rand(iTemp)*150;
			dialog.text = "A quantia é bem pequena, é "+FindRussianMoneyString(sti(pchar.GenQuest.Nobledonation.Money))+". Então, pode me ajudar?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Nobledonation.Money))
			{
				link.l1 = "Sim, claro. Pegue.";
				link.l1.go = "donation_2";
			}
			link.l2 = "Eu até ajudaria, mas meus bolsos também estão vazios – não tenho nem um peso sobrando.";
			link.l2.go = "donation_exit";
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeOfficersLoyality("bad_all", 1);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
		
		case "donation_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Nobledonation.Money));
			dialog.text = "Minha gratidão, "+GetAddress_Form(NPChar)+"! Você me salvou! Tenho amigos na residência do governador e vou contar a eles sobre sua generosidade. Mil vezes obrigado novamente!";
			link.l1 = "De nada, senhor. Tenho certeza de que faria o mesmo por mim.";
			link.l1.go = "donation_3";
		break;
		
		case "donation_3":
			DialogExit();
			ChangeOfficersLoyality("good_all", rand(2)+1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), rand(1)+2);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
//<-- помощь деньгами

//-------------------------------------------------семейная реликвия---------------------------------------------
		case "lombard":
			LombardText();
			dialog.text = "Preciso da sua ajuda. Você é rico e um cavalheiro, então espero que compreenda. Não faz muito tempo, eu estava desesperado por dinheiro, então tive que ir ao banqueiro e penhorar "+pchar.GenQuest.Noblelombard.Item+"\nEle ofereceu boas condições. Dez por cento ao mês, três meses no total. Mas o prazo acabou e eu não tenho dinheiro para resgatar o item por causa de um acontecimento infeliz\nAgora ele diz que encontrou um comprador para "+pchar.GenQuest.Noblelombard.Item+" e ele vai vendê-lo se eu não pagar minha dívida e os juros imediatamente. Mas eu não tenho muito dinheiro agora, e o objeto que eu penhorei é muito valioso...";
			link.l1 = "E como posso te ajudar com isso, "+GetAddress_FormToNPC(NPChar)+"?";
			link.l1.go = "lombard_1";
		break;
		
		case "lombard_1":
			dialog.text = "I'm asking you to speak with our banker. Offer him money, vouch for me... or do something else. Unfortunately, I have no one else to turn to; all of my good friends have suddenly gone 'bankrupt'. In three months "+pchar.GenQuest.Noblelombard.Text+", and I will repay all your costs, double! You have my word as a gentleman!";
			link.l1 = "Certo, vou tentar te ajudar com esse caso.";
			link.l1.go = "lombard_2";
			link.l2 = "Infelizmente, eu mesmo estou 'quebrado' no momento. Então não posso te ajudar, me desculpe mesmo!";
			link.l2.go = "lombard_exit";
		break;
		
		case "lombard_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_2":
			dialog.text = "Obrigado pela sua compreensão. Estarei esperando por você na taverna. Venha assim que puder.";
			link.l1 = "...";
			link.l1.go = "lombard_3";
		break;
		
		case "lombard_3":
			DialogExit();
			pchar.GenQuest.Noblelombard.id = npchar.id;
			AddDialogExitQuestFunction("Noblelombard_TookQuest");
		break;
		
		case "lombard_4":
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard"))
			{
				pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
				dialog.text = "O que você pode dizer, "+GetAddress_Form(NPChar)+"? Já foi ao banco? Tem boas ou más notícias?";
				if (pchar.GenQuest.Noblelombard == "full") link.l1 = "Já quitei. Paguei toda a sua dívida sozinho. Você pode ir lá e recuperar sua relíquia.";
				if (pchar.GenQuest.Noblelombard == "maxpercent") link.l1 = "Já paguei. Quitei todos os juros dos últimos três meses e também dos próximos três. Pode esperar seu dinheiro com tranquilidade. Só não se esqueça de quitar a dívida principal em três meses.";
				if (pchar.GenQuest.Noblelombard == "minpercent") link.l1 = "Já paguei. Quitei todos os juros dos últimos três meses. O banqueiro concordou em esperar mais três meses até você conseguir juntar o valor total.";
				link.l1.go = "lombard_5";
			break;
			}
			if (pchar.GenQuest.Noblelombard == "fail")
			{
				dialog.text = "O que você pode dizer, "+GetAddress_Form(NPChar)+"? Já foi ao banco? Tem boas ou más notícias?";
				link.l1 = "Eu tentei. Aquele avarento pediu uma quantia absurda. Recusou qualquer pedido de desconto e eu não tenho o valor necessário. Então não pude te ajudar. Desculpe.";
				link.l1.go = "lombard_fail";
			}
			else
			{
				dialog.text = "O que você pode dizer, "+GetAddress_Form(NPChar)+"?   Já foi ao banco?   Tem boas notícias ou más?";
				link.l1 = "Já estou nisso. Espere.";
				link.l1.go = "exit";
				NextDiag.TempNode = "lombard_4";
			}
		break;
		
		case "lombard_fail":
			pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
			dialog.text = "Meh, "+GetAddress_Form(NPChar)+"... Agora você também é testemunha da ganância incontrolável desses malditos agiotas sedentos de sangue. Por Deus, senhor, eles fazem os judeus parecerem santos! Lembre-se disso quando tentar pegar dinheiro emprestado com eles, como eu fiz. Obrigado por pelo menos tentar...";
			link.l1 = "Nunca gostei deles. Bem, quem gosta de agiotas? Me desculpe, "+GetAddress_FormToNPC(NPChar)+". Adeus.";
			link.l1.go = "lombard_fail_1";
		break;
		
		case "lombard_fail_1":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_fail");
		break;
		
		case "lombard_5":
			dialog.text = "Incrível! Você acabou de me salvar, "+GetAddress_Form(NPChar)+"! Eu nunca vou esquecer isso. Garanto que todas as suas despesas serão reembolsadas em dobro. Venha falar com nosso banqueiro em três meses. Vou abrir um depósito em seu nome.";
			link.l1 = "Certo, vou fazer como você disse. Até mais!";
			link.l1.go = "lombard_6";
		break;
		
		case "lombard_6":
			dialog.text = "Obrigado mais uma vez, capitão. Boa sorte!";
			link.l1 = "...";
			link.l1.go = "lombard_7";
		break;
		
		case "lombard_7":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_success");
		break;
//<-- семейная реликвия

//------------------------------------------привезти рабов под заказ--------------------------------------------
		case "slaves":
			npchar.quest.slaves.price = 3+hrand(1);//цена на рабов в дублонах
			npchar.quest.slaves.qty = 50+hrand(5)*10;//количество
			npchar.quest.slaves.money = sti(npchar.quest.slaves.qty)*sti(npchar.quest.slaves.price);
			dialog.text = "Eu sou dono de um "+LinkRandPhrase("factory","minha","plantação")+" e eu sempre preciso de novos escravos. O clima realmente acaba com eles. Agora mesmo eu preciso "+sti(npchar.quest.slaves.qty)+" cabeças. Estou disposto a encomendar um lote delas. Pagarei ouro por cada cabeça, "+sti(npchar.quest.slaves.price)+" dobrões\nSem pressa, não vou te limitar no tempo se você conseguir o que eu preciso. Bem, dentro do razoável, é claro, não demore mais de meio ano. Então, o que me diz? Negócio fechado?";
			link.l1 = "Fechado! O tráfico de escravos é um negócio sujo, mas vale o risco.";
			link.l1.go = "slaves_1";
			link.l2 = "Com licença, mas eu não sou um mercador de escravos. Esse não é o meu ramo.";
			link.l2.go = "exit_slaves";
		break;
		
		case "exit_slaves":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "slaves_1":
			dialog.text = "Muito bem então. Estarei esperando por você quando trouxer a carga. Pode me encontrar na igreja das 11h até 13h todos os dias. No restante do dia, estou ocupado ou trabalhando.";
			link.l1 = "Certo. Vou me lembrar disso. Até mais, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			DialogExit();
			sGlobalTemp = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			SaveCurrentNpcQuestDateParam(npchar, "slaves_date");//запоминаем дату
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", npchar.city+"_church", "sit", "sit"+(1+rand(5)), "Nobleslaves_Place", 10.0);
			chrDisableReloadToLocation = true;//закрыть локацию
			Colonies[FindColony(npchar.city)].questslaves = true;
			sTitle = npchar.city+"Nobleslaves";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Nobleslaves", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sQty", sti(npchar.quest.slaves.qty));
			AddQuestUserData(sTitle, "sMoney", sti(npchar.quest.slaves.money));
		break;
		
		case "slaves_3":
			if (GetNpcQuestPastDayParam(npchar, "slaves_date") < 180)
			{
				dialog.text = "Você trouxe "+sti(npchar.quest.slaves.qty)+" escravos como pedi, capitão?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= sti(npchar.quest.slaves.qty))
				{
					link.l1 = "Sim. Todo o lote está no meu porão de carga. Estou pronto para entregá-los a você.";
					link.l1.go = "slaves_4";
				}
				else
				{
					link.l1 = "Não, deixa comigo.";
					link.l1.go = "exit";
					NextDiag.TempNode = "slaves_3";
				}
			}
			else
			{
				dialog.text = "Capitão, se veio por causa daqueles escravos... Já comprei o suficiente e não preciso de mais agora. Você demorou demais, desculpe.";
				link.l1 = "Que pena! Mas você tem razão, eu não fui rápido o bastante. Adeus!";
				link.l1.go = "slaves_8";
			}
		break;
		
		case "slaves_4":
			dialog.text = "Excelente. Vou mandar um bote buscá-los imediatamente.";
			link.l1 = "E o meu pagamento?";
			link.l1.go = "slaves_5";
		break;
		
		case "slaves_5":
			dialog.text = "Não se preocupe, eu me lembro. Aqui, pegue o valor, "+sti(npchar.quest.slaves.price)+" doblões por cabeça. Um ótimo negócio para nós dois, não acha?";
			link.l1 = "Obrigado. Foi um prazer fazer negócios com você.";
			link.l1.go = "slaves_6";
		break;
		
		case "slaves_6":
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(npchar.quest.slaves.qty));
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.slaves.money));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.slaves.money))+"");
			PlaySound("interface\important_item.wav");
			dialog.text = "Com certeza... Com licença, preciso ir agora. Até mais!";
			link.l1 = "Boa sorte, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_7";
		break;
		
		case "slaves_7":
			DialogExit();
			npchar.lifeday = 0;
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			LAi_SetActorType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, npchar.city+"_church", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "2");
			CloseQuestHeader(sTitle);
		break;

		case "slaves_8":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "3");
			CloseQuestHeader(sTitle);
		break;
//<-- привезти рабов под заказ

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Ouça, como cidadão desta cidade, estou lhe pedindo para embainhar sua espada.","Ouça, como cidadão desta cidade, peço que guarde sua espada.");
			link.l1 = LinkRandPhrase("Certo.","Como quiser.","Certo.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetHP(NPChar, 400, 400);
			TakeNItems(NPChar, "potion2", 3);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "TempFight");
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterNationReputation(pchar, sti(npchar.nation), -3);
		break;
	}
}

string DonationText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "I've lost all my money in gambling yesterday and I don't have enough sum to wipe away the debt. Can you help me?" break;
		case 1: sText = "I had a nice time yesterday with a... certain lady of the evening, and now she is trying to blackmail me. I need to pay her first and then I will deal with her... Can you help me with some money?" break;
		case 2: sText = "I ran through a local fool with my rapier recently and now the commandant demands a bribe to hush up the event. I am short of money now. Can you help me?" break;
		case 3: sText = "I was unlucky enough to lose a bet and I don't have a trifling sum to repay the debt of honor. Can you help me?" break;
		case 4: sText = "Some bastard knows about my... indiscreet activities concerning a married woman. I don't have enough money to shut his mouth. Just a few gold coins are needed... " break;
		case 5: sText = "Some bastard has stolen important papers from my house and demanding a significant sum for their return. I've almost got it, just a few more coins needed. Can you help me?" break;
	}
	return sText;
}

void LombardText()
{
	switch (hrand(5))
	{
		case 0:
			pchar.GenQuest.Noblelombard.Item = "my mother's diamond pendant made by a jeweler from Madrid";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my inheritance","my ship will return from Africa loaded with slaves");
		break;
		case 1: pchar.GenQuest.Noblelombard.Item = "an emerald necklace of my sister crafted by a jeweler in Paris";
				pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will inherit a county in Europe","my ship will return from India loaded with spices and silk");
		break;
		case 2:
			pchar.GenQuest.Noblelombard.Item = "family ring with an emblem of our kin";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my expedition will return from the Spanish Main with gold ingots","I will get my inheritance");
		break;
		case 3:
			pchar.GenQuest.Noblelombard.Item = "a ruby bracelet of my wife, a gift from her mother";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my investment with the interest from a European bank","I will get the profits from my plantation");
		break;
		case 4:
			pchar.GenQuest.Noblelombard.Item = "a necklace of gold and diamonds, piece work, a pride of my wife";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get profits from my current business","my ship will be back from Africa with the cargo hold stuffed with black ivory");
		break;
		case 5:
			pchar.GenQuest.Noblelombard.Item = "an ivory cane of semiprecious stones, a gift from my grandfather";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my ship will be back from India with the cargo hold filled with silks and spices","I will receive my interest from a European bank");
		break;
	}
}
