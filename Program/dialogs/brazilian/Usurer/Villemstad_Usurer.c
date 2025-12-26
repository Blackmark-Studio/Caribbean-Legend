// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que perguntas você tem?","Como posso ajudá-lo?"),"Você tentou me fazer essa pergunta não faz muito tempo...","É, deixa eu adivinhar... Dando voltas de novo?","Ouça, eu cuido das finanças aqui, não respondo perguntas...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Umph, onde foi parar minha memória...","Você acertou, me desculpe...","Entendi...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Mynheer, tenho um assunto um tanto incomum. Sei que um corsário francês chamado Gaius Marchais lhe vendeu recentemente dois itens únicos: um ostensório de ouro e um turíbulo de ouro. Gostaria de comprá-los do senhor.";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(npchar, "quest.GOT_chest") && CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "Trouxe para você um pequeno baú de dobrões.";
                link.l1.go = "guardoftruth_3";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Ah, sim! Eu me lembro deles, claro! Eram mesmo itens originais e, mais importante, caros. Mas você chegou tarde demais, capitão, não os tenho mais. Já os vendi.";
			link.l1 = "Inacreditável! E quem se interessaria por objetos de igreja desse tipo? Senhor, para quem o senhor os vendeu? Gostaria de tentar comprá-los de volta...";
			link.l1.go = "guardoftruth_1";
			npchar.quest.utensil = "true";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Hm, e por que eu deveria te dar os nomes dos meus clientes?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "self_win")
			{
				link.l1 = "Talvez seja porque sou um bom amigo aos olhos do governador Matthias Beck, e posso pedir a ele a sanção adequada para você?";
				link.l1.go = "guardoftruth_2_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "holl_win")
				{
					link.l1 = "Talvez seja porque tenho excelentes relações com a Companhia Holandesa das Índias Ocidentais e já prestei grande ajuda a muitos colonos holandeses no arquipélago?";
					link.l1.go = "guardoftruth_2_2";
				}	
				else
				{
					link.l1 = "Talvez porque eu vou pagar por isso?";
					link.l1.go = "guardoftruth_2_3";
					npchar.quest.GOT_chest = "true";
				}
			}
		break;
		
		case "guardoftruth_2_1":
			dialog.text = "Ah, claro que está "+GetFullName(pchar)+", um amigo do próprio governador que desmascarou a conspiração criminosa de Lucas Rodenburg... Como eu poderia esquecer disso? Claro, vou lhe contar.";
			link.l1 = "Então, estou ouvindo.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_2":
			dialog.text = "Ah, certo, você está "+GetFullName(pchar)+", o grande conquistador do 'navio fantasma' dos piratas. Como eu poderia esquecer disso? Claro, vou te contar.";
			link.l1 = "Então, estou ouvindo.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_3":
			dialog.text = "Certo, então. Por um baú cheio até a tampa de dobrões de ouro, acho que posso te contar sobre aqueles que chegaram antes de você para comprar.";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "Aqui está. Esses itens são muito valiosos para mim...";
				link.l1.go = "guardoftruth_3";
			}
			else
			{
				link.l1 = "Tudo bem, vou trazer o que você pediu. São itens muito valiosos para mim...";
				link.l1.go = "exit";
			}
		break;
		
		case "guardoftruth_3":
			RemoveItems(pchar, "chest", 1);
			Log_Info("You've given a chest of doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Maravilha. Nesse caso, estou disposto a compartilhar algumas informações com você.";
			link.l1 = "Estou ouvindo.";
			link.l1.go = "guardoftruth_4";
			DeleteAttribute(npchar, "quest.GOT_chest");
		break;
		
		case "guardoftruth_4":
			dialog.text = "O turíbulo de ouro foi comprado por um homem chamado Rolande Moses, mais conhecido como Rollie o Cap. Não faço ideia por que esse açougueiro precisava de um objeto precioso da igreja, mas por algum motivo ele ficou indescritivelmente feliz com isso... Aliás, duvido que você chegue a encontrar o próprio Rollie.";
			link.l1 = "Por que isso?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Porque esse ávido saqueador de mercadores ingleses solitários recentemente navegou seu escuna direto para as garras do Coronel Fox. Sabe quem é esse? ";
			link.l1 = "Pode apostar! O comandante dos 'Sea Foxes' em St. John's, em Antígua...";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Então, você entende por que nunca mais veremos o pobre Rolande. O coronel tomou o saveiro dele com todos os sobreviventes da tripulação e os entregou em St. Jones, onde provavelmente já enforcaram todos eles.";
			link.l1 = "Entendi. E a custódia?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "O ostensório foi adquirido recentemente pela Senhora Belinda de Ribero, de Cumaná. Uma senhora muito notável, parente do próprio Fernando de Villegas, governador de Cumaná. Suponho que ela quisesse oferecê-lo como presente à igreja.";
			link.l1 = "Senhora Belinda de Ribero? Posso encontrá-la em Cumana, certo?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Com certeza. Ela mesma disse que iria direto para casa depois de Willemstad.";
			link.l1 = "Certo. Obrigado, "+npchar.name+", você foi de grande ajuda!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Sempre que quiser, senhor. Venha me visitar de vez em quando!";
			link.l1 = "Desejo a você clientes ricos, com bolsos cheios e cérebros vazios... Ha-ha!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			AddQuestRecord("Guardoftruth", "23");
			pchar.questTemp.Guardoftruth.Usurer = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
