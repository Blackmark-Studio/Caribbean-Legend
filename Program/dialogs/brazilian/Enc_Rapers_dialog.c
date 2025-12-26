void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "Exit_Fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar); 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			
			if(pchar.GenQuest.EncGirl == "RapersTreasure")
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}			
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");			
				sld = CharacterFromID("CangGirl");
				LAi_SetActorType(sld);
				LAi_ActorAfraid(sld, npchar, true);
			}	
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();	
			AddDialogExitQuest("OpenTheDoors");			
		break;
		
		case "First time":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
//			Diag.TempNode = "OnceAgain";
			if(pchar.GenQuest.EncGirl == "Begin_1")
			{
				dialog.text = LinkRandPhrase("Siga o seu caminho, "+GetSexPhrase("companheiro","moça")+". Ela vai nos agradecer no final, sabe.","Cai fora! Deixa os cavalheiros se divertirem.","Isso não é da sua conta, "+GetSexPhrase("estranho","moça")+". Vamos só nos divertir um pouco, e é só isso!");
				link.l1 = LinkRandPhrase("Eu não vou permitir isso!","Abandone seus planos malignos neste instante!","Não vou tolerar nenhum tipo de violência!");
				link.l1.go = "Node_Fight";
				link.l2 = RandPhraseSimple("Entendi, estou indo embora. Desculpe incomodar.","Não vou me atrever a incomodá-lo de novo. Desculpe por te importunar.");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			if(pchar.GenQuest.EncGirl == "Begin_2")
			{
				if(sti(pchar.rank) < 10)
				{
					dialog.text = LinkRandPhrase("Siga seu próprio caminho, "+GetSexPhrase("companheiro","moça")+". No final, ela vai nos agradecer, sabia.","Cai fora! Deixa os cavalheiros se divertirem.","Isso não é da sua conta, "+GetSexPhrase("estranho","moça")+". Vamos só nos divertir um pouco, e é só isso!!");
					link.l1 = LinkRandPhrase("Eu não vou permitir isso!","Abandone seus planos malignos neste instante!","Não vou tolerar nenhum tipo de violência!");
					link.l1.go = "Node_Fight";
					link.l2 = RandPhraseSimple("Entendi, estou indo embora. Desculpe por incomodar.","Não vou me atrever a incomodá-lo de novo. Desculpe por incomodar.");
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_11";
				}
				else
				{
					dialog.text = RandPhraseSimple("Ei, "+GetSexPhrase("estranho","moça")+", por que está procurando confusão? Essa moça é uma figura 'bem conhecida' aqui no nosso povoado. Já pagamos o que devíamos, mas ela te viu e resolveu fugir com o nosso dinheiro.","Ei, "+GetSexPhrase("companheiro","moça")+", siga seu caminho e não se meta nos nossos assuntos. Ganhamos essa moça num jogo de dados, mas ela foi rápida demais e fugiu, estamos caçando ela nessa selva faz uma hora.");
					link.l1 = "Eu não me importo, não vou deixar você machucá-la!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("Ah, entendi! E eu quase acreditei nela! Que descarada...","Ah, bom, aí já é outra história então. Aproveitem, pessoal!");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}	
			}
			if(pchar.GenQuest.EncGirl == "Begin_3")
			{
				if(sti(pchar.rank) < 20)
				{	
					dialog.text = "Siga seu próprio caminho, "+GetSexPhrase("bom homem","moça")+". A gente resolve isso sem você.";
					link.l1 = "Não vou tolerar nenhum tipo de violência!";
					link.l1.go = "Node_5";
					pchar.GenQuest.EncGirl = "Begin_33";
				}
				else
				{
					dialog.text = RandPhraseSimple("Ei, "+GetSexPhrase("estranho","moça")+", por que você está procurando confusão? Essa moça é uma figura 'bem conhecida' aqui no nosso povoado. Já pagamos o que devíamos, mas ela te viu e resolveu fugir com o nosso dinheiro.","Ei, "+GetSexPhrase("companheiro","moça")+", siga seu caminho e não se meta nos nossos assuntos. Ganhamos essa moça num jogo de dados, mas ela foi rápida demais pra fugir, estamos atrás dela faz uma hora.");
					link.l1 = "Eu não me importo – não vou deixar você machucá-la!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("Ah, entendi! E eu quase acreditei nela! Que moça atrevida...","Ah, bom, aí já é outra história então. Aproveitem, pessoal!");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}			
		break;
		
		case "Node_Fight":
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Bem, você certamente escolheu a hora certa para dar uma volta...","Então, você decidiu ser um herói?")+" Resolver com h"+GetSexPhrase("im","er")+", rapazes!","Você "+GetSexPhrase("gosma","imundície")+"! Você ousa ficar no nosso caminho?! Cortem "+GetSexPhrase("im","er")+"!");
			link.l1 = "Já vi pessoas bem mais ameaçadoras!";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_3":
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * sti(pchar.rank);
			dialog.text = "Você devia saber que ela nos custou caro! E se você é tão nobre assim, pode levá-la por "+sti(pchar.GenQuest.EncGirl.price)+" pesos."+GetSexPhrase(" Você vai se divertir com ela, he-he...","")+"";
			if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = RandPhraseSimple("Aqui está o seu dinheiro. Vou levá-la comigo.","Pare de ranger os dentes. Eu vou levar a garota comigo. Aqui está o seu dinheiro.");
				link.l1.go = "Node_4";
			}	
			link.l2 = LinkRandPhrase("Então, é dinheiro que você quer? Ou prefere o aço frio?","Isso era pra ser engraçado? Olhe pra garota, seu idiota! Ela está assustada!","Quem você pensa que engana, seu degenerado!");
			link.l2.go = "Node_Fight";
		break;
		
		case "Node_4": // бандюки уходят, девица остаётся - ГГ ее выкупил у бандюков
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price))); 
			ChangeCharacterComplexReputation(pchar,"nobility", 7);
			//pchar.quest.LandEnc_RapersBadExit.over = "yes";
			sGlobalTemp = "Saved_CangGirl";
			pchar.GenQuest.EncGirl.Ransom = true;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_5":
			dialog.text = "Por que você acreditou nela logo de cara? Que violência? Ela fugiu de casa, e fomos enviados pelo nosso chefe para encontrá-la.";
			link.l1 = RandPhraseSimple("Bem, aí já é outra história, então. Vai, corre atrás do seu fujão.","Ah, entendi. Bem, continue atrás dela então... e eu tenho uns assuntos para resolver.");
			link.l1.go = "Exit_NoFight";
			link.l2 = RandPhraseSimple("Conte essas histórias de fada pros seus netos, se viver tempo suficiente pra ter algum!","Quem você acha que está enganando, seu desgraçado?!");
			link.l2.go = "Node_6";
			link.l3 = "Eu mesmo vou levá-la para casa, para evitar qualquer problema. Quem são os pais dela?";
			link.l3.go = "Node_7";
		break;
		
		case "Node_6":
			dialog.text = "Quer morrer? A escolha é sua...";
			link.l1 = "Olha quem fala.";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_7":
			sGlobalTemp = "Saved_CangGirl";
			if(pchar.GenQuest.EncGirl.city == "Panama") i = hrand(2);
			else	i = hrand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = "is a store owner";
					pchar.GenQuest.EncGirl.FatherGen = "of a store owner";
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = "serves in the port office";
					pchar.GenQuest.EncGirl.FatherGen = "who serves in the port office";
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = "serves as the prison's commandant";
					pchar.GenQuest.EncGirl.FatherGen = "of a prison's commandant";
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = "is a shipyard owner";
					pchar.GenQuest.EncGirl.FatherGen = "of a shipyard owner";
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;				
			}
			dialog.text = "O pai dela "+pchar.GenQuest.EncGirl.FatherNom+", no assentamento de "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+". Mas, por favor, não nos decepcione, porque ele não é alguém com quem se brinca, ele vai arrancar nosso couro vivo...";
			link.l1 = "Não se preocupe. Eu vou entregá-la a ele.";
			link.l1.go = "Node_12";
			pchar.GenQuest.EncGirl = "toParents";
		break;
		
		case "Node_12":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
				sld.lifeDay = 0;
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_8":
			dialog.text = "E então nos encontramos de novo. Onde está sua companheira? Ah, bem, na verdade não preciso dela se você está aqui.";
			link.l1 = "Senhores, eu realmente acho que vocês já receberam dinheiro suficiente para deixar a moça em paz.";
			link.l1.go = "Node_9";
		break;
		
		case "Node_9":
			if(hrand(1) == 0)
			{	
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;	
			}	
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);	
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;	
			}	
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch(hrand(4))
			{
				case 0:
					sTemp = "a leg";
				break;
				case 1:
					sTemp = "an arm";
				break;
				case 2:
					sTemp = "an ear";
				break;
				case 3:
					sTemp = "a nose";
				break;
				case 4:
					sTemp = "an eye";
				break;
			}
			dialog.text = "O que é o seu dinheiro comparado aos tesouros de "+GetName(pchar.GenQuest.EncGirl.PirateIdx,pchar.GenQuest.EncGirl.PirateName1,NAME_GEN)+"? "+"Ele era tão ganancioso que não queria casar a própria filha só pra não ter mais despesas...\nMas ele guardou a nossa parte trancada nos baús dele! "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.PirateName2,NAME_NOM)+" perdeu na abordagem "+sTemp+"! E então, o que você tem no lugar? "+"Um punhado miserável de prata? "+GetName(pchar.GenQuest.EncGirl.PirateIdx,pchar.GenQuest.EncGirl.PirateName1,NAME_NOM)+" sempre levava todo o saque para o esconderijo dele. Mas agora não vamos desistir! Mostre onde estão os baús dele!";
			link.l1 = "Olha, eu com certeza não aceitei ficar de guarda dos tesouros do seu capitão, mas não posso te mostrar o lugar... Porque eu não faço ideia de onde fica.";
			link.l1.go = "Node_10";
		break;
		
		case "Node_10":
			dialog.text = "Você está mentindo!!! Eu sinto o cheiro de ouro vindo dessa caverna! Mostre o lugar se não quiser morrer!";
			link.l1 = "Vejo que minhas palavras não conseguiram te convencer. Talvez minha espada seja mais persuasiva?";
			link.l1.go = "Node_11";
		break;
		
		case "Node_11":
			pchar.GenQuest.EncGirl = "RapersTreasure";
			dialog.text = "Você "+GetSexPhrase("cur","imundície")+"! Saia do meu caminho!";
			link.l1 = "Argh!";
			link.l1.go = "exit_fight";
		break;
		
		case "EncGirl_Berglar":
			dialog.text = "Olá, bom "+GetSexPhrase("homem","senhora")+". Recebemos reclamações sobre você.";
			link.l1 = "Reclamações de quem? Daquela vadia?";
			link.l1.go = "EncGirl_Berglar1";
		break;
		
		case "EncGirl_Berglar1":
			dialog.text = "Olha como fala, tá bom? Não vou permitir que você insulte minha irmã! Primeiro você a atacou na selva, depois a trouxe pra cá "+GetSexPhrase("por mais indecência","e me roubaram")+".";
			link.l1 = "Ei, camarada, eu realmente preciso ouvir tudo isso?";
			link.l1.go = "EncGirl_Berglar2";
		break;
		
		case "EncGirl_Berglar2":
			pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money)/5) + 5000;
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000) pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
			{
				dialog.text = "Não. Apenas uma quantia modesta de "+sti(pchar.GenQuest.EncGirl.BerglarSum)+" pesos vão te livrar de toda essa encrenca.";
				if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
				{
					link.l1 = "Bem, atos nobres realmente custam caro hoje em dia. Tudo bem, pode pegar...";
					link.l1.go = "EncGirl_Berglar3";
				}	
				link.l2 = "Acho que sairia mais barato abrir um buraco na sua barriga do que deixar você me atrapalhar no caminho da saída.";
				link.l2.go = "EncGirl_Berglar4";
			}
			else
			{
				dialog.text = "Não. Mas você também vai virar os bolsos para fora, senão eu te furo!";
				link.l1 = "Certo, pega logo, seu canalha! Mas você não vai sair impune dessa...";
				link.l1.go = "EncGirl_Berglar3_1";
				link.l2 = "Acho que seria mais fácil abrir um buraco na sua barriga do que deixar você me atrapalhar no caminho da saída.";
				link.l2.go = "EncGirl_Berglar4";				
			}			
		break;
		
		case "EncGirl_Berglar3":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
			dialog.text = "Muito bem. Já vai tarde.";
			link.l1 = "Boa sorte.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoom");			
		break;
		
		case "EncGirl_Berglar3_1":
			dialog.text = "Claro que não vou, claro... Bem, adeus pra você, "+GetSexPhrase("companheiro","moça")+"."+GetSexPhrase(" E lembre-se, você não é tão bonito a ponto de qualquer garota se apaixonar por você assim que te visse. Essa é a lição que eu te dou.","")+"";
			link.l1 = ""+GetSexPhrase("Isso com certeza!..","Vai embora logo!")+"";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");			
		break;
		
		case "EncGirl_Berglar4":
			dialog.text = "Você parece "+GetSexPhrase("um homem tão nobre","uma dama tão bem-educada")+", por que tanta grosseria?";
			link.l1 = "Isso me convém melhor...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_fight");
		break;
		
		case "Node_2":
			dialog.text = "Bem, você pediu por isso! Devemos fazer cócegas n"+GetSexPhrase("im","er")+" com aço, rapazes?";
			Link.l1 = "Reze antes de morrer!";
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = "Então, vai querer se juntar ou não? "+GetSexPhrase("Cai fora, não tem o bastante pra todo mundo","Vaza enquanto pode, uma moça já basta pra gente")+"!";
			Link.l1 = "Bem, então não vou te atrapalhar.";
			Link.l1.go = "Exit_NoFight";
			Link.l2 = "Não vou permitir que aconteça qualquer violência!";
			Link.l2.go = "Node_2";
		break;				
	}
}
