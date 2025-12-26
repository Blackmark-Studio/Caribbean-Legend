// Джино Гвинейли - алхимик
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> Страж истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino1")
			{
				dialog.text = "Oh! Bom dia, senhor. Como o senhor chegou aqui?";
				link.l1 = "Bom dia, Gino. Vamos nos conhecer melhor. Eu sou o Capitão "+GetFullName(pchar)+" e estou aqui com a permissão do John. Deixe-me deixar uma coisa clara – preciso da sua ajuda, mas também posso ajudar você.";
				link.l1.go = "guardoftruth_0";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Oh! Bom dia, senhor. Como o senhor chegou aqui? E onde está o John?";
				link.l1 = "Então, então... Então era você que sempre se escondia atrás dessa porta fechada! Interessante... Sobre o John... Ele se foi. E agora esta casa é minha. Mas não se preocupe. Vamos nos conhecer melhor. Quem é você, e o que está fazendo aqui?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
			}
			else
			{
				// --> Страж истины
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "threeitems")
				{
					dialog.text = "Olá, "+pchar.name+". Seu rosto me diz que você encontrou algo importante. Já reuniu todos os componentes do Guardião da Verdade?";
					link.l1 = "Exatamente! Estou com os três itens: a adaga, o mapa e a bússola!";
					link.l1.go = "guardoftruth_34";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino")
				{
					dialog.text = "Olá, "+pchar.name+". O que aconteceu? Você está com uma expressão estranha no rosto...";
					link.l1 = "Preciso conversar com você, Gino. É importante.";
					link.l1.go = "guardoftruth";
					break;
				}
				// Ксочитэм
				if (CheckAttribute(pchar, "questTemp.Ksochitam") && pchar.questTemp.Ksochitam == "begin")
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"Sim, eu me lembro, já se passaram dois dias e você quer saber sobre o Guardião da Verdade, estou certo?";
					link.l1 = "Sim, você é! Conseguiu descobrir alguma coisa?";
					link.l1.go = "ksochitam";
					break;
				}
				//--> Португалец
				if (CheckAttribute(pchar, "questTemp.Portugal.Nomoney"))
				{
					dialog.text = "Você trouxe 5.000 pesos, "+pchar.name+"?";
					if (sti(pchar.money) >= 5000)
					{
						link.l1 = "Claro. Aqui, pegue o dinheiro e compre tudo o que precisar.";
						link.l1.go = "Portugal_3";
						SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
						DeleteAttribute(pchar, "questTemp.Portugal.Nomoney");
						pchar.quest.Portugal_Ill1.over = "yes";
						pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
						pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";
					}
					else
					{
						link.l1 = "Infelizmente, não estou com o dinheiro agora.";
						link.l1.go = "Portugal_nomoney";
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal.Die"))
				{
					dialog.text = "Ai de mim, "+pchar.name+", sinto muito - o paciente faleceu. Ele piorou de repente e morreu muito rápido.";
					link.l1 = "Que pena... Que Deus tenha piedade da alma dele!";
					link.l1.go = "exit";
					DeleteAttribute(pchar, "questTemp.Portugal.Die");
					pchar.quest.Remove_Avendel.win_condition.l1 = "Location_Type";
					pchar.quest.Remove_Avendel.win_condition.l1.location_type = "town";
					pchar.quest.Remove_Avendel.function = "RemoveAvendelnDoc";
					AddQuestRecord("Portugal", "6");
					CloseQuestHeader("Portugal");
					pchar.questTemp.Portugal = "end";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToAntigua")
				{
					dialog.text = "Olá, "+pchar.name+". Aconteceu alguma coisa? Você parece muito preocupado...";
					link.l1 = "Gino, tenho um pedido incomum pra você! Tem um homem com febre alta no meu navio. Ele está delirando e inconsciente... você pode ajudá-lo?";
					link.l1.go = "Portugal";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Portugal_wait")
				{
					dialog.text = ""+pchar.name+", estou esperando o paciente. Apresse-se, quanto mais rápido você trazê-lo aqui, maiores serão as chances de eu conseguir salvá-lo.";
					link.l1 = "Sim, sim, ele será trazido aqui imediatamente.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentStart")
				{
					dialog.text = "Você o trouxe bem na hora, "+pchar.name+". Ele está em estado crítico, mas ainda há uma chance.\nCapitão, estou ficando sem ingredientes e não temos tempo para buscá-los na selva. Preciso comprar tudo dos herbalistas locais por 5.000 pesos. Você pode me arranjar essa quantia?";
					if (sti(pchar.money) >= 5000)
					{
					link.l1 = "Claro. Aqui, pegue o dinheiro e compre tudo o que precisar.";
					link.l1.go = "Portugal_3";
					SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
					}
					else
					{
						link.l1 = "Infelizmente,  eu não tenho o dinheiro agora.";
						link.l1.go = "Portugal_nomoney";
						pchar.quest.Portugal_Ill.over = "yes";
						pchar.quest.Portugal_Ill1.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill1.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
						pchar.quest.Portugal_Ill1.function = "Portugal_ToAntiguaOver";//не принесёт через 1 день - Португальцу капут
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentCurrent")
				{
					dialog.text = "Agora não tenho nada a dizer, "+pchar.name+". Estou lutando pela vida do paciente. Ainda há alguma esperança. Volte mais tarde, acredito que em breve poderei lhe dizer algo mais específico.";
					link.l1 = "Tudo bem, Gino, eu volto mais tarde.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentFinish")
				{
					pchar.quest.Portugal_Ill.over = "yes";
					dialog.text = "Tenho novidades,"+pchar.name+". Não vou dizer que seu homem está bem, mas ele está vivo. A doença está recuando e já dá pra notar uma melhora. Para ser sincero, não esperava que minhas poções fossem ajudá-lo tanto.";
					link.l1 = "Isso é uma ótima notícia, Gino, mas me diga, quando poderei levá-lo? Temos uma longa viagem pela frente e o tempo está passando.";
					link.l1.go = "Portugal_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentComplete")
				{
					dialog.text = "Bom dia, capitão. Que bom te ver.";
					link.l1 = "Como está o nosso paciente, Gino?";
					if (GetQuestPastDayParam("questTemp.Portugal_threedays") > 2) link.l1.go = "Portugal_9";
					else link.l1.go = "Portugal_threedays";
					break;
				}
				// <--Португалец
				dialog.text = "Bom dia, capitão. Como vai? Precisa da minha ajuda?";
				if (!CheckAttribute(npchar, "quest.rome"))
				{
					link.l1 = "Sim. Gino, imagino que você seja um homem erudito, e talvez até conheça latim...";
					link.l1.go = "rome";
				}
				if (CheckCharacterItem(pchar, "chemistry"))
				{
					link.l2 = "Tenho algo diferente. Um pequeno presente para você. Aqui, dê uma olhada neste livro.";
					link.l2.go = "chemistry";
				}
				if (CheckAttribute(npchar, "quest.colt") && CheckCharacterItem(pchar, "pistol7"))
				{
					link.l2 = "Sim, Gino. Quero te mostrar esta pistola. Já viu algo parecido com ela?";
					link.l2.go = "colt";
				}
				if (CheckAttribute(npchar, "quest.sample") && CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
				{
					link.l2 = "Trouxe uma amostra da carga para minha pistola.";
					link.l2.go = "colt_1";
				}
				if (CheckAttribute(npchar, "quest.cartridge"))
				{
					link.l2 = "E quanto às acusações pela pistola? Já tem alguma pista?";
					link.l2.go = "cartridge";
				}
				// Addon 2016-1 Jason Пиратская линейка
				if (CheckAttribute(pchar, "questTemp.Mtraxx.Gord"))
				{
					link.l3 = "Gino, encontrei a palavra 'gord'—que não conheço—no diário de um capitão. Você sabe o que significa?";
					link.l3.go = "mtraxx";
				}
				link.l9 = "Bom dia, Gino. Estou bem, não preciso de ajuda. Só queria saber como você está e conversar um pouco.";
				link.l9.go = "exit";	
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			pchar.questTemp.HWIC.Jino = "true"; // Addon 2016-1 Jason Пиратская линейка
			dialog.text = "Meu nome é Gino. Gino Gvineili. Sou cientista. Meu trabalho é preparar pós, misturas e outros remédios para o senhor Murdock. Mas como ele se foi...";
			link.l1 = "Bem, eu sou "+GetFullName(pchar)+". Capitão do meu próprio navio. Então, você é um alquimista?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Not only am I an alchemist, but also a physician. I possess considerable knowledge of medicine. I know much about healing herbs, and I am able to brew mixtures and potions from them. But chemistry is my true calling; I do a great deal of experimenting, and some of my inventions might be of use to people like you.\nI know Latin, French, English, and Italian. My help will be indispensable if you are planning to run a drugstore as Mister Murdock did...";
			link.l1 = "Oho! Não é todo dia que se encontra um homem tão erudito. O negócio da farmácia vai bem, claro, mas eu sou um marinheiro... hm, até pra mim isso soa estranho... Enfim, tenho certeza de que vamos ser bons amigos, Gino. Pode continuar morando aqui e cuidando das suas coisas de ciência...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "";
			link.l1 = "E se algum dia eu precisar da ajuda de um alquimista, curandeiro ou cientista – já sei a quem recorrer... Me diga, por que você está sempre trancado aqui dentro? Você nunca sai para fora?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Eu só saio quando preciso comprar ingredientes ou ervas para meus experimentos. Gosto de viver sozinho, é o meu jeito. Dediquei minha vida à ciência e não me interesso pela vida comum. Livros, escritos, tubos de ensaio, retortas...\nO senhor Murdock me deu essa oportunidade em troca de ajudá-lo a fabricar drogas.";
			link.l1 = "Agora você vai ter ainda mais tempo, Gino. Mas vai ter que abrir mão de um pouco do seu tempo de experimentos se eu precisar da sua ajuda, combinado?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Claro, Capitão. Vou chamá-lo de Capitão, "+GetAddress_Form(NPChar)+", se não se importar? Vou deixar toda a minha pesquisa caso precise das minhas habilidades práticas ou do meu conhecimento teórico.";
			link.l1 = "Excelente. Fico feliz que tenhamos nos entendido tão rápido. Não se preocupe com suas despesas, eu ou meu intendente vamos lhe deixar quantias razoáveis de tempos em tempos.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Obrigado, Capitão. Não preciso de muito... Capitão, tive uma ideia... por que você não aprende um pouco de alquimia? Pode ser muito útil pra você.";
			link.l1 = "Hum. Como meu irmão costumava dizer – não tenha frescura em aprender a fazer as coisas com as próprias mãos. Então, tudo bem, por que não. O que você pode me mostrar?";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Bem, certamente, você não vai conseguir transformar ferro em ouro, isso é impossível... ainda, mas pode aprender a misturar ingredientes seguindo instruções para criar poções ou outros itens úteis. Aqui, pegue esta bolsa. Ela contém tudo que um alquimista iniciante vai precisar: tubos de ensaio, frascos, retortas, alambiques, espátulas, tubos de vidro, um bico de gás, e por aí vai...";
			link.l1 = "Fascinante!";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			Log_Info("You have received an alchemist's kit");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "Você precisa conhecer uma receita para preparar uma poção ou um item. As receitas podem ser compradas com mercadores ou encontradas em qualquer lugar. Depois de estudar uma receita, reúna todos os ingredientes necessários e siga exatamente o que está escrito ali.\n Use seus instrumentos de alquimia, encontre ou compre um almofariz e pistilo, procure um cadinho—infelizmente, não tenho um extra para lhe dar. Ervas, destilados, poções, minerais, até sucata—tudo serve, desde que você tenha a receita certa e as ferramentas adequadas.";
			link.l1 = "Entendi. Vou tentar preparar alguma coisa quando tiver um tempo livre. Valeu, Gino! Você pode me passar uma receita simples? Só pra começar? ";
			link.l1.go = "meeting_8";
		break;
		
		case "meeting_8":
			dialog.text = "Não tenho nenhuma tarefa fácil... mas aqui, pegue esta receita de antídoto. Suponho que você seja capaz de lidar com isso. Fique com ela.";
			link.l1 = "Obrigado! Vou aprender. Agora vou indo, Gino! Cuide da minha casa, acho que não vou aparecer aqui com frequência, então fique à vontade para usar não só o seu quarto, mas também o resto da casa.";
			link.l1.go = "meeting_9";
		break;
		
		case "meeting_9":
			DialogExit();
			GiveItem2Character(pchar, "recipe_potion4"); // belamour legendary edition
			Log_Info("You have received an antidote recipe");
			PlaySound("interface\notebook.wav");
			Log_Info("You need to have the Alchemy skill in order to craft potions, amulets and items!");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "rome":
			dialog.text = "Sim, Capitão, eu conheço a língua dos antigos romanos. Todo estudioso, especialmente um curandeiro ou alquimista, precisa saber latim. Precisa dos meus conhecimentos em latim?";
			link.l1 = "Sim. Gino, não me tome por tolo, mas... bem, como posso explicar...";
			link.l1.go = "rome_1";
		break;
		
		case "rome_1":
			dialog.text = "Fale abertamente, capitão. Não tenha vergonha.";
			link.l1 = "Certo. Você pode fazer uma lista de aforismos latinos eruditos para mim? Veja, tem... um homem que gosta de se gabar da sua 'erudição', e às vezes ele usa essas frases em latim para me mostrar como sou ignorante perto dele. Algo como... 'si vis pacem, para bellum'...";
			link.l1.go = "rome_2";
		break;
		
		case "rome_2":
			dialog.text = "'Si vis pacem, para bellum', quer dizer?";
			link.l1 = "Sim, sim. Quero aprendê-las para derrotar meu arrogante ir... meu amigo.";
			link.l1.go = "rome_3";
		break;
		
		case "rome_3":
			AddQuestRecordInfo("Rome", "1");
			dialog.text = "Não há nada de estranho ou vergonhoso no seu pedido, capitão. Conhecer os aforismos dos antigos que entraram para a história faz de você um homem culto. Aqui, pegue este texto. É exatamente o que você pediu.";
			link.l1 = "Valeu, Gino! Obrigado, de verdade! Vou ler quando tiver um tempo livre...";
			link.l1.go = "exit";
			npchar.quest.rome = true;
			NextDiag.TempNode = "First time";
		break;
		
		case "chemistry":
			RemoveItems(pchar, "chemistry", 1);
			Log_Info("You have given Lavoisier's chemistry textbook");
			dialog.text = "Mostre-me... (lendo) Impossível! Um 'pequeno presente', você diz? Este livro não tem preço! Onde você conseguiu isso?! Isto é... um verdadeiro tesouro!";
			link.l1 = "Fico feliz que tenha gostado.";
			link.l1.go = "chemistry_1";
		break;
		
		case "chemistry_1":
			dialog.text = "(Lendo) Incrível! Nunca ouvi falar disso... e isto? Não entendo nada aqui... mas vou entender, droga! Ah, em breve o trabalho vai ferver no meu laboratório! "+pchar.name+", você nem imagina O QUE você me deu...";
			link.l1 = "Por que não faria? Faço sim. Um livro científico para um cientista...";
			link.l1.go = "chemistry_2";
		break;
		
		case "chemistry_2":
			dialog.text = "Mas quem é o autor desse milagre? Antoine-Laurent de Lavoisier, França... Nunca ouvi falar dele. Mas espere! Como isso é possível! O ano de publicação é 1789? Mas como...";
			link.l1 = "Eu também não sei por que esse ano está escrito aí. Bom, talvez eu saiba. Mas aconselho você a não pensar muito nisso. O livro é útil e isso é o que importa.";
			link.l1.go = "chemistry_3";
		break;
		
		case "chemistry_3":
			dialog.text = "É mais promissor do que eu poderia imaginar, e esse ano deve ser algum erro de impressão... Seja como for. Muito obrigado, capitão!";
			link.l1 = "De nada, Gino. Está tudo nas suas mãos.";
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "pistol7"))
			{
				link.l1 = "Isso não é tudo, Gino. Quero te mostrar esta pistola. Já viu algo assim?";
				link.l1.go = "colt";
			}
			npchar.quest.colt = true;
		break;
		
		case "colt":
			dialog.text = "Eu não sou armeiro, mas vou dar uma olhada... Não, nunca vi nada parecido. Por que pergunta?";
			link.l1 = "Esta pistola é poderosa e destrutiva, mas precisa de cargas especiais para funcionar. Nada mais serve. E eu não faço ideia de como fabricar mais munição para ela. Por isso vim aqui pedir seu conselho.";
			link.l1.go = "colt_1";
		break;
		
		case "colt_1":
			dialog.text = "Você tem pelo menos uma rodada para me mostrar como exemplo? Se não tiver, receio que não vou poder ajudar.";
			if (CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
			{
				link.l1 = "Sim. A carga tem duas partes: a bala em si e esta peça aqui, que acende a pólvora.";
				link.l1.go = "colt_2";
			}
			else
			{
				link.l1 = "Que fracasso! Que vergonha! Tudo bem, talvez eu encontre mais e traga para você.";
				link.l1.go = "exit";
				npchar.quest.sample = true;
			}
			DeleteAttribute(npchar, "quest.colt");
		break;
		
		case "colt_2":
			RemoveItems(pchar, "pistol7", 1);
			RemoveItems(pchar, "GunCap_colt", 1);
			RemoveItems(pchar, "shotgun_cartridge", 1);
			Log_Info("You have given a revolver's cartridge");
			Log_Info("You have given a capsule");
			PlaySound("interface\important_item.wav");
			dialog.text = "Interessante! Parece simples, tem pólvora dentro, uma bala entra por cima, mas parece um pouco estranho. E esse 'troço'... hm. A pólvora não explode sem isso, certo? Curioso... Olha, Capitão, deixa tudo isso comigo: a pistola e as cargas. Volte daqui a um mês, preciso de tempo pra entender como funciona.";
			link.l1 = "Ótimo! Tente descobrir como isso funciona, estou mesmo querendo disparar esta pistola.";
			link.l1.go = "colt_3";
		break;
		
		case "colt_3":
			dialog.text = "O principal problema é descobrir do que é feita essa substância que faz a pólvora explodir. Este livro vai ser útil. Vou tentar chegar ao fundo disso.";
			link.l1 = "Certo. Adeus, Gino!";
			link.l1.go = "colt_4";
		break;
		
		case "colt_4":
			DialogExit();
			DeleteAttribute(npchar, "quest.sample");
			SetFunctionTimerCondition("Colt_Timer", 0, 0, 30, false); // таймер
		break;
		
		case "cartridge":
			dialog.text = "Sim, descobri do que são feitas as cargas da pistola. Tenho que dar o devido crédito ao livro que você me deu. Sem ele, não teria conseguido. Mas preciso avisar, Capitão, não vai ser fácil fabricar munição e cápsulas para essa arma.";
			link.l1 = "Cápsulas?";
			link.l1.go = "cartridge_1";
		break;
		
		case "cartridge_1":
			dialog.text = "A cápsula é aquela 'coisa' que, como você disse, acende a pólvora. Mas vamos começar do início. Está pronto?";
			link.l1 = "Sim! Estou te ouvindo com muita atenção.";
			link.l1.go = "cartridge_2";
		break;
		
		case "cartridge_2":
			AddQuestRecordInfo("Recipe", "shotgun_bullet");
			SetAlchemyRecipeKnown("shotgun_bullet");
			dialog.text = "Então, primeiro, você precisa fabricar uma bala especial. Balas comuns não vão funcionar. Ela precisa ter um formato cônico específico. Você vai ter que encontrar um molde para esse tipo de bala, o que eu chamo de molde de bala. Pegue balas de chumbo comuns, derreta-as em um cadinho e despeje o chumbo derretido no molde. Deixe a peça esfriar e então retire a bala pronta.";
			link.l1 = "E onde posso encontrar um molde de bala assim?";
			link.l1.go = "cartridge_3";
		break;
		
		case "cartridge_3":
			dialog.text = "Eu não sei, capitão. Sou alquimista, não ferreiro. Pegue esta bala como exemplo, talvez você descubra o que fazer.";
			link.l1 = "Certo. Continue...";
			link.l1.go = "cartridge_4";
		break;
		
		case "cartridge_4":
			AddQuestRecordInfo("Recipe", "shotgun_cartridge");
			SetAlchemyRecipeKnown("shotgun_cartridge");
			dialog.text = "Depois você precisa fazer um recipiente para a pólvora. É lá que você coloca a bala. Escrevi instruções claras para você. Leia com atenção e tente seguir.";
			link.l1 = "Bom...";
			link.l1.go = "cartridge_5";
		break;
		
		case "cartridge_5":
			AddQuestRecordInfo("Recipe", "GunCap_colt");
			SetAlchemyRecipeKnown("GunCap_colt");
			dialog.text = "Agora precisamos conseguir as cápsulas. Você vai precisar de uma folha de cobre bem fina – faça você mesmo a partir de um pepita de cobre. Recorte círculos nela do mesmo tamanho das balas. Depois, coloque prata fulminante dentro deles usando cera.";
			link.l1 = "Prata fulminante? O que é isso?";
			link.l1.go = "cartridge_6";
		break;
		
		case "cartridge_6":
			dialog.text = "Eu mesmo não sabia disso, descobri o segredo no seu livro. É um pó branco que pode ser feito de prata, álcool e ácido nítrico. Ele explode facilmente ao ser esfregado ou sacudido, por isso serve bem para acender a pólvora dos cartuchos da sua pistola. É uma coisa desagradável, já explodiu duas vezes durante meus testes até eu acertar a receita.";
			link.l1 = "Fui sortudo de ter este livro comigo!";
			link.l1.go = "cartridge_7";
		break;
		
		case "cartridge_7":
			dialog.text = "Be very careful, this stuff is explosive as hell! I could make some myself, but storing fulminating silver is too dangerous; it's vital that you put it in the capsules right after it's made. I can't craft copper capsules, I'm no blacksmith, as I've told you before.";
			link.l1 = "Certo. Me dê a receita, eu mesmo vou aprender.";
			link.l1.go = "cartridge_8";
		break;
		
		case "cartridge_8":
			AddQuestRecordInfo("Recipe", "OxyHydSilver");
			SetAlchemyRecipeKnown("OxyHydSilver");
			dialog.text = "De nada. Siga a receita à risca e preste atenção na ordem do processo, ou vai acabar pelos ares com seus frascos.";
			link.l1 = "Vou tomar cuidado.";
			link.l1.go = "cartridge_9";
		break;
		
		case "cartridge_9":
			dialog.text = "Além disso, leve estes dois frascos. Este aqui contém ácido nítrico, e este aqui contém álcool. Com eles, você vai conseguir fazer prata fulminante suficiente para encher cerca de 20 cápsulas.";
			link.l1 = "Obrigado, Gino!";
			link.l1.go = "cartridge_10";
		break;
		
		case "cartridge_10":
			GiveItem2Character(pchar, "Mineral29");
			GiveItem2Character(pchar, "Mineral28");
			Log_Info("You have received a flask of nitric acid");
			Log_Info("You have received a flask of spirit");
			PlaySound("interface\important_item.wav");
			dialog.text = "Leve também sua pistola e a carga de amostra. Boa sorte, capitão, na fabricação das suas cargas. Espero que continue vivo e inteiro.";
			link.l1 = "Vou fazer o que puder para me proteger. E, Gino, já te disse que você é um gênio?";
			link.l1.go = "cartridge_11";
		break;
		
		case "cartridge_11":
			TakeNItems(pchar, "pistol7", 1);
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 1);
			dialog.text = "Você está me fazendo corar, Capitão, estou falando sério...";
			link.l1 = "Tá bom. Adeus, Gino! Você é o meu melhor alquimista!";
			link.l1.go = "cartridge_12";
		break;
		
		case "cartridge_12":
			DialogExit();
			DeleteAttribute(npchar, "quest.cartridge");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx":
            dialog.text = "Gord, gord... Você poderia me contar mais sobre o capitão? De onde ele é?";
			link.l1 = "Não faço ideia. Embora ele tenha nascido em algum lugar do Norte, às vezes o chamavam de Viking.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Um viking! Sim, sim, eu me lembro, li sobre isso em um livro de história. Um gord é um assentamento fortificado de um jarl livre.";
			link.l1 = "Um jarl livre? Quem seria esse?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "É um príncipe dos homens do Norte. Jarls livres com seus bandos de guerra costumavam saquear e pilhar a Europa séculos atrás em seus navios, os drakkars. Você poderia chamá-los de piratas, suponho. Os gords eram suas bases e lares, lugares onde podiam descansar, cultivar e festejar.";
			link.l1 = "Entendi. Então esse forte deve ser o esconderijo de pirata dele... Valeu, Gino!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookFourth");
		break;
		
	// ----------------------------------------- Португалец ----------------------------------------------------
		case "Portugal":
			dialog.text = "Febre e delírios, é isso? Que interessante. Traga-o aqui imediatamente! Vou ver o que posso fazer. Mas não posso prometer nada se o estado dele for muito grave... Ele é seu oficial?";
			link.l1 = "Não, graças a Deus, ele não está. Gino, escuta, não pergunta quem ele é, só faz o que puder, isso é muito importante pra mim!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Certo, leve-o para dentro, para o seu quarto. Vou preparar algumas misturas... talvez essa raiz...";
			link.l1 = "Vou trazê-lo aqui imediatamente!";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1 = "location";
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1.location = "SentJons_HouseF3";
			PChar.quest.Portugal_DoctorPodhodit.function = "Portugal_DoctorPodhodit";
		break;
		
		case "Portugal_nomoney":
			dialog.text = "Então tente encontrar o quanto antes, não vou conseguir curá-lo sem o remédio e pode ser tarde demais se você não se apressar.";
			link.l1 = "Tá bom, eu vou conseguir o dinheiro.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal.Nomoney = "true";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Excelente, Capitão. Agora vou preparar algumas misturas, e recomendo que deixe meu paciente em paz. Volte aqui amanhã.";
			link.l1 = "Certo, Gino. Eu confio nas suas misturas e no seu talento.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal = "TreatmentCurrent";
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
		break;
		
		case "Portugal_4":
			dialog.text = "Bem, acho que em duas semanas ele vai estar bem. Não posso prometer que vá conseguir dançar, mas pelo menos vai conseguir ficar de pé sozinho, isso é certo.";
			link.l1 = "Droga, eu não tenho duas semanas! Eu preciso... zarpar o quanto antes!";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Captain, I am not a mage, but I can assure you that the man is too weak for now. I am not sure he will survive even a few days on the ship; you can't move him!";
			link.l1 = "Tá bom, tá bom, mas duas semanas—não, até uma semana já é demais!";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "Três dias... sim, acredito que em três dias você pode tentar zarpar, mas ele vai precisar de cuidados e remédios, e vocês terão que fazer paradas.";
			link.l1 = "Tenho um médico, ele vai cuidar dele. Voltarei em três dias e o levaremos, é o máximo que posso fazer. Precisamos seguir viagem, mesmo com paradas... ah, e mais uma coisa – Gino, você é um gênio!";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			dialog.text = "Obrigado, capitão. Volte para buscar seu amigo em três dias, mas não o incomode até lá. Ele precisa de repouso absoluto.";
			link.l1 = "Certo, entendi. Eu vou levá-lo em três dias.";
			link.l1.go = "Portugal_8";
		break;
		
		case "Portugal_8":
			DialogExit();
			SaveCurrentQuestDateParam("questTemp.Portugal_threedays");
			pchar.quest.Portugal_Ill2.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill2.function = "Portugal_ToAntiguaOver";//чтобы не тянул
			pchar.questTemp.Portugal = "TreatmentComplete";
			pchar.quest.Avendel_room.win_condition.l1 = "location";
			pchar.quest.Avendel_room.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room.function = "AvendelSpeach";
		break;
		
		case "Portugal_threedays":
			dialog.text = "Ele está indo bem, mas o progresso é lento. Ainda não dá para levá-lo.";
			link.l1 = "Sim - sim, Gino, eu me lembro. Três dias...";
			link.l1.go = "exit";
		break;
		
		case "Portugal_9":
			pchar.quest.Portugal_Ill2.over = "yes";
			dialog.text = "Não houve piora, mas ele também não melhorou de verdade. Continua inconsciente, sem entender onde está ou por que está aqui, embora isso não pareça incomodá-lo muito. Ainda está com febre, então não tenho certeza se levá-lo a bordo agora é uma boa ideia.";
			link.l1 = "Não posso esperar mais, já estamos aqui há tempo demais. Arrume suas misturas que vão ajudá-lo na viagem e vamos embora. Espero que esse desgraçado seja forte o bastante para sobreviver tempo suficiente para encarar sua sentença de morte...";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			dialog.text = "Espere, Capitão! Eu estive tratando dos condenados? Mas que diabos? Foi feito um trabalho enorme aqui, você faz ideia de como é difícil preparar pólvora seca...";
			link.l1 = "Gino, você não precisava saber disso. Não se preocupe tanto, ele é um pirata, e dos mais notórios. Preciso levá-lo para Curaçao para uma reunião com as autoridades da Companhia o quanto antes. Ponto final.";
			link.l1.go = "Portugal_11";
		break;
		
		case "Portugal_11":
			dialog.text = "Certo, você é quem sabe. Pirata então... Curaçao. Tanto faz, mas me escute: ele vai passar a maior parte do tempo dormindo, só que o balanço do navio e o calor sufocante podem atrasar tudo. Recomendo fazer uma parada depois de alguns dias de viagem e deixar seu... prisioneiro descansar em terra. Caso contrário, corre o risco de chegar em Curaçao só para pendurar um cadáver...";
			link.l1 = "Certo, eu faço isso. Martinica serve, fica quase no meio do caminho para Curaçao. Espero que o vento esteja a favor. Vou levá-lo agora e partiremos. Obrigado mais uma vez, Gino.";
			link.l1.go = "Portugal_12";
		break;
		
		case "Portugal_12":
			dialog.text = "De nada, capitão. Lembre-se que você tem quatro dias — bem, cinco, mas não mais do que isso. E só mais uma coisa... sabe, eu costumo cuidar das pessoas não porque quero vê-las enforcadas depois do meu tratamento. Um médico é responsável por seus pacientes, não importa quem sejam. E estou me sentindo realmente mal...";
			link.l1 = "Me desculpe por te envolver nisso tudo, mas sem você não teríamos chance alguma. Precisamos zarpar agora, senão os portugueses vão conseguir se reunir na nossa porta para encontrar o chefe deles.";
			link.l1.go = "Portugal_13";
		break;
		
		case "Portugal_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3_Room", "goto", "goto2", "Portugal_JinoNorm", -1);//Джино в свою комнату
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			pchar.quest.Portugal_Ill3.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill3.function = "Portugal_ToAntiguaOver";//5 дней до Мартиники
			pchar.questTemp.Portugal = "ToMartinique";
			pchar.quest.Avendel_room1.win_condition.l1 = "location";
			pchar.quest.Avendel_room1.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room1.function = "AvendelSpeach";
			pchar.quest.Portugal_street.win_condition.l1 = "location";
			pchar.quest.Portugal_street.win_condition.l1.location = "SentJons_town";
			pchar.quest.Portugal_street.function = "PortugalOnStreet";
		break;
		// <-- Португалец
		case "guardoftruth_0":
			dialog.text = "Interessante... E como exatamente você pode me ajudar? Eu não preciso de ajuda, nem pedi por ela...";
			link.l1 = "Mas você vai precisar disso. Primeiro me escute, depois decida.";
			link.l1.go = "guardoftruth";
		break;
		
		case "guardoftruth":
			dialog.text = "Estou ouvindo.";
			link.l1 = "Estive em Santiago recentemente... visitando o Padre Vincento. Ele estava procurando por seu secretário desaparecido chamado... Jesus, por que você ficou tão pálido, Gino?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Você... você viu o inquisidor? Ele está...";
			link.l1 = "Não se preocupe, Gino. Não existe a menor chance de eu te entregar para ele, mesmo que essa tenha sido a ordem: te encontrar e te levar até ele. Preciso conseguir algumas informações sobre um índio do povo Itza. Me fale sobre Tayasal, seus tesouros e o 'mal' que o cerca.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Vejo que você está bem informado. Foi o padre Vincento quem lhe contou isso?";
			link.l1 = "Consegui algumas informações com ele e outras pessoas. Mas quero ouvir o seu lado. Você foi secretário dele, então deve ter registrado o interrogatório, não é?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Você não faz ideia do que ele estava fazendo com aquele pobre índio!.. Me dá arrepios toda vez que lembro daquele interrogatório.";
			link.l1 = "Mesmo assim, vamos conversar sobre isso. Quem era aquele índio? Como ele foi parar nas mãos do Padre Vincento?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "He was among the Indians of the Itza people who travelled from Tayasal in search of the Kukulcan Mask - an artifact of the ancient Maya god Kukulcan. Those Indians encountered a band of white adventurers led by Archibald Calhoun - a treasure hunter from Scotland. Only one Indian survived; his name was Ksatl Cha. He had three interesting items on him, I will tell you about them later.\Calhoun tried to force the prisoner to tell him about treasures, but he kept silent. So the Scot delivered him to Santiago, to Father Vincento, in exchange for permission to visit Spanish cities for a year. He knew that the inquisitor was very interested in all kinds of local mysteries and legends. Vincento made the Indian talk. He started talking a lot, he told us everything he knew, and the information we got out of him shocked the inquisitor himself.";
			link.l1 = "É mesmo? E o que poderia fazer Sua Graça tremer?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Vou te contar tudo em ordem. Existe uma antiga cidade maia chamada Tayasal nas profundezas das selvas de Yucatán. Ela é habitada pelos descendentes dos maias – o povo Itza. Eles tentam viver de acordo com as regras e tradições dos seus ancestrais. É claro que eles não gostam do estado do mundo moderno – quero dizer, do domínio do homem branco. Eles sonham com os bons tempos antigos. E aqui vem a parte mais interessante. Um grupo de aventureiros brancos, por acaso, chegou perto de Tayasal e sequestrou a filha do chefe supremo dos Itza. Isso aconteceu quase um quarto de século atrás. Essa foi a gota d’água, e Kanek, o chefe, ficou furioso. Ele decidiu realizar o ritual mais perigoso e secreto dos maias – invocar um deus indígena para apagar todos os descendentes dos conquistadores brancos...";
			link.l1 = "Hm... Esse deve ser o demônio de que o padre Vincento falou. Mas como esse deus indígena vai lidar com os colonizadores brancos? Será que ele vai aparecer como um dragão e queimar todo mundo?";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Oh, "+pchar.name+", deixa essas histórias de monstros de fogo para as velhas fofoqueiras! Na verdade, você não está tão errado, mas o nosso caso é mais complicado e sério. Nem mesmo o Dilúvio conseguiria impedir a Europa de avançar sobre o Novo Mundo. Para cada morto, dez virão em seu lugar. Kanek precisava destruir a própria possibilidade da colonização europeia.";
			link.l1 = "Bem, isso já aconteceu.";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Você está pensando na direção certa, capitão... O objetivo do ritual de Kanek não era apenas invocar o ser superior, mas também criar uma fenda espaço-temporal.";
			link.l1 = "O quê?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Os antigos maias tinham um conhecimento extraordinário, capitão. Kanek encontrou uma descrição de um ritual que permite controlar o tempo.";
			link.l1 = "Uau! Incrível!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Escute. O objetivo final do ritual é mudar o passado para tornar impossível a chegada do homem branco ao Novo Mundo. Para conseguir isso, eles vão enviar alguém para o passado, alguém que tenha autoridade, poder e a capacidade de mudar o destino das pessoas. Mas, acima de tudo, essa pessoa precisa ter conhecimento moderno.\nPense bem, "+pchar.name+", o que teria acontecido com Colombo se suas caravelas tivessem sido recebidas por uma frota indígena de fragatas e galeões armados com canhões modernos? E se as arcabuzes dos soldados brancos não tivessem sido enfrentadas por arcos e lanças, mas por morteiros e mosquetes?";
			link.l1 = "Eu suponho que as Américas talvez nem tivessem sido descobertas....";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Exatamente! E talvez algum 'Colombo' indígena tivesse descoberto a Europa...";
			link.l1 = "Interessante, e quem o Kanek vai mandar para o passado? Um dos seus guerreiros nus? Duvido que ele consiga ensinar alguma coisa aos próprios ancestrais...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "Não ria, Capitão. Kanek não passou anos em templos maias só lendo os escritos deles. Um deus indígena deve ser enviado ao passado em forma humana...";
			link.l1 = "Gino, que bobagem é essa que você está dizendo? Você está....";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "Até o Filho de nosso Senhor, Jesus Cristo, veio à nossa terra em forma humana e nasceu de uma mulher, a Santa Virgem Maria...";
			link.l1 = "Jesus, Gino... você tá falando sério?";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Claro que sim. Ksatl Cha foi muito convincente...";
			link.l1 = "Mas qual deus Kanek escolheu para uma missão tão 'nobre'?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "O ritual deveria invocar apenas um Ser Supremo. A serpente emplumada, Quetzalcoatl, Kukulcan...";
			if (CheckAttribute(pchar, "questTemp.Dolly")) link.l1 = "Kukulcan?! Já tive a imprudência de encontrar o 'espírito' dele, que habita as estátuas. Agora entendi... continue!";
			else link.l1 = "Hm. Interessante. Já ouvi esse nome pelo padre Vincento... continue!";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Kanek decided to summon Kukulcan, since the Itza already possessed an ancient artifact of this god - the Mask of Kukulcan. Whoever holds the mask is able to pass through the portal, and only he will be accepted by the ancient Maya as a living god.\nThe priest performed the ritual, summoning Kukulcan to incarnate in the body of a mortal. He also created a time rift that drew several random people from the future into our era.\nThe purpose of this extraction was to endow Kukulcan's incarnation not only with the knowledge of our time, but also of the future. But something went wrong, and all those people arrived elsewhere, not in Tayasal. I have never met any of them.\nSeveral portals were created throughout the archipelago; they were meant to transport bearers of future knowledge and Itza agents across the region and to Tayasal. But these portals failed in their purpose—no one has been brought to Tayasal in the last 25 years...";
			if (CheckAttribute(pchar, "questTemp.Dolly"))
			{
				link.l1 = "Certo... Porque esses portais só transferem pessoas capturadas entre si. Incrível!";
				link.l1.go = "guardoftruth_15a";
			}
			else
			{
				link.l1 = "Interessante...";
				link.l1.go = "guardoftruth_16";
			}
		break;
		
		case "guardoftruth_15a":
			dialog.text = "Você viu aqueles portais? Me conta!";
			link.l1 = "Talvez depois, Gino... Agora estou mais interessado na sua história. Continue!";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Padre Vincento está ciente de tudo que te contei. Isso, claro, o deixou preocupado. Se Kukulcan, encarnado em forma humana, chegar ao portal junto com a Máscara e todo o conhecimento que acumulou... Fim dos tempos. Apocalipse.\nSe o passado muda – o futuro também. Nossa realidade vai se transformar, desaparecer, se dissolver. Você e eu talvez nunca nasçamos. Ou seremos diferentes. Assim que Kukulcan alcançar o passado – deixaremos de existir.";
			link.l1 = "E quem é a encarnação de Kukulcan?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Who knows. He might be anyone who was born a quarter of a century ago, when the ritual was conducted. In you, for example... just kidding. But we still have a chance. First, Kukulcan's incarnation is just a mortal person; he can drown, be stabbed, be shot, or die of fever. And in such a case, no apocalypse will ever happen.\nSecond, it is impossible to reach the past without the mask. Kanek stashed it very well—maybe too well, it seems. It might be that even the incarnated Kukulcan will fail to find it.";
			link.l1 = "Me conte mais.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Some time after the ritual, a group of Spanish conquistadors almost reached Tayasal and nearly made it to the treasury. The Itza managed to kill all of them except one—a strong giant, seven feet tall.   Kanek was worried that the Mask could be stolen by any stranger, so he decided to protect the relic. He devised his own ritual, using the ancient Maya's knowledge. He took three items which he believed held the power of the white man: a dagger, which once belonged to Cortez himself, and a compass. He also used that dagger to carve out a piece of skin from the back of the captured Spanish giant as the third item. The man himself was sacrificed on the altar of Kukulcan. Three items were used in the ritual.   And from this ritual, a new island was born, in the open sea, not far from Yucatan. No one knows its location, but the Mask is stashed there. In order to find it, one must use the dagger, the compass, and the piece of skin. Besides, all items from the treasury are cursed; not a single one of them can leave the archipelago.   An attempt to do so will cause a storm which will drive the ship right onto the rocks of the island where the Mask is hidden. It is called Ksocheatem. Smart, isn't it?";
			link.l1 = "Talvez até inteligente demais. Isso é inegável. Mas como diabos Ksatl Cha estava tão bem informado? Duvido muito que Kanek compartilhasse esse tipo de informação com guerreiros comuns...";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Thing is, the current chief of the Itza, Urakan, son of Kanek, had told this warrior everything. He sent Ksatl Cha with a group of warriors to find the secret island and the Mask of Kukulcan. He had given him the Guardian of Truth to do that; it is the name of the three items together - the dagger, the compass, and the map made of human skin.";
			link.l1 = "O mapa? E por que Urakan precisava da Máscara? Ele resolveu mudar o passado por conta própria?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "A pele carrega os contornos do arquipélago, por isso a chamam de mapa. Urakan queria a Máscara por um motivo muito simples – ele não deseja destruir a realidade existente nem sacrificar sua vida e a de seu povo pela glória dos antigos. Por isso ele estava decidido a destruir a Máscara a qualquer custo. Mas Ksatl Cha foi capturado por Calhoun e... bem, você já sabe o resto da história. Ele nunca chegou a Ksocheatem.";
			link.l1 = "Então é possível evitar o fim dos tempos encontrando e destruindo a Máscara? E onde está esse... Guardião da Verdade agora?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "A adaga 'Garra do Chefe' e a bússola 'Flecha do Caminho' ficaram com Calhoun, e o mapa de pele 'Das Duas Aparências' ainda está em algum lugar com a Inquisição. Calhoun usou o mapa como mordaça para calar o prisioneiro. Ele não fazia ideia para que serviam esses objetos.";
			link.l1 = "O que você acabou de dizer? 'Garra do Chefe'? Droga, essa adaga está comigo agora! O Fadey me deu ela para pagar a dívida que tinha com meu irmão! Olha só!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			dialog.text = "Incrível... É mesmo. Eu me lembro disso.";
			link.l1 = "Gino, me diga, o que exatamente o Padre Vincento sabe da sua história?";
			link.l1.go = "guardoftruth_23";
		break;
		
		case "guardoftruth_23":
			dialog.text = "Tudo, exceto informações sobre o Guardião da Verdade e como fazê-lo revelar a localização da ilha secreta onde a Máscara de Kukulcan está escondida. Ksatl Cha me contou sobre isso quando estávamos a sós, pouco antes de eu lhe dar uma mistura venenosa para acabar com seu sofrimento. Ele morreu com um sorriso no rosto.\nCom certeza, eu não podia ficar em Santiago depois do que fiz. Tinha sérias suspeitas de que me tornei uma testemunha importante e perigosa para o inquisidor. O padre Vincento sempre consegue o que quer, não importa o preço. Ksatl Cha contou a ele sobre o tesouro em Tayasal.";
			link.l1 = "Esses tesouros já foram encontrados por um aventureiro chamado Miguel Dichoso. Você já ouviu falar dele?";
			link.l1.go = "guardoftruth_24";
		break;
		
		case "guardoftruth_24":
			dialog.text = "Não. E onde ele está agora, com seus tesouros?";
			link.l1 = "Eu quero me conhecer. É por isso que vim até você, estou atrás daquele ouro indígena. Dichoso levou os tesouros para a Europa e sumiu com eles.";
			link.l1.go = "guardoftruth_25";
		break;
		
		case "guardoftruth_25":
			dialog.text = "Eu vou te contar onde estão os tesouros e o próprio Dichoso.";
			link.l1 = "Gino, você me surpreende. Como você sabe disso?!";
			link.l1.go = "guardoftruth_26";
		break;
		
		case "guardoftruth_26":
			dialog.text = "Você pode entender isso pela minha história, Capitão. Os tesouros de Tayasal eram amaldiçoados – nenhum item pode ser levado do arquipélago. Qualquer navio...";
			link.l1 = "... será pego pela tempestade e lançado na ilha onde a Máscara de Kukulcán está escondida! Eu estava cego, mas agora enxergo. Acho que já sei o suficiente para encontrar Ksocheatem, os tesouros e a própria Máscara!";
			link.l1.go = "guardoftruth_27";
		break;
		
		case "guardoftruth_27":
			dialog.text = "Quer salvar o mundo, Capitão?";
			link.l1 = "Quero encontrar meu irmão pródigo... Gino, como faço para o Guardião da Verdade revelar a localização da ilha? Você disse que sabe como!";
			link.l1.go = "guardoftruth_28";
		break;
		
		case "guardoftruth_28":
			dialog.text = "Eu conheço o método, mas não sei os detalhes. Não vou conseguir te ajudar até ter todos os componentes do Guardião.";
			link.l1 = "Hm. Já temos a adaga. Só faltam a bússola e o mapa. Calhoun está com a bússola, e o Padre Vincento tem o mapa...";
			link.l1.go = "guardoftruth_29";
		break;
		
		case "guardoftruth_29":
			dialog.text = "Você vai voltar para o inquisidor? Mas como vai fazer o relatório...";
			link.l1 = "Eu preciso convencer o Padre Vincento de que você está morto, Gino. Só assim ele vai parar de procurar por você. Vamos dizer que você teve um ataque repentino ao me ver. Você deveria me dar algum objeto que eu possa usar como prova da sua morte.";
			link.l1.go = "guardoftruth_30";
		break;
		
		case "guardoftruth_30":
			dialog.text = "Vincento não vai acreditar na história do ataque cardíaco, mas vai acreditar se você disser que me suicidei bebendo um veneno com cheiro de amêndoas. Entregue a ele meu almanaque, ele sabe que nunca me separo dele.";
			link.l1 = "Tá bom. Porque eu preciso desse contato com o inquisidor. Ele provavelmente sabe muito sobre os nossos negócios.";
			link.l1.go = "guardoftruth_31";
		break;
		
		case "guardoftruth_31":
			dialog.text = "Tome cuidado com o Padre Vincento. Ele é tão perigoso quanto um tigre e joga conforme as próprias regras. Não vai dividir nem tesouros nem fama com você.";
			link.l1 = "I understand that. Fine, Gino, give me your almanac and try to remember what the Indian told you about the Guardian of Truth, because I want to piece it together. I need to find Ksocheatem; I am sure that I will find not only the mask and the treasures there, but also my dear brother.";
			link.l1.go = "guardoftruth_32";
		break;
		
		case "guardoftruth_32":
			dialog.text = "Pegue. Boa sorte, capitão!";
			link.l1 = "Eu não estou me despedindo, Gino...";
			link.l1.go = "guardoftruth_33";
		break;
		
		case "guardoftruth_33":
			DialogExit();
			Log_Info("You have received an almanac");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "Almanac");
			ChangeItemDescribe("Almanac", "itmdescr_jinobook");
			pchar.questTemp.Guardoftruth = "twoitems";
			AddQuestRecord("Guardoftruth", "37");
		break;
		
		case "guardoftruth_34":
			dialog.text = "Foi difícil, capitão?";
			link.l1 = "Melhor não falar sobre isso... Muita gente morreu para conseguir esses itens. Gente demais. Parece que não sou o único ansioso para encontrar o misterioso Ksocheatem. ";
			link.l1.go = "guardoftruth_35";
		break;
		
		case "guardoftruth_35":
			dialog.text = "Posso imaginar... Aliás, como está o Padre Vincento? Você ainda fala com ele com frequência?";
			link.l1 = "Até agora sim, mas acho que não há mais necessidade disso. Tenho todos os componentes do Guardião da Verdade, o que significa que possuo a chave para o paradeiro de Ksocheatem. Por algum motivo, não estou com vontade de relatar meu sucesso a Sua Graça.";
			link.l1.go = "guardoftruth_36";
		break;
		
		case "guardoftruth_36":
			dialog.text = "Tome cuidado, "+pchar.name+". Padre Vincento tem centenas de olhos e mãos. Mãos muito longas...";
			link.l1 = "Passei por muita coisa nos últimos meses, e agora com certeza não tenho medo, nem do Padre Vincento, nem do olhar ou das mãos dele. Tanto faz. Está na hora de encontrarmos Ksocheatem usando os componentes do Guardião. Você sabe como fazer isso? ";
			link.l1.go = "guardoftruth_37";
		break;
		
		case "guardoftruth_37":
			dialog.text = "Na verdade, não. Ksatl Cha foi bem vago. Acho que o índio nem sabia direito como fazer o Guardião funcionar. Deixe os componentes comigo e vou tentar descobrir. Volte daqui a dois dias e talvez eu já tenha resolvido esse enigma.";
			link.l1 = "Certo, Gino. Estou contando com você. Aqui, pegue-os.";
			link.l1.go = "guardoftruth_38";
		break;
		
		case "guardoftruth_38":
			dialog.text = "Pode ter certeza de que eles vão ficar seguros e inteiros comigo.";
			link.l1 = "Disso eu não duvido. Bom, não vou te incomodar agora, Gino. Boa sorte com sua pesquisa!";
			link.l1.go = "guardoftruth_39";
		break;
		
		case "guardoftruth_39":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			RemoveItems(pchar, "knife_01", 1);
			RemoveItems(pchar, "skinmap", 1);
			RemoveItems(pchar, "arrowway", 1);
			pchar.questTemp.Guardoftruth = "end";
			SetFunctionTimerCondition("Ksochitam_StartSearchIsland", 0, 0, 2, false);
			CloseQuestHeader("Guardoftruth");
			AddQuestRecord("Ksochitam", "1");
		break;
		
		case "ksochitam":
			dialog.text = "Em parte. Quer dizer, eu tenho alguma coisa, mas não sei como fazer tudo isso funcionar de verdade. Vamos tentar resolver esse quebra-cabeça juntos.";
			link.l1 = "Vamos tentar! Me diga suas ideias.";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "Ksatl Cha disse algo assim: 'A Garra do Chefe fará o mapa se revelar. A Flecha do Caminho mostrará a direção das aparições.'";
			link.l1 = "E o que você conseguiu fazer?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "Descobri como fazer o mapa se 'revelar'. Você já deu uma olhada no mapa de Duas Aparências?";
			link.l1 = "Hm. E havia algo incomum? Algum contorno estranho do arquipélago...";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			GiveItem2Character(pchar, "skinmap");
			dialog.text = "Pegue e dê outra olhada. Preste atenção.";
			link.l1 = "Bem, vamos fazer isso se você insiste.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_1";
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "ksochitam_wait":
			dialog.text = "Você ainda não olhou o mapa, "+pchar.name+"...";
			link.l1 = "Sim, sim, eu vou fazer isso agora...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_wait";
		break;
		
		case "ksochitam_5":
			dialog.text = "";
			link.l1 = "Vi sim. Não vi nada de novo. Só algumas formas encobertas de ilhas e do continente. O que era pra eu ver ali?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "Espere um segundo. Agora você precisa fazer esse mapa se revelar. Pegue a adaga e toque suavemente o mapa com a lâmina. Não pressione, precisamos evitar qualquer dano. Pegue a adaga. E preste muita atenção!";
			link.l1 = "Interessante! Vamos ver...";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			DialogExit();
			GiveItem2Character(pchar, "knife_01");
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_2";
			sld = ItemsFromID("skinmap");
			sld.mark = 2;
		break;
		
		case "ksochitam_8":
			dialog.text = "Bem, você vê alguma diferença agora?";
			link.l1 = "Sim. Quando você toca o mapa com a adaga, aparecem duas marcas de caveira, e elas estão sempre nos mesmos lugares...";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "Nos mesmos dois lugares, "+pchar.name+"!   Por isso ela era chamada de Mapa das Duas Aparências!";
			link.l1 = "E o que isso significa?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "Acho que sim, muita coisa... Mas ainda vêm mais enigmas por aí. Imagino que esses crânios sejam as aparições de que Ksatl Cha falou. Então, a bússola deve mostrar a direção certa para Ksocheatem a partir deles. Você viu a bússola, "+pchar.name+"?";
			link.l1 = "Yes. It looks like an ordinary naval compass, but it behaves strangely; its needle twitches in different directions or starts spinning wildly.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "Eu achei que colocar a bússola sobre os crânios faria a seta parar e apontar uma direção clara no mapa. Para isso, coloquei-a em um crânio e depois no outro, enquanto tocava o mapa com a adaga.";
			link.l1 = "E daí?";
			link.l1.go = "ksochitam_12";
		break;
		 
		case "ksochitam_12":
			dialog.text = "Inútilmente. A bússola não mudou de comportamento. O ponteiro continua girando descontroladamente. Parece que estou fazendo algo errado. Ou talvez eu tenha entendido mal as palavras de Ksatl Cha.";
			link.l1 = "Então a adaga e o mapa funcionam, mas a bússola não?";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			dialog.text = "A Flecha do Caminho com certeza deve funcionar, só não sabemos ainda como fazê-la funcionar. "+pchar.name+",  você conhece a geografia do arquipélago melhor do que eu... Me diga, que lugares são revelados pelo mapa de duas faces?";
			link.l1 = "Só um segundo! (dando uma olhada)... Muito bem... A terra à esquerda é o continente ocidental. Aquela à direita parece ser a ilha de Dominica. Algo assim.";
			link.l1.go = "ksochitam_14";
		break;
		
		case "ksochitam_14":
			dialog.text = "E me diga: Há... algo interessante nesses lugares?";
			link.l1 = "O que você quer dizer?";
			link.l1.go = "ksochitam_15";
		break;
		
		case "ksochitam_15":
			dialog.text = "Eu mesmo não tenho certeza... Bem, algo especial?";
			link.l1 = "Gino, não fala em enigmas. Explica de um jeito simples.";
			link.l1.go = "ksochitam_16";
		break;
		
		case "ksochitam_16":
			dialog.text = "Só posso supor que esses crânios indicam lugares reais. A Flecha do Caminho não funciona quando está sobre as imagens do mapa. Talvez ela funcione perto das características geográficas reais que o mapa revela?";
			link.l1 = "Gino, você é um gênio! Western Main, Dominica? Os crânios são grandes demais para indicar os locais exatos.";
			link.l1.go = "ksochitam_17";
		break;
		
		case "ksochitam_17":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = ""+pchar.name+", vamos fazer o seguinte: Traga-me um mapa de papel do arquipélago, combine-o com o mapa das Duas Aparições e marque as aparições com cruzes. Talvez isso te leve a algumas suposições?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "Eu tenho este velho mapa do arquipélago.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "Tenho este belo mapa do arquipélago.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "Tenho aqui um excelente mapa do arquipélago.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Combinado. Eu vou trazer o mapa e continuamos...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_17_1":
			dialog.text = "Ah, qual é, "+pchar.name+"! Este pergaminho da época de Colombo não é muito melhor que o mapa de pele. Tenho certeza de que deve haver algo melhor que essa porcaria no mundo. Traga-me outro mapa, um mais recente!";
			link.l1 = "Tudo bem...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_2":
			dialog.text = "Perfeito! Agora marque os locais das aparições no mapa. Isso vai facilitar para tirarmos conclusões.";
			link.l1 = "Só um segundo, Gino!";
			link.l1.go = "ksochitam_18";
		break;
		
		case "ksochitam_17_3":
			dialog.text = "De jeito nenhum vamos estragar um mapa tão bonito com as nossas marcas. Você mesmo vai precisar dele, "+pchar.name+". Traga-me outro mapa, um pouco mais modesto!";
			link.l1 = "Tudo bem...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_map_wait":
			dialog.text = "Você trouxe um mapa do arquipélago, "+pchar.name+"?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "Eu tenho este velho mapa do arquipélago.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "Tenho este belo mapa do arquipélago.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "Tenho aqui um excelente mapa do arquipélago.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Ainda não, mas já encomendei. Em breve vou receber e continuaremos...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_18":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_19";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto1", "Ksochitam_SitTable", -1);
		break;
		
		case "ksochitam_19":
			dialog.text = "";
			link.l1 = "Pronto... Fiz as marcações, mas as informações ainda não são precisas. O primeiro local fica em algum lugar a noroeste de Blueweld. O segundo está no centro da ilha de Dominica.";
			link.l1.go = "ksochitam_20";
		break;
		
		case "ksochitam_20":
			dialog.text = "Alguma ideia?";
			link.l1 = "Não. Mas acho que deveríamos levar a Flecha do Caminho até lá e observar o que acontece. Claro, é como procurar uma agulha no palheiro, mas não temos ideia melhor mesmo.";
			link.l1.go = "ksochitam_21";
		break;
		
		case "ksochitam_21":
			dialog.text = "Concordo com você, "+pchar.name+". Você vai me deixar navegar com você?";
			link.l1 = "Está interessado em pôr suas suposições à prova? Seria uma honra tê-lo no convés do meu navio, Gino. Arrume suas coisas!";
			link.l1.go = "ksochitam_22";
		break;
		
		case "ksochitam_22":
			dialog.text = "Não vai demorar. Estarei pronto em algumas horas. Aqui, pegue a Flecha do Caminho.";
			link.l1 = "Bem-vindo a bordo!";
			link.l1.go = "ksochitam_23";
		break;
		
		case "ksochitam_23":
			LAi_SetOwnerType(npchar);
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_24";
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetPlayerType(pchar);
			GiveItem2Character(pchar, "arrowway");
			pchar.questTemp.Ksochitam = "seekway";
			sld = ItemsFromID("skinmap");
			sld.mark = 1;
			pchar.quest.Ksochitam_room.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Ksochitam_room.win_condition.l1.location = pchar.location;
			pchar.quest.Ksochitam_room.function = "Ksochitam_JinoPassenger";
			AddQuestRecord("Ksochitam", "2");
		break;
		
		case "ksochitam_24":
			dialog.text = "Sim, sim, "+pchar.name+", estou me preparando. Logo estarei pronto.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_24";
		break;
		
		case "ksochitam_25":
			dialog.text = "E daí, "+pchar.name+", estamos tendo alguma sorte na nossa busca?";
			link.l1 = "Estávamos certos. É isso. O ídolo indígena é uma das suas formas.";
			link.l1.go = "ksochitam_26";
		break;
		
		case "ksochitam_26":
			dialog.text = "Oh! Deve ser um daqueles ídolos que supostamente transportavam pessoas para Tayasal! Eu estava te contando sobre eles, lembra? Então, para onde está apontando a Flecha do Caminho?";
			link.l1 = "Está apontando para noroeste. Marquei a direção no mapa. Mas a linha desenhada atravessa quase todo o Mar do Caribe. Precisamos encontrar outra aparição em Dominica para achar Ksocheatem.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_27":
			dialog.text = "Tenho certeza de que vamos encontrar outro ídolo lá... você concorda com a minha hipótese, "+pchar.name+"?";
			link.l1 = "Eu sei, Gino. Agora vamos parar de perder tempo e começar a procurar.";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_28":
			DialogExit();
			locations[FindLocation(pchar.location)].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
		break;
		
		case "ksochitam_29":
			dialog.text = "E daí, "+pchar.name+", você encontrou algo interessante?";
			link.l1 = "Estávamos certos. É isso. O ídolo indígena é uma das suas formas.";
			link.l1.go = "ksochitam_30";
		break;
		
		case "ksochitam_30":
			dialog.text = "Oh! Deve ser um daqueles ídolos que, dizem, transportavam pessoas para Tayasal! Eu estava te contando sobre eles, lembra? Então, para onde a Flecha do Caminho está apontando?";
			link.l1 = "Noroeste. Marquei a direção no mapa. Mas a linha traçada atravessa quase todo o Mar do Caribe. Precisamos encontrar outro ponto de desembarque no continente para achar Ksocheatem.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_31":
			dialog.text = "E daí, "+pchar.name+", você encontrou o segundo ídolo?";
			link.l1 = "Yes. I have drawn the direction shown by the Arrow of the Way. Now we know the location of Ksocheatem; it's not the exact spot, but we know where to search! I will search the whole area where the lines cross, and I will find that damn island!";
			link.l1.go = "ksochitam_32";
		break;
		
		case "ksochitam_32":
			dialog.text = "I am glad to hear such enthusiasm in your voice. But we must prepare well for the upcoming expedition; it is unknown what we will face there. I doubt we will receive a warm welcome...";
			link.l1 = "Você está preocupado com algo específico ou só está expressando preocupações?";
			link.l1.go = "ksochitam_33";
		break;
		
		case "ksochitam_33":
			dialog.text = "Pense bem, "+pchar.name+".. Ksocheatem was created by Mayan magic performed by Kanek. It is not a natural formation and it possesses evil and destructive powers. It is unknown what awaits us there; I doubt we will find sunshine, peaceful seas, whores, or a calm wind there.";
			link.l1 = "Certo, Gino. Vou considerar suas palavras e me preparar para a expedição. Vou deixar meu navio pronto e cuidar das poções e da munição...";
			link.l1.go = "ksochitam_34";
		break;
		
		case "ksochitam_34":
			dialog.text = "Uma decisão muito sábia. Então, vamos voltar para o navio?";
			link.l1 = "Claro! Vamos!";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_35":
			dialog.text = "Chegamos, "+pchar.name+"! Uh, o vento está uivando!";
			link.l1 = "Sim, Gino, você tinha razão, não tem nenhum sol para nos receber... Também não vejo nenhuma prostituta. Na verdade, nem sei o que nos espera aqui.";
			link.l1.go = "ksochitam_36";
		break;
		
		case "ksochitam_36":
			dialog.text = "Bem, você escolheu um lugar péssimo para desembarcar, Capitão! Só tem pedras e penhascos por toda parte! E como pretende chegar ao interior da ilha daqui?";
			link.l1 = "Eu não vi nenhuma outra baía adequada para desembarcar nesta ilha por causa dessa maldita tempestade! Enfim, isso é melhor do que nada. Vou dar um jeito de me virar entre essas pedras, já passei por coisa pior. Não entre em pânico, amigo!";
			link.l1.go = "ksochitam_37";
		break;
		
		case "ksochitam_37":
			dialog.text = "Não gosto desta ilha, "+pchar.name+"!   Isso é assustador. E essa tempestade deve estar presa à ilha. Este lugar está condenado, com certeza!";
			link.l1 = "Eu também não gosto muito deste lugar, Gino! Mas essa ilha realmente existe, o que significa que a história de Kukulcan é verdadeira. Todos estaremos em perigo se ele conseguir chegar a Tayasal com a Máscara...";
			link.l1.go = "ksochitam_38";
		break;
		
		case "ksochitam_38":
			dialog.text = "Tente encontrar a Máscara, Capitão! Ela é mais importante do que todos os tesouros do mundo! Deve estar por aqui em algum lugar! Quando a tivermos, vamos destruir os planos de Kukulcan e não deixaremos que ele mude o passado!";
			link.l1 = "E como é essa máscara, você sabe?";
			link.l1.go = "ksochitam_39";
		break;
		
		case "ksochitam_39":
			dialog.text = "Não faço ideia! Mas acho que você vai reconhecer, é um artefato indígena antigo, difícil confundir com outra coisa!";
			link.l1 = "Entendi. Vou ficar de olho! Certo, Gino, volte para o navio! Não precisa ficar vagando pela ilha, sua cabeça vale demais para arriscar!";
			link.l1.go = "ksochitam_40";
		break;
		
		case "ksochitam_40":
			dialog.text = "Não vou mentir, Capitão, não sou bom de briga e não me sinto à vontade neste lugar. Posso te dar um conselho? Cada parte do Guardião está ligada à magia desta ilha. Ksatl Cha comentou que a adaga tem poder sobre os habitantes daqui, mas não sei exatamente o que ele quis dizer.   Vou ficar a bordo. Se precisar de mim, me encontre lá.";
			link.l1 = "Ótimo. Agora me deseje sorte, Gino!";
			link.l1.go = "ksochitam_41";
		break;
		
		case "ksochitam_41":
			dialog.text = "Boa sorte, "+pchar.name+"Que Deus te abençoe e te proteja!";
			link.l1 = "...";
			link.l1.go = "ksochitam_42";
		break;
		
		case "ksochitam_42":
			DialogExit();
			NextDiag.CurrentNode = "adversary";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "quest", "quest1", "Ksochitam_JinoStay", 10.0);
			AddQuestRecord("Ksochitam", "6");
		break;
		
		case "adversary":
			dialog.text = "Como você está, "+pchar.name+" ? Precisa de algum conselho? ";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L1"))
			{
				link.l1 = "Esta maldita ilha está infestada de mortos-vivos, e aqueles malditos esqueletos são surpreendentemente resistentes. Não faço ideia de como enfrentá-los.";
				link.l1.go = "adversary_1";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L2"))
			{
				link.l1 = "Se você virar à esquerda na bifurcação, vai acabar chegando à caverna. Mas para onde devo ir depois? Temo que a caverna seja um beco sem saída...";
				link.l1.go = "adversary_2";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L3"))
			{
				link.l1 = "Consegui entrar na caverna úmida, você pode mergulhar na parte submersa dela. Mas não vejo nenhuma saída por lá...";
				link.l1.go = "adversary_3";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L4"))
			{
				link.l1 = "Se você pegar à esquerda na bifurcação, vai chegar à caverna. Mas para onde devo ir depois? Temo que a caverna seja um beco sem saída...";
				link.l1.go = "adversary_4";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L5"))
			{
				link.l1 = "Há um ponto na grande caverna onde você pode mergulhar na parte alagada. Mas parece que não há saída por lá...";
				link.l1.go = "adversary_5";
			}
			link.l10 = "Está tudo certo até agora, Gino, estou bem.";
			link.l10.go = "exit";
			NextDiag.TempNode = "adversary";
		break;
		
		case "adversary_1":
			dialog.text = "Ksatl Cha mentioned the Chief's Claw. Try to use it against the skeletons; the Indian said that this dagger holds power over the inhabitants of Ksocheatem.";
			link.l1 = "Com certeza vou tentar!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L1");
		break;
		
		case "adversary_2":
			dialog.text = "E como é essa caverna?";
			link.l1 = "Bem, há uma pequena caverna na rocha, é úmida, e a água balança no fundo como as ondas do mar...";
			link.l1.go = "adversary_2_1";
		break;
		
		case "adversary_2_1":
			dialog.text = "Se a água se move, então a caverna deve ter alguma ligação com o mar e não pode ser um beco sem saída. Procure uma passagem, ela deve estar aí.";
			link.l1 = "A caminho...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L2");
		break;
		
		case "adversary_3":
			dialog.text = "Se houver um caminho da caverna principal para a alagada, e se a água se mover como ondas na principal, então a caverna alagada tem uma segunda passagem. Procure com mais atenção, mas tome cuidado ou vai acabar se afogando.";
			link.l1 = "Eu vou mergulhar...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L3");
		break;
		
		case "adversary_4":
			dialog.text = "E como é essa caverna?";
			link.l1 = "Bem, é bem grande, tem algumas cavernas, é úmida, e tem um buraco pequeno com água parada...";
			link.l1.go = "adversary_4_1";
		break;
		
		case "adversary_4_1":
			dialog.text = "Se a água estiver parada, então a caverna não tem ligação com o mar e pode ser um beco sem saída.";
			link.l1 = "Eu pensei o mesmo. Já procurei lá por muito tempo e só existe uma entrada, que também serve de saída...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L4");
		break;
		
		case "adversary_5":
			dialog.text = "Se a água ainda está na caverna, então talvez você tenha razão. Procure um pouco mais, mas não fique triste se não encontrar nada. É provável que seja um beco sem saída.";
			link.l1 = "Entendi...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L5");
		break;
		
		case "adversary_6":
			dialog.text = ""+pchar.name+", Os navios espanhóis estão atrás de nós! Agora não é a melhor hora para conversar!";
			link.l1 = "Sim, claro...";
			link.l1.go = "exit";
			NextDiag.TempNode = "adversary_6";
		break;
		
		case "ksochitam_43":
			dialog.text = "Seus olhos felizes me dizem que você encontrou o que procurava.";
			link.l1 = "Sim. Os tesouros de Miguel Dichoso e a Máscara de Kukulcan. Agora, a encarnação dele nunca mais poderá mudar o futuro!";
			link.l1.go = "ksochitam_44";
		break;
		
		case "ksochitam_44":
			dialog.text = "Incrível! Você é um herói, "+pchar.name+"...";
			link.l1 = "Gino, você tem certeza de que isso é suficiente para deter Kukulcan?";
			link.l1.go = "ksochitam_45";
		break;
		
		case "ksochitam_45":
			dialog.text = "Segundo Ksatl Cha, sim. E ele estava citando Urakan. O pai dele, Kanek, foi quem começou toda essa confusão. Alguma dúvida?";
			link.l1 = "Fui recebido na baía por um visitante do passado – Alonso de Maldonado. Ele estava em Tayasal quando Kanek realizou o ritual para criar o Guardião da Verdade. Foi arrastado para a fenda espaço-temporal, mas sobreviveu... Até hoje.";
			link.l1.go = "ksochitam_46";
		break;
		
		case "ksochitam_46":
			dialog.text = "";
			link.l1 = "Ele disse que eu preciso fechar o portal de uma vez por todas para proteger o nosso mundo. Para isso, tenho que destruir a Máscara em um altar em Tayasal.";
			link.l1.go = "ksochitam_47";
		break;
		
		case "ksochitam_47":
			dialog.text = "E você vai para Tayasal? Isso é loucura! "+pchar.name+", você conseguiu a máscara e a encarnação de Kukulcan não poderá fazer nada! E o próprio Kanek tem certeza disso! Por isso Urakan enviou Ksatl Cha para encontrar Ksocheatem – para pegar a Máscara e destruí-la.";
			link.l1 = "E se esse Urakan estivesse planejando destruir a máscara em Tayasal?";
			link.l1.go = "ksochitam_48";
		break;
		
		case "ksochitam_48":
			dialog.text = ""+pchar.name+", até agora, só um homem conseguiu escapar vivo de Tayasal, e esse foi Miguel Dichoso. Também Maldonado, mas ele foi uma exceção. Mesmo que a encarnação de Kukulcan volte ao passado, ele será morto pelos antigos maias!";
			link.l1 = "E se eles não o matarem, mas o reconhecerem?";
			link.l1.go = "ksochitam_49";
		break;
		
		case "ksochitam_49":
			dialog.text = "Então, você está planejando uma expedição para Tayasal?";
			link.l1 = "Eu não sei, Gino. Sinceramente, não sei...";
			link.l1.go = "ksochitam_50";
		break;
		
		case "ksochitam_50":
			dialog.text = "Então pense nisso, por que faria isso? Você já ouviu minha opinião. Agora depende de você..."+pchar.name+", você vai me levar para St. John's?";
			link.l1 = "Certo, Gino. Vamos zarpar o quanto antes. Já tive o bastante desta ilha miserável.";
			link.l1.go = "ksochitam_51";
		break;
		
		case "ksochitam_51":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_52";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Ksochitam", "16");
			pchar.quest.Ksochitam_gohome.win_condition.l1 = "location";
			pchar.quest.Ksochitam_gohome.win_condition.l1.location = "sentjons_town";
			pchar.quest.Ksochitam_gohome.function = "Ksochitam_ArriveHome";
			pchar.questTemp.Ksochitam = "gohome";
		break;
		
		case "ksochitam_52":
			dialog.text = "Vamos chegar em casa logo, "+pchar.name+"? Sinto tanta falta dos meus frascos e tubos...";
			link.l1 = "Sim, sim, Gino, logo estaremos em Antígua.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_52";
		break;
		
		case "ksochitam_53":
			dialog.text = "Que bom que finalmente estamos de volta! Não consigo imaginar como vocês marinheiros conseguem passar tanto tempo nesses navios...";
			link.l1 = "É questão de hábito, Gino.";
			link.l1.go = "ksochitam_54";
		break;
		
		case "ksochitam_54":
			dialog.text = "Vou me deitar na minha cama, sentindo o chão firme sob os pés, com grande prazer... Espero, "+pchar.name+", que você nem pensou em visitar Tayasal?";
			link.l1 = "Ainda não sei, Gino. Para ser sincero, ainda não tenho certeza.";
			link.l1.go = "ksochitam_55";
		break;
		
		case "ksochitam_55":
			dialog.text = "Destrua a máscara de Kukulcan e viva sem preocupações, Capitão. Se quiser, podemos dissolver a máscara no ácido mais forte que tenho. Não vou guardar ressentimento por causa disso.";
			link.l1 = "Sabe, vou esperar um pouco. Sempre teremos tempo para destruir isso.";
			link.l1.go = "ksochitam_56";
		break;
		
		case "ksochitam_56":
			dialog.text = "A decisão é sua. Se resolver poupar este mundo desse artefato, venha até mim. Minha gratidão por uma viagem maravilhosa, Capitão!";
			link.l1 = "Quando quiser, Gino. Até mais!";
			link.l1.go = "exit";
			NextDiag.TempNode = "first time";
			AddDialogExitQuestFunction("Ksochitam_TripComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Você é um "+GetSexPhrase("Ladrão, senhor! Guardas, peguem ele","Ladrão, garota! Guardas, peguem ela ")+"!!!","Olha só! No momento em que me perdi em contemplação, você resolveu mexer no meu baú! Ladrão! Peguem o ladrão!!!","Guardas! Roubo! Peguem o ladrão!!!");
			link.l1 = "Droga!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
