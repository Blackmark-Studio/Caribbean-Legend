// посредник-дипломат кланов Джузеппе Фацио
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Olá, olá... Você é novo por aqui? Não me lembro do seu rosto. Permita-me apresentar: sou Giuseppe Fazio, especialista em resolver problemas nesta pequena ilha.";
				link.l1 = TimeGreeting()+". Meu nome é "+GetFullName(pchar)+". Você está certo, sou novo aqui. Perdoe minha curiosidade – mas que tipo de problemas você resolve?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, você de novo, querido "+pchar.name+"! O que traz você à minha humilde casa?";
				if (CheckAttribute(pchar, "GenQuest.NarvalConflict") || CheckAttribute(pchar, "GenQuest.RivadosConflict") || CheckAttribute(pchar, "GenQuest.SharkConflict"))
				{
					link.l10 = "Fazio, estou com um sério conflito com um dos clãs. Preciso resolver esse problema.";
					link.l10.go = "conflict";
				}
				// --> квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_3")
				{
					link.l4 = "Giuseppe, estou procurando por um homem chamado Adolf Barbier. Disseram que você estava bebendo com ele na taverna recentemente...";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && pchar.questTemp.LSC.Drink == "begin")
				{
					link.l5 = "Giuseppe, dizem que você é completamente resistente à bebida. Não importa o quanto beba, você sempre continua de pé.";
					link.l5.go = "drink";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && PCharDublonsTotal() >= 100 && pchar.questTemp.LSC.Drink == "wait")
				{
					link.l5 = "Estou pronto para jogar seu jogo. Aqui está minha aposta.";
					link.l5.go = "drink_4";
				}
				// <-- квестовые ветки
				if (CheckAttribute(npchar, "quest.parol"))
				{
					link.l1 = "Quero saber as senhas atuais dos clãs para entrar nos territórios deles.";
					link.l1.go = "parol_choice";
				}
				link.l2 = LinkRandPhrase("Tem alguma coisa interessante pra contar?","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Nada de especial, Giuseppe. Só queria te ver.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "De tudo um pouco, meu caro, de tudo um pouco. Por exemplo, eu apaziguo as coisas entre o almirante e os clãs. Como você talvez já saiba, os Rivados, os Narvais e o almirante são inimigos declarados. Eu atuo como mediador quando a situação complica.  Além disso, costumo ser a parte neutra quando o almirante vende mantimentos para os clãs. Mas isso é só uma pequena parte dos meus negócios. Então, se tiver problemas com os Rivados ou os Narvais, não hesite em pedir minha ajuda, veremos o que pode ser feito.";
			link.l1 = "Tudo bem. Vou pensar nisso.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// пароли
		case "parol_choice":
			dialog.text = "Que clã?";
			link.l1 = "Narvais.";
			link.l1.go = "parol_nrv";
			link.l2 = "Rivados.";
			link.l2.go = "parol_rvd";
		break;
		
		case "parol_nrv":
			dialog.text = "Quer ver o Donald Greenspen, certo?";
			link.l1 = "Certo. Então, você sabe a senha?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Narwals";
			sTotalTemp = sNrvParol;
		break;
		
		case "parol_rvd":
			dialog.text = "Quer ver o Eddie Negro, acertei?";
			link.l1 = "Algo assim. Então, você sabe a senha?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Rivados";
			sTotalTemp = sRvdParol;
		break;
		
		case "parol":
			if (!CheckAttribute(npchar, "quest.parolrules"))
			{
				dialog.text = "Claro! Mas deixe-me te explicar alguns detalhes primeiro. As senhas são sempre uma palavra só e mudam toda semana: nos dias sete, quatorze, vinte e um e vinte e oito de cada mês.\nEntão fique atento à data de hoje para não errar. E, como você deve imaginar, não é de graça. Cinquenta dobrões por senha. Só aceito dobrões, lembre-se disso.";
				link.l1 = "Cinquenta doblões? Isso é uma fortuna!";
				link.l1.go = "parol_1";
			}
			else
			{
				dialog.text = "Claro, meu rapaz. Você sabe o preço. Tem cinquenta dobrões?";
				if (PCharDublonsTotal() >= 50)
				{
					link.l1 = "Sim. Pegue suas moedas.";
					link.l1.go = "parol_pay";
				}
				link.l2 = "Infelizmente, não. Talvez mais tarde...";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "parol_1":
			dialog.text = "Ora, ora, meu rapaz, calma. Não seja ganancioso, confie em mim: eu sei o verdadeiro valor das minhas informações. Você não vai simplesmente andar pelos navios da "+pchar.questTemp.LSC.parol+" certo? Certo. Então você tem que estar pronto para perder umas moedas... Então, está pronto para pagar cinquenta dobrões?";
			if (PCharDublonsTotal() >= 50)
			{
				link.l1 = "Sim. Pegue suas moedas.";
				link.l1.go = "parol_pay";
			}
			link.l2 = "Infelizmente, eu não tenho esse tipo de dinheiro. Talvez mais tarde...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
			npchar.quest.parolrules = "true";
		break;
		
		case "parol_pay":
			RemoveDublonsFromPCharTotal(50);
			dialog.text = "Ótimo! Foi um prazer fazer negócio com você. A senha atual para "+pchar.questTemp.LSC.parol+" is: '"+sTotalTemp+"'. Lembre-se bem disso e não cometa nenhum erro, ou não darei nem uma moeda pela sua vida.";
			link.l1 = "Eu sei, eu sei... Obrigado!";
			link.l1.go = "exit";
			AddQuestRecord("LSC", "parol");
			AddQuestUserData("LSC", "sText", pchar.questTemp.LSC.parol);
			AddQuestUserData("LSC", "sParol", sTotalTemp);
			if (pchar.questTemp.LSC.parol == "Rivados") pchar.questTemp.LSC.RParol_bye = "true";
			else pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "adolf":
			dialog.text = "Ah, mas é claro, meu velho Adolfo! Sim, conversei com ele. Veja, meu caro, fiquei feliz por ter meu dinheiro de volta, aquele dinheiro que achei que nunca mais veria! Adolfo pegou uma boa quantia emprestada dando como garantia seu excelente rifle e teve dificuldades para me pagar de volta\nPerdi toda esperança de reaver o dinheiro e já estava prestes a vender aquele stutzen para o nosso querido Axel Yost. Mas, de repente, o bom Adolfo me trouxe meu ouro! Descobri que ele conseguiu juntar moedas suficientes não só para recuperar o stutzen, mas também para comprar a cabine do Sessile Gallard na proa do 'Santa Florentina'!\nCom certeza, isso é muito melhor do que viver num porão meio alagado\nEntão, Adolfo tem seu rifle de volta, uma casa nova e eu, meu dinheiro. Por que eu recusaria um drinque com ele, ainda mais quando é ele quem paga?";
			link.l1 = "Ah, claro! Você tinha muitos motivos pra beber. E de graça... Obrigado, Giuseppe, você me ajudou muito. Agora eu sei onde encontrar o Adolf.";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Sempre um prazer, querido. Mas não procure o Adolfo na cabine dele até o anoitecer, ele está muito ocupado, correndo pra lá e pra cá com uns assuntos... Ah, e venha me visitar mais vezes, vamos conversar!";
			link.l1 = "Vou te convidar quando eu tiver minha própria cabine... Adeus, e boa sorte!";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			DialogExit();
			LSC_CreateAdolfClone(); // заменяем Адольфа клоном
			pchar.questTemp.Saga.SharkHunt = "search_mush_4"; //флаг на Адольфа в каюте
			AddQuestRecord("SharkHunt", "14");
		break;
		
		case "whiskey":
			switch (sti(npchar.quest.poisonnode))
			{
				case 1: // у себя
					dialog.text = "Ah? Por que está entrando no meu lugar como se tivesse um incêndio? Quem você pensa que é??";
					link.l1 = "Sua justiça... envenenador!";
					link.l1.go = "whiskey_1";
				break;
				
				case 2: // на Эве
					dialog.text = "Me poupe! Eu juro, eles me obrigaram! Eles apontaram uma arma pra mim...";
					link.l1 = "Cala a boca. Eu sei disso. Onde está o último desgraçado? Onde está Marcello Ciclope?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
				
				case 3: // у Акулы
					dialog.text = "Eu juro, eles me forçaram! Já contei tudo ao almirante! Eu não consegui resistir, eles iam...";
					link.l1 = "Cala a boca. Eu sei disso. Onde está o último desgraçado? Onde está o Marcello Ciclope?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
			}
		break;
		
		case "whiskey_1":
			dialog.text = "O que... o que você disse?";
			link.l1 = "Eu sei de tudo, seu bastardo. Você está trabalhando com o Chad Kapper. Trouxe um barril de rum envenenado para o almirante. Agora reze, seu desgraçado...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Espere! Pare! Me poupe! Eu juro, eles me obrigaram! Eles apontaram uma arma para mim...";
			link.l1 = "Cale a boca. Eu sei disso. Onde está o último desgraçado? Onde está o Marcello Ciclope?!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Eu... eu... eu não sei!";
			link.l1 = "Você está mentindo, canalha! Eu vejo isso. Onde está o Ciclope?";
			if (pchar.questTemp.LSC.Mary == "die") link.l1.go = "whiskey_10"; // ушел на Флерон
			else link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "Ele... ele recebeu algumas ordens do Kapper e foi embora. Eu não sei onde ele está!";
			link.l1 = "Mentindo de novo. Você sabe de tudo. Não seja covarde, sua criatura imunda – Kapper está morto e não vai te fazer mal. Mas se não me disser onde está o Marcello, eu te mato como um porco agora mesmo! O que o Chad mandou o Ciclope fazer?";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "Ele mandou ele matar... Mary Vermelha.";
			link.l1 = "O quê?! Fale logo, como ele vai fazer isso? É impossível entrar na cabine dela! Como ele pretende matá-la?!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			dialog.text = "Ele vai entrar na cabine do Jurgen enquanto o ferreiro estiver fora. Depois, vai descer até o porão, atravessá-lo e chegar à cabine da Mary\nA única coisa que ele vai precisar fazer então é esperar até a garota virar de costas ou adormecer. Foi isso que o Chad me contou. Não sei de mais nada, eu juro!";
			link.l1 = "Já chega. Quando ele foi? Quando, me diga, o Ciclope foi até a 'Ferraria Ceres'?";
			link.l1.go = "whiskey_7";
		break;
		
		case "whiskey_7":
			dialog.text = "Ele já deve estar na cabine do Jurgen... ou lá embaixo no porão de carga...";
			link.l1 = "Porra! Não tenho tempo pra nadar em volta da ilha! Me diz a senha dos navios dos Narvais! Fala logo, e se mentir pra mim, eu ainda vou sobreviver, mas você com certeza vai morrer!";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "'"+sNrvParol+"'...";
			link.l1 = "Entendi. Agora reze para que a garota sobreviva.";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "whiskey_repeat";
			pchar.quest.LSC_RescueMary.win_condition.l1 = "location";
			pchar.quest.LSC_RescueMary.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_RescueMary.function = "LSC_RescueMary";
			AddQuestRecord("SharkHunt", "46");
			AddQuestUserData("SharkHunt", "sParol", sNrvParol);
			pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "whiskey_repeat":
			dialog.text = "Eu já te contei tudo o que sei! Eu juro!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "whiskey_repeat";
		break;
		
		case "whiskey_10":
			dialog.text = "Ele... Ele está em algum lugar dentro do 'Fleron'. Chad mandou ele se esconder lá e esperar as próximas ordens.";
			link.l1 = "Entendi. É melhor que seja verdade...";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.LSC_FindCyclop.win_condition.l1 = "location";
			pchar.quest.LSC_FindCyclop.win_condition.l1.location = "FleuronTavern";
			pchar.quest.LSC_FindCyclop.function = "LSC_SetCyclop_Fl";
			NextDiag.CurrentNode = "whiskey_repeat";
			AddQuestRecord("SharkHunt", "51");
			
		break;
		
		// --> конфликты
		case "conflict":
			dialog.text = "É mesmo? Então, meu rapaz, qual clã está te incomodando?";
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				link.l1 = "Narvais.";
				link.l1.go = "narval";
				npchar.quest.clan = "narval";
			}
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				link.l2 = "Rivados.";
				link.l2.go = "rivados";
				npchar.quest.clan = "rivados";
			}
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				link.l3 = "Piratas do Almirante.";
				link.l3.go = "shark";
				npchar.quest.clan = "shark";
			}
			link.l4 = "Que nada. Eu estava brincando, Giuseppe, estou bem.";
			link.l4.go = "exit";
		break;
		
		case "narval":
			npchar.quest.price = sti(pchar.GenQuest.NarvalConflict)*50;
			if (sti(pchar.GenQuest.NarvalConflict) < 3) dialog.text = "Bem, não é exatamente um conflito, só um pequeno mal-entendido, he-he. "+sti(npchar.quest.price)+"  dobrões e seu problema estará resolvido em um dia.";
			else
			{
				if (sti(pchar.GenQuest.NarvalConflict) >= 3 && sti(pchar.GenQuest.NarvalConflict) < 10) dialog.text = "Claro, já ouvi falar disso. Você causou uma bela confusão, meu caro. Mas existe uma saída. "+sti(npchar.quest.price)+" dobrões e seu problema será resolvido em um dia.";
				else dialog.text = "A ilha inteira sabe sobre a chacina que você cometeu. Não vai ser fácil te ajudar, mas ainda há uma chance. "+sti(npchar.quest.price)+" dobrões e eu vou tentar resolver seu problema.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Aqui, pegue suas moedas e resolva isso.";
				link.l1.go = "pay";
			}
			link.l2 = "Infelizmente, não tenho dobrões suficientes comigo agora. Mas vou trazê-los depois, e voltaremos a conversar.";
			link.l2.go = "exit";
		break;
		
		case "rivados":
			npchar.quest.price = sti(pchar.GenQuest.RivadosConflict)*50;
			if (sti(pchar.GenQuest.RivadosConflict) < 3) dialog.text = "Bem, não é exatamente um conflito, só um pequeno mal-entendido, he-he. "+sti(npchar.quest.price)+"  dobrões e seu problema será resolvido em um dia.";
			else
			{
				if (sti(pchar.GenQuest.RivadosConflict) >= 3 && sti(pchar.GenQuest.RivadosConflict) < 10) dialog.text = "Claro, já ouvi falar disso. Você causou uma bela confusão, meu caro. Mas existe uma saída. "+sti(npchar.quest.price)+"  dobrões e seu problema estará resolvido em um dia.";
				else dialog.text = "A ilha inteira sabe sobre o massacre que você cometeu. Não vai ser fácil te ajudar, mas ainda há uma chance. "+sti(npchar.quest.price)+" dobrões e eu vou tentar resolver o seu problema.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Aqui, pegue suas moedas e resolva isso.";
				link.l1.go = "pay";
			}
			link.l2 = "Infelizmente, não tenho dobrões suficientes comigo agora. Mas vou trazê-los depois, e conversaremos novamente.";
			link.l2.go = "exit";
		break;
		
		case "shark":
			npchar.quest.price = sti(pchar.GenQuest.SharkConflict)*50;
			if (sti(pchar.GenQuest.SharkConflict) < 3) dialog.text = "Bem, não é exatamente um conflito, só um pequeno mal-entendido, he-he. "+sti(npchar.quest.price)+" dobrões e seu problema será resolvido em um dia.";
			else
			{
				if (sti(pchar.GenQuest.SharkConflict) >= 3 && sti(pchar.GenQuest.SharkConflict) < 10) dialog.text = "Claro, já ouvi falar disso. Você causou uma bela confusão, meu caro. Mas há uma saída. "+sti(npchar.quest.price)+" dobrões e seu problema será resolvido em um dia.";
				else dialog.text = "A ilha inteira já sabe do massacre que você cometeu. Não vai ser fácil te ajudar, mas ainda há uma chance. "+sti(npchar.quest.price)+" dobrões e eu vou tentar resolver seu problema.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Aqui, pegue suas moedas e resolva isso.";
				link.l1.go = "pay";
			}
			link.l2 = "Infelizmente, não tenho dobrões suficientes comigo agora. Mas vou trazê-los depois, e conversaremos novamente.";
			link.l2.go = "exit";
		break;
		
		case "pay":
			RemoveDublonsFromPCharTotal(sti(npchar.quest.price));
			PlaySound("interface\important_item.wav");
			Log_Info("You have given "+sti(npchar.quest.price)+" doubloons");
			dialog.text = "Excelente. Agora sente-se e descanse um pouco. É melhor você ficar na minha cabine até eu resolver seu problema. Não quero que você piore ainda mais as coisas, meu caro.";
			link.l1 = "Tudo bem...";
			link.l1.go = "peace";
		break;
		
		case "peace":
			DialogExit();
			GetCharacterPos(pchar, &locx, &locy, &locz);
			pchar.locx = locx;
			pchar.locy = locy;
			pchar.locz = locz;
			SetLaunchFrameFormParam("One day later..."+ NewStr() +"Fazio has dealt with the conflict", "Reload_To_Location", 0.1, 5.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
			WaitDate("", 0, 0, 1, 3, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			switch (npchar.quest.clan)
			{
				case "narval":
					DeleteAttribute(pchar, "GenQuest.NarvalConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") || !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false);//открыть вход к Дональду
					LAi_group_SetRelation("LSC_NARVAL", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "rivados":
					DeleteAttribute(pchar, "GenQuest.RivadosConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend") || !CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload33", false);//открыть вход к Эдди
					LAi_group_SetRelation("LSC_RIVADOS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "shark":
					DeleteAttribute(pchar, "GenQuest.SharkConflict"); // мирим
					LSC_OpenSanAvgustinDoors(); // открыть сан-августин
					LSC_OpenTartarusDoors(); // открыть тартарус
					LAi_group_SetRelation("LSC_SHARK", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
			}
			DeleteAttribute(npchar, "quest.clan");
			DeleteAttribute(npchar, "quest.price");
		break;
		
		// --> пей до дна
		case "drink":
			dialog.text = "Vamos lá, meu rapaz! Eles estão mentindo, todos eles, he-he. Minha cabeça só é um pouco mais dura que a média, mas sou um ser humano como você, então também fico bêbado de rum. As pessoas bebem rum para ficar bêbadas, esse é o único propósito dele. Já pensou nisso, querido?";
			link.l1 = "É verdade.";
			link.l1.go = "drink_1";
		break;
		
		case "drink_1":
			dialog.text = "Quer jogar um jogo divertido comigo? Chama-se 'Beba Até a Última Gota!', ha-ha! Aposto que você já ouviu falar. Acertei?";
			link.l1 = "É, ouvi uns boatos sobre isso... Eu diria que foi 'cara na mesa'.";
			link.l1.go = "drink_2";
		break;
		
		case "drink_2":
			dialog.text = "Ha-ha-ha, meu caro rapaz, você fez o velho rir, o que mais posso dizer! 'Cara na mesa!' Vou lembrar disso... Então, o que me diz? Vamos jogar por cem doblões?";
			link.l1 = "Cem dobrões?";
			link.l1.go = "drink_3";
		break;
		
		case "drink_3":
			dialog.text = "Sim, e quem perder paga as bebidas. Fechado?";
			if (PCharDublonsTotal() >= 100)
			{
				link.l1 = "Sim, combinado. Aqui está minha aposta.";
				link.l1.go = "drink_4";
			}
			link.l2 = "Hum. Eu não tenho tantas dobras assim.";
			link.l2.go = "drink_wait";
		break;
		
		case "drink_wait":
			dialog.text = "Bem, venha me ver quando tiver, e jogaremos!";
			link.l1 = "Tudo bem...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Drink = "wait";
		break;
		
		case "drink_4":
			RemoveDublonsFromPCharTotal(100);
			Log_Info("You have given 100 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Excelente, meu caro! Então, me encontre às nove da noite na taverna do Sancho! Sim, sua aposta fica comigo se você se atrasar, essa é uma das regras. Mas você não vai se atrasar, não é, meu rapaz?";
			link.l1 = "Claro, Giuseppe. Prepare-se para uma briga de garrafas!";
			link.l1.go = "drink_5";
		break;
		
		case "drink_5":
			dialog.text = "E você, e você, meu caro! Cara na mesa! Ha-ha!";
			link.l1 = "Te vejo na taverna às nove!";
			link.l1.go = "drink_6";
		break;
		
		case "drink_6":
			DialogExit();
			pchar.questTemp.LSC.Drink = "start";
			pchar.quest.LSC_DrinkOver.over = "yes"; //снять таймер
			pchar.quest.LSC_Drink.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink.win_condition.l1.date.hour  = 21.0;
			pchar.quest.LSC_Drink.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink.function = "LSC_DrinkPrepare";
			pchar.quest.LSC_Drink_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.hour  = 23.0;
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink_Over.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "2");
		break;
		
		case "drink_8":
			dialog.text = "Então, minha querida, pronta para beijar a mesa, hein? O bom Sancho já trouxe o rum pra gente. Não preciso te explicar as regras, né? São bem simples: a gente bebe da mesma garrafa até um de nós cair.\nSim, podemos conversar, devemos conversar! Falar com gente decente é uma maravilha, não acha? E se você ganhar, pode pedir seu prêmio ao Sancho. Preparada?";
			link.l1 = "Eu diria que sim. Vamos começar, Giuseppe!";
			link.l1.go = "drink_9";
		break;
		
		case "drink_9":
			DialogExit();
			pchar.questTemp.LSC.Drink = "go";
			pchar.quest.LSC_Drink_Over.over = "yes"; //снять таймер
			ChangeCharacterAddressGroup(pchar, "FleuronTavern", "quest", "sit1");
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
			ChangeCharacterAddressGroup(npchar, "FleuronTavern", "quest", "sit2");
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			DoQuestFunctionDelay("LSC_DrinkGo", 0.6);
		break;
		
		case "drunk":
			dialog.text = "Quinze homens no morto... hic! Aha! Io-ho-ho... E... garrafa...";
			link.l1 = "Glorioso...";
			link.l1.go = "exit";
			NextDiag.TempNode = "drunk";
		break;
		// <-- пей до дна
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
