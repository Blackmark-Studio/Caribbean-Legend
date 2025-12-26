void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "O que você quer?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		case "Alonso":
			NextDiag.TempNode = "Alonso";
			
			// --> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "...";
				Link.l1 = "Alonso, preciso falar com você.";
				Link.l1.go = "SharlieEpilog_Alonso_1";
				break;
			}
			// эпилог <--
			
			if (GetDLCenabled(DLC_APPID_1))
			{
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FirstStage", "ready"))
				{
					dialog.text = "Permissão para falar, capitão?";
					link.l1 = "Até mais, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Pode ir em frente.";
					link.l2.go = "Alonso_1";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.SecondStage", "ready"))
				{
					dialog.text = "Permissão para falar, capitão?";
					link.l1 = "Até mais, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Pode ir em frente.";
					link.l2.go = "Alonso_Lvl_8_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.ThirdStage", "ready"))
				{
					dialog.text = "Permissão para falar, capitão?";
					link.l1 = "Até mais, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Pode ir em frente.";
					link.l2.go = "Alonso_Lvl_12_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FourthStage", "ready"))
				{
					dialog.text = "Permissão para falar, capitão?";
					link.l1 = "Até mais, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Pode ir em frente.";
					link.l2.go = "Alonso_Lvl_16_Start";
					break;
				}
			}
			
			dialog.text = " Nada a relatar, capitão.";
			link.l1 = "Pode continuar, Alonso.";
			link.l1.go = "exit";
		break;
		
		case "Alonso_1":
			DelLandQuestMark(npchar);
			dialog.text = "Como você está aguentando?";
			link.l1 = "O que você quer dizer?";
			link.l1.go = "Alonso_2";
		break;
		
		// Основная развилка стадии 1
        case "Alonso_2":
            dialog.text = "Você já navega por essas águas do Caribe há meses, enquanto alguns não aguentam nem uma semana por aqui. A tripulação te respeita, isso é certo, mas eu? Me preocupo com o que te espera pela frente.\n"+"Compartilhe seus pensamentos com a gente, capitão. Faça esse favor pra tripulação. Onde está o "+pchar.ship.name+" indo?";
                          
            link.l1 = "Não tenho um plano. Quero primeiro entender o terreno. A aventura vai nos encontrar sozinha.";
            link.l1.go = "Alonso_Choice_1";
            
            link.l2 = "Essas águas estão cheias de predadores, Alonso. E o "+pchar.ship.name+" é o menor deles. Por enquanto.";
            link.l2.go = "Alonso_Choice_2";
            
            link.l3 = "Eu gosto de ganhar dinheiro. De preferência de forma legal. Mas vamos ver como isso vai ser.";
            link.l3.go = "Alonso_Choice_3";
			
            if (!SandBoxMode)
            {
                link.l4 = "Você conhece a história. Depois daquela conversa memorável no Ulysses, tudo só ficou mais complicado...";
                link.l4.go = "Alonso_Choice_4";
            }
        break;
        
        case "Alonso_Choice_1":
            dialog.text = "Isso é que é liberdade! Só não esqueça de guardar o suficiente para manter o navio e deixar algo no cofre para os dias difíceis.\n"+"Seja qual for o seu humor, missão ou mapa do tesouro, aceite transportar passageiros, cargas, qualquer trabalho que aparecer pelo caminho.\n"+"Não faz mal arriscar um pouco no comércio também – compre barato onde for fácil ver, venda onde conseguir.\n"+"E se você avistar um navio mercante solitário pelo caminho... Heh. Como você disse, capitão. A aventura vai nos encontrar, com certeza.";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50);
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            
            link.l1 = "Obrigado pelo bom conselho, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_2":
            dialog.text = "Negócio lucrativo, se o seu navio aguentar. Encontre os mercadores solitários e mostre a eles o verdadeiro significado de 'economizar no centavo, perder na libra'.\n"+"Infelizmente para você, tem outro ditado que entra em cena: 'A verdade sempre aparece.' Sempre tem algum linguarudo na tripulação que vai contar sobre suas façanhas no primeiro porto que aparecer.\n"+"Então ou você rouba um pouco de todo mundo, ou escolhe uma bandeira inimiga para a vida toda.\n"+"Talvez eu esteja me adiantando. Se as coisas apertarem de verdade, tem um advogado em Port Royal que resolve tudo com as autoridades pelo preço certo. Pode chamar de imposto da pirataria, heh-heh!";
            
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", -1);
            
            link.l1 = "Obrigado pelo bom conselho, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_3":
            dialog.text = "Olha, não posso te ajudar muito com isso, capitão. Você vai precisar de um navio mercante de verdade – uma barquentina, ou melhor ainda, uma barca. Provavelmente vou me arrepender de dizer isso, mas é melhor instalar canhões mais leves ou até abrir mão da artilharia de vez.\n"+"Pegue contratos de carga com os donos das lojas, faça comércio por conta própria pelo caminho e transporte passageiros.\n"+"Quando juntar dinheiro suficiente, invista em lojas e bancos. Pode acreditar, capitão – um dia seu dinheiro vai começar a render, e você vai poder comprar um navio de verdade com umas centenas de homens a bordo.\n"+"Aliás, quem vai pagar por isso é a sua empresa, não você.";
            
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            AddCharacterExpToSkill(pchar, SKILL_SAILING, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "Obrigado pelo bom conselho, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_4":
            dialog.text = "Eu vejo de outro jeito, capitão. No Ulysses você era só um passageiro – essas pobres almas não têm controle sobre o próprio destino. Agora você é um capitão que conquistou seu chapéu, o que significa que pode resolver qualquer problema. Já te disse antes – não existe posição mais alta no nosso mundo.\n"+"Meu instinto diz que essa história com seu irmão ainda vai se arrastar por anos, então cuide de você primeiro. Monsieur Michel não vai a lugar nenhum, heh-heh...\n"+"Você não é o único com problemas no Caribe. É a hora perfeita para ajudar os outros enquanto ganha dinheiro, equipamentos e contatos. Você vai aprender tudo o que precisa para esse negócio de família pelo caminho...";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 100);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "Obrigado pelo bom conselho, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
		
        case "Alonso_Common_End":
            dialog.text = "Não se prenda a um só papel, capitão. Faça o que quiser, quando quiser. Pegue tudo e não devolva nada. Você vai se sair muito bem.";
            link.l1 = "E obrigado pela sabedoria também.";
            link.l1.go = "Alonso_Common_End_2";
        break;
        
        case "Alonso_Common_End_2":
            dialog.text = "É pra isso que você me paga, capitão. Acha mesmo que a tripulação obedece suas ordens só por causa do salário miserável?\n"+"Dezenas de homens espremidos em espaços apertados, sem saber quando vão ver terra de novo, ou se vão ver algum dia. E afundar um navio? Fácil demais.";
            link.l1 = "Sim, sim, já ouvi esse discurso antes, Alonso. O que você estava dizendo sobre navios?";
            link.l1.go = "Alonso_Common_End_3";
        break;
        
        case "Alonso_Common_End_3":
            dialog.text = "Heh! Um navio é uma prisão, um acampamento militar e um mosteiro, tudo ao mesmo tempo. É um monte de homens juntos, no fim das contas. Então, os problemas se resolvem ou na conversa, ou na base do chicote. No seu caso, heh-heh, a segunda opção não rola, então achei melhor a gente bater um papo. Pra facilitar sua vida, entende.";
            link.l1 = "Você já esteve preso alguma vez? No exército? Ou num mosteiro, Deus me livre? Pensando bem, Alonso, me conte sobre você. Mal sei alguma coisa a seu respeito.";
            link.l1.go = "Alonso_Story_1";
        break;
        
        // История Алонсо
        case "Alonso_Story_1":
            dialog.text = "Bem, mosteiros eu sempre evitei, não vou mentir. Mas já servi na Santa Inquisição uma vez...";
            link.l1 = "Como diabos isso aconteceu?";
            link.l1.go = "Alonso_Story_2";
        break;
        
        case "Alonso_Story_2":
            dialog.text = "Oh! Foi assim. Eu estava fazendo minha parte como mercenário na guerra europeia. Só Deus sabe como aquilo começou ou quem lutava contra quem. Tudo que sabíamos era que a guerra já durava trinta anos e quais comandantes pagavam mais ou menos em dia. Agora, isso sim foi uma aventura!\n"+"Isso foi em 42... ou teria sido em 41? Não importa. Duas companhias, ambas a serviço do Imperador, se encontraram numa floresta. Na neblina. E começaram a se massacrar! Três dias de carnificina!";
            link.l1 = "Como isso é possível?";
            link.l1.go = "Alonso_Story_3";
        break;
        
        case "Alonso_Story_3":
            dialog.text = "Tenta distinguir amigo de inimigo naquela neblina. Além disso, já faziam três meses que não recebíamos, então todo mundo só pensava em saque.\n"+"Matamos metade uns dos outros. Quando percebemos, já era tarde demais. Foi aí que conheci esse moscovita. Grande como um urso, mas com um coração de ouro!";
            link.l1 = "O que aconteceu depois?";
            link.l1.go = "Alonso_Story_4";
        break;
        
        case "Alonso_Story_4":
            dialog.text = "Você sabe como é na guerra? O primeiro a dar a notícia vira herói. Então pensamos – por que não transformar esse desastre em vantagem pra gente!\n"+"Juntei os rapazes, fomos até o pagador, contamos sobre uma 'batalha gloriosa.' Os salários dos mortos foram cortados, os sobreviventes receberam, eu e meu amigo ganhamos um extra, e o comandante ficou com a parte dele.";
            link.l1 = "Então você é rico, Alonso.";
            link.l1.go = "Alonso_Story_5";
        break;
        
        case "Alonso_Story_5":
            dialog.text = "Ha! Passamos uma semana bebendo vinho e jogando cartas. Por sorte, meu novo amigo da gelada Moscóvia tinha uma queda por bugigangas raras, senão eu teria acabado na prisão dos devedores. Comprou um troféu meu – uma pistola magnífica de três canos, e por um preço justo também. Não se aproveitou da minha má sorte.";
            link.l1 = "É uma bela história, Alonso. Parece até que você acabou de inventar isso.";
            link.l1.go = "Alonso_Gift";
        break;
        
        // Вручение подарка
        case "Alonso_Gift":
            dialog.text = "Você me magoa, capitão. Aqui, aceite este pequeno presente.";
            link.l1 = "O que foi?";
            link.l1.go = "Alonso_Gift_2";
        break;
        
        case "Alonso_Gift_2":
            // Выдаем Берендейку
            GiveItem2Character(pchar, "talisman20");
			SetAlchemyRecipeKnown("talisman20");
            
            dialog.text = "Um bandoleiro para combate de mosquete. Todo mundo usa isso na terra do meu amigo moscovita. Ou pelo menos foi o que ele disse.\n"+"Que isso lhe seja útil, capitão. Considere como um presente da tripulação.";
            link.l1 = "Inesperado! Obrigado, Alonso. E quanto àquele serviço na Inquisição?";
            link.l1.go = "Alonso_Escape";
        break;
        
        case "Alonso_Escape":
            PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Ah...\n"+"Os sinos estão tocando, capitão! Hora de voltar ao trabalho. Continuamos outra hora.";
            link.l1 = "Com certeza vamos continuar essa conversa. Obrigado pelo presente!";
            link.l1.go = "exit";
            
			AddDialogExitQuestFunction("LoyaltyPack_FirstStage_DlgExit");
        break;
		
		// (Level 8) - Continuing the story
        case "Alonso_Lvl_8_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Você conquistou muito desde a última vez que conversamos, e ninguém - nem a tripulação, nem eu - duvida mais dos seus talentos.";
			link.l1 = "Havia dúvidas?";
			link.l1.go = "Alonso_Lvl_8_1";
        break;

        case "Alonso_Lvl_8_1":
            dialog.text = "Claro que havia. Somos gente simples – sempre nos preparamos para o pior. Aproveite sua liberdade, capitão. Continue assim e vai conhecer um outro lado do Caribe.";
            link.l1 = "Que bom ouvir isso. Agora me conte sobre seu tempo na Inquisição. Da última vez, você começou com uma história do exército e terminou nela também.";
            link.l1.go = "Alonso_Lvl_8_2";
        break;

        case "Alonso_Lvl_8_2":
            dialog.text = "O que eu posso dizer? Depois daquele massacre sem sentido, mas muito lucrativo, na floresta, eu e o Moscovita ficamos parceiros de verdade e armamos mais alguns esquemas juntos.\n"+"Eu me lembro de quando decidimos atacar um comboio de suprimentos imperial. Os batedores disseram que estavam transportando troféus, ouro, armas...";
            link.l1 = "Então, conseguiu fazer?";
            link.l1.go = "Alonso_Lvl_8_3";
        break;

        case "Alonso_Lvl_8_3":
            dialog.text = "Foi fácil demais. Atacamos pelos dois lados, espantamos os guardas, abrimos as carroças – e o que achamos? Repolho! Repolho podre e fedorento pra alguma guarnição! Mas quer saber? A gente não comia fazia uma semana, então até isso nos deixou felizes!";
            link.l1 = "Como se a comida no meu navio fosse muito melhor.";
            link.l1.go = "Alonso_Lvl_8_4";
        break;

        case "Alonso_Lvl_8_4":
            dialog.text = "Bem, agora já me acostumei. Mas naquela época... Depois de uma semana procurando comida, você roía até a casca das árvores!\n"+"Mas meu amigo não desanimou. Tirou uma garrafa da sua bebida especial – receita moscovita, segundo ele. Ninguém se importou com o que era, desde que não fosse vinagre! Depois de uns goles, até aquele repolho parecia um banquete!";
            link.l1 = "Nojento.";
            link.l1.go = "Alonso_Lvl_8_5";
        break;

        case "Alonso_Lvl_8_5":
            dialog.text = "O que é nojento é o estado dos nossos barris de água, mas aquela aguardente moscovita salvou minha vida naquele dia.";
            link.l1 = "Como assim?";
            link.l1.go = "Alonso_Lvl_8_6";
        break;

        case "Alonso_Lvl_8_6":
            dialog.text = "Ficamos completamente bêbados ali mesmo, na lama da estrada, com repolho boiando ao nosso redor. Bem, uma coisa levou à outra, e acabei discutindo com um nobre. Um alemão, todo certinho e cheio de frescura. Se achava bom demais pra beber com a gente, só ficou lá limpando o mosquete e soltando comentários sarcásticos.\n"+"Então lá estamos nós, afogando as mágoas comendo repolho. E ele começa a nos dar uma lição sobre sabedoria militar. Diz que nossas espadas e lanças de confiança logo serão esquecidas, mas a baioneta — ah, essa sim é o futuro e a chave de tudo.\n"+"Então eu discuti com ele, e de alguma forma acabamos concordando em lutar até a morte – com baionetas, veja só. Nem me pergunte como isso aconteceu, eu mesmo não lembro.\n"+"Mas só havia duas baionetas em toda a nossa companhia. Uma era daquele oficialzinho, a outra do Fox, um inglês. Peguei o fuzil dele emprestado e matei o alemão a golpes, depois tratei de sumir.";
            link.l1 = "Mas você estava com fome e bêbado.";
            link.l1.go = "Alonso_Lvl_8_7";
        break;

        case "Alonso_Lvl_8_7":
            dialog.text = "Depois descobri que a bebida do meu amigo realmente deixa a mão firme quando você está balançando um mosquete pesado. Então agora estou mais inclinado a concordar com as ideias do alemão morto.";
            link.l1 = "E como isso se relaciona com o seu serviço na Inquisição?";
            link.l1.go = "Alonso_Lvl_8_Gift";
        break;

        case "Alonso_Lvl_8_Gift":
            dialog.text = "Você não acredita em mim de novo, capitão! Aqui, pega isso.";
            link.l1 = "Uma garrafa e um pedaço de papel?";
            link.l1.go = "Alonso_Lvl_8_Gift_2";
        break;

        case "Alonso_Lvl_8_Gift_2":
            // Даём игроку настойку и рецепт
            GiveItem2Character(pchar, "vodka");
            SetAlchemyRecipeKnown("vodka");

            dialog.text = "Essa é a bebida de que eu te falei. E aqui está a receita. Vai que você acaba gostando, heh-heh.";
            link.l1 = "Desculpe, meu amigo, mas rabiscos e alguma mistura duvidosa não...";
            link.l1.go = "Alonso_Lvl_8_Gift_3";
        break;

        case "Alonso_Lvl_8_Gift_3":
            // Даём игроку мушкет с багинетом
            GiveItem2Character(pchar, "mushket10");

            dialog.text = "Tá bom, tá bom, capitão. Eu ia te dar isso de qualquer jeito. Esse tipo de arma não combina comigo, mas vai ser útil pra você. Baionetas são raridade por aqui. Mas depois que aprender a usar uma, vai até esquecer de sabre.";
            link.l1 = "Espera, esse é mesmo o mosquete daquele oficial imperial? Aquele que você matou?";
            link.l1.go = "Alonso_Lvl_8_Gift_4";
        break;

        case "Alonso_Lvl_8_Gift_4":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "O próprio. Como pode ver, eu disse a verdade, capitão.";
            link.l1 = "Mas não foi isso que eu perguntei.";
            link.l1.go = "Alonso_Lvl_8_Escape";
        break;

        case "Alonso_Lvl_8_Escape":
            dialog.text = "Os sinos estão tocando, capitão! Hora de voltar ao trabalho. Continuamos outra hora.";
            link.l1 = "Com certeza vamos continuar essa conversa. Obrigado pelo mosquete!";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_SecondStage_DlgExit");
        break;

        // (Уровень 12)
        case "Alonso_Lvl_12_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Capitão, sobre os novos recrutas...";
			link.l1 = "Aconteceu alguma coisa?";
			link.l1.go = "Alonso_Lvl_12_1";
        break;

        case "Alonso_Lvl_12_1":
            dialog.text = "Queria informar que, na missa desta noite, um dos recrutas disse que queria embarcar especificamente no seu navio.";
            link.l1 = "E o que exatamente isso quer dizer?";
            link.l1.go = "Alonso_Lvl_12_2";
        break;

        case "Alonso_Lvl_12_2":
            dialog.text = "Logo pode haver mais como ele. Agora você tem um nome, capitão.";
            link.l1 = "Engraçado que até agora eu não sei o que está por trás do seu nome. Você nunca terminou aquela história sobre a Inquisição.";
            link.l1.go = "Alonso_Lvl_12_3";
        break;

        case "Alonso_Lvl_12_3":
            dialog.text = "Ah, onde eu estava... Isso! Então decidimos seguir carreira como fornecedores militares. A guerra estava chegando ao fim, era preciso pensar no futuro. E a cabeça do meu amigo sempre fervilhava de ideias sobre o que viria pela frente.";
            link.l1 = "Isso sim é uma virada na vida. Não faz muito tempo você estava se embriagando ao lado de uma carroça saqueada cheia de repolho.";
            link.l1.go = "Alonso_Lvl_12_4";
        break;

        case "Alonso_Lvl_12_4":
            dialog.text = "Espera, fica ainda melhor. Recebemos uma encomenda de cem capacetes para um regimento. E ainda adiantaram uma bela quantia. Então a gente comemorou... Jogamos cartas e tudo mais.\n"+"Acorda de manhã --- o dinheiro sumiu, o exército parte em dois dias, e ainda temos cem capacetes para entregar!";
            link.l1 = "E então, o que você fez?";
            link.l1.go = "Alonso_Lvl_12_5";
        break;

        case "Alonso_Lvl_12_5":
            dialog.text = "Fui até o campo de batalha fresco, juntei chapéus dos mortos. Depois preguei pedaços de metal, coloquei placas... Ficou ridículo, mas funcionou! Com certeza podia te salvar de um golpe de sabre. Bom, pelo menos uma vez, né. Tão bom quanto qualquer elmo, não acha?!";
            link.l1 = "O intendente reconheceu a sua engenhosidade?";
            link.l1.go = "Alonso_Lvl_12_6";
        break;

        case "Alonso_Lvl_12_6":
            dialog.text = "Nos mandaram para o tribunal por desvio de dinheiro e fraude. Mas sabe de uma coisa? Depois ficamos sabendo que aqueles chapéus salvaram vidas mais de uma vez. E as nossas também, no fim das contas.";
            link.l1 = "Como assim?";
            link.l1.go = "Alonso_Lvl_12_7";
        break;

        case "Alonso_Lvl_12_7":
            dialog.text = "Bem, nós dois fomos jogados na prisão. E nossa companhia foi mandada para uma missão. Não sei onde nem contra quem, e provavelmente eles também não sabiam. Nunca mais voltaram.\n"+"... "+"Desculpe, capitão. Vamos continuar outra hora. Pegue este chapéu e as instruções. Fiz ontem pra te animar... Mas só acabei me deixando triste à toa.";
            link.l1 = "Claro, Alonso. Obrigado pelo presente.";
            link.l1.go = "Alonso_Lvl_12_Gift";
        break;

        case "Alonso_Lvl_12_Gift":
            // Даём игроку шляпу
            GiveItem2Character(pchar, "hat10");
            SetAlchemyRecipeKnown("Hat10");

            DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_ThirdStage_DlgExit");
        break;

        // (Уровень 16) - Финальный
        case "Alonso_Lvl_16_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Capitão, só queria avisar que sua tripulação está sendo tratada como realeza nas tavernas e bordéis agora. Servir sob sua bandeira tem peso hoje em dia!";
			link.l1 = "Obrigado, Alonso... Pena que eu mesmo ainda não estou vendo muito desse tratamento real.";
			link.l1.go = "Alonso_Lvl_16_1";
        break;

        case "Alonso_Lvl_16_1":
            dialog.text = "Logo você vai saber. O Caribe é como uma torta dividida entre algumas dezenas de capitães. Em breve, você vai ter seu lugar à mesa e pegar a sua fatia.\n"+"E quem sabe? Talvez você seja a lenda do Caribe que leva tudo para si.";
            link.l1 = "Então, vai terminar sua história? Paramos quando você foi jogado na prisão.";
            link.l1.go = "Alonso_Lvl_16_2";
        break;

        case "Alonso_Lvl_16_2":
            dialog.text = "Ha! O caso dos grandes ladrões de chapéu. Um moscovita e um português numa cela minúscula em algum lugar da Flandres. Esperando a sentença. Enforcamento, claro.\n"+"Um cavalheiro importante nos salvou – era um embaixador moscovita! Velho amigo do Fadey. Estava de passagem, soube do nosso aperto e comprou nossa liberdade!";
            link.l1 = "Fadey? O Fadey? E você ficou quieto sobre isso?!";
            link.l1.go = "Alonso_Lvl_16_3";
        break;

        case "Alonso_Lvl_16_3":
            dialog.text = "É isso mesmo. Foi aí que nos separamos – ele voltou para Moscou, talvez para lutar contra os poloneses ou resolver algum grande negócio. Eu fiquei mais um tempo na velha terra, e agora estou aqui.";
            link.l1 = "Impressionante, Alonso. Todo esse tempo e você conseguiu me contar tudo, menos sobre você mesmo. Engraçado como um sujeito esperto como você deixou escapar algo sobre a Inquisição.";
            link.l1.go = "Alonso_Lvl_16_4";
        break;

        case "Alonso_Lvl_16_4":
            dialog.text = "E eu te disse a mais pura verdade, capitão! Se não acredita em mim, pergunte ao próprio Fadey. Não é difícil encontrá-lo em Basse-Terre.";
            link.l1 = "Talvez eu aceite. Então, cadê meu presente?";
            link.l1.go = "Alonso_Lvl_16_5";
        break;

        case "Alonso_Lvl_16_5":
            dialog.text = "Hã?";
            link.l1 = "Você me dava um presente ao final de cada história.";
            link.l1.go = "Alonso_Lvl_16_Escape";
        break;

        case "Alonso_Lvl_16_Escape":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Ouviu isso? Os sinos estão tocando. Hora de trabalhar.";
            link.l1 = "Pode continuar, Alonso.";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_FourthStage_DlgExit");
        break;
		
		// --> Эпилог
		case "SharlieEpilog_Alonso_1":
			dialog.text = "É sobre o Floran? Já falei com ele que...";
			link.l1 = "Não, camarada, é por outro motivo. Decidi zarpar para a Europa. Por tempo indeterminado.";
			link.l1.go = "SharlieEpilog_Alonso_2";
		break;

		case "SharlieEpilog_Alonso_2":
			if (GetCompanionQuantity(pchar) <= 1) sStr = "nosso navio";
			else sStr = "nossos navios";
			dialog.text = "Sem problemas, capitão. Nosso navio está firme, a tripulação é experiente, só precisamos de mantimentos...";
			link.l1 = "Vou embarcar em outro navio. Como passageiro. Você terá que registrar "+sStr+" na capitania do porto e dispensar a tripulação. E também tomar uma decisão: ficar por aqui e entrar em outro navio, ou me acompanhar até a França — como amigo.";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;

		case "SharlieEpilog_Alonso_3":
			dialog.text = "...";
			link.l1 = "Aliás, uma informação totalmente não relacionada com isso: (sussurrando) conheço umas gatinhas em Bordeaux... Aqui no Caribe não se encontra moças assim. Elas adoram tipos como você — e se você começar a contar nossas histórias de batalha...";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;

		case "SharlieEpilog_Alonso_4":
			dialog.text = "Bom, se for pelas gatinhas... então eu vou com você. Hehe. Mas por que não no nosso navio? E por que como passageiro? Os rapazes podem resmungar um pouco, mas com você eles iriam até o inferno.";
			link.l1 = "Quando cheguei aqui pela primeira vez, nunca imaginei ser marinheiro. E agora não consigo imaginar outra vida. Quero saber se consigo aceitar que não sou mais capitão... e que talvez tenha que deixar para trás os saques e a vida no mar.";
			link.l1.go = "SharlieEpilog_Alonso_nothing";
			link.l2 = "É uma longa história. Te conto na taverna — com uma caneca de rum. E chame a tripulação. Vamos fazer uma baita festa de despedida. Toma, entregue a eles um mês de soldo como bônus.";
			link.l2.go = "SharlieEpilog_Alonso_salary";
		break;

		case "SharlieEpilog_Alonso_nothing":
			dialog.text = "Não se pode fugir do destino, capitão. Se estiver destinado a ser capitão até o fim dos seus dias — assim será.";
			link.l1 = "Veremos, "+npchar.name+", veremos. Por ora — temos trabalho. Partimos em duas semanas. Duvido que você adivinhe em qual navio...";
			link.l1.go = "SharlieEpilog_Alonso_5";
		break;

		case "SharlieEpilog_Alonso_salary":
			dialog.text = "Isso sim é atitude! Assim vai ser mais fácil dar a notícia pra eles.";
			link.l1 = "Duvido que você adivinhe em qual navio...";
			link.l1.go = "SharlieEpilog_Alonso_5";
			salary = GetSalaryForShip(PChar);
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;

		case "SharlieEpilog_Alonso_5":
			dialog.text = "Não me deixe na curiosidade, capitão.";
			link.l1 = "Na pinassa '"+GetShipName("Ulysse")+"'.";
			link.l1.go = "SharlieEpilog_Alonso_6";
		break;

		case "SharlieEpilog_Alonso_6":
			dialog.text = "Não pode ser... Vamos zarpar no mesmo navio com que chegamos? Não acredito no que ouço...";
			link.l1 = "Exatamente ele, "+npchar.name+". Como descobri isso — te conto depois, na taverna, com uma caneca de rum. Agora temos tarefas a cumprir.";
			link.l1.go = "SharlieEpilog_Alonso_7";
		break;

		case "SharlieEpilog_Alonso_7":
			dialog.text = "Entendido, capitão... Ahh... Vai ser difícil me despedir dos rapazes. São como uma família pra mim. Mas fazer o quê...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alonso";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			AddDialogExitQuestFunction("SharlieEpilog_Alonso_exit");
		break;
		// эпилог <--
	}
} 