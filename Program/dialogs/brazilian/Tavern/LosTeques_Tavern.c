#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	bool bLock = (CheckAttribute(pchar, "GenQuest.BrothelLock")) && (GetCharacterIndex("Mary") != -1);
	bool bLock1 = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) && (IsOfficer(characterFromId("Helena")));

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Levantaram um alarme na cidade. Todo mundo está te procurando! Se eu fosse você, não ficaria aqui por muito tempo.","A guarda inteira está vasculhando a cidade tentando te encontrar. Eu não sou idiota, e não vou conversar com você!","Corre, amigo, antes que os soldados te transformem em picadinho..."),LinkRandPhrase("O que você quer, canalha?! A guarda da cidade já está no seu encalço. Você não vai longe, pirata!","Assassino imundo, saia da minha casa! Guardas!!","Não tenho medo de você, cachorro! A forca está te chamando, você não vai longe..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, não estou preocupado com o alarme...","Eles não têm chance de me pegar."),RandPhraseSimple("Cale a boca, "+GetWorkTypeOfMan(npchar,"")+", ou eu arranco essa sua língua maldita.","Heh, "+GetWorkTypeOfMan(npchar,"")+", você também quer caçar um pirata? Olha, fique tranquilo e talvez você saia dessa vivo..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"! Bem-vindo, "+GetAddress_Form(NPChar)+" à Taverna da Mina de Los-Teques. Comida, bebida e garotas, tudo por preços acessíveis! Meu nome é "+GetFullName(npchar)+" e estou sempre ao seu dispor.";
				Link.l1 = "Vamos ver... Eu sou "+GetFullName(pchar)+". Prazer em conhecê-lo, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Aha, é o meu velho conhecido, Capitão "+GetFullName(pchar)+"! Que bom te ver, velho! Rum, garotas?";
				if (makeint(pchar.money) >= 5)
				{
					link.l1 = "Me sirva um pouco de rum, "+npchar.name+".";
					link.l1.go = "drink";
				}
				link.l2 = "Quero descansar um pouco. Você tem um quarto livre?";
				link.l2.go = "room";
				link.l3 = LinkRandPhrase("Tem alguma novidade?","O que há de novo por aqui?","Como está a vida em terra firme?");
				link.l3.go = "rumours_tavern";
				link.l4 = "Não, não preciso de nada, "+npchar.name+". Só passei aqui para te cumprimentar.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ah, que alegria! Rostos novos são raros na nossa cidade. Que tal eu servir um rum pra você e a gente bate um papo...";
			link.l1 = "É a minha primeira vez aqui e gostaria de saber um pouco mais sobre este povoado.";
			link.l1.go = "info";
			if (makeint(pchar.money) >= 5)
			{
				link.l2 = "Me sirva um pouco de rum, "+npchar.name+".";
				link.l2.go = "drink";
			}
			link.l3 = "Quero descansar um pouco. Você tem um quarto livre?";
			link.l3.go = "room";
		break;
		
		case "info":
			dialog.text = "Nada de interessante para contar. Todo dia é a mesma coisa: tédio, sol e poeira. Só vivem aqui soldados, negros e índios. De vez em quando aparecem alguns aventureiros e bandidos famintos por ouro\nÀs vezes, senhores e capitães como você nos visitam para vender escravos por lingotes e comprar metais preciosos. Nosso comerciante é uma figura interessante, ele vende não só pepitas de ouro e prata, mas também pedras semi-preciosas\n Dizem que quem entende do assunto pode achar essas pedrinhas muito úteis. Então dê uma olhada na nossa loja. A mina mesmo fica mais adiante, sob a montanha. Você pode visitá-la se quiser, mas recomendo não irritar os guardas\nNão converse com os condenados e que Deus te livre de roubar alguma coisa. De qualquer forma, o melhor lugar desse povoado é a minha taverna, o melhor lugar para descansar desse inferno ardente!";
			link.l1 = "Obrigado pela informação!";			
			link.l1.go = "exit";
		break;
		
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 3)
			{
				dialog.text = "Capitão, acho melhor você parar. Deus me livre de você causar confusão enquanto está sob efeito de álcool. Aqui somos bem rigorosos com isso. Nem sua autoridade vai te ajudar.";
				link.l1 = "Hm... Acho que você tem razão - já bebi o suficiente. Obrigado pela preocupação!";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -5);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "De nada, capitão. Só cinco peças de oito por uma caneca do meu melhor rum jamaicano escuro!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("Certo, à sua saúde e à prosperidade do seu estabelecimento!","Está bem, para aqueles no mar!","Certo, à prosperidade da sua cidade!"),LinkRandPhrase("Então, aos ventos da fortuna, a uma rajada de sorte, que todos nós vivamos mais leves e prósperos!","Certo, ao vento sempre soprando a nosso favor em todos os assuntos!","Certo, à felicidade, à sorte, à alegria e às mulheres!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
		break;
		
		case "room":
			if (CheckAttribute(pchar, "GenQuest.LosTequesSex"))
			{
				dialog.text = "Senhor, você pagou por um quarto e por uma moça. Suba, ela já está te esperando faz um tempo.";
				link.l1 = "Certo.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Temos, sim. Por quanto tempo você pretende ficar?";
			if(!isDay())
			{
				link.l1 = "Até de manhã.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Até o anoitecer.";
				link.l1.go = "room_night";
				link.l2 = "Até a manhã seguinte.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "Serão dez peças de oito. Quer uma moça para o quarto também? Só mil pesos pela garota.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Não, não preciso de uma moça. Aqui, fique com isso pelo quarto.";
				link.l1.go = "room_day_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Tá bom, fico com o quarto e a moça. Aqui está o dinheiro.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Infelizmente, não posso pagar pelo quarto.";
			link.l3.go = "exit";
		break;

		case "room_day_next":
			dialog.text = "Isso vai custar dez peças de oito. Quer uma moça para o quarto também? Só mil pesos pela garota.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Não, não preciso de uma moça. Aqui, fique com isso pelo quarto.";
				link.l1.go = "room_day_wait_next";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Certo. Vamos ficar com o quarto e com a moça. Aqui está o dinheiro.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Infelizmente, não posso pagar pelo quarto.";
			link.l3.go = "exit";
		break;

		case "room_night":
			dialog.text = "Serão dez peças de oito. Quer uma moça para o quarto também? Só mil pesos pela garota.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Não, não preciso de companhia. Aqui, fique com isso pelo quarto.";
				link.l1.go = "room_night_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Certo. Vamos ficar com o quarto e com a moça. Aqui está o dinheiro.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_night";
				}
			}
			link.l3 = "Infelizmente, não posso pagar pelo quarto.";
			link.l3.go = "exit";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -20);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "room_girl":
			AddMoneyToCharacter(pchar, -1010);
			dialog.text = "Pode subir, señor. A moça vai estar te esperando. Aproveite a estadia!";
			link.l1 = "Obrigado, camarada...";
			link.l1.go = "room_girl_1";
		break;
		
		case "room_girl_1":
			DialogExit();
			pchar.GenQuest.CannotWait = true;
			pchar.GenQuest.LosTequesSex = "true";
			LocatorReloadEnterDisable("LosTeques_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("LosTeques_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			sld = GetCharacter(NPC_GenerateCharacter("MineFuckGirl" , "squaw_"+(rand(2)+1), "woman", "woman_B", 1, SPAIN, 1, true, "quest"));
			sld.dialog.FileName = "Tavern\LosTeques_Tavern.c";
			sld.dialog.currentnode = "MineFuckGirl";
			//sld.greeting = "";
			sld.name = GetIndianName(WOMAN);
			sld.lastname = "";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "LosTeques_tavern_upstairs", "goto", "goto1");
		break;
		
		case "MineFuckGirl":
			dialog.text = "Como vai, mestre branco. Não olhe para "+npchar.name+" assim mesmo, "+npchar.name+"sabe fazer tudo ainda melhor do que a branca do bordel. Ah, senhor, você é tão bonito... Prometo, esta índia vai te amar por muito tempo.";
			link.l1 = "Parece ótimo, mostre-me seus melhores amuletos indígenas. Não vou precisar de uma dança da chuva para te deixar molhada...";
			link.l1.go = "MineFuckGirl_sex";
		break;
		
		case "MineFuckGirl_sex":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Roubo em plena luz do dia!!! O que está acontecendo aqui?! Espera, calma aí, amigo...","Ei, o que você está fazendo aí?! Tentando me roubar? Agora você está encrencado...","Espera aí, que diabos você está fazendo? Então você é um ladrão! Considere isso o fim da linha, seu canalha...");
			link.l1 = LinkRandPhrase("Diabo!","Porra!","Ah, merda");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
