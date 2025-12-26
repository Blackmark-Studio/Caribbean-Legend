// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que deseja? Pode perguntar.","Estou ouvindo você, qual é a pergunta?"),"Esta é a segunda vez que você tenta perguntar...","Esta é a terceira vez que você tenta perguntar...","Quando isso vai acabar?! Sou um homem ocupado, cuidando dos assuntos da colônia, e você ainda está me importunando!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Agora não. Lugar e hora errados."),"Verdade... Mas depois, não agora...","Vou perguntar... Mas um pouco mais tarde...","Sinto muito, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_8")
			{
				link.l1 = "Excelência, gostaria de relatar atividades comerciais ilegais nesta ilha.";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_12")
			{
				link.l1 = "Gostaria de ouvir um relatório sobre sua missão em relação ao contrabando de velas de seda.";
                link.l1.go = "Mtraxx_4";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_10_continue" && !CheckAttribute(npchar, "quest.slaveships"))
			{
				link.l1 = "Cheguei em nome do Governador-Geral Phillipe de Poincy. Minha missão é entregar os escravizados capturados dos holandeses, está correto?";
                link.l1.go = "patria_Sl";
			}
			if (CheckAttribute(npchar, "quest.slaveships.wait") && GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000)
			{
				link.l1 = "Trouxe os escravos, conforme combinado.";
                link.l1.go = "patria_Sl_2";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_start" && CheckAttribute(pchar, "questTemp.Patria.Curacao.DoilyReady"))
			{
				link.l1 = "Cheguei sob as ordens do Governador-Geral Phillipe de Poincy para participar de uma expedição conjunta a Curaçao contra os holandeses.";
                link.l1.go = "patria_Sl_4";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_wait" && GetCompanionQuantity(pchar) < 3)
			{
				link.l1 = "Meu esquadrão foi reduzido, podemos partir agora.";
                link.l1.go = "patria_Sl_6";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "Interessante. Estou ouvindo.";
			link.l1 = "Recebi informações confiáveis de que uma brigantina holandesa, a 'Utrecht', sob bandeira inglesa, vem descarregando grandes quantidades de lona de seda na Baía de Portland há bastante tempo. Eles operam há mais de um ano, sempre à noite, entre os dias 10 e 15 de cada mês.";
			link.l1.go = "Mtraxx_1";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Tem certeza de que sua fonte é confiável?";
			link.l1 = "Às vezes nem confio em mim mesmo, porém o homem que revelou essa informação é confiável. Além disso, ele não tinha motivo para mentir.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
			string sTemp = "this";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
            dialog.text = "Muito bem, capitão. Trata-se de uma questão séria e devo agir com base nas informações apresentadas, mesmo que seu informante tenha mentido ou apenas se enganado. Enviarei uma patrulha costeira no horário especificado e, se suas informações forem confirmadas, você será generosamente recompensado. Atividades ilegais como essas devem ser severamente reprimidas.";
			link.l1 = "Eu vou te ver "+sTemp+" mês, no dia 16. A situação certamente se resolverá até lá.";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_11";
			int month = sti(pchar.questTemp.Mtraxx.month);
			pchar.quest.mtr_silk_smuggler.over = "yes";
			pchar.quest.mtr_silk_smuggler_over.over = "yes";
			DeleteQuestCondition("Mtraxx_SilkCreateSmuggler");
			DeleteQuestCondition("Mtraxx_SilkSmugglerFail");
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.hour  = 6;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.day   = 16;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.function = "Mtraxx_SilkSmugglerPatrol";
			sTemp = "this";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
			AddQuestRecord("Roger_2", "19");
			AddQuestUserData("Roger_2", "sDate", sTemp);
			if (CharacterIsAlive("Mtr_Utreht"))
			{
				sld = CharacterFromID("Mtr_Utreht");
				sld.lifeday = 0;
			}
		break;
		
		case "Mtraxx_4":
            dialog.text = "As suas informações estavam corretas, capitão. Nós emboscamos os criminosos durante a transação. O 'Utrecht' tentou escapar e resistiu, mas foi afundado pela nossa corveta de patrulha. Quatro compradores resistiram à prisão. Um foi morto a tiros, e os outros três fugiram para a selva. Toda a carga de 80 rolos de seda foi transferida para o tesouro de Port Royal. Embora não tenhamos conseguido identificar o chefe dessa rede, o morto permanece sem identificação e os demais escaparam, declaro esta operação um sucesso completo. Duvido que esses canalhas tenham coragem de voltar aqui algum dia.\nVocê nos prestou um grande serviço, capitão, sendo diligente e desmascarando os trapaceiros. Aqui estão 10.000 pesos como recompensa.";
			link.l1 = "Muito obrigado, Vossa Excelência. Fico satisfeito em ver que tudo saiu conforme o planejado e que os contrabandistas tiveram o que mereciam. Com isso, me despeço. Tenha um ótimo dia.";
			link.l1.go = "Mtraxx_5";
		break;
		
		case "Mtraxx_5":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_13";
			AddQuestRecord("Roger_2", "20");
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		// Jason НСО
		case "patria_Sl":
			if (GetSquadronGoods(pchar, GOOD_SLAVES) < 500)
			{
				dialog.text = "Exatamente. Quantos escravos você trouxe?";
				link.l1 = "Ainda estou trabalhando nisso. Em breve voltarei com os resultados.";
				link.l1.go = "patria_Sl_wait";
				break;
			}
			dialog.text = "Exatamente. Quantos escravos você trouxe?";
			link.l1 = ""+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000) link.l1.go = "patria_Sl_2";
			else link.l1.go = "patria_Sl_1";
		break;
		
		case "patria_Sl_wait":
			DialogExit();
			npchar.quest.slaveships.wait = "true";
		break;
		
		case "patria_Sl_1":
			dialog.text = "Hum, o Chevalier prometeu que não haveria menos de 3.000 escravos";
			link.l1 = "Está certo. A culpa é minha: alguns dos escravizados foram mortos pelo fogo de canhão de um navio inimigo, outros morreram no caminho. Vou corrigir meu erro e retornar para você. Tudo será feito conforme o contrato.";
			link.l1.go = "patria_Sl_wait";
		break;
		
		case "patria_Sl_2":
			DeleteAttribute(npchar, "quest.slaveships.wait");
			dialog.text = "Excelente! Com o Chevalier de Poincy, é possível realmente fazer negócios. Diga ao Governador-Geral que meu esquadrão para o ataque a Curaçao estará pronto em um mês. Tenho certeza de que ele vai enviá-lo a mim para essa campanha, então nos veremos em breve, Monsieur de Maure.";
			link.l1 = "Ficarei feliz em encontrá-lo novamente, Coronel. Agora, permita-me despedir-me.";
			link.l1.go = "patria_Sl_3";
		break;
		
		case "patria_Sl_3":
			DialogExit();
			npchar.quest.slaveships = "true";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, GetSquadronGoods(pchar, GOOD_SLAVES));
			AddQuestRecord("Patria", "57");
			pchar.questTemp.Patria = "epizode_10_return";
			pchar.quest.Patria_SlaveShipsJamaicaTimeOver.over = "yes"; //снять таймер на доставку рабов
			SetFunctionTimerCondition("Patria_CuracaoDoilyReady", 0, 0, 30, false); // таймер на 1 месяц на готовность эскадры д'Ойли
			SetFunctionTimerCondition("Patria_CuracaoTimeOver", 0, 0, 62, false); // таймер на 2 месяца на туда-обратно к Пуанси
			SaveCurrentQuestDateParam("questTemp.Patria.Curacao.Date"); // запоминаем дату
			// меняем отношение наций
			pchar.questTemp.Patria.Friend = "true";
			LaunchNationLegend();
			DeleteAttribute(pchar, "questTemp.Patria.Friend");
			DoQuestCheckDelay("sea_victory", 0.2);
		break;
		
		case "patria_Sl_4":
			dialog.text = "Eu não tinha dúvidas de que seria você. Melhor ainda! Nossa esquadra está pronta. Um navio de linha de primeira classe e dois de quarta classe. O tamanho máximo de toda a esquadra não deve ultrapassar cinco navios.";
			if (GetCompanionQuantity(pchar) > 2)
			{
				link.l1 = "Então vou deixar os navios extras no cais e ficar só com dois. No final, teremos cinco navios.";
				link.l1.go = "patria_Sl_5";
			}
			else
			{
				link.l1 = "Sim, exatamente cinco, e não mais. Devemos partir.";
				link.l1.go = "patria_Sl_6";
			}
		break;
		
		case "patria_Sl_5":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_wait";
		break;
		
		case "patria_Sl_6":
			dialog.text = "Perfeito. Agora vou explicar o plano pelo qual iremos agir: talvez você queira mudar ou acrescentar algo, e então discutiremos isso.";
			link.l1 = "Estou ouvindo, Coronel.";
			link.l1.go = "patria_Sl_7";
		break;
		
		case "patria_Sl_7":
			dialog.text = "Não faz sentido capturar Curaçao: é a principal colônia holandesa do arquipélago, e mesmo que tomemos o forte de Willemstad e hasteemos uma bandeira inglesa ou francesa, será muito difícil manter a ilha sob nosso controle. Os holandeses farão de tudo para recuperá-la e enviarão esquadras militares para atacá-la. No geral, não há razão para capturá-la, já que não é obrigatório. O mais importante para nós é forçar Stuyvesant a assinar o tratado em termos favoráveis para nós, e para isso basta destruir as principais defesas do inimigo e colocar os holandeses sob a ameaça de destruição completa da colônia de Willemstad.";
			link.l1 = "Sobre o que será o tratado?";
			link.l1.go = "patria_Sl_8";
		break;
		
		case "patria_Sl_8":
			dialog.text = "O tratado foi redigido por mim e pelo Chevalier de Poincy. Ele trata de vários aspectos do comércio, do fim da 'guerra comercial' entre a Companhia e a Inglaterra, da rejeição das reivindicações de Stuyvesant sobre a ilha de Sint Maarten, e de outros assuntos políticos que pouco lhe interessam.";
			link.l1 = "Entendido.";
			link.l1.go = "patria_Sl_9";
		break;
		
		case "patria_Sl_9":
			dialog.text = "Here's the plan: first, with all our forces, we'll attack the fort and destroy it. The Dutch will expect a landing of troops, but we won't do that; the greatest casualties are usually suffered when storming a bastion from the sea. Instead, we will land assault teams at two points on the island: Cape Santa Maria and the Blanca lagoon, and we will advance overland to the city gate of Willemstad. I have ordered that field artillery be brought with us on the ships – there are no impenetrable thickets in Curaçao, and we will be able to wheel the cannons across the ground without any difficulty. While the Dutch are left puzzled as to what is happening, we will take the town under our sights from the jungle and block any chance of reinforcements arriving from the fort by land. After that, we will bombard the town with cannon fire. Surely, the garrison of the fort will attempt a sortie, but they will be powerless against field cannons and our musketeers, and even if their cannons in the fort remain operational, they won't be able to bring them into the jungle. In addition, our ships will simulate preparations for a seaborne landing to strike fear into the enemy and sap their morale. After some time, when the Dutch fully realise the hopelessness of their situation, we will summon their parliamentarians for negotiations. What do you think, captain?";
			link.l1 = "Plano brilhante! E o melhor é que não vamos perder nenhum soldado junto às muralhas do forte.";
			link.l1.go = "patria_Sl_10";
		break;
		
		case "patria_Sl_10":
			dialog.text = "Fico feliz que tenha gostado das minhas ideias. Vamos seguir em frente então!";
			link.l1 = "Vamos!";
			link.l1.go = "patria_Sl_11";
		break;
		
		case "patria_Sl_11":
			DialogExit();
			chrDisableReloadToLocation = true;
			pchar.questTemp.Patria = "epizode_11_continue";
			AddQuestRecord("Patria", "60");
			pchar.quest.Patria_CuracaoTimeOver.over = "yes"; // снять таймер 2 месяца
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "PortRoyal_townhall", "goto", "goto4");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 7.0);
			Patria_CuracaoSail();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
