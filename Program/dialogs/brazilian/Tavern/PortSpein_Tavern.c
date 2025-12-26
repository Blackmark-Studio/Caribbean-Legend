// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais perguntas você tem?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),"Você tentou me fazer uma pergunta há pouco tempo, "+GetAddress_Form(NPChar)+"...","Durante todo este dia, é a terceira vez que você faz essa pergunta...","Mais perguntas, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar minha memória...","Sim, realmente é a terceira vez...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin" && sti(pchar.money) >= 3000)
			{
				link.l1 = "Ouvi dizer que a tuberculose está se espalhando pelo seu forte. Você acha que a epidemia vai chegar à cidade?";
				link.l1.go = "Consumption";
			}
			if (CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.Commandant") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "O que você pode dizer sobre o comandante do forte?";
				link.l1.go = "Consumption_8";
			}
			if (!CheckAttribute(npchar, "quest.Consumption_1") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Me diga, o nome 'Juan' significa algo para você?";
				link.l1.go = "Consumption_12";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Escute, em abril de 1654 uma fragata atracou no seu porto sob o comando do Capitão Miguel Dichoso, e depois disso ele desapareceu. Tem algo que possa me contar sobre isso?";
				link.l1.go = "guardoftruth";
			}
			//--> Оковы Азарта
			if (CheckAttribute(pchar, "questTemp.OZ_Tavern_1"))
			{
				link.l2 = "Me conte, "+npchar.name+", quem é esse Javier Castillo?";
				link.l2.go = "OZ_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.OZ_Tavern_2"))
			{
				link.l2 = "Vamos voltar à conversa sobre o homem que pode influenciar o Javier.";
				link.l2.go = "OZ_Tavern_2_1";
			}
			//<-- Оковы Азарта

		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "O comandante diz que não há perigo. Quem fica curioso demais acaba trancado nas casamatas. Eu não sou um deles, desculpe.";
			link.l1 = "É mesmo? Uma taberneira sem vontade de ouvir rumores – isso é novidade! Quem sabe o tilintar de alguns pesos reacenda sua curiosidade?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "A prata é tentadora, claro, mas minha própria pele vale mais. Talvez eu possa lhe contar outra coisa, señor? Na verdade, sempre fico feliz em conversar, é só puxar assunto!";
			link.l1 = "Então é assim que a coisa se desenrola... Muito bem, aqui nesta bolsa tem três mil peças de oito e vamos bater um papo agradável sobre o tempo, combinado?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3000);
			dialog.text = "Oh, você é persistente, señor. Só lembre-se, essa conversa nunca aconteceu. (sussurrando) Tenho ouvido, vez após vez, já faz um ano inteiro, que pessoas estão definhando nas nossas prisões, morrendo de tuberculose. Você pode culpar as autoridades, pode culpar Deus, ou o Diabo, mas a maioria põe a culpa na má sorte. Essa maldita doença tira vidas tão rápido. Às vezes colocam um homem perfeitamente saudável lá dentro, e em uma ou duas semanas ele se vai. Assim, de repente...";
			link.l1 = "Mas que coisa... Um ano inteiro, é isso mesmo? E ninguém se mexeu pra resolver isso?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Who cares, señor? Who cares about prisoners? The scum of society - or so the great men in silk say. There was a physician who worked in the dungeons. Tried to heal those poor souls. He didn't last long; it seems the illness claimed him too.\nThe commandant doesn't let people in now, and our authorities pay no mind to such matters, especially when they have to pay less for prison rations.";
			link.l1 = "Interessante, mas o que há nessa doença que te assusta tanto a ponto de, trancados atrás de paredes seguras, estarmos sussurrando como freiras no confessionário?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "É difícil para mim te contar, mas teve um sujeito aqui. Ele foi preso por contrabando e ficou trancado por uns seis meses até que os amigos dele pagaram para tirá-lo de lá. Bem, você sabe—juntaram ouro para quem precisasse, pagaram o que foi pedido, e o sujeito saiu. Mas desde então ele ficou meio louco.";
			link.l1 = "Mais louco que um rato de porão?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Acho que sim. Ele ficou inútil para os companheiros depois disso, passando o dia inteiro aqui, bebendo até se destruir. Parecia que queria apagar algo da cabeça. Sempre que ficava bêbado, contava histórias sobre o tal consumo que leva as pessoas em silêncio\nEssas eram as palavras dele. Segundo ele, 'consumo' é a pior coisa que pode acontecer a um homem.";
			link.l1 = "Devaneios de um bêbado. E daí?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			if (CheckAttribute(pchar, "questTemp.Consumption.Commandant"))
			{
				dialog.text = "Nada, só sei que ele criou coragem com uns goles e começou a falar cada vez mais, até que, de repente, alguém cortou a garganta dele e jogou o corpo na sarjeta... quem fez isso e por quê, pra mim tanto faz.";
				link.l1 = "O que você pode dizer sobre o comandante?";
				link.l1.go = "Consumption_8";
			}
			else
			{
				dialog.text = "Nada, além do fato de que ele ficou corajoso, começou a falar cada vez mais e, de repente, alguém cortou sua garganta e jogou ele na sarjeta... e pra mim tanto faz quem fez isso ou por quê. (fala mais alto) Sim, as baías e recifes aqui são mesmo perigosos, senhor. Tem que tomar cuidado quando as tempestades vêm das Grandes Antilhas, se errar o vento, já era! Tenha um bom descanso, senhor, obrigado pela visita!";
				link.l1 = "Tempestades... certo. Obrigado, também.";
				link.l1.go = "Consumption_7";
			}
			pchar.questTemp.Consumption.Contra = "true";
		break;
		
		case "Consumption_7":
			DialogExit();
			npchar.quest.Consumption = "true";
			AddQuestRecord("Consumption", "2");
		break;
		
		case "Consumption_8":
			dialog.text = "O que posso dizer sobre ele? É coronel, chegou da Europa há alguns anos depois de receber esse cargo. Dizem que foi rebaixado no Velho Mundo por uns negócios suspeitos. Não sei se é verdade, mas no começo rolavam uns boatos. Mas quem é que não tem boatos a seu respeito, não é?";
			link.l1 = "Negócios sujos, é isso que você diz... Interessante. Mais alguma coisa?";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			dialog.text = "Bem, o que posso dizer... O coronel parece ser um homem profundamente preocupado com a própria segurança. É verdade, essas bandas não são seguras por causa de piratas, bandidos, índios e outros canalhas, mas o Senhor Comandante nunca sai de casa sem vários guarda-costas\nA mansão dele fica nesta cidade, e ele a transformou numa pequena fortaleza – os criados são bem armados e mantêm as janelas trancadas.";
			link.l1 = "Mas durante o dia ele trabalha na prisão, não é?";
			link.l1.go = "Consumption_10";
		break;
		
		case "Consumption_10":
			dialog.text = "Sim, mas aquela mansão basicamente está só esperando por uma emboscada ou invasão. De qualquer forma, o Señor Comandante aparentemente não volta lá com frequência — uma fortaleza de verdade é mais o estilo dele, he-he.";
			link.l1 = "Obrigado, você foi de grande ajuda. Até mais, "+npchar.name+"!";
			link.l1.go = "Consumption_11";
		break;
		
		case "Consumption_11":
			DialogExit();
			if (CheckAttribute(npchar, "quest.Consumption")) AddQuestRecord("Consumption", "4");
			else AddQuestRecord("Consumption", "5");
			DeleteAttribute(pchar, "questTemp.Consumption.Commandant");
			pchar.questTemp.Consumption = "current";
		break;
		
		case "Consumption_12":
			dialog.text = "Juan? Qual deles? Tem muitos por aqui, normalmente as pessoas têm sobrenome também... ou pelo menos um apelido...";
			link.l1 = "Eu estava pensando... Talvez o apelido dele seja 'Consumo', você já ouviu falar disso?";
			link.l1.go = "Consumption_13";
		break;
		
		case "Consumption_13":
			dialog.text = "Meu Deus, você vai falar disso de novo! Não, graças a Deus, não ouvi nada. Juro! Agora, vamos mudar de assunto. Por favor!";
			link.l1 = "Tá bom, tá bom, não precisa ter um troço...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption_1 = "true";
		break;
		//<-- Цена чахотки
		
		//--> Оковы Азарта
		case "OZ_Tavern_1":
			dialog.text = "Javier é um jogador de cartas, trapaceiro e vigarista. Vive rondando a taverna, sempre procurando alguém para arrancar uns pesos.";
			link.l1 = "Então, ele não foi visto em outros negócios suspeitos? Talvez ele tenha inimigos?";
			link.l1.go = "OZ_Tavern_2";
			DeleteAttribute(pchar, "questTemp.OZ_Tavern_1");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Tavern_2":
			dialog.text = "Bem, digamos apenas que ele tem bem menos amigos do que gente sonhando em torcer o pescoço dele. Mas se você quiser o nome de alguém que realmente pode influenciá-lo, isso vai te custar mil pesos. Pague – e eu conto tudo.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Certo, pegue seu dinheiro, seu velho agiota.";
				link.l1.go = "OZ_Tavern_3";
			}
			else
			{
				link.l1 = "Vamos voltar a essa conversa depois. Agora eu não tenho essa quantia.";
				link.l1.go = "exit";
				pchar.questTemp.OZ_Tavern_2 = true;
				AddLandQuestMark(npchar, "questmarkmain");
			}
		break;
		
		case "OZ_Tavern_2_1":
			dialog.text = "Capitão, trouxe os mil pesos?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Tenho sim. Pegue, seu velho agiota.";
				link.l1.go = "OZ_Tavern_3";
			}
			else
			{
				link.l1 = "Droga. Eu volto já.";
				link.l1.go = "exit";
			}
		break;
		
		case "OZ_Tavern_3":
			dialog.text = "Agora sim, isso já está melhor. Veja, o Javier não tem só dívidas de jogo. Um dia ele resolveu se aventurar no comércio de antiguidades, mas como você deve imaginar, não acabou bem pra ele. No começo até que as coisas foram razoavelmente bem, mas aí ele topou com uma chance de conseguir um certo item raro\nEle ficou tão empolgado com a ideia que saiu batendo em todas as portas de agiotas atrás de dinheiro. Naturalmente, ninguém deu uma moeda sequer. Então encontrou outro sujeito tão fissurado em antiguidades quanto ele e pegou emprestado cento e cinquenta mil pesos. O resto, acho que você já imagina\nEle foi passado pra trás, e agora essa dívida pesa no pescoço dele como uma pedra. Pagou só uns trocados, e pelo jeito, não pretende quitar o resto, mesmo com o credor já tendo contratado gente pra ameaçá-lo\nO homem a quem ele deve é Felipe Alarcon. A casa dele fica em frente ao banco – você vai reconhecer fácil, é uma mansão magnífica com colunas na entrada.";
			link.l1 = "Obrigado!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			DeleteAttribute(pchar, "questTemp.OZ_Tavern_2");
			AddDialogExitQuestFunction("OZ_Felip_1");
			DelLandQuestMark(npchar);
		break;
		//<-- Оковы Азарта
		
		case "guardoftruth":
			dialog.text = "Eu me lembro dele. Ele costumava passar aqui na minha taverna, mas não falava muito. Tomava umas doses de rum, trocava umas palavras baixas com alguns clientes e ia embora. Sempre sombrio e sério, como todo mundo daquele navio. Mercenários com cara de poucos amigos, sempre de olho e com as lâminas à mão. Diziam que o navio estava cheio de tesouros, mas eu não acredito nessas histórias. Carga valiosa nunca viaja sozinha, sem escolta. Eles ficaram aqui um dia e depois partiram. Ouvi dizer que foram para a Europa. É só isso que eu sei.";
			link.l1 = "Entendi. Bem, pelo menos é alguma coisa...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "40");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
