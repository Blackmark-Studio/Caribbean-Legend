// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que perguntas você tem?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),"Você tentou me fazer uma pergunta há pouco tempo, "+GetAddress_Form(NPChar)+"...","No decorrer deste dia inteiro, esta é a terceira vez que você toca nesse assunto...","Mais perguntas, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar minha memória...","Sim, é mesmo a terceira vez...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(PChar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesorotavern")
			{
				link.l1 = "Escute, "+npchar.name+", você ouviu algo sobre um homem chamado Miguel Dichoso? Dizem que o navio dele foi visto nas águas da Isla Tesoro...";
				link.l1.go = "guardoftruth";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Escute, "+npchar.name+", você não viu o Miguel Dichoso por Isla Tesoro ultimamente?";
				link.l1.go = "tieyasal";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Sim, já ouvi. Aquele fidalgo espanhol vendeu ao Shark Dodson um navio extraordinário, uma fragata, quando ainda morava aqui. Ah, aquele navio... Era incrível...";
			link.l1 = "Deixe-me adivinhar: ela tinha um casco moderno, elegante, e conseguia chegar a dezesseis nós? E o nome dela era 'Santa Quitaria'?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Quanto à estrutura e à velocidade, você está certíssimo, mas ela tinha outro nome: 'San Martin'. O Tubarão pagou uma fortuna em ouro para aquele canalha por esse navio.";
			link.l1 = "Tem certeza de que era 'San Martin' e não 'Santa Quiteria'? Quando foi que ele comprou? E por que você chamou o Dichoso de canalha?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Malditos sejam meus olhos, tenho certeza absoluta de que era o 'San Martin', porque eu mesmo vi os homens do Alexus arrancando uma placa com aquelas bobagens papistas da popa. Shark Dodson a rebatizou de 'Fortuna', um nome muito mais digno para uma beleza dessas. (cospe) Ele comprou o navio no inverno de 54, pouco antes do Blaze ser assassinado. Por que chamei Don Miguel de canalha? Porque ele roubou a droga do navio da marinha espanhola em Providence! Dodson armou um espetáculo de fogo e fumaça para o forte de San Juan e sua guarnição, como ele sempre me contava quando estava bêbado. O Shark sacrificou dois luggers avariados para fazer a luta com a fragata parecer real. Quando anoiteceu, ele levou o 'San Martin' em segredo para Isla Tesoro. O Shark ficou com o navio e o Dichoso ficou com o dinheiro. O safado depois disse aos superiores que a fragata tinha afundado durante a luta com a frota pirata, e o comandante do forte de San Juan confirmou a história.";
			link.l1 = "Ah, como esses fidalgos espanhóis enchem os bolsos! Que espertalhão! Me diga, você tem certeza de que isso aconteceu no inverno de 1654? Não poderia ter sido na primavera? E aquele navio não mostrava sinais de desgaste da tempestade?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Tenho quase certeza de que era inverno... Ah, vai saber. Talvez fosse primavera. Não lembro direito. Provavelmente eu estava bêbado. A fragata não tinha nenhum sinal de desgaste, estava novinha em folha.";
			link.l1 = "E onde está agora aquela bela fragata?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "É uma história sombria... Quando Blaze foi assassinado, todos suspeitaram do Shark porque o colar dele, um dente de tubarão, foi encontrado no corpo. Além disso, algumas pessoas viram o Shark na casa do Blaze naquela noite\nShark fugiu de Isla Tesoro antes que lhe dessem a marca negra. Ele procurou o Pastor Sombrio e trocou sua fragata por uma brigue. Ninguém sabe onde ele está agora. Zachary vendeu a fragata para William Paterson depois.";
			link.l1 = "Quem é esse Paterson?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "O quê, você nunca ouviu falar do Willie Paterson? Ele é um escocês, acabou de chegar ao Caribe. Se acha capitão da frota real, o queridinho do Coronel Fox! Aliás, começou a fazer uns negócios com o Jackman também. O navio principal do Paterson é o próprio 'Fortune'.";
			link.l1 = "Entendi. Você sabe onde o Dichoso está agora?";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Não faço ideia. Depois daquela confusão com a 'Fortuna', não vi mais ele na Isla Tesoro e também não ouvi mais nada sobre ele.";
			link.l1 = "Tudo bem, "+npchar.name+", obrigado pelas informações detalhadas! Você é um excelente dono de taverna! Queria que houvesse mais pessoas como você... Tchau!";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Boa sorte, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60_1");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "Parece que vocês dois estão se perseguindo, hein. Sim, Dichoso esteve aqui, bem onde você está agora. E do mesmo jeito, ele perguntou de você da última vez que você esteve em Sharptown.";
			link.l1 = "Droga! Essa é a notícia... E onde está o Miguel agora?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Não faço ideia. Ele foi para o mar onde... mencionou algo sobre Blueweld. Provavelmente foi até lá só para te encontrar.";
			link.l1 = "Foi você quem o mandou para Blueweld?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Não. Só disse a ele que fazia muito tempo que eu não te via.";
			link.l1 = "Entendi. Certo, então. Valeu, amigo!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			AddQuestRecord("Tieyasal", "3");
			npchar.quest.tieyasal = "true";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
