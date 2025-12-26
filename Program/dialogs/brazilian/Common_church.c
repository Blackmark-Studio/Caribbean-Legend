// boal 25/04/04 общий диалог церковь
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    
    string iDay, iMonth, lastspeak_date, eggStr;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }
	
    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {	
        npchar.quest.BadMeeting = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }
    
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}
	
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
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
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("Meu filho","Minha filha")+", infelizmente, não posso te oferecer abrigo. Corra!","A guarda da cidade está vasculhando a cidade à sua procura, "+GetSexPhrase("meu filho","minha filha")+". As portas da minha igreja estão sempre abertas aos que sofrem, mas não posso lhe oferecer abrigo...",""+GetSexPhrase("Meu filho","Minha filha")+", você tem que correr! Não demore, eu te imploro!"),LinkRandPhrase("O que você está fazendo na igreja, alma perdida? Exijo que saia imediatamente, antes que os soldados te encontrem aqui e provoquem um massacre!","Saia do templo neste instante, seu debochado! Eu nunca vou proteger um canalha como você!","Saia do templo do nosso Senhor neste instante! Não precisamos de assassinos aqui!"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Ah, qual é, padre...","Eu não preciso da sua ajuda mesmo..."),LinkRandPhrase("Só não fique no meu caminho, pai...","Eu vou, não se preocupe...","Padre, pare de se preocupar – eu realmente não tenho tempo pra isso"));
				link.l1.go = "fight";
				break;
			} 
            if (npchar.quest.BadMeeting != lastspeak_date)
			{
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && NPChar.location != "LosTeques_church" && rand(5) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // 280313
				{
					dialog.text = "...eles vão queimar no fogo do inferno para sempre! Nunca verão...";
					link.l1 = RandPhraseSimple("Hum! Estou atrapalhando, padre?","Isso sim é que é discurso!");
					link.l1.go = "GenQuest_Church_2_Start_1";
					NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
				{
					Dialog.Text = ""+GetSexPhrase("Meu filho","Minha filha")+", fico feliz em te ver de novo!";
					link.l1 = "E fico feliz em vê-lo com saúde, Padre "+NPChar.name+"...";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
				{
					Dialog.Text = ""+GetSexPhrase("Meu filho","Minha filha")+"! Fico feliz em vê-lo novamente com saúde e bom ânimo. O Senhor deve ter nos ajudado nessa situação, não é?";
					link.l1 = "Sim, "+RandPhraseSimple("padre","santo Padre")+", embora o vento nem sempre estivesse a meu favor, embora eu tenha gasto mais tempo, esforço e dinheiro - sua missão está cumprida.";
					link.l1.go = "GenQuest_Church_1_Complete_1";
					break;
				}
				Dialog.Text = "Bem-vindo ao nosso sagrado lar, "+GetSexPhrase("meu filho","minha filha")+".";
				link.l1 = "Olá, padre santo.";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
				{
					dialog.text = "Saudações, Ellen, minha filha.";
					link.l1 = "E para o senhor também, padre.";
				}
				link.l1.go = "node_3";
				Link.l2 = "Você não é meu pai, e nunca mais fale comigo desse jeito.";
				Link.l2.go = "node_2";
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}
			else
			{
				Dialog.Text = "Saia do templo do Senhor, blasfemo! Não temos nada para discutir!";
				Link.l1 = "Eu nem queria mesmo.";
				Link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "node_2":
			dialog.text = "Ah, seu blasfemo! Vá embora! Não ouse profanar o templo do nosso Senhor com a sua presença!";
			link.l1 = "Eu nem ia ficar aqui.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
			{
				dialog.text = "Fico feliz que, apesar dos seus... envolvimentos com Jan, você não se esqueça do nosso Senhor e de Sua casa. Em que posso ajudar?";
			}
			else
			{
				dialog.text = "Que o Senhor abençoe você e seus negócios... Veio até mim por algum motivo em especial?";
			}
    		link.l1 = RandPhraseSimple("Gostaria de fazer uma doação.","Quero doar para uma boa causa.");
    		link.l1.go = "donation";
    		link.l2 = RandPhraseSimple("Acho que está na hora de uma confissão.","Quero confessar, "+RandPhraseSimple("padre.","santo Padre."));
    		link.l2.go = "ispoved";
    		link.l3 = RandPhraseSimple("Tenho negócios com você, "+RandPhraseSimple("padre.","santo Padre."),"Vim a negócios, "+RandPhraseSimple("padre.","santo Padre."));
    		link.l3.go = "work";
			
			//--> Сага
			// Картахена, Чика Гонсалес
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && pchar.location == "Cartahena_church" && sti(pchar.money) >= 1000)
			{
				link.l4 = "Gostaria de encomendar uma missa para o descanso da alma de uma senhora.";
				link.l4.go = "saga";				
			}
			// поиски исцеления от заклятий
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location != "Bridgetown_church" && !CheckAttribute(npchar, "quest.seektreatment"))
			{ // все церкви, кроме Бриджтауна
				link.l4 = "Padre, eu preciso de ajuda. Estou realmente doente. Alguma maldição pagã terrível caiu sobre mim. Por favor, me ajude, eu imploro!";
				link.l4.go = "seektreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location == "Bridgetown_church")
			{ // попал в Бриджтаун
				link.l4 = "Padre, eu preciso de ajuda. Estou realmente doente. Alguma maldição pagã terrível caiu sobre mim. Por favor, me ajude, eu imploro!";
				link.l4.go = "findtreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessFindTreatment") && pchar.location == "Bridgetown_church")
			{ // пришёл в Бриджтаун по направлению
				link.l4 = "Padre, eu preciso de ajuda. Estou realmente doente. Alguma maldição pagã terrível caiu sobre mim. Disseram que só você pode me ajudar. Eu imploro...";
				link.l4.go = "findtreatment";
			}
			// исцеление от заклятий Джесс
			if(CheckAttribute(pchar, "questTemp.Saga.JessTreatment") && pchar.location == "Bridgetown_church")
			{
				link.l4 = "Padre, eu preciso de ajuda. Estou realmente doente. Alguma maldição pagã terrível caiu sobre mim. Fui enviado até você por... Jessica Rose. Ela disse que você poderia me ajudar.";
				link.l4.go = "treatment";
			}
			if(CheckAttribute(npchar, "quest.candle"))
			{
				link.l4 = "Sobre as velas...";
				link.l4.go = "candle";
			}
			if(CheckAttribute(npchar, "quest.prayer") && GetNpcQuestPastDayParam(npchar, "prayer_date") >= 1 && stf(environment.time) >= 22.0)
			{
				link.l4 = "Estou pronto para rezar, padre.";
				link.l4.go = "prayer";
			}
			//<-- Сага
			
			// Warship, 30.05.11. Миниквест из дел чести "Divine justice".
			if(CheckAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest") && AffairOfHonor_GetCurQuest() == "GodJudgement" &&
				NPChar.city == PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId)
			{
				link.l5 = "Coisas terríveis estão acontecendo, padre.";
				link.l5.go = "AffairOfHonor_GodJudgement_1";
			}
			
			link.l6 = "Com licença, mas eu preciso ir.";
			link.l6.go = "exit";
		break;

		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "Não se preocupe, meu filho. O Senhor vê o seu sofrimento e vai estender a mão para ajudar. Sempre carregue uma cruz com você para fortalecer sua fé.";
			Link.l1 = "Obrigado, santo Padre.";
			Link.l1.go = "exit";
			AddItems(PChar, "amulet_3", 15);
			DeleteAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest");
		break;

// Jason-------------------------------------------------Сага----------------------------------------------
		//--> Чика Гонсалес
		case "saga" :
			dialog.text = "Vou cumprir humildemente sua vontade por 1.000 pesos.";
			Link.l1 = "Aqui está, Padre - por favor, aceite essas moedas.";
			Link.l1.go = "saga_1";
		break;
		
		case "saga_1" :
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Obrigado, meu filho. Qual é o nome da senhora por quem devo rezar?";
			Link.l1 = "O nome dela era Chica Gonzales, e ela deixou este mundo há muitos anos.";
			Link.l1.go = "saga_2";
		break;
		
		case "saga_2" :
			dialog.text = "Que estranho... Aconteceu alguma coisa com o Alvarez, e ele te perguntou sobre isso?";
			Link.l1 = "E quem é esse Alvarez, e o que há de tão estranho no meu pedido?";
			Link.l1.go = "saga_3";
		break;
		
		case "saga_3" :
			dialog.text = "Pois bem, pois bem! Todo mês, Alvarez, que guarda nosso farol há duas décadas, manda celebrar uma missa pela alma dessa senhora. Ninguém além dele jamais se importou com Dona Gonzales. E agora você aparece aqui. Foi o que pensei. Mas, enfim, não é da minha conta. Claro, terei prazer em humildemente atender ao seu pedido para ajudar essa alma errante a encontrar paz e o caminho para o paraíso.";
			Link.l1 = "Obrigado, santo Padre.";
			Link.l1.go = "saga_4";
		break;
		
		case "saga_4" :
			DialogExit();
			if(CheckAttribute(pchar,"questTemp.Saga7"))
			{
				AddQuestRecord("Saga", "151");
				DeleteAttribute(pchar,"questTemp.Saga7");
			}
			else AddQuestRecord("Saga", "15");
			Saga_SetOrtega();
			pchar.questTemp.Saga = "ortega";
			pchar.quest.Saga_Gonsales1.over = "yes"; //снять возможное прерывание
			if (GetCharacterIndex("SagaGonsalesB") != -1)
			{
				sld = characterFromId("SagaGonsalesB");
				sld.lifeday = 0;
			}
		break;
		
		// belamour участвовал в событиях Картахены
		case "saga_5" :
			dialog.text = "Tem mais alguém por quem você gostaria de encomendar um réquiem?";
			Link.l1 = "Mmm... Não, acho que não. Preciso pedir para mais alguém?";
			Link.l1.go = "saga_6";
		break;
		
		case "saga_6" :
			dialog.text = "Bem, talvez pelos centenas de inocentes que caíram pela sua mão ou pelas lâminas dos seus companheiros sem Deus quando vocês saquearam esta cidade infeliz?.. Porém, é improvável que um simples padre consiga tocar a consciência de um homem que matou cidadãos simples e pacíficos sem nenhum remorso...";
			Link.l1 = "Papai, o senhor não entende... Tudo isso ficou no passado. Aqui e agora, não pretendo fazer mal a ninguém.";
			Link.l1.go = "saga_7";
		break;
		
		case "saga_7" :
			pchar.questTemp.saga7 = true;
			dialog.text = "Posso confiar na sua palavra...? Mas, de qualquer forma, este é um solo sagrado que não deve ser manchado de sangue. Então, não vou chamar os guardas. Vá em paz. Talvez, antes de enfrentar o julgamento de Deus, você ainda tenha tempo para se redimir de pelo menos alguns dos seus pecados.";
			Link.l1 = "Talvez. Que seja feita a vontade de Deus.";
			Link.l1.go = "saga_4";
		break;
		// <-- Чика Гонсалес
		
		// --> исцеление от заклятий
		case "treatment":
			dialog.text = "Jessica? Eu me lembro dela. Pobre coitada. Mas ela não morreu?";
			link.l1 = "Ela morreu, padre santo. Agora que ela se foi, que o Senhor descanse sua alma. Mas ela me garantiu que o senhor poderia me ajudar.";
			link.l1.go = "treatment_1";
			DeleteAttribute(pchar, "questTemp.Saga.JessTreatment");
		break;
		
		case "treatment_1":
			dialog.text = "Quem lançou esses feitiços sobre você, meu filho? Fale a verdade.";
			link.l1 = "Ela... ela fez isso. Jessica.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "Deus nos proteja! Foi exatamente o que pensei. Mergulhar em rituais pagãos pode lançar até as almas mais fortes no abismo da escuridão... Mas... ela morreu mesmo? Ou... não completamente?";
			link.l1 = "Você é muito perspicaz, Padre. Agora ela está realmente morta.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			dialog.text = "Essa pobre pecadora se confessou comigo várias vezes. O ódio a consumiu por dentro. Eu sabia o que ela pretendia. Tentei impedi-la, tentei fazê-la seguir o caminho certo, mas todos os meus esforços foram em vão. Avisei sobre o perigo terrível e as consequências graves de seus atos impuros...";
			link.l1 = "Sim, santo Padre. O que vi foi realmente terrível. Mas... como posso ser curado?";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "Pela força da oração, meu filho. Pela força da oração sagrada de purificação em nosso templo. Você terá que rezar por muito tempo, e não só por você mesmo. Vai ter que rezar por ela também.";
			link.l1 = "Para a Jessica?";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "Sim. Por você e pela alma dela. Venha aqui às dez da noite, para que ninguém te distraia. Você terá que rezar a noite inteira. Traga vinte velas grossas de cera, acenda todas e reze até que queimem por completo.";
			link.l1 = "E então eu vou ficar curado?";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "Está tudo nas mãos do Senhor. Vou te ensinar a rezar e deixar as Sagradas Escrituras com você. O poder da oração sagrada vai destruir os feitiços malignos que caíram sobre você, e também purificar a alma da pobre Jessica.";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "Tenho vinte velas de cera comigo. Estou pronto para ficar no templo e começar a rezar.";
				link.l1.go = "treatment_9";
			}
			else
			{
				link.l1 = "Eu ainda não tenho vinte velas comigo. Vou conseguir!";
				link.l1.go = "treatment_7";
			}
		break;
		
		case "treatment_7":
			dialog.text = "Tudo bem, meu filho. Vou te esperar. Não perca tempo!";
			link.l1 = "Eu estarei aqui em breve...";
			link.l1.go = "treatment_8";
		break;
		
		case "treatment_8":
			DialogExit();
			npchar.quest.candle = "true";
		break;
		
		case "candle":
			dialog.text = "Você trouxe vinte velas, meu filho?";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "Sim, Padre. Tenho vinte velas de cera comigo. Estou pronta para ficar no templo e começar a rezar.";
				link.l1.go = "treatment_9";
				DeleteAttribute(npchar, "quest.candle");
			}
			else
			{
				link.l1 = "Ainda não – mas vou conseguir de qualquer jeito.";
				link.l1.go = "exit";
			}
		break;
		
		case "treatment_9":
			dialog.text = "Bem, meu filho. Me entregue-os e volte amanhã depois das dez da noite. Vou te ensinar as orações necessárias e deixar você na igreja durante a noite.";
			link.l1 = "Obrigado, santo Padre. Até amanhã!";
			link.l1.go = "treatment_10";
		break;
		
		case "treatment_10":
			DialogExit();
			RemoveItems(pchar, "mineral3", 20);
			LAi_RemoveLoginTime(npchar);
			LAi_SetLoginTime(npchar, 6.0, 22.99);
			npchar.quest.prayer = "true";
			SaveCurrentNpcQuestDateParam(npchar, "prayer_date");
		break;
		
		case "prayer":
			dialog.text = "I have prepared the texts of the prayers for you , my son. I also left your twenty candles and the Holy Scripture. Light the candles and start praying. Pray without a stop; pray for your recovery and for the soul of this poor sinner Jessica. If you forget something or if you don't understand something - it doesn't really matter. Pray from your heart, your sincere desire is what matters to our Lord.";
			link.l1 = "Obrigado, padre. Entendi.";
			link.l1.go = "prayer_1";
		break;
		
		case "prayer_1":
			dialog.text = "Eu voltarei de manhã. Também vou rezar por você...";
			link.l1 = "Obrigado, santo Padre.";
			link.l1.go = "prayer_2";
		break;
		
		case "prayer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_BarbadosTreatment", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "seektreatment":
			dialog.text = "Que feitiços pagãos te atormentaram, meu filho?";
			link.l1 = "I don't know how they are called. I am weak and sluggish; I cannot run around, and it is very difficult for me to fight.";
			link.l1.go = "seektreatment_1";
		break;
		
		case "seektreatment_1":
			if (sti(pchar.questTemp.Saga.JessSeekTreatment) == 3)
			{
				dialog.text = "Já ouvi falar dessas coisas... Foram trazidas ao nosso mundo pelas bruxas profanas desses pagãos de pele vermelha. Eu aconselharia você a procurar o padre superior da igreja em Bridgetown – ele passou vários anos estudando a influência perniciosa das maldições indígenas sobre os corpos e almas dos cristãos.";
				link.l1 = "E ele seria capaz de me ajudar?!";
				link.l1.go = "seektreatment_4";
			}
			else
			{
				dialog.text = "Já ouvi falar dessas coisas... Foram trazidas ao nosso mundo pelas bruxas profanas desses pagãos de pele vermelha. Infelizmente, o único conselho que posso te dar é passar mais tempo em oração, meu filho, e depositar suas esperanças na misericórdia de nosso Senhor.";
				link.l1 = "Mas será que não há mesmo nada a fazer sobre isso, Padre?! Vou ficar assim... até o fim dos meus dias?";
				link.l1.go = "seektreatment_2";
			}
		break;
		
		case "seektreatment_2":
			dialog.text = "Não desanime, meu filho. O Senhor vai ouvir você e mandará ajuda. Mas eu recomendo que procure em outros lugares sagrados — talvez existam padres que saibam como remover maldições pagãs.";
			link.l1 = "Obrigado, Padre! Eu vou me curar – nem que eu tenha que visitar todas as igrejas do arquipélago!";
			link.l1.go = "seektreatment_3";
		break;
		
		case "seektreatment_3":
			dialog.text = "Vá, meu filho, e que o Senhor cuide de você.";
			link.l1 = "Adeus, padre.";
			link.l1.go = "exit";
			npchar.quest.seektreatment = "true";
			pchar.questTemp.Saga.JessSeekTreatment = sti(pchar.questTemp.Saga.JessSeekTreatment)+1;
		break;
		
		case "seektreatment_4":
			dialog.text = "Só o Senhor pode te ajudar – e você mesmo, meu filho. Um padre só pode te ensinar o que fazer e como. Vá vê-lo.";
			link.l1 = "Obrigado, padre! Você me salvou! Vou zarpar para Barbados imediatamente!";
			link.l1.go = "seektreatment_5";
		break;
		
		case "seektreatment_5":
			dialog.text = "Vá agora, e que o Senhor cuide de você.";
			link.l1 = "Adeus, Padre.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment");
			pchar.questTemp.Saga.JessFindTreatment = "true";
		break;
		
		case "findtreatment":
			dialog.text = "Que maldições pagãs caíram sobre você, meu filho? Deixe-me adivinhar: você não consegue correr, um sabre é pesado demais para você e seus movimentos estão lentos e pesados?";
			link.l1 = "Como o senhor sabia disso, Padre?";
			link.l1.go = "findtreatment_1";
		break;
		
		case "findtreatment_1":
			dialog.text = "Não foi difícil perceber, olhando para o seu jeito de andar quando se aproximou de mim, meu filho. Que o Senhor tenha piedade de nossas almas pecadoras... Diga-me, meu filho, e seja sincero – quem lançou esses encantamentos sobre você?";
			link.l1 = "Precisa de um nome, Padre?";
			link.l1.go = "findtreatment_2";
		break;
		
		case "findtreatment_2":
			dialog.text = "Se você sabe o nome, então diga.";
			link.l1 = "O nome dela era... Jessica Rose.";
			link.l1.go = "findtreatment_3";
		break;
		
		case "findtreatment_3":
			dialog.text = "Deus nos proteja! Mergulhar em rituais pagãos pode lançar até as almas mais fortes no abismo da escuridão... O que aconteceu com ela, com essa pobre alma?";
			link.l1 = "Ela morreu, padre.";
			link.l1.go = "findtreatment_4";
		break;
		
		case "findtreatment_4":
			dialog.text = "Mas... ela morreu mesmo? Ou... não completamente?";
			link.l1 = "Você é extremamente perspicaz, padre. Agora ela está realmente morta.";
			link.l1.go = "treatment_3";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment"); // если было
			DeleteAttribute(pchar, "questTemp.Saga.JessFindTreatment"); // если было
		break;
		//<-- Сага
		
		// Church GenQuest_2 -->	
		case "GenQuest_Church_2_Start_1":
			dialog.text = "...e a misericórdia do Senhor! Que a escuridão universal consuma suas almas por seus pecados...";
			link.l1 = LinkRandPhrase("Santo Padre","Padre","Pai")+", você não acha que está sendo um pouco exagerado? Olha, desse jeito você ainda vai ter um troço...";
			link.l1.go = "GenQuest_Church_2_Start_2";
			link.l2 = "Bem... droga. Então, adeus.";
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_2":
			dialog.text = "Oh, "+GetSexPhrase("meu filho","minha filha")+", terrível sacrilégio, o mais hediondo dos crimes acaba de acontecer! Roubar da igreja!!! É como enfiar a mão no bolso do próprio Senhor!";
			link.l1 = "Ah, entendi... Como isso aconteceu?";
			link.l1.go = "GenQuest_Church_2_Start_3";
			link.l2 = LinkRandPhrase("É muito triste e tudo mais, mas eu realmente preciso ir...","Meus pêsames, padre, mas preciso ir...","Você deve ter confiado demais no Todo-Poderoso. Devia ter usado fechaduras mais seguras. Bem, tenho que ir...");
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_3":
			dialog.text = "Durante a calada da noite, uns canalhas levaram tudo o que a paróquia arrecadou! Esses blasfemos até roubaram o cálice sagrado!";
			link.l1 = "O tempora, o mores... Mas espero que você tenha feito algo enquanto a pista ainda estava quente?";
			link.l1.go = "GenQuest_Church_2_Start_4";
		break;
			
		case "GenQuest_Church_2_Start_4":
			dialog.text = "Mas é claro! Eu excomunguei esses ladrões blasfemos, e agora estou lançando uma anátema sobre eles!";
			link.l1 = "Não tenho dúvidas de que é uma medida bastante eficaz. Mas eu quis dizer algo mais prático. Organizar uma perseguição, por exemplo.";
			link.l1.go = "GenQuest_Church_2_Start_5";
		break;
			
		case "GenQuest_Church_2_Start_5":
			dialog.text = "Ah, o que pode fazer um simples padre, preso ao voto de não resistir ao mal? Esses canalhas certamente já estão longe daqui, gastando o fruto do roubo em tavernas ou se entregando à devassidão e ao vício na companhia de mulheres perdidas! Espero mesmo que encontrem o fim deles por lá!";
			link.l1 = RandPhraseSimple("Tenho certeza de que um fim assim é muito mais atraente do que ser enforcado. Mas não vou tomar mais o seu tempo. Tudo de bom.","Bem, um dia, mais cedo ou mais tarde, todos nós vamos nos juntar aos nossos antepassados, mas eu não diria não para um fim mais rápido para eles. Mas agora preciso ir. Boa sorte.");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Santo Padre","Padre","Pai")+", mas não estou preso a nenhum voto, e com disposição ajudarei o Senhor a trazer o tempo da retribuição.";
			link.l2.go = "GenQuest_Church_2_Start_5_1";
		break;
		
		case "GenQuest_Church_2_Start_5_1": //выше - выход из диалога без подтверждения - странно, однако
			dialog.text = "Vou rezar por você, meu filho! Vá agora e mostre a esses trapaceiros o que eles merecem!";
			link.l1 = "Não tenha dúvida, Padre";
			link.l1.go = "GenQuest_Church_2_Start_6";
		break;
			
		case "GenQuest_Church_2_Start_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_2.StartQuest = true;
			PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City;	// Город, в котором спрашиваем
			PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // На каком острове опрашиваем бандюков
			PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_2.AskPeople = true;
			PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
			PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
			PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank)+8)*543+3210;
			PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount)/3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		break;
			
		case "GenQuest_Church_2_Thief_2":
			dialog.text = "Bem, talvez o Criador todo-bondoso mande peste e fome aos seus filhos tolos para castigá-los por seus pecados...";
				link.l1 = "Por orgulho, por exemplo, ou ganância... Por que ficou pálido, padre?";
				link.l1.go = "GenQuest_Church_2_Thief_3";
			break;
			
		case "GenQuest_Church_2_Thief_3":
			if(rand(1) == 0) // Священник искренне раскаивается...
			{
				dialog.text = "Jesus, meu Senhor, tenha piedade deste servo pecador... Você... Você encontrou os ladrões? Conseguiu derrotá-los?";
					link.l1 = "Vamos recordar os Dez Mandamentos, conhecidos por todo bom cristão desde o berço: não matarás, não roubarás, não levantarás falso testemunho. Pode uma pessoa temente a Deus quebrá-los — e ainda mais, um sacerdote espiritual...?!";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
			}
			else
			{
				dialog.text = " O ar aqui está tão pesado... Então, você encontrou os ladrões? Conseguiu acabar com eles? ";
					link.l1 = "Lembremos dos Dez Mandamentos, conhecidos por todo bom cristão desde o berço: não matarás, não roubarás, não levantarás falso testemunho. Será que uma pessoa temente a Deus pode quebrá-los – e ainda mais, um padre espiritual?!..";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_1_1":
			dialog.text = ""+GetSexPhrase("Meu filho","Minha filha")+"... Deus me perdoe... tanto dinheiro, tanta tentação... o homem é fraco, realmente fraco! Eu não aguentei... perdi o juízo... rezei dia e noite, fiz penitência, jejuei com rigor, mortifiquei minha carne... Indigno, supliquei aos Céus apenas que poupassem aqueles pobres homens que eu havia tentado, movido pela minha própria ganância...";
			link.l1 = LinkRandPhrase("Pai","Padre","Pai")+", calma. Eles não disseram nada sobre isso... e não vão dizer, com certeza. Aliás, devolveram voluntariamente o cálice da Comunhão para mim, que eu trouxe de volta para você.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_2":
			dialog.text = "Meu Senhor, eu Te agradeço! Meu Deus, Tu ouviste as preces do teu servo indigno, um pecador caído mergulhado na sujeira e no vício...";
			link.l1 = "Qualquer um poderia ter cometido um erro... Mas, já que seu arrependimento parece sincero, eu lhe digo: você é um homem decente e um bom padre. Se for julgado, nada de bom sairá disso. Cabe a você decidir se permanece a serviço do Senhor ou não – só Ele pode lhe dizer e lhe guiar...";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_3":
			if(rand(1) == 0) // Священник хочет всучить ГГ бабло
			{
				dialog.text = ""+GetSexPhrase("Meu filho","Minha filha")+"... Com lágrimas de arrependimento e gratidão, aceitarei este cálice de suas mãos. A pureza e nobreza da sua alma realmente me tocaram. Eu te abençoo de todo o coração, e humildemente peço que aceite esta pequena lembrança de "+FindRussianMoneyString(iMoneyToCharacter)+"... Espero que seja suficiente para cobrir suas despesas?";
				// ГГ не берёт деньги. Плюсанем репу
				link.l1 = "Isto não é necessário, Santo Padre "+NPChar.name+". Eu não sou exatamente a pessoa mais pobre, então é melhor você usar esse dinheiro para o bem da sua paróquia.";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				// ГГ берёт деньги
				link.l2 = "Obrigado, "+LinkRandPhrase("Pai","padre","santo Padre")+", isso já é mais do que suficiente.";
				link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
			}
			else
			{
				dialog.text = ""+GetSexPhrase("Meu filho","Minha filha")+"... Com lágrimas de arrependimento e gratidão, aceitarei este cálice de suas mãos como um sinal da misericórdia e do perdão do Senhor. A pureza e a nobreza de sua alma realmente me tocaram. Eu te abençoo de todo o coração!";
				link.l1 = "Obrigado pela bênção, "+LinkRandPhrase("padre.","Pai.")+".";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				link.l1 = "A bênção certamente é necessária, mas não faria mal apoiá-la com algo mais concreto, considerando as despesas consideráveis que tive...";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
			}
			ChurchGenQuest2_RemoveCup();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "Oh, criança, sinto muito de verdade... Espero que esta pequena contribuição de "+FindRussianMoneyString(iMoneyToCharacter)+" será suficiente para cobrir suas despesas?";
			link.l1 = "Sim, "+LinkRandPhrase("padre.","Pai.")+", já chega, obrigado.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_1":
			dialog.text = "Não entendo muito bem as suas insinuações, "+GetSexPhrase("meu filho","minha filha")+", do que você está falando?!";
			link.l1 = "Estou falando das coisas terríveis que a ganância pode fazer com um homem, e que eu ouvi de uns trapos de gente que supostamente roubaram sua igreja... Queria dizer alguma coisa?";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_2":
			dialog.text = "Eu diria, criança, que está falando com um homem da igreja e deveria mostrar um pouco mais de respeito, ou pode acabar se arrependendo. Quanto a este cálice – nunca o vi antes, mas se quiser doá-lo para a paróquia, então...";
			link.l1 = "Calma aí, padre. Você só vai receber quando se explicar.";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_3":
			if(rand(1) == 0) // Просто несколько разные варианты диалога
			{
				dialog.text = "O que há para explicar?! Agora, veja - você é um "+GetSexPhrase("homem esperto","garota esperta")+", e certamente você deve entender que tudo o que esses canalhas possam ter lhe dito – que eu supostamente os contratei – é uma mentira descarada! O Senhor vai punir esses blasfemadores não só pelo sacrilégio, mas também por falso testemunho!";
				link.l1 = "Deixe o Senhor em paz! Como você pode saber o que aquelas pobres almas me disseram – aquelas contra quem você me colocou? Talvez eu as tenha matado antes que tivessem tempo de me contar algo ruim sobre você?";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
			}
			else
			{
				dialog.text = "There's nothing for me to talk about with you! You haven't fulfilled your obligation in the face of our Lord; you're swearing at the temple; you're attempting to blackmail a priest, displaying some church utensils - and it remains yet to be seen how you got it! Thank the God that I am not calling the acolytes to catch you red-handed!";
				link.l1 = "Bem... Vejo que você afundou tanto no pecado que já não teme mais o julgamento dos homens. Mas ainda existe a justiça divina, e todos nós teremos que responder por ela, mais cedo ou mais tarde. Pegue seus 'utensílios da igreja' e reflita se é digno de tocá-los, Padre "+NPChar.name+".";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
				link.l2 = "Perdoe minhas dúvidas, Padre, pois o coração mortal é fraco e a alma se confunde. Por favor, aceite o cálice e me dê sua bênção.";
				link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1":
			dialog.text = "Mmmm... "+GetSexPhrase("Meu filho... Senhor... Senhor...","Minha filha... Senhorita... Senhora...")+" "+PChar.name+"... estou pronto para me curvar diante de você... e discutir nossas desavenças, por assim dizer... e compensar seus gastos com esta quantia modesta de "+FindRussianMoneyString(iMoneyToCharacter)+"... claro, se você não pretende envolver outros nessa história...";
			// При этом варианте репу плюсуем
			link.l1 = "Eu não vou envolver ninguém. Pegue o cálice! E nem pense que eu aceitaria o ouro que você estava furtando às escondidas dos bolsos dos seus paroquianos!";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
			// При этом - минусуем
			link.l2 = "Não vou envolver ninguém. Pegue o cálice! Só aceito este ouro porque já gastei muito tempo e dinheiro com você.";
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1":
			// ничего не принесли священнику.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
			{
				link.l1 = "Más notícias, "+LinkRandPhrase("Pai","Padre","Pai")+": os ladrões foram traiçoeiros e astutos demais, então não consegui recuperar o ouro da igreja...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
				break;
			}
			// Принесли священнику только чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
			{
				link.l1 = "Más notícias, "+LinkRandPhrase("Pai","Padre","Pai")+": Consegui alcançar os ladrões, mas meu único troféu foi este cálice.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Принесли священнику и деньги и чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "Tenho certeza de que vai gostar das novidades – puni devidamente os ladrões e recuperei o dinheiro da paróquia, além deste cálice.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Pai","Padre","Pai")+", eu trouxe más notícias... Precisei gastar muito tempo, esforço e recursos para caçar aqueles canalhas, mas quando os encontrei, descobri que eles tinham bebido e esbanjado tudo, menos este cálice...";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Священник - вор.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
			{
				dialog.text = "Oh, "+GetSexPhrase("meu filho","minha filha")+", o que poderia ter acontecido comigo? É o seu caminho que está cheio de perigos e ansiedade, enquanto minha cela tranquila, um domínio de reflexão e oração, é uma ilha serena em um oceano tempestuoso de paixões humanas...";
					link.l1 = "E nada pode perturbar a serenidade da sua solitária felicidade?";
					link.l1.go = "GenQuest_Church_2_Thief_2";
				break;
			}
			// Короткий вариант прохождения квеста.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "Tenho certeza de que essa notícia vai te alegrar – eu puni os ladrões e recuperei o dinheiro da paróquia.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Pai","Padre","Pai")+"... tenho que te decepcionar. Passei o arquipélago todo atrás dos ladrões, enfrentei inúmeros perigos e obstáculos, quase me arruinei, e no fim os alcancei, mas infelizmente... eles já tinham gasto todo o dinheiro da igreja.";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1": // ГГ решил заныкать деньги...
			if(rand(1) == 0)	// Священник верит ГГ но не даёт денег...
			{
				if(rand(4) == 3) // Более "мягкий" исход событий.
				{
					dialog.text = "Oh, "+GetSexPhrase("meu filho","minha filha")+". Suas palavras me mergulharam em profunda tristeza - mas não em desespero, pois o desespero é um pecado mortal! O Senhor nos enviou mais uma provação para fortalecer nossa fé.";
						link.l1 = "Amém, Padre...";
						link.l1.go = "exit";
						sQuestTitle = NPChar.City + "ChurchGenQuest2";
						AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
						AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
						CloseQuestHeader(sQuestTitle);
						ChangeCharacterComplexReputation(PChar,"nobility", -2);
						DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
						NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
				}
				else
				{
					dialog.text = ""+GetSexPhrase("Meu filho","Minha filha")+", não minta para o seu pastor espiritual.";
						link.l1 = "Me desculpe de verdade, Padre, mas juro que estou dizendo a verdade.";
						link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
				}
			}
			else
			{
				// Священник даёт деньги ГГ...
				iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
				dialog.text = "Oh, "+GetSexPhrase("meu filho","minha filha")+". Suas palavras me mergulharam em profunda tristeza - mas não em desespero, pois o desespero é um pecado mortal! O Senhor nos impôs mais uma provação para fortalecer nossa fé. Mas seus esforços e despesas precisam ser recompensados, mesmo que tenham sido em vão. Por favor, aceite esta quantia modesta - "+FindRussianMoneyString(iMoneyToCharacter)+" - e continue no seu caminho justo!";
					link.l1 = "Hmm!... Obrigado, padre, vou usar esse dinheiro para uma causa virtuosa.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
					link.l2 = LinkRandPhrase("Pai","Padre","Pai")+"... Eu não posso aceitar uma recompensa por um trabalho que não fiz. É melhor usar esse dinheiro para restaurar o altar.";
					link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
			if(rand(6) == 3)
			{
				dialog.text = "Certo, eu acredito em você, "+GetSexPhrase("meu filho","minha filha")+". O Senhor nos enviou mais uma provação para fortalecer nossa fé.";
				link.l1 = "Amém...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1"
				break;
			}
				dialog.text = "Desprezível! Você realmente achou que poderia enganar nosso Senhor?! Maldição sobre você"+GetSexPhrase(", canalha",", vadia")+"! Saia daqui, e lembre-se de que esse dinheiro não vai te trazer nenhum benefício!";
				link.l1 = "Como assim?! Padre!..";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			ChangeCharacterComplexReputation(PChar,"nobility", -3);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			ChangeCharacterComplexReputation(PChar, "nobility", -6);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddCharacterExpToSkill(PChar, "Fortune", -70);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			npchar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1":
			if(rand(1) == 0) // Поверил.
			{
				dialog.text = "Oh, "+GetSexPhrase("meu filho","minha filha")+". Suas palavras me mergulharam em profunda tristeza – mas não em desespero, pois o desespero é um pecado mortal! O Senhor colocou mais uma provação diante de nós para fortalecer nossa fé.";
				link.l1 = "Amém, Padre...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // Переход сюда, т.к. одно и тоже.
			}
			else
			{
				dialog.text = "Sim, é exatamente aquele cálice que foi roubado junto com o dinheiro... Mas... Se você está com ele, por que não trouxe o dinheiro de volta? Era uma quantia considerável, e com certeza aqueles canalhas não teriam gastado tudo tão rápido... "+GetSexPhrase("Meu filho","Minha filha")+", lembre-se de que não há pecado maior do que mentir para o seu pastor espiritual e dar falso testemunho no templo diante de Deus!";
				link.l1 = "Santo Padre "+NPChar.name+", eu quase perdi a vida para conseguir este vaso, só para te fazer feliz. Nem vou mencionar quanto dinheiro gastei com tudo isso!";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
			}
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
			dialog.text = "Saia daqui e agradeça ao Todo-Poderoso, que me deu um coração manso. É só por isso que você ainda não foi marcado como ladrão e canalha!";
			link.l1 = "Como assim?! "+LinkRandPhrase("Santo Padre","Padre","Pai")+"!..";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -5);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, iMoneyToCharacter);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -1);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_1":
			dialog.text = "Oh, "+GetSexPhrase("meu filho","minha filha")+". Suas palavras me mergulharam em profunda tristeza - mas não em desespero, pois o desespero é um pecado mortal! O Senhor colocou mais uma provação diante de nós para fortalecer nossa fé.";
			link.l1 = "Amém, Padre...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_1":
			dialog.text = "Senhor, eu Te agradeço! De fato, você foi o instrumento Dele, meu filho! Eu sabia que nosso Pai Celestial iria te mostrar o caminho e te dar toda a ajuda que precisasse. Eu estava orando sem parar, e...";
			link.l1 = "Sabe, padre, em situações como essa, armas certamente são mais úteis do que orações. Mas, pelo visto, suas preces foram mesmo ouvidas.";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_2":
			dialog.text = ""+GetSexPhrase("Meu filho","Minha filha")+", quero te recompensar como merece, você"+GetSexPhrase(", como um verdadeiro cavaleiro da Santa Igreja,","")+" fiz tudo ao meu alcance para supera...";
			link.l1 = "Padre, o senhor realmente está exagerando meus humildes feitos. Agora vou deixá-lo para louvar nosso Senhor...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
		// <-- квесты церкви

		case "donation":
			dialog.Text = "Claro, "+GetSexPhrase("meu filho","minha filha")+". Quanto você gostaria de doar para a Santa Igreja?";
			Link.l1 = "Me desculpe, padre, mas mudei de ideia.";
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = "Minha doação será modesta – apenas 100 pesos.";
				Link.l2.go = "donation paid_100";
			}
			if(makeint(PChar.money)>=1000)
			{
				Link.l3 = "1000 pesos. Acho que isso deve ser suficiente.";
				Link.l3.go = "donation paid_1000";
			}
			if(makeint(PChar.money)>=5000)
			{
				Link.l4 = "Tenho sorte com dinheiro, então vou doar 5.000 pesos.";
				Link.l4.go = "donation paid_5000";
			}
			//-->> квест пожертвования хозяйки борделя
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = "Padre, quero fazer uma doação, mas não em meu nome. Estou fazendo isso a pedido de outra pessoa.";
				Link.l5.go = "HostessChurch";
			}
			//<<-- квест пожертвования хозяйки борделя
		break;

		case "No donation":
			dialog.Text = "Hum... Bem, essa é a sua decisão, e você é livre para mudar de ideia. E não se esqueça de que isso será levado em conta no Dia do Julgamento.";
			Link.l1 = "Assim como muitas outras coisas também vão mudar. Vamos mudar de assunto.";
			Link.l1.go = "node_3";
			Link.l2 = "Me desculpe, pai, mas chegou a hora de eu partir.";
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = "Em nome da Santa Igreja, eu lhe agradeço, "+GetSexPhrase("meu filho","minha filha")+", pelo seu presente.";
			Link.l1 = "Preciso falar com o senhor, Padre.";
			Link.l1.go = "node_3";
			Link.l2 = "Me desculpe, pai, mas chegou a hora de eu partir.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = "Em nome da Santa Igreja, eu lhe agradeço.";
            Link.l1 = "Preciso falar com o senhor, Padre.";
			Link.l1.go = "node_3";
			Link.l2 = "Me desculpe, pai, mas chegou a hora de eu partir.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = "Em nome da Santa Igreja, agradeço pelo seu presente.";
            Link.l1 = "Preciso falar com você, Padre.";
			Link.l1.go = "node_3";
			Link.l2 = "Me desculpe, pai, mas chegou a hora de eu partir.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = "Claro, "+GetSexPhrase("meu filho","minha filha")+", estou ouvindo você.";
			link.l1 = "Mudei de ideia. Talvez na próxima.";
			link.l1.go = "exit";
			link.l2 = "Estou tão cheio de pecados, Padre. Um dia não seria suficiente para listar todas as minhas faltas...";
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = "Todos nós somos pecadores, meu filho...";
			link.l1 = "Sim, mas em minha consciência, o peso de milhares de mortes é um fardo pesado. Roubei e afundei navios...";
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = "Espero que não houvesse ninguém entre aqueles que navegaram sob a bandeira de "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Não, claro que não, Padre.";
			link.l1.go = "ispoved_3";
			link.l2 = "De todo tipo, Padre...";
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = "Então nosso Senhor irá absolvê-lo desses pecados. Porque esta é uma época cruel, e ao destruir os inimigos do seu soberano, você está salvando a vida de seus súditos leais.";
			link.l1 = "Obrigado, padre, isso foi um grande alívio... Vou indo agora.";
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = "O Senhor não vai te absolver de um pecado desses! Reze e se arrependa, se arrependa e reze! Só tem um caminho pra você agora – o convento!";
			link.l1 = "O convento vai ter que esperar. Pelo menos, não nesta vida. Adeus...";
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
        	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
        	{
        		dialog.text = "Me desculpe, "+GetSexPhrase("meu filho","minha filha")+", mas todos os confessionários estão ocupados no momento. Poderei ouvir sua confissão em meia hora, no mínimo.";
				link.l1 = "Com licença, "+RandPhraseSimple("padre","Pai")+", isso é outra história. Padre "+PChar.GenQuest.ChurchQuest_1.PriestName+", de "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+", certa vez confiou a você tesouros inestimáveis da biblioteca teológica. Ele me pediu para devolvê-los.";
				link.l1.go = "GenQuest_Church_1_Dialog_1";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
				break;
        	}
			dialog.text = "Que tipo de negócio traz você aqui, "+GetSexPhrase("meu filho","minha filha")+"?";
			link.l1 = "Quero te fazer uma pergunta, Padre...";
			link.l1.go = "quests"; // ссылка к НПС
            link.l2 = RandPhraseSimple("Queria falar sobre trabalhar pelo bem da Igreja de "+NationNameGenitive(sti(NPChar.nation))+".","Como estão as coisas na paróquia? Precisa de alguma ajuda?");
			link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
	            link.l3 = RandPhraseSimple("Padre","Pai")+", quero conversar com você sobre questões financeiras."; //(пересылка в кредиты)
	            link.l3.go = "LoanForAll";
            }
			// -->
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = "Preciso de cuidados.";
                link.l4.go = "healthAdd_1";
            }
            
			//квест мэра - на связь с нашим шпионом
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
	            link.l7 = RandPhraseSimple("Padre","Santo Padre")+", estou aqui a pedido de um homem. O nome dele é Governador "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".";
	            link.l7.go = "IntelligenceForAll";
            }
			//--> Jason Церковная депеша
			if (CheckAttribute(pchar, "GenQuest.Monkletter") && npchar.city == pchar.GenQuest.Monkletter.City)
			{
	            link.l10 = "Padre, trouxe para o senhor documentos de um monge da cidade de "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity)+".";
	            link.l10.go = "Monkletter";
            }
			//<-- Церковная депеша
			//--> Jason Доставка молитвенников
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "go" && sti(npchar.nation) == sti(pchar.GenQuest.Churchbooks.Nation) && npchar.city != pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "Padre, eu vim da colônia de "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity)+". A igreja local precisa de mais livros de oração, e o monge sugeriu procurar você sobre isso.";
	            link.l11.go = "Churchbooks";
            }
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "return" && npchar.city == pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "Padre, trouxe os livros de oração para a sua paróquia.";
	            link.l11.go = "Churchbooks_2";
            }
			//<-- Доставка молитвенников
			link.l99 = "Mudei de ideia, tenho muito o que fazer.";
			link.l99.go = "exit";
		break;

		case "prihod":
			if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
		    {
		        dialog.text = "Que ótimo. E mesmo assim, nestes tempos sombrios, "+GetSexPhrase("meu filho","minha filha")+", nem todo visitante do templo pode ser útil para a nossa Santa Igreja.";
				link.l1 = LinkRandPhrase("Pai","Padre","Pai")+", sou um verdadeiro cristão, e minhas intenções de servir nossa Santa Madre Igreja são as mais sinceras."+GetSexPhrase(" Quem vai apoiá-la, se não seu fiel cavaleiro, como eu?","")+"";
				link.l1.go = "GenQuest_Church_1_Start_1";
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
		    }
			else
			{
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}	
            dialog.text = "Até agora tudo está tranquilo na paróquia, "+GetSexPhrase("meu filho","minha filha")+". Obrigado pela oferta.";
    		link.l2 = "Bem, se está tudo certo, acho que vou cuidar dos meus afazeres.";
    		link.l2.go = "exit";
			DeleteAttribute(npchar, "quest.add");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
		break;
		
		// Church GenQuest_1 -->
		case "GenQuest_Church_1_Start_1":
			dialog.text = "Bem, eu tenho uma missão delicada, que exige não só pureza de intenção, mas também muita coragem e bastante discrição...";
			link.l1 = LinkRandPhrase("Pai","Padre","Pai")+", ficarei feliz em lhe prestar qualquer serviço, mesmo que para isso eu tenha que ir direto para o inferno! Que Deus me perdoe por essas palavras profanas.";
			link.l1.go = "GenQuest_Church_1_Start_2";
		break;
			
		case "GenQuest_Church_1_Start_2":
			PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
			Church_GenQuest1_InitStartParam(NPChar);
			dialog.text = "Oh! Que bom... Mas, de novo, isso é um assunto muito delicado... Há algum tempo, o padre superior "+PChar.GenQuest.ChurchQuest_1.ToName+" de "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Gen")+" em "+XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland+"Voc")+"pegou emprestado alguns tratados teológicos e manuscritos antigos da biblioteca da igreja para mim por um tempo. Como o pedido veio acompanhado da insistência do arcebispo para não impedir a bela luz do conhecimento de se espalhar, não pude recusar, mesmo presumindo que as dificuldades das viagens pelo mar não permitiriam que ele devolvesse os manuscritos no prazo... Você poderia me ajudar a resolver esse problema?";
			link.l1 = "Tenho medo, "+LinkRandPhrase("Pai","padre","santo Padre")+", não vou poder fazer isso por você. Este é um assunto muito delicado, e só um verdadeiro diplomata conseguiria resolvê-lo.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Pai","Padre","Pai")+", sua missão não me parece tão complicada. Vou pra lá imediatamente.";
			link.l2.go = "GenQuest_Church_1_Start_3";
		break;
			
		case "GenQuest_Church_1_Start_3":	// Квест взят
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.StartQuest = true;
			PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_1.AskOwner = true;
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
		break;
			
		case "GenQuest_Church_1_Dialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene"))	// Сцена 2а
			{
				dialog.text = "Oh! Sim... De fato, agora me lembro... Mas, "+GetSexPhrase("meu filho","minha filha")+", esses tesouros são mais espirituais do que materiais! Eles já ajudaram muito meus paroquianos e podem fazer isso novamente no futuro!";
				link.l1 = "Mas, "+LinkRandPhrase("Pai","Padre","Pai")+", os paroquianos do Padre "+PChar.GenQuest.ChurchQuest_1.PriestName+" também precisa de salvação, e sem essas obras, ele ficará sem o apoio dos pilares da teologia, e seus sermões carecerão de inspiração.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_1";
			}
			else	// Сцена 2б-а и 2б-б
			{
				dialog.text = "Oh, sim!.. De fato... "+GetSexPhrase("Meu filho","Minha filha")+", esses tesouros são mais espirituais do que materiais! Eles já ajudaram muito meus paroquianos, então, para minha vergonha, eu 'esqueci' de devolvê-los ao verdadeiro dono...";
				link.l1 = "De fato, "+RandPhraseSimple("Pai","Padre","Pai")+", de fato. Por isso o Padre "+PChar.GenQuest.ChurchQuest_1.PriestName+" pediu que eu entregasse estes livros a ele pessoalmente.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_1": // Сцена 2а
			dialog.text = "Eu entendo, meu filho, mas não rezamos todos os dias ao nosso Senhor: 'perdoai as nossas ofensas, assim como nós perdoamos a quem nos tem ofendido'? E a igreja de "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" mais rico do que a minha modesta paróquia.";
			link.l1 = "Com certeza o senhor está certo, padre, mas acabei de lembrar de outro trecho das Escrituras Sagradas: 'Não busque o caminho fácil, pois é lá que o Diabo nos espera, e sua voz é ainda mais sutil e a tentação ainda mais forte, quanto mais fácil for o caminho!' E padre "+PChar.GenQuest.ChurchQuest_1.PriestName+" estava prestes a enviar uma mensagem ao arcebispo sobre o seu esquecimento – só consegui convencê-lo a desistir por pouco.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_1":
			dialog.text = "P-P-Pra o a-arcebispo?! Por uma coisa tão trivial assim!.. Por quê? Sério? Eu já ia mandar esses trabalhos pro meu querido irmão em Cristo de qualquer jeito – só não tinha surgido uma boa oportunidade pra entregar pra ele. Mas em você, "+GetSexPhrase("meu filho","minha filha")+", vejo um verdadeiro servo digno de nosso Senhor. Aqui - leve estes livros e manuscritos e, por favor, entregue-os ao Padre "+PChar.GenQuest.ChurchQuest_1.PriestName+" são e salvo. E a isso, acrescento minha mais sincera gratidão.";
			link.l1 = "Claro, "+LinkRandPhrase("Pai","Padre","Pai")+". Claro...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			// Предмет "рукопись" -->
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			// <-- Предмет "рукопись"
		break;
			
		case "GenQuest_Church_1_Dialog_1_2":	// Сцена 2б-а и 2б-б
			// Генерим кэпа -->
			sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "mercen_" + (rand(14)+14), "man", "man", 15, NPChar.nation, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 40, 35, "blade_13", "pistol3", "grapeshot", 30);
			FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS16, 75, 70, 65);
			sld.Abordage.Enable = false;
			sld.ShipEnemyDisable  = true; // флаг не обижаться на выстрелы
			LAi_SetImmortal(sld, true);
			sld.Dialog.FileName = "GenQuests_Dialog.c";
			sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
			Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetType("ChurchGenQuest1_CapGroup", "trade");
			Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetTaskNone("ChurchGenQuest1_CapGroup");
			Group_LockTask("ChurchGenQuest1_CapGroup");
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
			PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
			PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
			PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			// <-- Генерим кэпа
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // Сцена 2б-а
			{
				dialog.text = "Mas, "+GetSexPhrase("meu filho","minha filha")+"... Veja, é que na semana passada eu conheci o capitão do navio '"+sld.Ship.Name+"', onde fui chamado para administrar a comunhão a um marinheiro moribundo. Para minha grande alegria, capitão "+GetFullName(sld)+" me disse que ele ia "+XI_ConvertString("Colony"+GetColonyExpect2Colonies(NPChar.city,PChar.GenQuest.ChurchQuest_1.QuestTown))+". E embora ele não merecesse nenhum acordo, ainda assim concordou em ajudar e me garantiu que o porto de "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" ele certamente vai visitar. Então aproveitei essa oportunidade, mandei os livros embora com aquele homem bondoso e confiei o destino deles ao Senhor.";
				link.l1 = "Hum, você tem certeza de que esse capitão é confiável? Ele entende o valor das obras que foram confiadas a ele e a importância dessa missão?";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
			}
			else // Сцена 2б-б
			{
				dialog.text = "Oh, "+GetSexPhrase("meu filho","minha filha")+"! Você chegou várias horas atrasado! Eu já enviei os livros do papai "+PChar.GenQuest.ChurchQuest_1.PriestName+" com o capitão "+PChar.GenQuest.ChurchQuest_1.CapFullName+". Hoje de manhã, aquele homem temente a Deus veio se confessar e comentou que hoje o navio dele ia partir para "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.CapColony)+". E embora o capitão não merecesse nenhum acordo, ele ainda assim concordou em ajudar e me garantiu que o porto de "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" com certeza ele vai visitar.";
				link.l1 = LinkRandPhrase("Pai","Padre","Pai")+"... tem certeza de que esse capitão é confiável? E também quero saber o nome do navio dele.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1":	// 2б-а
			dialog.text = "Eu confio nas pessoas, "+GetSexPhrase("meu filho","minha filha")+", cada um de nós foi criado à imagem e semelhança do nosso Senhor, e o Seu fogo sagrado arde em cada alma!";
			link.l1 = "Ugh. Esse é um argumento de peso, sem dúvida. Bem... Então me abençoe, Padre, e deseje-me sorte na minha busca por esse capitão.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // Полная инфа о кэпе
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_1":
			dialog.text = "Você deveria confiar nas pessoas, "+GetSexPhrase("meu filho","minha filha")+". Quanto ao navio dele, não tenho nada a dizer.";
			link.l1 = "E você entregou manuscritos valiosos para algum capitão sem nem se preocupar em saber o nome do navio dele?!!";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_2":
			dialog.text = "Veja, "+GetSexPhrase("meu filho","minha filha")+", capitão "+PChar.GenQuest.ChurchQuest_1.CapFullName+" é muito temente a Deus...";
			link.l1 = "Bem, eu já ouvi isso.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_3":
			dialog.text = "Paciência, "+GetSexPhrase("rapaz","moça")+"! Capitão "+PChar.GenQuest.ChurchQuest_1.CapFullName+" é uma pessoa muito temente a Deus, e até hoje seu navio tinha um nome que nenhum clérigo deveria jamais pronunciar, nem mesmo em pensamento, muito menos em voz alta! E hoje, durante sua confissão, eu apontei isso para ele. Pois, como diz a Bíblia, a pureza da alma deve ser preservada por nós pecadores ainda mais do que a pureza do corpo, pois nosso Senhor nega Seu Reino aos de boca suja...";
			link.l1 = "Entendi. "+LinkRandPhrase("Pai","Padre","Pai")+", entendi! "+PChar.GenQuest.ChurchQuest_1.CapFullName+", um notório jogador e bêbado, famoso em todo o Caribe, decidiu renomear sua velha embarcação por sua sugestão?";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_4":
			dialog.text = "Você é bem perspicaz, "+GetSexPhrase("meu filho","minha filha")+". Não sei o novo nome desse navio, mas tenho certeza de que é algo grandioso.";
			link.l1 = "Oh, "+RandPhraseSimple("Pai","Padre","Pai")+"... Obrigado por tudo. E reze pela minha alma pecadora...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
		break;
			
		case "GenQuest_Church_1_Complete_1":
			dialog.text = "Oh, meu filho! Tenho rezado com fervor, e tudo parece ter se resolvido da melhor forma possível! Pela sua ajuda e fé, "+GetSexPhrase("meu filho","minha filha")+", o paraíso e cânticos angelicais certamente estarão esperando por...";
			link.l1 = RandPhraseSimple("Padre.","Pai.")+", não pretendo encontrar São Pedro tão cedo, Deus me livre. Quanto aos vivos – eles precisam de muitas coisas materiais além de promessas de felicidade celestial...";
			link.l1.go = "GenQuest_Church_1_Complete_2";
		break;
			
		case "GenQuest_Church_1_Complete_2":
			dialog.text = "Sim, sim, "+GetSexPhrase("meu filho","minha filha")+", é claro. Vou recompensá-lo como merece. Aqui, pegue isto e lembre-se de que nosso Senhor castiga as almas tolas que desejam demais as bênçãos terrenas e adoram o demônio dourado!";
			link.l1 = "Obrigado, "+LinkRandPhrase("Pai","Padre","santo Padre")+". Por favor, leve seus tão aguardados livros e manuscritos e reze pela minha alma pecadora... Adeus!";
			link.l1.go = "GenQuest_Church_1_Complete_3";
		break;
			
		case "GenQuest_Church_1_Complete_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			RemoveItems(PChar, "Bible", 1);
			items[FindItem("Bible")].Name = "itmname_bible";
			BackItemDescribe("Bible");
			DeleteAttribute(items[FindItem("Bible")], "City");
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddCharacterExpToSkill(PChar, "Leadership", 50); // Бонус в авторитет
			AddCharacterExpToSkill(PChar, "Fortune", 50); // Бонус в удачу
			TakeNItems(pchar, "chest", 3+hrand(1));
			PlaySound("interface\important_item.wav");
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
			Group_DeleteGroup("ChurchGenQuest1_CapGroup"); // Трем кэпа
			PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; // Завершаем, если вдруг осталось
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
			break;
		// <-- Church GenQuest_1

        case "healthAdd_1":
            if (stf(pchar.Health.maxHP) == 60.0) // отлично
            {
                dialog.text = "Sua saúde está "+GetHealthNameMaxSmall(pchar)+", e as feridas vão cicatrizar sozinhas. Você só precisa evitar derramamento de sangue e cuidar da sua saúde.";
    			link.l1 = "Obrigado, isso com certeza é um alívio. Vou tentar me controlar e evitar brigas por um tempo.";
    			link.l1.go = "exit";
            }
            else
            {
    			dialog.text = "Sua saúde está "+GetHealthNameMaxSmall(pchar)+", e embora os ferimentos se curem sozinhos, você deveria cuidar disso.";
    			link.l1 = "O que é necessário para isso?";
    			link.l1.go = "healthAdd_2";
			}
			link.l2 = "E por que minha saúde está piorando?";
    		link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = "Isso é muito simples, "+GetSexPhrase("meu filho","minha filha")+". Você sofre dano cada vez que é ferido. Isso não passa despercebido. Sua saúde piora a cada ferimento e, como resultado, você fica mais fraco. Sua tripulação, ao ver o capitão enfraquecido, perde o respeito por você. No entanto, você se torna mais cauteloso e sua capacidade de se defender aumenta temporariamente. Descansar e evitar ferimentos vai te ajudar a permanecer forte.";
			link.l1 = "Obrigado pelo esclarecimento.";
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = "Oração e abstinência de violência, "+GetSexPhrase("meu filho","minha filha")+". Então o Senhor lhe devolverá o que você perdeu.";
			link.l1 = "Mas você poderia rezar por mim?";
			link.l1.go = "healthAdd_3";
			link.l2 = "Então não tem jeito? Hmm... Você realmente me tranquilizou, obrigado.";
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
            if (npchar.quest.HealthMonth != iMonth)
            {
    			dialog.text = "Eu? Isso é certamente possível. Mas você vai precisar fazer uma doação para a nossa paróquia.";
    			link.l1 = pcharrepphrase("Quanto?","Com prazer! Quanto?");
    			link.l1.go = "healthAdd_4";
    			link.l2 = "Acho que vou me virar sozinho...";
    			link.l2.go = "exit";
			}
			else
			{
                dialog.text = ""+GetSexPhrase("Meu filho","Minha filha")+", já estou rezando pelo seu bem-estar. Essas orações vão ocupar todo o meu tempo até o fim do mês.";
    			link.l1 = "Obrigado, "+RandPhraseSimple("padre.","Santo Padre.");
    			link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = "Cem mil pesos serão um pagamento suficiente pelo milagre da cura.";
			link.l1 = pcharrepphrase("O quê?!! Você ficou maluco? Eu só pagaria uma quantia dessas depois de roubar umas duas igrejas!","Isso é demais para mim. Dizem que é verdade – saúde não se compra com dinheiro.");
			link.l1.go = "exit";
            if (sti(pchar.Money) >= 100000)
            {
    			link.l2 = "Eu concordo!";
    			link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
            AddMoneyToCharacter(pchar, -100000);
            AddCharacterMaxHealth(pchar, 4); // можно не проверять, тк явно меньше 51
            npchar.quest.HealthMonth = iMonth;
			dialog.text = "Certo. Sua saúde vai melhorar um pouco. Mas você ainda precisa evitar confusões e se cuidar bem, senão esse efeito vai passar. Vou precisar passar um mês inteiro em oração pelo seu corpo mortal.";
			link.l1 = "Obrigado. Se acontecer alguma coisa, volto a te procurar daqui a um mês.";
			link.l1.go = "exit";
		break;
		
		//квест пожертвования хозяйки борделя
		case "HostessChurch":
			dialog.text = "E quem é essa alma caridosa que está doando o dinheiro?";
			link.l1 = "Hmm... Aquela é a dona do bordel local.";
			link.l1.go = "HostessChurch_call";
			link.l2 = "Eu prefiro manter os nomes em segredo. Pode ser uma doação anônima, certo?";
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return"; //флаг на возвращение
		break;
		
		case "HostessChurch_call":
			if (isBadReputation(pchar, 5)) 
			{
				if (rand(100) < GetCharacterSkill(pchar, "Fortune")) //рендом вешаем на удачу
				{
					dialog.text = "You are a sinner, yet you ask for a sinner? You'd better think about your soul first; in fact, all of us will appear before the Lord!";
					link.l1 = "É verdade. Espero que nosso Senhor tenha misericórdia de mim... Então, e quanto à doação?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Afasta-te de mim, Satanás!!! Leva teu dinheiro profano e sai daqui!";
					link.l1 = "Como assim, Padre?! Viemos até o senhor de coração aberto, e o senhor...";
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) //рендом вешаем на харизму
				{
					dialog.text = "Fico feliz que você esteja ajudando os pecadores a encontrar o caminho para o nosso Senhor. Por isso, você receberá sua recompensa no Céu!";
					link.l1 = "Seria ótimo! Então, e quanto à doação?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Não posso aceitar dinheiro obtido pelo pecado. Devolva-o àquela mulher caída, "+GetSexPhrase("meu filho","minha filha")+". Ninguém encontra o caminho para Deus através do dinheiro.";
					link.l1 = "É uma pena que você esteja rejeitando ela. Uma pena mesmo.";
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		
		case "HostessChurch_notCall":
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				dialog.text = "Pegar esse dinheiro, sem nem saber de onde veio...";
				link.l1 = "Sim, padre, exatamente. Por favor, aceite esta contribuição, dada de coração!";
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = "Pegar esse dinheiro, sem nem saber de onde veio? Você tá maluco?! E se esse dinheiro estiver manchado de sangue!";
				link.l1 = "Papai, todo dinheiro carrega sangue...";
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = "Eu aceito. "+GetSexPhrase("meu filho","minha filha")+". Vai e conta isso para a sua mulher caída.";
			link.l1 = "Certo, padre. Obrigado.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_ok_1":
			dialog.text = "Eu aceito. "+GetSexPhrase("meu filho","minha filha")+". Conte isso ao seu benfeitor.";
			link.l1 = "Certo, padre. Obrigado.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_bad":
			dialog.text = "Fora daqui, criatura do inferno, e nem pense em aparecer aqui de novo!";
			link.l1 = "Heh, como quiser.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_1":
			dialog.text = "Esta é a minha decisão. Vá em paz, "+GetSexPhrase("meu filho","minha filha")+".";
			link.l1 = "Adeus, padre.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_2":
			dialog.text = "É isso que você pensa, blasfemo?! Saia do templo agora mesmo e não ouse aparecer aqui de novo!";
			link.l1 = "Ah, é mesmo? Deixa pra lá, estou indo embora...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;

		//--> Jason Церковная депеша
		case "Monkletter":
			if (CheckAttribute(pchar, "GenQuest.Monkletter.Late"))
			{
				dialog.text = "Eu quase tinha perdido a esperança de ver esses papéis de novo. Por que demorou tanto, meu filho?";
				link.l1 = "Foram... acontecimentos inesperados, Padre.";
				link.l1.go = "Monkletter_1";
			}
			else
			{
				dialog.text = "Eu estava esperando por esses documentos, filho. Obrigado pela entrega rápida. Aceite essas moedas e vá com a minha bênção.";
				link.l1 = "Obrigado, Padre. Foi um prazer ajudar a Santa Igreja!";
				link.l1.go = "Monkletter_3";
			}
		break;
		
		case "Monkletter_1":
			dialog.text = "Estamos todos nas mãos de Deus, meu filho... O homem propõe, mas Deus dispõe. Me passe esses papéis e vá em paz.";
			link.l1 = "Aqui está, padre. Tudo de bom para o senhor!";
			link.l1.go = "Monkletter_2";
		break;
		
		case "Monkletter_2":
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "2");
			CloseQuestHeader("Monkletter");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter_3":
			dialog.text = "Que Deus te abençoe, meu filho. Que o Todo-Poderoso te proteja nas suas viagens!";
			link.l1 = "Adeus, Padre.";
			link.l1.go = "Monkletter_4";
		break;
		
		case "Monkletter_4":
			pchar.quest.Monkletter_Over.over = "yes"; //снять таймер
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "3");
			CloseQuestHeader("Monkletter");
			TakeNItems(pchar, "gold_dublon", 10+rand(5));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
			addLiberMisBonus();
		break;
		//<-- Церковная депеша
		
		//--> Jason Доставить молитвенники
		case "Churchbooks":
			dialog.text = "Você foi enviado para pegar nossos livros de oração — para a igreja de "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity+"Gen")+"? Bem. Tenho um pacote com trinta livros de oração. Pegue, meu filho.";
			link.l1 = "Obrigado, padre. Adeus!";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			dialog.text = "Que o Senhor te proteja nas suas viagens! Vá em paz...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Churchbooks", "2");
			pchar.GenQuest.Churchbooks = "return";
			GiveItem2Character(pchar, "prayer_book");//поставить соотв.предмет
		break;
		
		case "Churchbooks_2":
			if (CheckAttribute(pchar, "GenQuest.Churchbooks.Late"))
			{
				dialog.text = "Obrigado pela sua ajuda, meu filho, embora tenha chegado com algum atraso.";
				link.l1 = "Fui atrasado por acontecimentos inesperados, Padre.";
				link.l1.go = "Churchbooks_3";
			}
			else
			{
				dialog.text = "Obrigado pela sua ajuda, meu filho. Você trouxe esses livros na hora certa. Por favor, aceite este amuleto sagrado como recompensa – ele vai te proteger do perigo no seu momento mais difícil.";
				link.l1 = "Obrigado, Padre. Foi um prazer ajudar a Santa Igreja!";
				link.l1.go = "Churchbooks_4";
			}
		break;
		
		case "Churchbooks_3":
			dialog.text = "Está tudo nas mãos de Deus, meu filho. Vá em paz!";
			link.l1 = "Adeus, padre.";
			link.l1.go = "exit";
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			AddQuestRecord("Churchbooks", "3");
			CloseQuestHeader("Churchbooks");
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;
		
		case "Churchbooks_4":
			dialog.text = "Que Deus te abençoe, meu filho. Que o Todo-Poderoso te proteja no seu caminho!";
			link.l1 = "Adeus, Padre.";
			link.l1.go = "Churchbooks_5";
		break;
		
		case "Churchbooks_5":
			pchar.quest.Churchbooks_Over.over = "yes"; //снять таймер patch-5
			DialogExit();
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			GiveItem2Character(pchar, pchar.GenQuest.Churchbooks.Item);
			Log_Info("You have received '"+XI_ConvertString(pchar.GenQuest.Churchbooks.Item)+"'");
			AddQuestRecord("Churchbooks", "4");
			CloseQuestHeader("Churchbooks");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
			addLiberMisBonus();
		break;
	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	DeleteAttribute(rItem, "City");
	rItem.Weight = 2;
	rItem.Name = "itmname_Bible";
	rItem.picIndex = 6;
	rItem.picTexture = "ITEMS_9";
	BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr); 
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
	PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;
	
	// Чтоб жизнь медом не казалась... Какие сцены будут в квесте, определяем в самом начале.
	int iRand = Rand(2);
	switch(iRand)
	{
		case "0":
			PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2A (just pick up the manuscript from the priest)."); 
		break;
		
		case "1":
			PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-A (search for a cap. There is full information about him).");
		break;
		
		case "2": // Этот флаг уже не проверяем, т.к. если нет тех, что выше, по-любому есть этот
			PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-B (search for a cap. The name of the ship is unknown)."); 
		break;
	}
}
