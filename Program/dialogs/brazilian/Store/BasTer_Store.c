// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Pode falar, o que você deseja?","Acabamos de falar sobre isso. Você deve ter esquecido...","Essa é a terceira vez hoje que você faz essa pergunta...","Olha, aqui é uma loja. As pessoas vêm para comprar. Não me atrapalhe!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez na próxima vez.","Certo, por algum motivo eu esqueci...","Sim, realmente é a terceira vez...","Hm, eu não vou...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			//Jason --> ----------------------------------мини-квест Бесчестный конкурент------------------------------------
			if (CheckAttribute(pchar, "questTemp.Shadowtrader"))
			{
				if(pchar.questTemp.Shadowtrader == "begin" && GetNpcQuestPastDayParam(npchar, "Shadowtrader_date") < 5 && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Obrigado, Capitão, por atender ao meu pedido. Agora, quando "+pchar.questTemp.Shadowtrader.Guardername+" está aqui, pelo menos posso me sentir um pouco mais tranquilo.";
					link.l1 = "Hum... Não quero parecer intrometido, mas me parece que você está com algum problema. Pode me contar o que está acontecendo – talvez eu possa ajudar?"; 
					link.l1.go = "Shadowtrader_fort";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.Trouble") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "E então? Você entregou minha carta?";
					link.l1 = "Sim. O comandante respondeu verbalmente que as provas apresentadas na sua carta não são suficientes para que a guarda da cidade tome alguma providência."; 
					link.l1.go = "Shadowtrader_trouble";
					pchar.quest.ShadowtraderTimeFort_Over.over = "yes";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store" && CheckAttribute(pchar, "questTemp.Shadowtrader.EndFort"))
				{
					dialog.text = "I have already heard the news - tonight the guards discovered an illegal trading post run by smugglers and arrested them all. It was under the command of a rare piece of scum, but it's alright now; he won't be able to do harm to anyone else for a while.\nThe Commandant told me about your role in all of this, you have my gratitude! You have kept your word! Here, take the money - 15,000 pesos. You have saved me. Nothing threatens my business now!";
					link.l1 = "De nada. Foi fácil."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Escape") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Então, alguma novidade boa, "+pchar.name+"?";
					link.l1 = "Encontrei o seu rival. Ele não vai mais te incomodar – consegui convencê-lo... a deixar esta ilha. A 'loja' dele ficava numa casa perto dos portões da cidade. Agora cabe a você decidir o que fazer com a carga que foi abandonada. Pode entregá-la às autoridades ou tentar ficar com ela para si."; 
					link.l1.go = "Shadowtrader_Escape_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Free") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Já fiquei sabendo das notícias – esta noite os guardas descobriram um esconderijo de contrabandistas debaixo de uma das casas. Dois bandidos foram encontrados mortos. Excelente trabalho, "+pchar.name+", eu admiro você! Aqui, pegue sua recompensa - 15.000 pesos. Você acabou de me salvar! Agora sim, vou negociar de verdade!\nSatisfaça minha curiosidade - o líder deles... também estava entre os dois mortos?";
					link.l1 = "Não. Mas ele nunca mais vai aparecer na sua cidade. Acredito que, neste momento, ele já esteja a dezenas de milhas desta ilha."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Kill") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Já fiquei sabendo das novidades – ontem à noite os guardas descobriram uma loja secreta de contrabandistas em uma das casas. Três bandidos foram encontrados mortos. Excelente trabalho, "+pchar.name+", eu admiro você! Aqui, pegue sua recompensa - 15.000 pesos. Você acabou de me salvar! Agora sim vou negociar de verdade!\nSatisfaça minha curiosidade - o líder deles... também estava entre os dois mortos?";
					link.l1 = "Sim. Você se livrou do seu rival para sempre. Ele nunca mais vai te incomodar."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
			}
			//<-- мини-квест Бесчестный конкурент
		break;
		
		// --> мини-квест Бесчестный конкурент
		case "Shadowtrader_begin":
			pchar.questTemp.Shadowtrader = "true";
			pchar.questTemp.Shadowtrader_Block = true;
			pchar.questTemp.Shadowtrader.Guardername = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "Você poderia ir até a taverna e procurar um homem chamado "+pchar.questTemp.Shadowtrader.Guardername+" e diga para ele vir aqui o quanto antes? Eu não posso sair da loja, e esse idiota está na taverna enchendo a cara de rum, e com certeza nem vai lembrar de aparecer aqui, mesmo estando de serviço.";
			link.l1 = "Sempre fico feliz em ajudar, ainda mais porque eu já ia passar na taverna mesmo.";
			link.l1.go = "Shadowtrader_begin_1";
			link.l2 = "Está tirando sarro de mim? Por acaso pareço seu garoto de recados? A taverna fica a poucos passos daqui – você mesmo pode ir até lá.";
			link.l2.go = "exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		
		case "Shadowtrader_begin_1":
			dialog.text = "Obrigada! Por favor, diga para ele vir aqui agora mesmo. Ai, por que ele precisa ser tão incômodo...";
			link.l1 = "Não se preocupe. Vou mandá-lo até você.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.City = npchar.City;
			pchar.questTemp.Shadowtrader.nation = sti(npchar.nation);
			//создаем охранника
			sld = GetCharacter(NPC_GenerateCharacter("ShadowGuarder" , "officer_7", "man", "man", 10, sti(npchar.nation), 5, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "topor_2", "pistol3", "bullet", 50);
			sld.name = pchar.questTemp.Shadowtrader.Guardername;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\LineMiniQuests\ShadowTrader.c";
			sld.dialog.currentnode = "ShadowGuarder";
			sld.greeting = "pirat_common";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator(pchar.questTemp.Shadowtrader.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "sit", "sit_front1");
			SaveCurrentNpcQuestDateParam(npchar, "Shadowtrader_date");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Shadowtrader_fort":
			dialog.text = "Oh, capitão, eu realmente agradeceria muito a sua ajuda. Você poderia, por favor, entregar esta carta ao comandante o quanto antes? Eu lhe pagarei 300 moedas por essa tarefa simples – como já disse, não posso sair da minha loja.";
			link.l1 = "Sem problema. Me dê essa carta.";
			link.l1.go = "Shadowtrader_fort_1";
			link.l2 = "Não, meu bom homem, não tenho mais tempo para essas bobagens.";
			link.l2.go = "Shadowtrader_fort_end";
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fort_1":
			dialog.text = "Aqui está. Por favor, entregue a ele hoje e traga-me a resposta dele.";
			link.l1 = "Não se preocupe, eu cuido disso.";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1"); // 240912
			pchar.questTemp.Shadowtrader.Tradername = GetFullName(npchar);
			SetFunctionTimerCondition("ShadowtraderTimeFort_Over", 0, 0, 1, false);
			pchar.questTemp.Shadowtrader = "current"
			pchar.questTemp.Shadowtrader.Fort = "true";
			AddQuestRecord("Shadowtrader", "1");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
		break;
		
		case "Shadowtrader_fort_end":
			dialog.text = "Bem, pelo visto vou ter que perguntar para outra pessoa. Desculpe incomodar, capitão.";
			link.l1 = "Sem problemas. Até logo!";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_trouble":
			dialog.text = "Foi isso que ele disse? Que prova ele quer de mim, então?! O meu cadáver? Bem, logo vai ter um, se continuar desse jeito!..";
			link.l1 = "Ei, ei, "+npchar.name+", se acalme, ou vai acabar tendo um troço. Aqui, beba um pouco de água... Agora me diga, o que aconteceu – talvez eu possa te ajudar?";
			link.l1.go = "Shadowtrader_trouble_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Trouble");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_trouble_1":
			dialog.text = "Oh, capitão! Por favor, pegue seus 300 pesos – eu quase tinha me esquecido... Claro, vou lhe contar, mas não sei como você poderia me ajudar. Meu negócio está quase arruinado – tudo por causa daqueles malditos contrabandistas e daquele desgraçado desconhecido que os lidera.";
			link.l1 = "Contrabandistas?";
			link.l1.go = "Shadowtrader_trouble_2";
			AddMoneyToCharacter(pchar, 300);
		break;
		
		case "Shadowtrader_trouble_2":
			dialog.text = "É isso! Esses canalhas claramente decidiram me expulsar da cidade! Até então, tudo seguia como de costume – eles revendiam itens proibidos e, quando as patrulhas os pegavam, se escondiam ou subornavam os guardas. Mas agora, abriram uma loja em algum beco e começaram a vender os produtos mais procurados por preços absurdamente baixos!\nEu não posso me dar a esse luxo – na verdade, ainda tenho que pagar impostos – estou ficando cada vez mais pobre, e os marinheiros quase não querem mais meus produtos – compram tudo desses vigaristas.";
			link.l1 = "Mas você deveria ter recorrido às autoridades! Afinal, é função delas impedir esse tipo de desordem.";
			link.l1.go = "Shadowtrader_trouble_3";
		break;
		
		case "Shadowtrader_trouble_3":
			dialog.text = "Você viu o resultado do último apelo com seus próprios olhos. O governador está ocupado demais, e o comandante não acreditou que contrabandistas abriram lojas clandestinas, ou então finge não acreditar – e, pelo que vejo, é isso mesmo\nClaro, por que fariam isso? E eu digo: tenho certeza de que algum canalha querendo me arruinar e me expulsar da cidade inventou tudo isso, e depois vai tomar meu negócio na surdina para lavar as mãos sujas dele.";
			link.l1 = "Hm... sua opinião não é infundada. É da natureza dos comerciantes usar alguém como bode expiatório... Ah, me desculpe, não quis dizer você, é claro. ";
			link.l1.go = "Shadowtrader_trouble_4";
		break;
		
		case "Shadowtrader_trouble_4":
			dialog.text = "Ah, nada demais... Mas outro dia um sujeito mal-encarado apareceu aqui e teve a cara de pau de dizer que, se eu continuasse fazendo barulho, iam botar fogo na minha loja.\nEntão contratei um segurança. "+pchar.questTemp.Shadowtrader.Guardername+" não sai barato, mas ele é um profissional, e sob a proteção dele posso me sentir um pouco mais tranquilo.";
			link.l1 = "Entendo... Uma história desagradável, de fato. Pelo visto, você estava certo – não há nada que eu possa fazer por você. Ainda assim, tenho certeza de que as coisas vão se resolver – esses estabelecimentos duvidosos geralmente não duram muito. Bem, boa sorte!";
			link.l1.go = "Shadowtrader_end";
			link.l2 = "Entendi. Bem, talvez eu ainda possa te ajudar...";
			link.l2.go = "Shadowtrader_trouble_5";
		break;
		
		case "Shadowtrader_trouble_5":
			dialog.text = "Você está me oferecendo sua ajuda mesmo assim? Mas o que vai fazer?";
			link.l1 = "Vou tentar encontrar esse seu 'colega' e... convencê-lo a parar de te incomodar. Sabe, eu tenho certas habilidades quando se trata de persuadir pessoas.";
			link.l1.go = "Shadowtrader_trouble_6";
		break;
		
		case "Shadowtrader_trouble_6":
			dialog.text = "Está falando sério? Que o Senhor abençoe sua causa justa! Se você me livrar dessa escória, serei eternamente grato.";
			link.l1 = "Certo, combinado. Vou começar a procurar, então.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.seeksmugglers = "true";
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
			AddQuestRecord("Shadowtrader", "2");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddQuestUserData("Shadowtrader", "sSex1", GetSexPhrase("ся","ась"));
		break;
		
		case "Shadowtrader_end":
			pchar.questTemp.Shadowtrader = "true";
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DialogExit();
		break;
		
		case "Shadowtrader_Escape_complete":
			dialog.text = "É verdade? Agora posso negociar sem medo? Ah, muito obrigado! Aqui está sua recompensa - 15.000 pesos. Quanto às mercadorias na casa deles, acho melhor entregá-las ao comandante. Mais uma vez, obrigado!";
			link.l1 = "De nada. Não foi tão difícil. Eu disse que sou bom de persuasão.";
			link.l1.go = "Shadowtrader_complete";
		break;
		
		case "Shadowtrader_complete":
			dialog.text = "Venha me visitar de novo, capitão – será sempre um prazer recebê-lo.";
			link.l1 = "Claro! Agora, permita-me retirar – tenho coisas a fazer! Adeus, e boa sorte nos seus negócios, "+npchar.name+"!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.End");
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.Shadowtrader = "complete";
			AddQuestRecord("Shadowtrader", "11");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DeleteAttribute(pchar, "questTemp.Shadowtrader.EndFort");
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		//<-- мини-квест Бесчестный конкурент
	}
	UnloadSegment(NPChar.FileDialog2);
}
