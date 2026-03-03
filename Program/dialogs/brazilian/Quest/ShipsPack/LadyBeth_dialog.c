void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "AlonsoNaPalube":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube"))
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube2 = true;
				dialog.text = "Sua decisão, Capitão? Talvez não devêssemos?";
				link.l1 = "Você conseguiu recrutar mais voluntários para a tarefa?";
				link.l1.go = "AlonsoNaPalube_StrongGroup";
			}
			else
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube = true;
				dialog.text = "Capitão, uma palavra.";
				link.l1 = "Relate, Alonso.";
				link.l1.go = "AlonsoNaPalube_2";
			}
			locCameraFromToPos(-10.33, 9.69, -22.16, true, -5.22, 7.19, -21.06);
		break;
		
		case "AlonsoNaPalube_2":
			dialog.text = "A tripulação está se perguntando quais são seus planos para Cayman. O pessoal está preocupado.";
			link.l1 = "Ainda não decidi. E por que os homens estão preocupados, Alonso?";
			link.l1.go = "AlonsoNaPalube_3";
		break;
		
		case "AlonsoNaPalube_3":
			dialog.text = "Esta ilha é o domínio do Capitão Blackwood. Os marinheiros dizem que ele está cavando tudo por aqui como um homem possuído, de ponta a ponta. Que já arruinou dezenas de homens nessas escavações... E os que conseguem sair de lá... contam histórias estranhas.";
			link.l1 = "Que tipo de histórias?";
			link.l1.go = "AlonsoNaPalube_4";
		break;
		
		case "AlonsoNaPalube_4":
			dialog.text = "O Blackwood já não é mais o homem que foi um dia. Ele está obcecado em encontrar um tesouro de conquistador. Está disposto a sacrificar tudo e todos por isso. Sabemos o quanto você gosta de se meter em histórias bonitas, desembarcar sozinho e cair em armadilhas... Pois desta vez, você não vai escapar.";
			link.l1 = "Obrigado pelo relatório e pelo aviso. Se eu decidir desembarcar, vou garantir que esteja à frente com um destacamento dos nossos melhores combatentes.";
			link.l1.go = "AlonsoNaPalube_5";
		break;
		
		case "AlonsoNaPalube_5":
			dialog.text = "Isso pode ser complicado, Capitão. Abordar um navio é uma coisa, mas desembarcar sob as balas dos fuzileiros e os sabres da ralé que dizem que Blackwood contratou de todos os cantos das Pequenas Antilhas é bem diferente. E circulam boatos ruins sobre Cayman... Não, não vai encontrar muitos voluntários para esse tipo de serviço.";
			link.l1 = "Então teremos que nos virar com quem estiver disponível. Sua participação é obrigatória, Alonso.";
			link.l1.go = "AlonsoNaPalube_LiteGroup";
			link.l2 = "Na minha opinião, já provei para todos tudo o que podia ser provado. Todos os bons lutadores e atiradores vão. Isso é uma ordem.";
			link.l2.go = "AlonsoNaPalube_StrongGroup";
			link.l3 = "Hum... Bem, preciso pensar em tudo isso. Talvez a gente volte a esse assunto mais tarde.";
			link.l3.go = "AlonsoNaPalube_Exit";
		break;
		
		case "AlonsoNaPalube_Exit":
			SetFunctionLocationCondition("LadyBeth_CaimanSea", "Caiman", false);
			EndQuestMovie();
			bQuestDisableMapEnter = false;
			chrDisableReloadToLocation = false;
			if(UnloadLocation(loadedLocation) == true)
			{
				pchar.Ship.Pos.x = 0;
				pchar.Ship.Pos.z = 0;
				pchar.Ship.Ang.y = 0;
				Land_MapLoad();
				pchar.location = "";
			}
		break;
		
		case "AlonsoNaPalube_LiteGroup":
			dialog.text = "Sim, Capitão!";
			link.l1 = "E o navio do Blackwood? Não vai causar problemas?";
			link.l1.go = "AlonsoNaPalube_Vpered";
			pchar.questTemp.LadyBeth_LiteGroup = true;
		break;
		
		case "AlonsoNaPalube_StrongGroup":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 40 || sti(pchar.rank) >= 12)
			{
				dialog.text = "Sim, Capitão!";
				link.l1 = "E o navio do Blackwood? Não vai causar problemas?";
				link.l1.go = "AlonsoNaPalube_Vpered";
				pchar.questTemp.LadyBeth_StrongGroup = true;
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 40) Notification_Skill(true, 40, SKILL_LEADERSHIP);
				if (sti(pchar.rank) >= 12) Notification_Level(true, 12);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube2"))
				{
					dialog.text = "Ainda não, Capitão.";
				}
				else
				{
					dialog.text = "Você não precisa provar nada para mim ou para seus oficiais, e seguiremos suas ordens para onde quiser, mas o marinheiro comum pensa diferente. Receio que teremos problemas, Capitão.";
				}
				link.l1 = "Então vamos ter que nos virar com quem estiver disponível. Sua participação é obrigatória, Alonso.";
				link.l1.go = "AlonsoNaPalube_LiteGroup";
				link.l2 = "Hum... Bem, preciso pensar melhor sobre tudo isso. Talvez a gente volte a esse assunto depois.";
				link.l2.go = "AlonsoNaPalube_Exit";
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 40) Notification_Skill(false, 40, SKILL_LEADERSHIP);
				if (sti(pchar.rank) < 12) Notification_Level(false, 12);
			}
		break;
		
		case "AlonsoNaPalube_Vpered":
			dialog.text = "Uma snow. Dizem que é uma verdadeira beleza com um temperamento feroz. Eu não me preocuparia com ela. Provavelmente, toda a tripulação está ralando em terra firme enquanto o navio está bem escondido nas reentrâncias da costa. Quando — e se — vencermos, podemos tomá-la como prêmio direto da praia.";
			link.l1 = "Reúna os homens. Hoje é um bom dia – a sorte estará do nosso lado.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_AlonsoNaPalube_Vpered");
		break;
		
		// Диалог в таверне с Блеквудом
		case "LadyBeth_DialogInCity": // главное меню
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Fourth"))
			{
				dialog.text = "Bom te ver, Capitão. Acho que já conversamos sobre tudo...";
				link.l1 = "De fato. Adeus.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LadyBeth_DialogInCity_again";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Third"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", "+npchar.name+"";
				link.l1.go = "LadyBeth_DialogInCity_Third_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", Capitão Blackwood.";
				link.l1.go = "LadyBeth_DialogInCity_Second_1";
				break;
			}
			if (startHeroType == 4)
			{
				dialog.text = "...";
				link.l1 = "Olá. Você é o Capitão Blackwood?";
				link.l1.go = "LadyBeth_DialogInCity_First_Helena_1";
			}
			else
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+". Você é o capitão Albert Blackwood, certo?";
				link.l1.go = "LadyBeth_DialogInCity_First_1";
			}
		break;
		
		case "LadyBeth_DialogInCity_again": // повтор
			dialog.text = "Que bom ver você, Capitão. Acho que já conversamos sobre tudo.";
			link.l1 = "De fato. Adeus.";
			link.l1.go = "exit";
			NextDiag.TempNode = "LadyBeth_DialogInCity_again";
		break;
		
		case "LadyBeth_DialogInCity_First_1": // первый диалог
			dialog.text = "Sim, sou eu. E você?";
			link.l1 = "Capitão "+GetFullName(pchar)+". Eu comando o navio '"+PChar.Ship.Name+"'.";
			link.l1.go = "LadyBeth_DialogInCity_First_2";
		break;
		
		case "LadyBeth_DialogInCity_First_2":
			dialog.text = "Capitão... Você já esteve em Cayman?";
			link.l1 = "Só passei por aqui.";
			link.l1.go = "LadyBeth_DialogInCity_First_3";
		break;
		
		case "LadyBeth_DialogInCity_First_3":
			dialog.text = "Você ouviu alguma coisa sobre tesouros por lá?";
			link.l1 = "Não, nada em especial.";
			link.l1.go = "LadyBeth_DialogInCity_First_4";
		break;
		
		case "LadyBeth_DialogInCity_First_4":
			dialog.text = "Vestígios de espanhóis? Armas antigas? Moedas da época dos conquistadores?";
			link.l1 = "Não encontrei nada parecido com isso.";
			link.l1.go = "LadyBeth_DialogInCity_First_5";
		break;
		
		case "LadyBeth_DialogInCity_First_5":
			dialog.text = "Lendas locais? Histórias sobre Cortez? Algo sobre sepultamentos?";
			link.l1 = "Me desculpe, capitão, mas eu não tenho essa informação. E isso já está começando a parecer um interrogatório.";
			link.l1.go = "LadyBeth_DialogInCity_First_6";
		break;
		
		case "LadyBeth_DialogInCity_First_6":
			dialog.text = "Me desculpe... Mau hábito de ex-oficial. É que... isso é extremamente importante pra mim.";
			link.l1 = "Por que você está tão interessado especificamente em Cayman?";
			link.l1.go = "LadyBeth_DialogInCity_First_7";
		break;
		
		case "LadyBeth_DialogInCity_First_7":
			dialog.text = "Não importa. Mais uma vez, peço desculpas.";
			link.l1 = "Entendi. Boa sorte nas suas buscas.";
			link.l1.go = "LadyBeth_DialogInCity_First_8";
		break;
		
		case "LadyBeth_DialogInCity_First_8":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Good night";
			else sStr = "Wishing you a good day";
			dialog.text = "Venha me procurar se encontrar algo que valha a pena. Eu gostaria de conversar com outro capitão... com alguém que entende o mar. "+sStr+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "LadyBeth_DialogInCity_First_9";
		break;
		
		case "LadyBeth_DialogInCity_First_9":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_1": // первый диалог с Элен
			dialog.text = "Em carne e osso. E você... Capitã Helen MacArthur? A pupila do Jan Svenson, certo? Já ouvi falar de você.";
			link.l1 = "Você está bem informado, Capitão Blackwood. Mas não me surpreende que um oficial inglês saiba sobre mim.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_2":
			dialog.text = "Ex-oficial. E todos os casacas vermelhas já sabem de você e das suas... preferências peculiares diante da Coroa. Dizem que ferro não tem cheiro. E a história de como seu pai, Sean MacArthur, te levou para o mar desde criança e te fez capitão já virou quase uma lenda na frota.";
			link.l1 = "E como é encontrar essa lenda?";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_3";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_3":
			dialog.text = "Eu, pessoalmente, estou impressionado. Embora muitos dos meus antigos colegas, devo admitir, achem isso bastante irritante. Mas para se tornar um capitão é preciso algo além de nascimento nobre ou uma patente real, não é?";
			link.l1 = "É verdade. É preciso conhecimento, experiência e estar sempre pronto para provar sua competência. Principalmente no meu caso.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_4";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_4":
			dialog.text = "Exatamente! No mar, como na vida, o que importa não são os títulos, mas os resultados. Prazer em conhecê-lo, Capitão MacArthur. Espero que nos encontremos de novo. Quem sabe você apareça para uma taça de vinho quando eu voltar da minha expedição?";
			link.l1 = "Talvez. Boa sorte nas suas buscas, Capitão.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_5_harizma";
			link.l2 = "Não estou interessado. Mas boa sorte nas suas buscas, Capitão.";
			link.l2.go = "LadyBeth_DialogInCity_First_Helena_5_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_harizma":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_oruzhie":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_1": // второй диалог
			dialog.text = "Ah, Capitão "+pchar.lastname+"! Que bom te ver. Quer se sentar?";
			link.l1 = "Com prazer.";
			link.l1.go = "LadyBeth_DialogInCity_Second_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_2":
			dialog.text = "Capitão... me diga, o que são tesouros de verdade para você?";
			link.l1 = "Um verdadeiro tesouro é o amor. A pessoa certa ao seu lado. Não há nada pior do que estar sozinho.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love";
			link.l2 = "Dinheiro, é claro. O que mais poderia ser um tesouro?";
			link.l2.go = "LadyBeth_DialogInCity_Second_3_sokrovisha";
			link.l3 = "Equipamento valioso e único. Uma boa espada ou pistola vale mais do que ouro.";
			link.l3.go = "LadyBeth_DialogInCity_Second_3_oruzhie";
			link.l4 = "Conhecimento. O tesouro mais valioso é o que você carrega na cabeça.";
			link.l4.go = "LadyBeth_DialogInCity_Second_3_znania";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love":
			if (startHeroType == 4)
			{
				dialog.text = "Amor? Hmm... Não esperava ouvir isso da filha de um pirata. Eu... eu fui noivo. Da Elizabeth. Filha de um fazendeiro de Barbados. Mas o pai dela... ele achou que eu não tinha dinheiro suficiente. O que eu poderia oferecer à filha dele além do meu amor? Você teve sorte, Capitão MacArthur. Teve um pai que valorizou mais o seu talento do que o seu dote.";
				link.l1 = "Talvez não seja questão de sorte, mas sim de que o verdadeiro amor não se mede em ouro. Meu pai entendia isso. E a sua noiva? Ela compartilha das ideias do pai dela?";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_1";
			}
			else
			{
				dialog.text = "Amor? Sim... Talvez você tenha razão. Eu... eu fui noivo. Em Barbados. Nós nos amávamos, mas... o pai dela me achou indigno. Ha! Não era rico o bastante. É por isso que estou aqui – procurando tesouros para provar que todos estavam errados. Talvez seja em vão?";
				link.l1 = "Talvez você devesse simplesmente falar com ela? Que se dane aquele fazendeiro.";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_2";
			}
			AddComplexLandExpToScill(100, 100, 0);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_2":
			dialog.text = "Conversar... Sim, talvez. Mas o que eu diria? 'Desculpe, não consegui te dar uma vida digna'? Não. Preciso voltar como vencedor. Ou não voltar nunca mais.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_1":
			dialog.text = "Elizabeth? Não... ela me ama. Mas eu... eu não podia deixá-la viver na pobreza. Ela merece mais. E eu preciso provar que sou digno dela.";
			link.l1 = "Às vezes, o orgulho atrapalha a felicidade mais do que a pobreza, Capitão.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_2":
			dialog.text = "Eu não posso voltar de mãos vazias. Simplesmente não posso. Me desculpe, tenho muito trabalho. Foi um prazer conversar com você, Capitão MacArthur.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha":
			dialog.text = "Que resposta banal. Mas é difícil discordar. De fato, quando você cresce nos cortiços de Bristol, quando precisa lutar por migalhas... começa a entender o verdadeiro valor do dinheiro. Não é luxo. É liberdade. É poder nunca mais voltar para aquela imundície de onde você saiu com tanto esforço.";
			link.l1 = "Concordo. Dinheiro resolve a maioria dos problemas. E se não resolve, é porque simplesmente não tem o bastante.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_sokrovisha_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha_2":
			dialog.text = "Exatamente! Você entende. Dinheiro não traz felicidade, mas a falta dele com certeza traz infelicidade. Eu sei disso melhor do que ninguém...";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie":
			dialog.text = "Interessante. Prático. Eu tenho uma arcabuz... de verdade, da época dos conquistadores. Presente de um certo padre. Às vezes acho que vale mais do que todo o ouro que já encontrei. Mas... não vai resolver meus problemas.";
			link.l1 = "Boas armas podem resolver muitos problemas. E elas nunca vão te trair.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie_2":
			dialog.text = "Isso é verdade. Mas algumas batalhas não podem ser vencidas só pela força das armas.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_znania":
			dialog.text = "Conhecimento... Sim, eu entendo. Estudei tudo o que pude sobre os conquistadores, sobre tesouros. Compilei um manual inteiro sobre caça ao tesouro. Criei um sistema de treinamentos regulares e recompensas materiais para a companhia de fuzileiros do navio. Qualquer capitão ficaria feliz em ter meu manual. Mas todo esse conhecimento... Não serve de nada se não levar a resultados. Resultados de verdade.";
			link.l1 = "Mas é o conhecimento que leva aos resultados. Sem ele, qualquer busca é só andar às cegas.";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "LadyBeth_DialogInCity_Second_4":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Well, it's already late, and I have a lot of work to do";
			else sStr = "Well, I have a lot of work to do";
			dialog.text = ""+sStr+". Obrigado pela conversa, Capitão. Foi realmente interessante.";
			link.l1 = "Obrigado, igualmente. "+Goodbye(true)+".";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_5":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Third = true;
		break;
		
		case "LadyBeth_DialogInCity_Third_2": // третий диалог
			dialog.text = "Ah, "+pchar.name+"! Que bom te ver. Tenho ótimas notícias – finalmente encontrei uma solução para os meus problemas. Em breve vou partir numa expedição, e desta vez vou voltar com um tesouro de verdade! Ah, um conselho de amigo – mantenha distância de Cayman. Agora aquele território é meu.";
			link.l1 = "Cayman não te pertence, Albert. Você não tem direitos da coroa sobre ele. Isso é pirataria.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma";
			link.l2 = "Você está me ameaçando, Blackwood?";
			link.l2.go = "LadyBeth_DialogInCity_Third_3_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma":
			dialog.text = "Direitos da Coroa? Você devia ter vivido nos cortiços de Bristol, "+pchar.name+", então você entenderia o valor desses papéis. Quando se está com fome, a lei não significa nada. Mas... você tem razão. Formalmente, não tenho nenhum direito sobre a ilha. Mas lá encontrei o que procurei por anos. E não vou deixar ninguém tirar isso de mim.";
			link.l1 = "Espero que você entenda que está seguindo um caminho perigoso.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma_2":
			dialog.text = "Sempre soube que meu caminho não seria fácil. Adeus, "+pchar.name+". Talvez a gente se encontre de novo.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie":
			dialog.text = "Ameaçando? Não, de jeito nenhum. Só um conselho amigável de um capitão para outro. Cayman é perigosa... principalmente para quem se mete nos meus assuntos.";
			link.l1 = "Vou lembrar do seu 'conselho'. Boa sorte em Cayman.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie_2":
			dialog.text = "E boa sorte para você, Capitão. Espero que não precise dela. Adeus.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_4":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Fourth = true;
		break;
		
		// Ловушка, абордаж в каюте
		case "LadyBeth_abordage":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Você?!! Acha que vou me render? Acha que vou voltar pra miséria? Prefiro morrer do que passar fome de novo na sarjeta! Sem piedade, sem recompensa, sem vitória! Debaixo do beliche tem um barril de pólvora... Vamos todos afundar juntos!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
			else
			{
				dialog.text = "Quem é você para me atacar?! Acha que vou me render? Não! Prefiro morrer a voltar a passar fome na miséria! Sem piedade, sem recompensa, sem vitória! Debaixo do beliche tem um barril de pólvora... Vamos todos afundar juntos!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
		break;
		
		// Блеквуд разговаривает с ГГ перед битвой на Каймане
		case "LadyBeth_BlackWood_Boss":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Capitão! Eu te avisei. Agora vai pagar pela sua curiosidade.";
			}
			else
			{
				dialog.text = "Quem é você e como ousa invadir o meu território?! Esta ilha é minha!";
			}
			link.l1 = "Vamos ver, Blackwood. Hoje haverá um homem obcecado a menos neste mundo.";
			link.l1.go = "LadyBeth_BlackWood_Boss_oruzhie_1";
			link.l2 = "Vamos resolver isso de forma pacífica, Blackwood. Eu posso ir embora.";
			link.l2.go = "LadyBeth_BlackWood_Boss_torgovlya_1";
			link.l3 = "Blackwood, você é um homem sensato! Você é um oficial! Tem a bandeira real hasteada no seu acampamento, pelo amor de Deus! Não podemos chegar a um acordo?";
			link.l3.go = "LadyBeth_BlackWood_Boss_harizma_1";
		break;
		
		case "LadyBeth_BlackWood_Boss_oruzhie_1":
			dialog.text = "Obcecado? Ha! Sou apenas um homem que sabe o que quer!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_1":
			dialog.text = "Sair? Depois do que você viu? Não, não, não! Ninguém pode saber o que eu encontrei aqui. Ninguém!";
			link.l1 = "Eu te dou minha palavra de que não vou contar a ninguém. Juro pela honra de um capitão.";
			link.l1.go = "LadyBeth_BlackWood_Boss_torgovlya_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_2":
			dialog.text = "Neste mundo não existe honra, Capitão. Só há sujeira, miséria e desprezo. Lamento, mas você precisa morrer aqui.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
		break;
		
		case "LadyBeth_BlackWood_Boss_harizma_1":
			dialog.text = "Eu pensei. Pensei muito. E percebi – essa é minha única chance. Ou eu encontro o ouro de Cortez, ou... nada. Entende? NADA! Eu não vou voltar pra minha vida de antes! Não vou voltar pra miséria e sujeira! Prefiro morrer aqui!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_2":
			dialog.text = "À batalha! Bullock, Fraser – disparem a metralha se eles se aproximarem! Hopkins, avance!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_CaimanKino_11");
		break;
		
		// Диалоги с офицерами
		case "LadyBeth_Helena_1": // Элен
			dialog.text = "Você está bem?";
			link.l1 = "Sim, está tudo bem. E você?";
			link.l1.go = "LadyBeth_Helena_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Helena_2":
			dialog.text = "Vivo. Mas essas batalhas em terra não são pra mim. Me dê um convés sob os pés e eu destruo qualquer navio, mas aqui... lugar estranho. Fazer uma centena de lobos-do-mar desembarcar, pegar picaretas, construir fortificações... Isso eu não conseguiria.";
			link.l1 = "Blackwood sabia como inspirar sua tripulação.";
			link.l1.go = "LadyBeth_Helena_3";
		break;
		
		case "LadyBeth_Helena_3":
			dialog.text = "Ouvi falar dele lá em Bluefield. Muitos marinheiros ingleses falavam dele com respeito. O melhor oficial da frota, uma carreira brilhante... e de repente jogou tudo fora para caçar tesouros.";
			link.l1 = "O que você acha dele?";
			link.l1.go = "LadyBeth_Helena_4";
		break;
		
		case "LadyBeth_Helena_4":
			dialog.text = "Acho que o exemplo do Blackwood mostra claramente o peso da responsabilidade que nós... digo, que você carrega diante... dos seus homens. Por favor, não se torne o mesmo tipo de capitão que ele se tornou.";
			link.l1 = " Vou tentar, Helen.";
			link.l1.go = "LadyBeth_Helena_5";
		break;
		
		case "LadyBeth_Helena_5":
			dialog.text = "Obrigado, meu Capitão. Eu sei que você vai conseguir.";
			link.l1 = "Nós vamos.";
			link.l1.go = "LadyBeth_Helena_6";
		break;
		
		case "LadyBeth_Helena_6":
			dialog.text = "Nós vamos.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Helena_7";
		break;
		
		case "LadyBeth_Helena_7":
			DialogExit();
			ReturnOfficer_Helena();
		break;
		
		case "LadyBeth_Mary_1": // Мэри
			dialog.text = "Charles... que lugar terrível é esse.";
			link.l1 = "Você está bem, Mary? Você aguentou firme como uma verdadeira soldada.";
			link.l1.go = "LadyBeth_Mary_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Mary_2":
			dialog.text = "Não, eu não estou nada bem, tá bom? Olha pra essas pessoas! Trabalharam até a exaustão, viveram na fome, morreram de doenças... E pra quê? Por um ouro que talvez nem exista.";
			link.l1 = "Blackwood acreditava que estava aqui.";
			link.l1.go = "LadyBeth_Mary_3";
		break;
		
		case "LadyBeth_Mary_3":
			dialog.text = "Esse casaco vermelho... igualzinho ao meu. Um oficial inglês... Sabe, de repente pensei nos meus pais, tá? Nas minhas origens... no que eu nunca conheci. Será que eu também sou um deles?";
			link.l1 = "Um desses?";
			link.l1.go = "LadyBeth_Mary_4";
		break;
		
		case "LadyBeth_Mary_4":
			dialog.text = "Aqueles que procuram algo que talvez nem exista. E então se perdem na busca. Eu... Eu gostaria de falar sobre isso depois, tudo bem. Quando sairmos deste lugar terrível.";
			link.l1 = "Claro, Mary.";
			link.l1.go = "LadyBeth_Mary_5";
		break;
		
		case "LadyBeth_Mary_5":
			dialog.text = "Vamos enterrá-lo primeiro, por favor? Mesmo que ele não mereça. Pelo homem que ele já foi um dia.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Mary_6";
		break;
		
		case "LadyBeth_Mary_6":
			DialogExit();
			ReturnOfficer_Mary();
		break;
		
		case "LadyBeth_Tichingitu_1": // Тичингиту
			dialog.text = "Capitão, Tichingitu sente que este lugar é ruim. Muito ruim.";
			link.l1 = "O que você quer dizer?";
			link.l1.go = "LadyBeth_Tichingitu_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Tichingitu_2":
			dialog.text = "Esta ilha agora está amaldiçoada. A terra absorveu sangue e lágrimas demais. Todo mundo que cava aqui respira essa maldição.";
			link.l1 = "Você acha que o Blackwood estava possuído?";
			link.l1.go = "LadyBeth_Tichingitu_3";
		break;
		
		case "LadyBeth_Tichingitu_3":
			dialog.text = "Não só possuído. Ele está... como posso dizer... um vaso vazio. Algo entrou nele e expulsou sua alma. Já vi isso antes. Quando o xamã da minha tribo oferecia sacrifício humano aos espíritos. Aquele xamã tinha o mesmo olhar.";
			link.l1 = "Mas o que poderia causar uma obsessão assim?";
			link.l1.go = "LadyBeth_Tichingitu_4";
		break;
		
		case "LadyBeth_Tichingitu_4":
			dialog.text = "Homem com vazio por dentro é fácil de encher com outros pensamentos. Alguém encontra sua fraqueza e se aproveita disso. Tichingitu quase sente pena desse homem.";
			link.l1 = "Quase?";
			link.l1.go = "LadyBeth_Tichingitu_5";
		break;
		
		case "LadyBeth_Tichingitu_5":
			dialog.text = "Sim, quase isso. Todo guerreiro é responsável por suas próprias escolhas. Mesmo que demônios sussurrem em seu ouvido.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Tichingitu_6";
		break;
		
		case "LadyBeth_Tichingitu_6":
			DialogExit();
			ReturnOfficer_Tichingitu();
		break;
		
		case "LadyBeth_Irons_1": // Томми
			dialog.text = "Droga, Capitão! Olha só isso! Igualzinho aos velhos tempos!";
			link.l1 = "Você sabe muito bem como é a guerra em terra.";
			link.l1.go = "LadyBeth_Irons_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Irons_2":
			dialog.text = "Isso me lembra a Batalha de Naseby. Nossa ala de cavalaria se chocou com os cavaleiros de Rupert. Eles lutaram com a mesma ferocidade pelo rei deles.";
			link.l1 = "O que você acha do Blackwood?";
			link.l1.go = "LadyBeth_Irons_3";
		break;
		
		case "LadyBeth_Irons_3":
			dialog.text = "Esse tal de Blackwood era ou um gênio ou completamente maluco. Acho que os dois. Sabe o que me surpreende? Os homens dele. Muitos eram ex-militares. Não uns qualquer da rua, mas soldados de verdade. E todos seguiram ele nessa loucura. Até a infantaria naval do Fox. Ha! Esse aí vai ficar satisfeito com o massacre de hoje! Nunca perdoou eles por terem desertado.";
			link.l1 = "Talvez seja pelo dinheiro?";
			link.l1.go = "LadyBeth_Irons_4";
		break;
		
		case "LadyBeth_Irons_4":
			dialog.text = "Não, tem mais coisa aí. Esse cara tinha poder sobre eles. Poder de verdade. E também ouvi dizer que ele era noivo de uma moça rica de Barbados. Estranho que ele não tenha se casado com ela depois de conseguir todos esses tesouros. Típico soldado — não sabia a hora de parar a guerra.";
			link.l1 = "Obrigado, Tommy. Você pensa mesmo, hein.";
			link.l1.go = "LadyBeth_Irons_5";
		break;
		
		case "LadyBeth_Irons_5":
			dialog.text = "Hã?";
			link.l1 = "Nada.";
			link.l1.go = "LadyBeth_Irons_6";
		break;
		
		case "LadyBeth_Irons_6":
			DialogExit();
			ReturnOfficer_Irons();
		break;
		
		case "LadyBeth_Knippel_1": // Книппель
			dialog.text = "Que amargura ver isso, Capitão. A que ponto chegamos?!";
			link.l1 = "Nós?";
			link.l1.go = "LadyBeth_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Knippel_2":
			dialog.text = "A frota inglesa! Olhe só: pequenos pontos de casacas vermelhas deitados numa pilha dessa escória morta!";
			link.l1 = "Alguns desses 'canalhas' são do nosso povo, Charlie. Eu entendo o que você sente, mas...";
			link.l1.go = "LadyBeth_Knippel_3";
		break;
		
		case "LadyBeth_Knippel_3":
			dialog.text = "Que se dane isso, senhor!";
			link.l1 = "Eu entendo o que você sente, mas é melhor direcionar sua raiva e decepção para o Blackwood. Foi ele quem desertou da sua querida frota inglesa e os trouxe até aqui.";
			link.l1.go = "LadyBeth_Knippel_4";
			link.l2 = "De fato. Vamos, o dia ainda não acabou.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_4":
			dialog.text = "Eles só estavam seguindo o comandante deles!";
			link.l1 = "Como você seguiu o Fleetwood?";
			link.l1.go = "LadyBeth_Knippel_5";
			link.l2 = "De fato. Vamos, o dia ainda não acabou.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_5":
			dialog.text = "Como se eu fosse te seguir!";
			link.l1 = "Espero ser um capitão melhor do que Blackwood e Fleetwood. Vamos, o dia ainda não acabou.";
			link.l1.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_6":
			dialog.text = "Sim, Capitão. E quando acabar – vou beber até o próximo acabar.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Knippel_7";
		break;
		
		case "LadyBeth_Knippel_7":
			DialogExit();
			ReturnOfficer_Knippel();
		break;
		
		case "LadyBeth_Alonso_1": // Алонсо
			dialog.text = "Madre de Deus, Capitão! Você está bem?";
			link.l1 = "Isso ainda vamos descobrir. Quantos homens perdemos?";
			link.l1.go = "LadyBeth_Alonso_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Alonso_2":
			
			dialog.text = "Morto? Nessa empreitada, nós perdemos "+sti(pchar.SailorDiedInBattleInfo)+" homens. Não quero parecer intrometido, Capitão, mas... Eu te avisei!";
			link.l1 = "Vou ignorar esse comentário porque hoje você se superou, Alonso. Onde foi que você aprendeu tantos talentos?";
			link.l1.go = "LadyBeth_Alonso_3";
		break;
		
		case "LadyBeth_Alonso_3":
			dialog.text = "Um dia eu te conto essa história, Capitão – se vivermos o bastante, é claro.";
			link.l1 = "Mais algum conselho valioso?";
			link.l1.go = "LadyBeth_Alonso_4";
		break;
		
		case "LadyBeth_Alonso_4":
			dialog.text = "Se houvesse tesouros aqui, já teriam encontrado faz tempo. Mas ainda assim devemos vasculhar a ilha e procurar sobreviventes, depois decidir o que fazer com eles. E não podemos esquecer o navio do Blackwood: só ouvi elogios sobre aquela maravilha de escuna. Seria um desperdício perder um prêmio desses, Capitão. Claro, só estou transmitindo o que a tripulação pensa sobre isso.";
			link.l1 = "Claro. Vamos. O saque nos espera!";
			link.l1.go = "LadyBeth_Alonso_5";
		break;
		
		case "LadyBeth_Alonso_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		// Диалог с матросом в гроте Каймана
		case "LadyBeth_MatrosyInGrot":
			dialog.text = "Não atirem! Nós nos rendemos!";
			link.l1 = "Quem é você?";
			link.l1.go = "LadyBeth_MatrosyInGrot_2";
		break;
		
		case "LadyBeth_MatrosyInGrot_2":
			dialog.text = "Nós... nós somos do 'Lady Beth'. Tripulação do Capitão Blackwood. Ele... ele está vivo?";
			link.l1 = "Não. Seu capitão está morto.";
			link.l1.go = "LadyBeth_MatrosyInGrot_3";
		break;
		
		case "LadyBeth_MatrosyInGrot_3":
			dialog.text = "Então acabou... Graças a Deus.";
			link.l1 = "Você não parece estar de luto pelo seu capitão.";
			link.l1.go = "LadyBeth_MatrosyInGrot_4";
		break;
		
		case "LadyBeth_MatrosyInGrot_4":
			dialog.text = "Você não entende. Blackwood era um grande homem. O melhor capitão que já conheci. Mas nos últimos meses... ele mudou. Ficou obcecado, cruel. Nos fazia trabalhar dia e noite, procurando por algo que talvez nem exista.";
			link.l1 = "Vou te levar para a minha tripulação. Precisamos de marinheiros experientes.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda";
			link.l2 = "Ai dos vencidos, rapazes. Agora o lugar de vocês é no meu porão. Se tiverem sorte, ainda vão ver alguma plantação em Barbados.";
			link.l2.go = "LadyBeth_MatrosyInGrot_PlusRaby";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda":
			dialog.text = "Sério? Você... você não tem medo de que a gente... de que tem algo errado com a gente depois de tudo isso?";
			link.l1 = "Todo mundo merece uma segunda chance.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda_1";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda_1":
			dialog.text = "Obrigado, Capitão. Juro que não vai se arrepender. Somos bons marinheiros. E... talvez agora os pesadelos parem.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 30;
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusRaby":
			dialog.text = "Obrigado, obrigado! Pelo menos vamos sobreviver. Tire a gente daqui, por favor. Esta ilha... é como se fosse amaldiçoada.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+30);
		break;
		
		case "LadyBeth_MatrosyInGrot_exit":
			DialogExit();
			for (i=1; i<=8; i++)
			{
				sld = CharacterFromID("LadyBeth_MatrosyPryachutsya_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		break;
		
		// Диалог с матросом на Леди Бет
		case "LadyBeth_EnemyMatros_1":
			dialog.text = "Que diabos?! Como vocês ousam atacar a 'Lady' e matar o Jeremy? Vocês não vão sair vivos daqui, seus canalhas, o capitão vai voltar e...";
			link.l1 = "Seu capitão está morto. Jeremy atirou primeiro, e eu vou levar sua 'Dama' como prêmio legítimo, pago com sangue.";
			link.l1.go = "LadyBeth_EnemyMatros_2";
		break;
		
		case "LadyBeth_EnemyMatros_2":
			dialog.text = "O capitão... morto? Você está mentindo, seu cachorro! Você não vale nem um botão do uniforme dele!";
			link.l1 = "Se esse uniforme significava algo, era para o Blackwood que já se foi. A escolha é de vocês – lutar por um homem morto ou salvar suas vidas.";
			link.l1.go = "LadyBeth_EnemyMatros_3";
		break;
		
		case "LadyBeth_EnemyMatros_3":
			if (CharacterIsHere("Helena"))
			{
				StartInstantDialog("Helena", "LadyBeth_EnemyMatros_Helena_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Knippel"))
			{
				StartInstantDialog("Knippel", "LadyBeth_EnemyMatros_Knippel_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Irons"))
			{
				StartInstantDialog("Irons", "LadyBeth_EnemyMatros_Irons_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			dialog.text = "Não vamos entregar o navio sem lutar!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		case "LadyBeth_EnemyMatros_Helena_1":
			dialog.text = "Escutem, pessoal. Sei que vocês são leais ao seu capitão. Isso merece respeito. Mas ele morreu, e vocês estão vivos. Agora precisam decidir como seguir em frente. Estamos oferecendo a vocês uma chance de recomeçar.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_Knippel_1":
			dialog.text = "Capitão, esses homens não são inimigos. Eles só estavam cumprindo ordens. Muitos deles são ex-marinheiros da coroa, bem treinados e disciplinados. Seria um desperdício não aproveitar as habilidades deles. Rapazes, já estive no lugar de vocês mais de uma vez nos meus anos de serviço na frota. E fiz a escolha certa. Façam o mesmo.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
		break;
		
		case "LadyBeth_EnemyMatros_Irons_1":
			dialog.text = "Pois bem, marujos! A escolha é simples – ou vocês vivem, seja como prisioneiros no porão ou se juntando à nossa tripulação com boa comida e pagamento regular, ou então... (passa o dedo pelo pescoço) Se fosse vocês, eu escolheria a primeira opção!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_10";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_5":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_6", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_6":
			dialog.text = "...";
			link.l1 = "Você vai fazer parte da minha tripulação.";
			link.l1.go = "LadyBeth_EnemyMatros_7";
			link.l2 = "Ai dos vencidos, rapazes. Agora o lugar de vocês é no meu porão. Se tiverem sorte, ainda vão acabar numa plantação em Barbados.";
			link.l2.go = "LadyBeth_EnemyMatros_9";
		break;
		
		case "LadyBeth_EnemyMatros_7":
			dialog.text = "Você vai nos aceitar na sua tripulação? Depois de tudo isso?";
			link.l1 = "Bons marinheiros sempre são valiosos. E o Capitão Blackwood sabia escolher seus homens.";
			link.l1.go = "LadyBeth_EnemyMatros_8";
		break;
		
		case "LadyBeth_EnemyMatros_8":
			dialog.text = "Obrigado, Capitão. Não vamos te decepcionar.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 12;
		break;
		
		case "LadyBeth_EnemyMatros_9":
			dialog.text = "Bem... pelo menos era o único jeito dessa aventura terminar. Nos perdoe, Capitão Blackwood. Não conseguimos te proteger.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+12);
		break;
		
		case "LadyBeth_EnemyMatros_10":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_11", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_11":
			dialog.text = "Não vamos entregar o navio sem lutar!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		// Диалог с Элизабет Бишоп
		case "LadyBeth_Elizabeth_1":
			dialog.text = "...";
			link.l1 = "Com licença. Você é a Elizabeth?";
			if (pchar.sex == "man") link.l1.go = "LadyBeth_Elizabeth_2";
			if (pchar.sex == "woman") link.l1.go = "LadyBeth_Elizabeth_Woman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Elizabeth_2":
			dialog.text = "Sim, sou eu. E quem é você?";
			link.l1 = "Capitão "+GetFullName(pchar)+". Eu... conheci Albert Blackwood.";
			link.l1.go = "LadyBeth_Elizabeth_3";
		break;
		
		case "LadyBeth_Elizabeth_3":
			dialog.text = "Meu Albert? Meu Deus... Ele está... ele está bem?";
			link.l1 = "Infelizmente, não. Ele morreu em batalha. Lutou até o fim.";
			link.l1.go = "LadyBeth_Elizabeth_4";
		break;
		
		case "LadyBeth_Elizabeth_4":
			dialog.text = "Eu... eu já suspeitava. Tantos anos sem uma única notícia... Sabe, eu esperei por ele. Esperei por muito tempo. Meu pai dizia que Albert só precisava esperar por uma promoção. O governador já tinha decidido tudo, era questão de alguns meses. Mas o Albert... ele entendeu aquela conversa de outro jeito. Disse que voltaria rico, digno da minha mão. E foi embora. Simplesmente... foi.";
			link.l1 = "Ele pensou em você até o último dia dele.";
			link.l1.go = "LadyBeth_Elizabeth_5";
		break;
		
		case "LadyBeth_Elizabeth_5":
			dialog.text = "Que tolice. Eu nunca precisei dos tesouros dele. Eu amava ele, não o dinheiro. Estava pronta para fugir com ele... mas ele era tão orgulhoso. Esperei por uma carta, qualquer notícia... E então só chegou esse manual estranho. Um documento tão frio, calculista... nada parecido com o Albert que eu conhecia. Foi aí que percebi que o tinha perdido.";
			link.l1 = "Entre as coisas dele, encontrei isto.";
			link.l1.go = "LadyBeth_Elizabeth_6";
		break;
		
		case "LadyBeth_Elizabeth_6":
			dialog.text = "Um mapa da minha casa? Eu era o maior tesouro dele? Que ironia. Ele procurou riquezas por todo o Caribe, e a única coisa que realmente importava pra ele sempre esteve aqui... Espere. Tenho algo pra você. Este é o manual do Albert. Ele me enviou isso há um ano. Disse que o ajudaria a encontrar tesouros e voltar pra mim. Agora vai ser mais útil pra você.";
			link.l1 = "Obrigada, Elizabeth. Sinto muito que tudo tenha acabado assim.";
			link.l1.go = "LadyBeth_Elizabeth_7";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_7":
			dialog.text = "E eu me casei, Capitão. Com o Sr. Bishop. Meu pai insistiu. Você não conhece esse homem... e nem iria querer. Todo dia eu penso em como minha vida teria sido se Albert apenas... tivesse voltado.";
			link.l1 = "Agora vou pensar nisso também.";
			link.l1.go = "LadyBeth_Elizabeth_8";
		break;
		
		case "LadyBeth_Elizabeth_8":
			dialog.text = "Adeus, Capitão. E... cuide-se. Não vá atrás de fantasmas.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
		
		case "LadyBeth_Elizabeth_Woman_2":
			dialog.text = "Sim, sou eu.";
			link.l1 = " Capitã Helen MacArthur. Eu... conheci Albert Blackwood.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_3";
		break;
		
		case "LadyBeth_Elizabeth_Woman_3":
			dialog.text = "Meu Albert? Meu Deus... Ele... E quem é você?";
			link.l1 = "Capitã Helen MacArthur, foi o que eu disse. Eu comando meu próprio navio.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_4";
		break;
		
		case "LadyBeth_Elizabeth_Woman_4":
			dialog.text = "Capitã? Uma mulher capitã? Você... Você conhecia o Albert? Em que sentido... conhecia ele?";
			link.l1 = "Só como capitão. Sinto muito, mas o Albert está morto. Eu testemunhei sua última batalha.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_5";
		break;
		
		case "LadyBeth_Elizabeth_Woman_5":
			dialog.text = "Eu entendo. Me perdoe pela desconfiança. É que... o Capitão Blackwood sempre chamou a atenção das mulheres. Até aqui, em Barbados. Principalmente aqui.";
			link.l1 = "Você amava ele.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_6";
		break;
		
		case "LadyBeth_Elizabeth_Woman_6":
			dialog.text = "De todo o meu coração. Papai dizia que Albert só precisava esperar por uma promoção. Era questão de alguns meses. Mas ele entendeu as palavras do papai como uma recusa por causa da pobreza. Disse que voltaria com tesouros. E foi embora.";
			link.l1 = "Homens e seu orgulho!";
			link.l1.go = "LadyBeth_Elizabeth_Woman_7";
		break;
		
		case "LadyBeth_Elizabeth_Woman_7":
			dialog.text = "Você tem sorte, Capitão MacArthur. É livre. Navega para onde quiser. Sem donos de fazenda, sem pais decidindo seu destino. Sem maridos achando que você é propriedade deles.";
			link.l1 = "A liberdade tem um preço alto. E você precisa defendê-la todos os dias.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_8";
		break;
		
		case "LadyBeth_Elizabeth_Woman_8":
			dialog.text = "Talvez eu tenha algo que possa te ajudar com isso. Aqui, pegue. Este é o manual de caça ao tesouro dele. O Albert me enviou isso faz mais ou menos um ano. Disse que era a melhor coisa que já tinha criado. Que isso ia ajudá-lo a ficar rico e voltar pra mim. Mas a cada página, ele se parecia menos com o Albert que eu conhecia.";
			link.l1 = "Obrigado. Vou ficar com isso.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_9";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_Woman_9":
			dialog.text = "Por favor, Capitão... valorize sua liberdade. Casei-me com o Coronel Bishop. Um homem que até meu pai teme. Se eu fosse livre, como você... Tudo seria diferente.";
			link.l1 = "Eu sei.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_10";
		break;
		
		case "LadyBeth_Elizabeth_Woman_10":
			dialog.text = "Despeça-se, Capitão. E que os ventos soprem a seu favor.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
	}
} 